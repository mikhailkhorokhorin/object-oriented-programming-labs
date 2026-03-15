#include "task_queue.hpp"

#include <gtest/gtest.h>

TEST(TaskQueueTest, PushPopWorks) {
    TaskQueue queue;
    bool executed = false;

    queue.push([&executed] { executed = true; });

    auto task = queue.pop();
    task();

    EXPECT_TRUE(executed);
}

TEST(TaskQueueTest, TryPopReturnsEmptyIfNoTasks) {
    TaskQueue queue;

    auto taskOpt = queue.tryPop();
    EXPECT_FALSE(taskOpt.has_value());
}

TEST(TaskQueueTest, TryPopReturnsTaskIfExists) {
    TaskQueue queue;
    bool executed = false;

    queue.push([&executed] { executed = true; });

    auto taskOpt = queue.tryPop();
    ASSERT_TRUE(taskOpt.has_value());

    (*taskOpt)();
    EXPECT_TRUE(executed);
}

TEST(TaskQueueTest, ExecuteAllRunsAllTasks) {
    TaskQueue queue;
    int counter = 0;

    queue.push([&counter] { counter += 1; });
    queue.push([&counter] { counter += 2; });
    queue.push([&counter] { counter += 3; });

    queue.executeAll();

    EXPECT_EQ(counter, 6);

    auto taskOpt = queue.tryPop();
    EXPECT_FALSE(taskOpt.has_value());
}
