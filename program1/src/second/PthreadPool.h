
#ifndef __MYSP_PTHREADPOOL_H__
#define __MYSP_PTHREADPOOL_H__

#include "TaskQueue.h"
#include <memory>
#include <vector>
using namespace std;

namespace mysp
{

class Pthread;

class PthreadPool{
	public:
		using Task = TaskQueue::Task;

		PthreadPool(size_t, size_t);
		~PthreadPool();

		void start();
		void stop();

		void addTask(Task);				//往线程池添加任务
	private:
		Task getTask();					//从缓冲区获取任务
		void threadFunc();				//线程池中每个线程的函数执行体

	private:
		size_t _threadNum;				//线程数
		size_t _taskSize;
		vector<shared_ptr<Pthread>> _threads;	//线程对象的容器
		TaskQueue _que;
		bool _isExit;
};

}

#endif
