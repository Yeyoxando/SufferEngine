#ifndef __TIME_H__ 
#define __TIME_H__

#include <data_types.h>

namespace Suffer {

	// Time in milliseconds.
	double Time();

	// Time in milliseconds without reset.
	double RawTime();

	// Sets the timer to the specified time, in seconds.
	void SetTime(double seconds);

}

#endif // __TIME_H__
