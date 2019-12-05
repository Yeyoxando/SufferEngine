/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Source
*/


#include <thread.h>
#include <px_sched.h>
#include <thread>
#include <chrono>

using namespace Suffer;

px_sched::Scheduler scheduler_;
bool one = false;

struct Thread::ThreadData {

	// PpluX Scheduler Stuff
	px_sched::Sync thread_;

};

Thread::Thread(){

	data_ = new ThreadData();
  if (!one) {
    scheduler_.init();
    one = true;
  }

	im_done_ = false;

}

Thread::~Thread(){

	if (data_ == nullptr) return;
	delete data_;
	data_ = nullptr;

}

void Thread::NewTask(Task t){

	scheduler_.run(t, &data_->thread_);

}

void Thread::WaitFor(Thread* thread){

	scheduler_.waitFor(thread->data_->thread_);

}

void Thread::WaitMe(){
    while (!im_done_) {
        printf("Waiting\n");
    };
}

void Thread::Sleep() {

	im_done_ = true;
	UniqueLock lock_(mutex_);
	current_state_condition_.wait_until(lock_, 0);

}

void Thread::Awake(){

	im_done_ = false;
	current_state_condition_.notify_one();

}

bool Thread::Finished(){
	return im_done_;
}

