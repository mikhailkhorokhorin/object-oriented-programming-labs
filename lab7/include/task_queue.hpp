#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>

class TaskQueue {
   public:
    TaskQueue() = default;
    ~TaskQueue() = default;

    void push(std::function<void()> task);

    std::function<void()> pop();

    std::optional<std::function<void()>> tryPop();

    void executeAll();

   private:
    std::queue<std::function<void()>> tasks;
    std::mutex mutex;
    std::condition_variable cv;
};
