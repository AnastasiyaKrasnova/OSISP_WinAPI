#include "ThreadPool.h"
#include<Windows.h>
#include <iostream>
#include <exception>

struct MyException : public std::exception {
	const char* what() const throw () {
		return "Custom Task Exception";
	}
};

int ThreadFunc1()
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc1\n");
		fflush(stdout);
		Sleep(1000);
	}
	return 0;
}

int ThreadFunc2(const int intValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc2, parameters: %d\n", intValue);
		fflush(stdout);
		Sleep(1000);
	}
	return 0;
}

char ThreadFunc3(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc3, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
char ThreadFunc5(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc5, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
char ThreadFunc6(const int intValue, const std::string stringValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc6, parameters: %d %s\n", intValue, stringValue.c_str());
		fflush(stdout);
		Sleep(1000);
	}
	return 'h';
}
int ThreadFunc4(const int intValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc4, parameters: %d\n", intValue);
		fflush(stdout);
		Sleep(1000);
		if (i == 2)
			throw MyException();
	}
	return 0;
}

int main()
{
	printf("Hardware concurrency: %u\n", std::thread::hardware_concurrency());

	ThreadPool *pool=new ThreadPool(5);

	auto res1 = pool->addTask(&ThreadFunc1);
	auto res2 = pool->addTask(&ThreadFunc2, 42);
	auto res3 = pool->addTask(&ThreadFunc3, 22, std::string("Hello thread3"));
	auto res4 = pool->addTask(&ThreadFunc4, 22);
	auto res5 = pool->addTask(&ThreadFunc5, 22, std::string("Hello thread5"));
	auto res6 = pool->addTask(&ThreadFunc6, 22, std::string("Hello thread6"));
	try {
		printf("ThreadFunc1 result = %d\n", res1.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->log.logTaskException(1);
	}
	catch (std::exception& e) {
		std::cout << "Task 1 was declined" << std::endl;
	}
	
	try {
		printf("ThreadFunc2 result = %d\n", res2.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->log.logTaskException(2);
	}
	catch (std::exception& e) {
		std::cout << "Task 2 was declined" << std::endl;
	}

	try {
		printf("ThreadFunc3 result = %d\n", res3.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->log.logTaskException(3);
	}
	catch (std::exception& e) {
		std::cout << "Task 3 was declined" << std::endl;
	}

	try {
		printf("ThreadFunc6 result = %d\n", res6.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->log.logTaskException(6);
	}
	catch (std::exception& e) {
		std::cout << "Task 6 was declined" << std::endl;
	}

	try
	{
		printf("ThreadFunc4 result = %d\n", res4.get());
	}
	catch (MyException& e) {
		std::cout << e.what() << std::endl;
		pool->log.logTaskException(4);
	}
	catch (std::exception& e) {
		std::cout << "Task 4 was declined" << std::endl;
	}

	getchar();
	return 0;
}