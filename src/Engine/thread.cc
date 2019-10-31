/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Source
*/


#include <thread.h>
#include <px_sched.h>

struct Thread::ThreadData {

	// PpluX Stuff
	px_sched::Scheduler scheduler_;
	px_sched::Sync thread_;

};

Thread::Thread(){

	data_ = new ThreadData();

	Init();

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

//void Thread::NewTask(void(*function)()){
//
//	// Making LAMBDA
//	auto function_thread = [&] { function;  };
//	data_->scheduler_.run(function_thread);
//
//}

void Thread::WaitFor(Thread* thread){

	data_->scheduler_.waitFor(thread->data_->thread_);

}

