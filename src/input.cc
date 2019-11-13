/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Input Source
 */

#include <input.h>
#include <glfw3.h>
#include <assert.h>
#include "suffermanager.h"


// --------------------------------------------------- //

struct Suffer::InputManager::Data {

    u32 key_;
    u32 action_;

    bool init = false;


    u32 GetGLFWKey(Suffer::InputManager::Key key);
    //static Suffer::InputManager::Key GetKey(u32 glfw_key);
    void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

};

// --------------------------------------------------- //

Suffer::InputManager::Key GetKey(u32 glfw_key) {

    switch (glfw_key) {

    case GLFW_KEY_A: return  Suffer::InputManager::k_A;
        break;
    case GLFW_KEY_B: return  Suffer::InputManager::k_B;
        break;
    case GLFW_KEY_C: return  Suffer::InputManager::k_C;
        break;
    case GLFW_KEY_D: return  Suffer::InputManager::k_D;
        break;
    case GLFW_KEY_E: return  Suffer::InputManager::k_E;
        break;
    case GLFW_KEY_F: return  Suffer::InputManager::k_F;
        break;
    case GLFW_KEY_G: return  Suffer::InputManager::k_G;
        break;
    case GLFW_KEY_H: return  Suffer::InputManager::k_H;
        break;
    case GLFW_KEY_I: return  Suffer::InputManager::k_I;
        break;
    case GLFW_KEY_J: return  Suffer::InputManager::k_J;
        break;
    case GLFW_KEY_K: return  Suffer::InputManager::k_K;
        break;
    case GLFW_KEY_L: return  Suffer::InputManager::k_L;
        break;
    case GLFW_KEY_M: return  Suffer::InputManager::k_M;
        break;
    case GLFW_KEY_N: return  Suffer::InputManager::k_N;
        break;
    case GLFW_KEY_O: return  Suffer::InputManager::k_O;
        break;
    case GLFW_KEY_P: return  Suffer::InputManager::k_P;
        break;
    case GLFW_KEY_Q: return  Suffer::InputManager::k_Q;
        break;
    case GLFW_KEY_R: return  Suffer::InputManager::k_R;
        break;
    case GLFW_KEY_S: return  Suffer::InputManager::k_S;
        break;
    case GLFW_KEY_T: return  Suffer::InputManager::k_T;
        break;
    case GLFW_KEY_U: return  Suffer::InputManager::k_U;
        break;
    case GLFW_KEY_V: return  Suffer::InputManager::k_V;
        break;
    case GLFW_KEY_W: return  Suffer::InputManager::k_W;
        break;
    case GLFW_KEY_X: return  Suffer::InputManager::k_X;
        break;
    case GLFW_KEY_Y: return  Suffer::InputManager::k_Y;
        break;
    case GLFW_KEY_Z: return  Suffer::InputManager::k_Z;
        break;
    case GLFW_KEY_SPACE: return  Suffer::InputManager::k_Space;
        break;
    case GLFW_KEY_ENTER: return  Suffer::InputManager::k_Enter;
        break;
    case GLFW_KEY_TAB: return  Suffer::InputManager::k_Tab;
        break;
    case GLFW_KEY_ESCAPE: return  Suffer::InputManager::k_Escape;
        break;
    case GLFW_KEY_DELETE: return  Suffer::InputManager::k_Delete;
        break;
    case GLFW_KEY_BACKSPACE: return  Suffer::InputManager::k_Backspace;
        break;
    case GLFW_KEY_UP: return  Suffer::InputManager::k_Up;
        break;
    case GLFW_KEY_DOWN: return  Suffer::InputManager::k_Down;
        break;
    case GLFW_KEY_RIGHT: return  Suffer::InputManager::k_Right;
        break;
    case GLFW_KEY_LEFT: return  Suffer::InputManager::k_Left;
        break;
    case GLFW_KEY_LEFT_CONTROL: return  Suffer::InputManager::k_Control;
        break;
    case GLFW_KEY_LEFT_ALT: return  Suffer::InputManager::k_Alt;
        break;
    case GLFW_KEY_LEFT_SHIFT: return  Suffer::InputManager::k_Shift;
        break;
    case GLFW_KEY_KP_0: return  Suffer::InputManager::k_Keypad_0;
        break;
    case GLFW_KEY_KP_1: return  Suffer::InputManager::k_Keypad_1;
        break;
    case GLFW_KEY_KP_2: return  Suffer::InputManager::k_Keypad_2;
        break;
    case GLFW_KEY_KP_3: return  Suffer::InputManager::k_Keypad_3;
        break;
    case GLFW_KEY_KP_4: return  Suffer::InputManager::k_Keypad_4;
        break;
    case GLFW_KEY_KP_5: return  Suffer::InputManager::k_Keypad_5;
        break;
    case GLFW_KEY_KP_6: return  Suffer::InputManager::k_Keypad_6;
        break;
    case GLFW_KEY_KP_7: return  Suffer::InputManager::k_Keypad_7;
        break;
    case GLFW_KEY_KP_8: return  Suffer::InputManager::k_Keypad_8;
        break;
    case GLFW_KEY_KP_9: return  Suffer::InputManager::k_Keypad_9;
        break;
    case GLFW_KEY_F1: return  Suffer::InputManager::k_F1;
        break;
    case GLFW_KEY_F2: return  Suffer::InputManager::k_F2;
        break;
    case GLFW_KEY_F3: return  Suffer::InputManager::k_F3;
        break;
    case GLFW_KEY_F4: return  Suffer::InputManager::k_F4;
        break;
    case GLFW_KEY_F5: return  Suffer::InputManager::k_F5;
        break;
    case GLFW_KEY_F6: return  Suffer::InputManager::k_F6;
        break;
    case GLFW_KEY_F7: return  Suffer::InputManager::k_F7;
        break;
    case GLFW_KEY_F8: return  Suffer::InputManager::k_F8;
        break;
    case GLFW_KEY_F9: return  Suffer::InputManager::k_F9;
        break;
    case GLFW_KEY_F10: return  Suffer::InputManager::k_F10;
        break;
    case GLFW_KEY_F11: return  Suffer::InputManager::k_F11;
        break;
    case GLFW_KEY_F12: return  Suffer::InputManager::k_F12;
        break;
    default:
        break;
    }

}

// --------------------------------------------------- //

u32 Suffer::InputManager::Data::GetGLFWKey(Suffer::InputManager::Key key) {

	switch (key){

		case Suffer::InputManager::k_A: return GLFW_KEY_A;
			break;
		case Suffer::InputManager::k_B: return GLFW_KEY_B;
			break;
		case Suffer::InputManager::k_C: return GLFW_KEY_C;
			break;
		case Suffer::InputManager::k_D: return GLFW_KEY_D;
			break;
		case Suffer::InputManager::k_E: return GLFW_KEY_E;
			break;
		case Suffer::InputManager::k_F: return GLFW_KEY_F;
			break;
		case Suffer::InputManager::k_G: return GLFW_KEY_G;
			break;
		case Suffer::InputManager::k_H: return GLFW_KEY_H;
			break;
		case Suffer::InputManager::k_I: return GLFW_KEY_I;
			break;
		case Suffer::InputManager::k_J: return GLFW_KEY_J;
			break;
		case Suffer::InputManager::k_K: return GLFW_KEY_K;
			break;
		case Suffer::InputManager::k_L: return GLFW_KEY_L;
			break;
		case Suffer::InputManager::k_M: return GLFW_KEY_M;
			break;
		case Suffer::InputManager::k_N: return GLFW_KEY_N;
			break;
		case Suffer::InputManager::k_O: return GLFW_KEY_O;
			break;
		case Suffer::InputManager::k_P: return GLFW_KEY_P;
			break;
		case Suffer::InputManager::k_Q: return GLFW_KEY_Q;
			break;
		case Suffer::InputManager::k_R: return GLFW_KEY_R;
			break;
		case Suffer::InputManager::k_S: return GLFW_KEY_S;
			break;
		case Suffer::InputManager::k_T: return GLFW_KEY_T;
			break;
		case Suffer::InputManager::k_U: return GLFW_KEY_U;
			break;
		case Suffer::InputManager::k_V: return GLFW_KEY_V;
			break;
		case Suffer::InputManager::k_W: return GLFW_KEY_W;
			break;
		case Suffer::InputManager::k_X: return GLFW_KEY_X;
			break;
		case Suffer::InputManager::k_Y: return GLFW_KEY_Y;
			break;
		case Suffer::InputManager::k_Z: return GLFW_KEY_Z;
			break;
		case Suffer::InputManager::k_Space: return GLFW_KEY_SPACE;
			break;
		case Suffer::InputManager::k_Enter: return GLFW_KEY_ENTER;
			break;
		case Suffer::InputManager::k_Tab: return GLFW_KEY_TAB;
			break;
		case Suffer::InputManager::k_Escape: return GLFW_KEY_ESCAPE;
			break;
		case Suffer::InputManager::k_Delete: return GLFW_KEY_DELETE;
			break;
		case Suffer::InputManager::k_Backspace: return GLFW_KEY_BACKSPACE;
			break;
		case Suffer::InputManager::k_Up: return GLFW_KEY_UP;
			break;
		case Suffer::InputManager::k_Down: return GLFW_KEY_DOWN;
			break;
		case Suffer::InputManager::k_Right: return GLFW_KEY_RIGHT;
			break;
		case Suffer::InputManager::k_Left: return GLFW_KEY_LEFT;
			break;
		case Suffer::InputManager::k_Control: return GLFW_KEY_LEFT_CONTROL;
			break;
		case Suffer::InputManager::k_Alt: return GLFW_KEY_LEFT_ALT;
			break;
		case Suffer::InputManager::k_Shift: return GLFW_KEY_LEFT_SHIFT;
			break;
		case Suffer::InputManager::k_Keypad_0: return GLFW_KEY_KP_0;
			break;
		case Suffer::InputManager::k_Keypad_1: return GLFW_KEY_KP_1;
			break;
		case Suffer::InputManager::k_Keypad_2: return GLFW_KEY_KP_2;
			break;
		case Suffer::InputManager::k_Keypad_3: return GLFW_KEY_KP_3;
			break;
		case Suffer::InputManager::k_Keypad_4: return GLFW_KEY_KP_4;
			break;
		case Suffer::InputManager::k_Keypad_5: return GLFW_KEY_KP_5;
			break;
		case Suffer::InputManager::k_Keypad_6: return GLFW_KEY_KP_6;
			break;
		case Suffer::InputManager::k_Keypad_7: return GLFW_KEY_KP_7;
			break;
		case Suffer::InputManager::k_Keypad_8: return GLFW_KEY_KP_8;
			break;
		case Suffer::InputManager::k_Keypad_9: return GLFW_KEY_KP_9;
			break;
		case Suffer::InputManager::k_F1: return GLFW_KEY_F1;
			break;
		case Suffer::InputManager::k_F2: return GLFW_KEY_F2;
			break;
		case Suffer::InputManager::k_F3: return GLFW_KEY_F3;
			break;
		case Suffer::InputManager::k_F4: return GLFW_KEY_F4;
			break;
		case Suffer::InputManager::k_F5: return GLFW_KEY_F5;
			break;
		case Suffer::InputManager::k_F6: return GLFW_KEY_F6;
			break;
		case Suffer::InputManager::k_F7: return GLFW_KEY_F7;
			break;
		case Suffer::InputManager::k_F8: return GLFW_KEY_F8;
			break;
		case Suffer::InputManager::k_F9: return GLFW_KEY_F9;
			break;
		case Suffer::InputManager::k_F10: return GLFW_KEY_F10;
			break;
		case Suffer::InputManager::k_F11: return GLFW_KEY_F11;
			break;
		case Suffer::InputManager::k_F12: return GLFW_KEY_F12;
			break;
		default: return -1;
			break;
	}

	return -1;

}

// --------------------------------------------------- //

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    Suffer::InputManager::Key key_event = GetKey(key);
    auto state = &suffer.input_manager_.input_events_[(u32)key_event].state_;

    if (action == GLFW_RELEASE) {
        state->released_ = true;
        state->recently_released_ = true;
    }

    if (action == GLFW_PRESS) {
        state->pressed_ = true;
        state->recently_pressed_ = true;
    }

}

// --------------------------------------------------- //

Suffer::InputManager::InputManager(){

}

// --------------------------------------------------- //

Suffer::InputManager::~InputManager(){
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
}

// --------------------------------------------------- //

void Suffer::InputManager::Data::Callback(GLFWwindow* window, int key, int scancode, int action, int mods){

    Suffer::InputManager::Key key_event = GetKey(key);

}

// --------------------------------------------------- //

void Suffer::InputManager::StartUp(){

    data_ = new Data();
    input_events_.alloc(INPUT_BUFFER);

    glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallback);

}

// --------------------------------------------------- //

void Suffer::InputManager::ShutDown(){

    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyDown(Key key){

    auto state = &suffer.input_manager_.input_events_[(u32)key].state_;
    if (state->pressed_) {
        state->pressed_ = false;
        return true;
    }

	return false;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyUp(Key key){
	
    auto state = &suffer.input_manager_.input_events_[(u32)key].state_;
    if (state->released_) {
        state->released_ = false;
        return true;
    }

    return false;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyPressed(Key key){

    
  static bool is_key_down = false;
  static int key_pressed = 0;

  if (is_key_down) {
    if (data_->GetGLFWKey(key) != data_->key_) return false;
  }

  if (data_->key_ == data_->GetGLFWKey(key) && data_->action_ == GLFW_PRESS) {
    is_key_down = true;
    key_pressed = data_->key_;
  }


  if (is_key_down) {
      if (IsKeyUp(key)) {
          is_key_down = false;
          return false;
      }
      return true;
  }
    

	//static bool is_key_down = false;

	//if (IsKeyDown(key) || is_key_down) {
	//	is_key_down = true;
	//	if (IsKeyUp(key)) {
	//		is_key_down = false;
	//		return false;
	//	}
	//	return true;
	//}

}

// --------------------------------------------------- //

bool Suffer::InputManager::MouseButtonDown(int id){

	int state = -1;

	// 0 = left  1 = right
	switch (id) {
		case 0: {
			state = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS) {
				state = -1;
				return true;
			}
			break;
		}
		case 1:
			state = glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_RIGHT);
			if (state == GLFW_PRESS) {
				state = -1;
				return true;
			}
			break;
		default:
			break;
	}

	return false;

}

// --------------------------------------------------- //

double Suffer::InputManager::MousePositionX(){

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return x;

}

// --------------------------------------------------- //

double Suffer::InputManager::MousePositionY(){

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return y;

}

// --------------------------------------------------- //

mathmorra::Vector2 Suffer::InputManager::MousePosition(){

    mathmorra::Vector2 result = mathmorra::Vector2(0.0f, 0.0f);

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

	result.x_ = x;
	result.y_ = y;

	return result;

}

// --------------------------------------------------- //

void Suffer::InputManager::MousePosition(mathmorra::Vector2& out){

    mathmorra::Vector2 result = mathmorra::Vector2(0.0f, 0.0f);

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

  out.x_ = x;
  out.y_ = y;

}

// --------------------------------------------------- //
