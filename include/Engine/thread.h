/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Header
*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <referenced.h>
#include <functional>

using namespace Suffer;

typedef std::function<void()> Task;

class Thread : public Referenced {

public:
	Thread();

	void NewTask(Task t);
	//void NewTask(void(*function)());
	void WaitFor(Thread* thread);

protected:
	Thread(const Thread&) = delete;
	virtual ~Thread();

private:
	void Init();

	struct ThreadData;
	ThreadData* data_ = nullptr;

};

#endif // __THREAD_H__

