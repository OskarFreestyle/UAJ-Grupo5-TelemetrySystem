#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

template <typename T>
class Queue
{
public:

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty())
        {
            cond_.wait(mlock);
        }
        auto item = queue_.front();
        queue_.pop();
        return item;
    }

    void pop(T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty())
        {
            cond_.wait(mlock);
        }
        item = queue_.front();
        queue_.pop();
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }

    void push(T&& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_.notify_one();
    }

    bool empty() {
        std::unique_lock<std::mutex> mlock(mutex_);
        bool empty = queue_.size() == 0;
        mlock.unlock();
        cond_.notify_one();
        return empty;
    }

    int size() {
        std::unique_lock<std::mutex> mlock(mutex_);
        int aux = queue_.size();
        mlock.unlock();
        cond_.notify_one();
        return aux;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

#endif