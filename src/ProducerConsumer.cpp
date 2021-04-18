#include "ProducerConsumer.h"

#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>


using std::cout; 
using std::endl;

using std::queue;
using std::mutex;
using std::thread;
using std::unique_lock;
using std::condition_variable;


const int maxQueueSize = 100;
queue<int> products;
mutex mtx;
condition_variable cond;


void consume()
{
	int count = 0;
	while (count <= maxQueueSize)
	{
		unique_lock<mutex> lock(mtx);
		if (products.empty())    //queue is empty
		{
			cond.wait(lock);
		}
		else {
			cout << "value: " << products.front() << endl;
			products.pop();
			cond.notify_one();
			count++;
		}
	}
}

void produce()
{
	int i = 0;
	while (i <= maxQueueSize)
	{
		unique_lock<mutex> lock(mtx);
		if (products.size() >= maxQueueSize)
		{
			cond.wait(lock);    //queue is full
		}
		else {
			products.push(i++);
			cond.notify_one();
		}
	}

	cond.notify_one();
}

void startProduceConsume()
{

	thread t1(consume);
	thread t2(produce);

	t1.join();
	t2.join();
}