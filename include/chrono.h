#ifndef __CHRONO_H__
#define __CHRONO_H__

class Chrono {

public:

	Chrono();
	~Chrono();

	double Now();
	double Difference(const double end, const double start);

	// Converters
	double ToSeconds(const double value);
	double ToNanoseconds(const double value);
	double ToMilliseconds(const double value);
	double ToMicroseconds(const double value);

};


#endif // __CHRONO_H__