#include "Thread.h"
#include <iostream>

using namespace std;

Thread::Thread()
	: _thread(nullptr),
	_pauseFlag(ATOMIC_VAR_INIT(false)),
	_stopFlag(ATOMIC_VAR_INIT(false)),
	_state(Stoped)
{

}

Thread::~Thread()
{
	stop();
}

Thread::State Thread::state() const
{
	return _state;
}

void Thread::start()
{
	if (_thread == nullptr)
	{
		_thread = new thread(&Thread::run, this);
		_pauseFlag = false;
		_stopFlag = false;
		_state = Running;
	}
}

void Thread::stop()
{
	if (_thread != nullptr)
	{
		_pauseFlag = false;
		_stopFlag = true;
		_condition.notify_all();  // Notify one waiting thread, if there is one.
		_thread->join(); // wait for thread finished
		delete _thread;
		_thread = nullptr;
		_state = Stoped;
	}
}

void Thread::pause()
{
	if (_thread != nullptr)
	{
		_pauseFlag = true;
		_state = Paused;
	}
}

void Thread::resume()
{
	if (_thread != nullptr)
	{
		_pauseFlag = false;
		_condition.notify_all();
		_state = Running;
	}
}

void Thread::run()
{
	

	while (!_stopFlag)
	{
		process();
		if (_pauseFlag)
		{
			unique_lock<mutex> locker(_mutex);
			while (_pauseFlag)
			{
				_condition.wait(locker); // Unlock _mutex and wait to be notified
			}
			locker.unlock();
		}
	}
	_pauseFlag = false;
	_stopFlag = false;
}

void Thread::msleep(int s)
{
	std::this_thread::sleep_for(std::chrono::microseconds(s));
}