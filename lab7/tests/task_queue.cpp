#include "task_queue.hpp"

#include <gtest/gtest.h>

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

TEST(TaskQueueTest, KeepsFifoOrder) {
    TaskQueue queue;
    std::vector<int> order;
    for (int i = 0; i < 3; ++i) {
        ASSERT_TRUE(queue.push([&order, i] { order.push_back(i); }));
    }
    EXPECT_EQ(queue.size(), 3U);
    while (auto task = queue.tryPop()) {
        (*task)();
    }
    EXPECT_EQ(order, (std::vector<int>{0, 1, 2}));
    EXPECT_FALSE(queue.tryPop().has_value());
}

TEST(TaskQueueTest, IsBounded) {
    TaskQueue queue(2);
    EXPECT_EQ(queue.capacity(), 2U);
    EXPECT_TRUE(queue.tryPush([] {}));
    EXPECT_TRUE(queue.tryPush([] {}));
    EXPECT_FALSE(queue.tryPush([] {}));
    EXPECT_EQ(queue.size(), 2U);
    EXPECT_EQ(TaskQueue(0).capacity(), 1U);
}

TEST(TaskQueueTest, PopBlocksUntilPush) {
    TaskQueue queue;
    std::atomic<int> value = 0;
    std::jthread consumer([&queue, &value] {
        auto task = queue.pop();
        ASSERT_TRUE(task.has_value());
        (*task)();
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_EQ(value.load(), 0);
    queue.push([&value] { value = 42; });
    consumer.join();
    EXPECT_EQ(value.load(), 42);
}

TEST(TaskQueueTest, PopReturnsEmptyOnStop) {
    TaskQueue queue;
    std::atomic<bool> finished = false;
    std::jthread consumer([&queue, &finished](const std::stop_token& stopToken) {
        EXPECT_FALSE(queue.pop(stopToken).has_value());
        finished = true;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_FALSE(finished.load());
    consumer.request_stop();
    consumer.join();
    EXPECT_TRUE(finished.load());
}

TEST(TaskQueueTest, PushBlocksWhileFull) {
    TaskQueue queue(1);
    ASSERT_TRUE(queue.push([] {}));
    std::atomic<bool> pushed = false;
    std::jthread producer([&queue, &pushed] {
        EXPECT_TRUE(queue.push([] {}));
        pushed = true;
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_FALSE(pushed.load());
    EXPECT_TRUE(queue.pop().has_value());
    producer.join();
    EXPECT_TRUE(pushed.load());
    EXPECT_EQ(queue.size(), 1U);
}

TEST(TaskQueueTest, PushGivesUpOnStop) {
    TaskQueue queue(1);
    ASSERT_TRUE(queue.push([] {}));
    std::jthread producer(
        [&queue](const std::stop_token& stopToken) { EXPECT_FALSE(queue.push([] {}, stopToken)); });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    producer.request_stop();
    producer.join();
    EXPECT_EQ(queue.size(), 1U);
}

TEST(TaskQueueTest, CloseWakesWaitersAndRejectsPush) {
    TaskQueue queue;
    std::jthread consumer([&queue] { EXPECT_FALSE(queue.pop().has_value()); });
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    queue.close();
    consumer.join();
    EXPECT_FALSE(queue.push([] {}));
    EXPECT_FALSE(queue.tryPush([] {}));
}

TEST(TaskQueueTest, ManyProducersOneConsumer) {
    constexpr int PRODUCERS = 4;
    constexpr int TASKS_PER_PRODUCER = 250;
    TaskQueue queue(8);
    std::atomic<int> executed = 0;
    std::jthread consumer([&queue, &executed] {
        for (int i = 0; i < PRODUCERS * TASKS_PER_PRODUCER; ++i) {
            auto task = queue.pop();
            ASSERT_TRUE(task.has_value());
            (*task)();
        }
        EXPECT_EQ(executed.load(), PRODUCERS * TASKS_PER_PRODUCER);
    });
    {
        std::vector<std::jthread> producers;
        for (int p = 0; p < PRODUCERS; ++p) {
            producers.emplace_back([&queue, &executed] {
                for (int i = 0; i < TASKS_PER_PRODUCER; ++i) {
                    EXPECT_TRUE(queue.push([&executed] { ++executed; }));
                }
            });
        }
    }
    consumer.join();
    EXPECT_EQ(executed.load(), PRODUCERS * TASKS_PER_PRODUCER);
}
