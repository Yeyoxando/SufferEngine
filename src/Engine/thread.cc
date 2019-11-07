/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Source
*/


#include <thread.h>
#include <px_sched.h>
#include <thread>
#include <chrono>

struct Thread::ThreadData {

	// PpluX Scheduler Stuff
	px_sched::Scheduler scheduler_;
	px_sched::Sync thread_;

};

Thread::Thread(){

	data_ = new ThreadData();

	Init();
	im_done_ = false;

}

Thread::~Thread(){

	if (data_ == nullptr) return;
	delete data_;
	data_ = nullptr;

}

void Thread::Init(){

	data_->scheduler_.init();

}

void Thread::NewTask(Task t){

	data_->scheduler_.run(t, &data_->thread_);

}

void Thread::WaitFor(Thread* thread){

	data_->scheduler_.waitFor(thread->data_->thread_);

}

void Thread::Sleep() {

	UniqueLock lock_(mutex_);

	im_done_ = true;
	current_state_condition_.wait_until(lock_, 0);

}

void Thread::Awake(){

	im_done_ = false;
	current_state_condition_.notify_one();

}

bool Thread::Finished(){
	return im_done_;
}

