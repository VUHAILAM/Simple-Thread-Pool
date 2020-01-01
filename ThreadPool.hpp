#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>

using Task = std::function<void()>;

class ThreadPool
{
private:
    /* data */
    int m_numThread;
    bool m_isStopping = false;
    std::vector<std::thread> m_thread;
    std::condition_variable m_event_var;
    std::mutex m_mutex;
    std::queue<Task> m_task;

public:
    ThreadPool(/* args */);
    ThreadPool(int numThread);
    ~ThreadPool();
    int pool_size();
    void start();
    void enqueue(Task task);
};

#endif //THREADPOOL_HPP