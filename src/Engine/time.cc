
#include <time.h>
#include <glfw3.h>

double Suffer::Time(){
	return glfwGetTime();
}

double Suffer::RawTime(){
	return glfwGetTimerValue();
}

void Suffer::SetTime(double seconds){
	glfwSetTime(seconds);
}

