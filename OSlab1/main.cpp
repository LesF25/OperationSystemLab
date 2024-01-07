#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex				mtx;
condition_variable	cv;
bool				trigger = false;


void producer_func()
{
	while (true)
	{
		this_thread::sleep_for(chrono::seconds(1));
		{
			unique_lock<mutex> ul(mtx);
			trigger = true;
			cout << "Событие отправлено\n";
			cv.notify_one();
		}
	}
}

void consumer_func()
{
	while (true)
	{
		unique_lock<mutex> ul(mtx);
		cv.wait(ul, []() {return trigger; });
		trigger = false;
		cout << "Событие обработано\n";
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	thread producer(producer_func);
	thread consumer(consumer_func);

	producer.join();
	consumer.join();

	return 0;
}