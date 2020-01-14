#pragma once

#include <thread>
#include <mutex>
#include <future>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>

class ThreadPool
{
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();

    template <class Func, class... Args>
    auto exec(Func func, Args... args)->std::future<decltype(func(args...))>;

private:
    std::queue<std::function<void()>> tasks;
    std::vector<std::thread> threads;

    std::atomic<bool> is_stoped;
    std::mutex mutex;
    std::condition_variable cond_var;

    class ThreadDesigner
    {
    public:
        ThreadDesigner(ThreadPool& s);
        void operator()();
    private:
        ThreadPool& thread_pool;
    };
};

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args)->std::future<decltype(func(args...))>
{
    auto func_applying = std::bind(func, std::forward<Args>(args)...);

    auto package_task =
        std::make_shared<std::packaged_task<decltype(func(args...))()>>(func_applying);

    std::future<decltype(func(args...))> result = package_task->get_future();

    {
        std::lock_guard<std::mutex> lock(mutex);

        auto task = [package_task]()
        {
            (*package_task)();
        };
        tasks.push(task);
    }

    cond_var.notify_one();
    return result;
}
