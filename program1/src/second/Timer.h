
#ifndef __MYSP_TIMER_H__
#define __MYSP_TIMER_H__

#include <functional>

namespace mysp
{

class Timer{
	public:
		using TimerCallBack = std::function<void()>;//重定义回调函数的标签
		Timer(int, int, TimerCallBack);
		~Timer();
		void start();			//开启定时器
		void stop();			//停止定时器
	private:
		int createTimerfd();
		void setTimerfd(int, int);
		void handleRead();		//处理定时器
	private:
		int _timerfd;			//linux下的线程类型
		int _initialTime;		
		int _intervalTime;
		bool _isStarted;		//记录定时器是否已开启
		TimerCallBack _cb;		//执行任务的函数对象
};

}

#endif
