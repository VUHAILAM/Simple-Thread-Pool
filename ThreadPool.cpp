#include "ThreadPool.hpp"

ThreadPool::ThreadPool()
{
}

ThreadPool::ThreadPool(int numThread)
{
    this->m_numThread = numThread;
}

ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock{m_mutex};
    m_isStopping = true;
    m_event_var.notify_all();
    for (auto &thread : m_thread)
    {
        thread.join();
    }
}

int ThreadPool::pool_size()
{
    return this->m_numThread;
}

void ThreadPool::start()
{
    for (int i = 0; i < m_numThread; i++)
    {
        m_thread.emplace_back([=] {
            while (true)
            {
                /* code */
                Task task;
                std::unique_lock<std::mutex> lock{m_mutex};

                m_event_var.wait(lock, [=] {
                    return m_isStopping || !m_task.empty();
                });

                if (m_isStopping && m_task.empty())
                    break;

                task = std::move(m_task.front());
                m_task.pop();

                task();
            }
        });
    }
}

void ThreadPool::enqueue(Task task)
{
    std::unique_lock<std::mutex> lock{m_mutex};
    m_task.emplace(std::move(task));
    m_event_var.notify_one();
}