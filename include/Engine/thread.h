/*
* Author: Pablo Bano Benito <banyobe@esat-alumni.com>
* Date: 10-31-2019
* Threads Header
*/

#ifndef __THREAD_H__
#define __THREAD_H__

#include <referenced.h>
#include <data_types.h>

namespace Suffer {

    class Thread : public Referenced {

    public:
	    Thread();

      /*
       * @brief: launches a new task on the current thread.
       * @param: the function pointer to execute.
       */
	    void NewTask(Task t);

      /*
       * @brief: wait for a thread to finish.
       * @param: the thread that is being waited
       */ 
	    void WaitFor(Thread* thread);

      void WaitMe();

      /*
       * @brief: sleeps the current thread and stops his execution.
       */
	    void Sleep();

      /*
       * @brief: awakes the current thread and begins his execution.
       */
	    void Awake();


      // DEPRECATED: will be removed
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

}

#endif // __THREAD_H__

