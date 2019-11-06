/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Header
*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <referenced.h>
#include <functional>
#include <condition_variable>
#include <mutex>

using namespace Suffer;

typedef std::function<void()>			Task;
typedef std::condition_variable			Condition;
typedef std::unique_lock<std::mutex>	UniqueLock;
typedef std::mutex						Mutex;

class Thread : public Referenced {

public:
	Thread();

	void NewTask(Task t);
	void WaitFor(Thread* thread);

	void Sleep();
	void Awake();

	bool Finished();


protected:
	Thread(const Thread&) = delete;
	virtual ~Thread();

private:
	void Init();

	struct ThreadData;
	ThreadData* data_ = nullptr;
	Condition current_state_condition_;
	Mutex mutex_;
	bool im_done_;

};

#endif // __THREAD_H__

