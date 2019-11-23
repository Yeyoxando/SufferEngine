/*
 * Author: Diego Ochando Torres <ochandoto@esat-alumni.com>
 * Date: 15-10-2019
 * Clear Command Source
 */

#include <clear.h>
#include <glfw3.h>

// ------------------------------------------------------------------------- //

Suffer::Clear::Clear(){

	cmd_type_ = Command::kRender;

}

// ------------------------------------------------------------------------- //

Suffer::Clear::~Clear(){

}

// ------------------------------------------------------------------------- //

void Suffer::Clear::Execute() const{

	glClearColor(color_.x_, color_.y_, color_.z_, 1.0f);
  
  glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glDepthFunc(GL_LESS);

}

// ------------------------------------------------------------------------- //