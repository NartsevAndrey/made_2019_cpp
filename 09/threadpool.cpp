#include "threadpool.h"

ThreadPool::ThreadPool(size_t poolSize)
    : is_stoped(false)
{
    for (size_t i = 0; i < poolSize; i++)
        threads.push_back(std::thread(ThreadDesigner(*this)));
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(mutex);
        is_stoped.store(true);
    }

    cond_var.notify_all();

    for (std::thread& thread : threads)
        thread.join();
}

ThreadPool::ThreadDesigner::ThreadDesigner(ThreadPool& s)
    : thread_pool(s)
{
}

void ThreadPool::ThreadDesigner::operator()()
{
    while (true)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(thread_pool.mutex);

            thread_pool.cond_var.wait(lock,
                [this]()
                {
                    return thread_pool.is_stoped || !thread_pool.tasks.empty();
                }
            );

            if (thread_pool.is_stoped)
                return;

            task = std::move(thread_pool.tasks.front());
            thread_pool.tasks.pop();
        }
        task();
    }
}
