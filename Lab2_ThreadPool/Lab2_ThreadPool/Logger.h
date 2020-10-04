#pragma once
#include <chrono>
#include <ctime> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Logger
{
public:
	
	void logThreadPoolInit(int count) {
		out.open("ThreadPool_Logs.txt");
		std::ostringstream oss;
		oss << count;
		std::string s = oss.str();
		if (out.is_open())
		{
			out << "ThreadPool with "+ s+ " threads is created" << std::endl;
		}
	}

	void logTaskAdding(int num) {
		std::ostringstream oss;
		oss << num;
		std::string s = oss.str();
		if (out.is_open())
		{
			out << "Task " + s + " successfully added to ThreadPool Task queue" << std::endl;
		}
	}

	void logTaskAddingError() {
		if (out.is_open())
		{
			out << "Error adding task" << std::endl;
		}
	}

	void logStop() {
		out.close();
	}

	void logTaskException(int num) {
		std::ostringstream oss;
		oss << num;
		std::string s = oss.str();
		if (out.is_open())
		{
			out << "Exception on task" + s << std::endl;
		}
	}

private:
	std::ofstream out;


};

