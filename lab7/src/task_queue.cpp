#include "task_queue.hpp"

void TaskQueue::push(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        tasks.push(std::move(task));
    }
    cv.notify_one();
}

std::function<void()> TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [this] { return !tasks.empty(); });
    auto task = std::move(tasks.front());
    tasks.pop();
    return task;
}

std::optional<std::function<void()>> TaskQueue::tryPop() {
    std::lock_guard<std::mutex> lock(mutex);
    if (tasks.empty())
        return std::nullopt;
    auto task = std::move(tasks.front());
    tasks.pop();
    return task;
}

void TaskQueue::executeAll() {
    std::queue<std::function<void()>> tmp;
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::swap(tmp, tasks);
    }

    while (!tmp.empty()) {
        auto task = std::move(tmp.front());
        tmp.pop();
        task();
    }
}
