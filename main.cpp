#include "ThreadPool.hpp"

#include <iostream>

int sum = 0;
int number = 0;

int main()
{
    ThreadPool pool = ThreadPool(5);
    pool.start();
    for (int i = 1; i <= pool.pool_size(); i++)
    {

        pool.enqueue([i] {
            number = rand()%1000;
            std::cout << "Item " << i << " add " << number << " to sum" << std::endl;
            sum += number;
            std::cout << "Item " << i << " finished" << std::endl;
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        });
    }

    std::cout << "Sum = " << sum << std::endl;
    return 0;
}