
#ifndef __MYSP_TASKQUEUE_H__
#define __MYSP_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>
using namespace std;

namespace mysp
{

class TaskQueue{
	using Task = function<void()>;	//任务的回调函数作为接口

	public:
		friend class PthreadPool;

		TaskQueue(size_t);

		bool empty() const;			//判断队列是否为空
		bool full() const;			//判断队列是否已满

		void push(Task);			//往队列中添加任务
		Task pop();					//从任务队列中获取任务

		void setState(bool);
	private:
		size_t _size;				//队列大小
		queue<Task> _que;			//队列
		MutexLock _mutex;			//互斥锁对象
		Condition _notEmpty;		//判断队列是否为空
		Condition _notFull;			//判断队列是否已满
		bool _destroy;				
};

}

#endif
