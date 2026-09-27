#include "task_queue.hpp"

#include <algorithm>
#include <utility>

TaskQueue::TaskQueue(std::size_t capacity) : capacity_(std::max<std::size_t>(1, capacity)) {
}

bool TaskQueue::push(Task task, const std::stop_token& stopToken) {
    std::unique_lock lock(mutex_);
    notFull_.wait(lock, stopToken, [this] { return closed_ || tasks_.size() < capacity_; });
    if (closed_ || tasks_.size() >= capacity_) {
        return false;
    }
    tasks_.push(std::move(task));
    lock.unlock();
    notEmpty_.notify_one();
    return true;
}

bool TaskQueue::tryPush(Task task) {
    std::unique_lock lock(mutex_);
    if (closed_ || tasks_.size() >= capacity_) {
        return false;
    }
    tasks_.push(std::move(task));
    lock.unlock();
    notEmpty_.notify_one();
    return true;
}

std::optional<TaskQueue::Task> TaskQueue::pop(const std::stop_token& stopToken) {
    std::unique_lock lock(mutex_);
    notEmpty_.wait(lock, stopToken, [this] { return closed_ || !tasks_.empty(); });
    return takeLocked();
}

std::optional<TaskQueue::Task> TaskQueue::tryPop() {
    const std::lock_guard lock(mutex_);
    return takeLocked();
}

std::optional<TaskQueue::Task> TaskQueue::takeLocked() {
    if (tasks_.empty()) {
        return std::nullopt;
    }
    Task task = std::move(tasks_.front());
    tasks_.pop();
    notFull_.notify_one();
    return task;
}

void TaskQueue::close() {
    {
        const std::lock_guard lock(mutex_);
        closed_ = true;
    }
    notEmpty_.notify_all();
    notFull_.notify_all();
}

std::size_t TaskQueue::size() const {
    const std::lock_guard lock(mutex_);
    return tasks_.size();
}

std::size_t TaskQueue::capacity() const {
    return capacity_;
}
