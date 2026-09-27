#pragma once

#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <optional>
#include <queue>
#include <stop_token>

class TaskQueue {
public:
    using Task = std::function<void()>;

    static constexpr std::size_t DEFAULT_CAPACITY = 1024;

    explicit TaskQueue(std::size_t capacity = DEFAULT_CAPACITY);

    bool push(Task task, const std::stop_token& stopToken = {});
    bool tryPush(Task task);

    std::optional<Task> pop(const std::stop_token& stopToken = {});
    std::optional<Task> tryPop();

    void close();

    std::size_t size() const;
    std::size_t capacity() const;

private:
    std::queue<Task> tasks_;
    std::size_t capacity_;
    bool closed_ = false;
    mutable std::mutex mutex_;
    std::condition_variable_any notEmpty_;
    std::condition_variable_any notFull_;

    std::optional<Task> takeLocked();
};
