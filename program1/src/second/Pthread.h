
#ifndef __MYSP__PTHREAD_H__
#define __MYSP__PTHREAD_H__

#include "Uncopyable.h"

#include <pthread.h>
#include <string>
#include <functional>

namespace mysp
{

extern __thread const char * pthreadName;

class Pthread
: private Uncopyable
{
	public:
		using PthreadCallBack = std::function<void()>;

		Pthread(PthreadCallBack &&, const std::string & name = std::string());

		~Pthread();

		void start();
		void join();

		bool isRunning() const { return _isRunning; }

	private:
		static void * pthreadFunc(void *);	//线程的函数执行体
	private:
		pthread_t _pthid;			//linux下的线程类型
		std::string _name;			
		bool _isRunning;			//记录线程是否正在运行
		PthreadCallBack _cb;		//执行任务的函数对象
};

}


#endif
