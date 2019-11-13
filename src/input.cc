/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Input Source
 */

#include <input.h>
#include <glfw3.h>
#include <assert.h>

// --------------------------------------------------- //

struct Suffer::InputManager::Data {

    u32 key_;
    u32 action_;

    bool init = false;

    u32 GetGLFWKey(Suffer::InputManager::Key key);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};


// --------------------------------------------------- //

Suffer::InputManager::InputManager(){

    data_ = new Data();
    glfwSetKeyCallback(glfwGetCurrentContext(), data_->KeyCallback);

}

// --------------------------------------------------- //

Suffer::InputManager::~InputManager(){
    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;
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

void Suffer::InputManager::Data::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //key_ = key;
    //action_ = action;
}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyDown(Key key){

	if (data_->key_ == data_->GetGLFWKey(key) && data_->action_ == GLFW_PRESS) {
    data_->key_ = -1;
    return true;
	}

	return false;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyUp(Key key){
	
	if (data_->key_ == data_->GetGLFWKey(key) && data_->action_ == GLFW_RELEASE) {
    data_->key_ = -1;
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
