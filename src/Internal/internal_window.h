// Author: Pablo Banyo Benito <banyobe@esat-alumni.com>

#ifndef __INTERNAL_WINDOW_H__
#define __INTERNAL_WINDOW_H__

#include "window.h"

// ------------------------------------------------------------------------- //

struct Suffer::Window::Data {

  GLFWwindow* window_;
  int height_;
  int width_;

};

// ------------------------------------------------------------------------- //

#endif //__INTERNAL_WINDOW_H__