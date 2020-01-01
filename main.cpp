#include "ThreadPool.hpp"

#include <iostream>

int sum = 0;
int number = 0;

int main()
{
    ThreadPool pool = ThreadPool(5);

    for (int i = 0; i < pool.pool_size(); i++)
    {

        pool.enqueue([] {
            number = rand();
            sum += number;
        });
    }
    return 0;
}