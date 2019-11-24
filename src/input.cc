/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Input Source
 */

#include <input.h>
#include <glfw3.h>
#include <assert.h>
#include "suffermanager.h"
#include "math_utils.h"
#include "common_definitions.h"
#include "internal_suffermanager.h"
#include "internal_input_manager.h"

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

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    auto key_event = GetKey(key);
    auto state = suffer.input_manager_.GetState(key_event);
    if (state == nullptr) return;
    if (action == GLFW_RELEASE) {
        state->released_ = true;
        state->recently_released_ = true;
        state->pressed_ = false;
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

void Suffer::InputManager::Update(){
    
    // This function will be called at the end of the frame.
    for (int i = 0; i < INPUT_BUFFER; ++i) {
        data_->input_events_[i].state_.recently_pressed_ = false;
        data_->input_events_[i].state_.recently_released_ = false;
        data_->input_events_[i].state_.released_ = false;
    }

}

// --------------------------------------------------- //

void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
    // TODO: Fill this
    suffer.input_manager_.mouse_.x_ = xpos;
    suffer.input_manager_.mouse_.y_ = ypos;

}

// --------------------------------------------------- //

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {

    float current_fov = suffer.GetCurrentScene()->GetMainCamera()->Fov();
    current_fov += (yoffset * 0.1f);
    suffer.GetCurrentScene()->GetMainCamera()->SetFOV(current_fov);

}

// --------------------------------------------------- //

void ErrorCallback(int error, const char* description){
    printf("Error: %s\n", description);
}

// --------------------------------------------------- //

void WindowResizeCallback(GLFWwindow* window, int width, int height) {
    // TODO: Fill this
}

// --------------------------------------------------- //

void Suffer::InputManager::StartUp(){

    data_ = new Data();
    data_->input_events_.alloc(INPUT_BUFFER);
    
    // Set callbacks
    glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), MouseCallback);
    glfwSetScrollCallback(glfwGetCurrentContext(), ScrollCallback);
    glfwSetErrorCallback(ErrorCallback);
    glfwSetWindowSizeCallback(glfwGetCurrentContext(), WindowResizeCallback);

}

// --------------------------------------------------- //

void Suffer::InputManager::ShutDown(){

    if (data_ == nullptr) return;
    delete data_;
    data_ = nullptr;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyDown(Key key){

    auto state = GetState(key);
    if (state == nullptr) return false;
    if (state->pressed_) {
        state->pressed_ = false;
        return true;
    }

	return false;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyUp(Key key){
	
    auto state = &suffer.input_manager_.data_->input_events_[(u32)key].state_;
    if (state->released_) {
        state->pressed_ = false;
        state->released_ = false;
        return true;
    }

    return false;

}

// --------------------------------------------------- //

bool Suffer::InputManager::IsKeyPressed(Key key){

    auto state = &suffer.input_manager_.data_->input_events_[(u32)key].state_;
    if (state->pressed_) return true;
    return false;

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

	return mouse_.x_;

}

// --------------------------------------------------- //

double Suffer::InputManager::MousePositionY(){

	return mouse_.y_;

}

// --------------------------------------------------- //

mathmorra::Vector2 Suffer::InputManager::MousePosition(){

	return mouse_;

}

// --------------------------------------------------- //

Suffer::InputManager::State* Suffer::InputManager::GetState(InputManager::Key state){
    if (state > INPUT_BUFFER) return nullptr;
    if (state < 0) return nullptr;
    return &suffer.input_manager_.data_->input_events_[(u32)state].state_;
}

// --------------------------------------------------- //