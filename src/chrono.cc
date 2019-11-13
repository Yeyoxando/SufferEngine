
#include "chrono.h"
#include <sokol_time.h>

// --------------------------------------------------- //

Suffer::Chrono::Chrono(){
	stm_setup();
}

// --------------------------------------------------- //

Suffer::Chrono::~Chrono(){

}

// --------------------------------------------------- //

double Suffer::Chrono::Now(){
	return stm_now();
}

// --------------------------------------------------- //

double Suffer::Chrono::Difference(const double end, const double start){
	return stm_diff(end, start);
}

// --------------------------------------------------- //

double Suffer::Chrono::ToSeconds(const double value){
	return stm_sec(value);
}

// --------------------------------------------------- //

double Suffer::Chrono::ToMilliseconds(const double value){
	return stm_ms(value);
}

// --------------------------------------------------- //

double Suffer::Chrono::ToMicroseconds(const double value){
	return stm_us(value);
}

// --------------------------------------------------- //

double Suffer::Chrono::ToNanoseconds(const double value){
	return stm_ns(value);
}

// --------------------------------------------------- //