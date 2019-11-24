#include "math_utils.h"
#include <stdlib.h>
#include <math.h>

float ThiefUtils::Math::fPI = 3.14159265358979323846264338327950288419716939937510f;
double ThiefUtils::Math::dPI = 3.14159265358979323846264338327950288419716939937510;

int ThiefUtils::Math::RandomRange(int min, int max){
  
  int value = rand() % max + min;
  while (value > max || value < min) {
    value = rand() % max + min;
  }
  return value;

}

float ThiefUtils::Math::Lerp(float x, float y, float s){
  return x + s * (y - x);
}

float ThiefUtils::Math::Clamp(float value, float min, float max){
  return Max(min, Min(max, value));
}

float ThiefUtils::Math::Clamp01(float value) {
  return Max(0.0f, Min(1.0f, value));
}

bool ThiefUtils::Math::Approximately(float one, float two) {
  return false;
}

float ThiefUtils::Math::Max(float x, float y){
  return x > y ? x : y;
}

float ThiefUtils::Math::Min(float x, float y){
  return x < y ? x : y;
}

float ThiefUtils::Math::Radians(float degrees){
  // (degrees * pi) / 180.0f;
  return (degrees * fPI) * 0.0055555555555556f;
}

float ThiefUtils::Math::Degrees(float radians){
  // (radians * 180.0f) / pi;
  return (radians * 180.0f) * 0.31830988618379067153776752674503f;
}

float ThiefUtils::Math::Ceil(float value){
  return ceil(value);
}

float ThiefUtils::Math::Floor(float value){
  return floor(value);
}

float ThiefUtils::Math::Map(float value, float start, float stop, float start2, float stop2){
  return start2 + (stop2 - start2) * ((value - start) / (stop - start));
}

