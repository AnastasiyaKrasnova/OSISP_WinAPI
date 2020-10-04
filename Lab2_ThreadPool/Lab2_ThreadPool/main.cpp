#include <iostream>
#include "ThreadPool.h"
#include<Windows.h>

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

int ThreadFunc4(const int intValue)
{
	for (int i = 0; i < 5; ++i)
	{
		printf("ThreadFunc4, parameters: %d\n", intValue);
		fflush(stdout);
		Sleep(1000);
		if (i == 2)
			throw std::runtime_error("ThreadFunc4 exception");
	}
	return 0;
}

int main()
{

	ThreadPool pool(2);

	auto res1 = pool.addTask(&ThreadFunc1);
	auto res2 = pool.addTask(&ThreadFunc2, 42);
	auto res3 = pool.addTask(&ThreadFunc3, 22, std::string("Hello thread3"));
	auto res4 = pool.addTask(&ThreadFunc4, 22);
	try {
		printf("ThreadFunc1 result = %d\n", res1.get());
	}
	catch (std::exception ex)
	{
		printf("%s\n", ex.what());
		pool.log.logTaskException(1);
	}
	
	try {
		printf("ThreadFunc2 result = %d\n", res2.get());
	}
	catch (std::exception ex)
	{
		printf("%s\n", ex.what());
		pool.log.logTaskException(2);
	}

	try {
		printf("ThreadFunc3 result = %d\n", res3.get());
	}
	catch (std::exception ex)
	{
		printf("%s\n", ex.what());
		pool.log.logTaskException(3);
	}

	try
	{
		printf("ThreadFunc4 result = %d\n", res4.get());
	}
	catch (std::exception ex)
	{
		printf("%s\n", ex.what());
		pool.log.logTaskException(4);
	}

	getchar();
	return 0;
}