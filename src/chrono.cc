
#include "chrono.h"
#include <sokol_time.h>

// --------------------------------------------------- //

Chrono::Chrono(){

}

// --------------------------------------------------- //

Chrono::~Chrono(){

}

// --------------------------------------------------- //

void Chrono::Init(){
	stm_setup();
}

// --------------------------------------------------- //

double Chrono::Now(){
	return stm_now();
}

// --------------------------------------------------- //

double Chrono::Difference(const double end, const double start){
	return stm_diff(end, start);
}

// --------------------------------------------------- //

double Chrono::ToSeconds(const double value){
	return stm_sec(value);
}

// --------------------------------------------------- //

double Chrono::ToMilliseconds(const double value){
	return stm_ms(value);
}

// --------------------------------------------------- //

double Chrono::ToMicroseconds(const double value){
	return stm_us(value);
}

// --------------------------------------------------- //

double Chrono::ToNanoseconds(const double value){
	return stm_ns(value);
}

// --------------------------------------------------- //