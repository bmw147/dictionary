
#include "Timer.h"
#include "Mylogger.h"

#include <unistd.h>
#include <sys/timerfd.h>

namespace mysp
{

Timer::Timer(int initialTime, int intervalTime, TimerCallBack cb)
: _timerfd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _isStarted(false)
, _cb(cb){
}

void Timer::start(){
	_isStarted = true;
	//添加到epoll读
}

void Timer::stop(){
	if (_isStarted){
		_isStarted = false;
		setTimerfd(0, 0);
	}
}

int Timer::createTimerfd(){
	int fd = timerfd_create(CLOCK_REALTIME, 0);
	if (fd == -1){
		LogError("timerfd_create error");
	}
	return fd;
}

void Timer::setTimerfd(int initialTime, int intervalTime){
	struct itimerspec value = {{initialTime, 0},
		{intervalTime, 0}
	};

	if (-1 == timerfd_settime(_timerfd, 0, &value, NULL)){
		LogError("timerfd_settime error");
	}
}

void Timer::handleRead(){
	uint64_t u;

	if (sizeof(u) != read(_timerfd, &u, sizeof(u))){
		LogError("read error");
	}
}

}
