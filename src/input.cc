/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Input Source
 */

#include <input.h>
#include <glfw3.h>

int inpKey;
int inpAction;
bool init = false;

/*
	There are some functions that are not declared in Header file (.h).
	This is because we won't show to the user that we use GLFW.
*/

// --------------------------------------------------- //

int GetGLFWKey(Suffer::Key key) {

	switch (key){

		case Suffer::k_A: return GLFW_KEY_A;
			break;
		case Suffer::k_B: return GLFW_KEY_B;
			break;
		case Suffer::k_C: return GLFW_KEY_C;
			break;
		case Suffer::k_D: return GLFW_KEY_D;
			break;
		case Suffer::k_E: return GLFW_KEY_E;
			break;
		case Suffer::k_F: return GLFW_KEY_F;
			break;
		case Suffer::k_G: return GLFW_KEY_G;
			break;
		case Suffer::k_H: return GLFW_KEY_H;
			break;
		case Suffer::k_I: return GLFW_KEY_I;
			break;
		case Suffer::k_J: return GLFW_KEY_J;
			break;
		case Suffer::k_K: return GLFW_KEY_K;
			break;
		case Suffer::k_L: return GLFW_KEY_L;
			break;
		case Suffer::k_M: return GLFW_KEY_M;
			break;
		case Suffer::k_N: return GLFW_KEY_N;
			break;
		case Suffer::k_O: return GLFW_KEY_O;
			break;
		case Suffer::k_P: return GLFW_KEY_P;
			break;
		case Suffer::k_Q: return GLFW_KEY_Q;
			break;
		case Suffer::k_R: return GLFW_KEY_R;
			break;
		case Suffer::k_S: return GLFW_KEY_S;
			break;
		case Suffer::k_T: return GLFW_KEY_T;
			break;
		case Suffer::k_U: return GLFW_KEY_U;
			break;
		case Suffer::k_V: return GLFW_KEY_V;
			break;
		case Suffer::k_W: return GLFW_KEY_W;
			break;
		case Suffer::k_X: return GLFW_KEY_X;
			break;
		case Suffer::k_Y: return GLFW_KEY_Y;
			break;
		case Suffer::k_Z: return GLFW_KEY_Z;
			break;
		case Suffer::k_Space: return GLFW_KEY_SPACE;
			break;
		case Suffer::k_Enter: return GLFW_KEY_ENTER;
			break;
		case Suffer::k_Tab: return GLFW_KEY_TAB;
			break;
		case Suffer::k_Escape: return GLFW_KEY_ESCAPE;
			break;
		case Suffer::k_Delete: return GLFW_KEY_DELETE;
			break;
		case Suffer::k_Backspace: return GLFW_KEY_BACKSPACE;
			break;
		case Suffer::k_Up: return GLFW_KEY_UP;
			break;
		case Suffer::k_Down: return GLFW_KEY_DOWN;
			break;
		case Suffer::k_Right: return GLFW_KEY_RIGHT;
			break;
		case Suffer::k_Left: return GLFW_KEY_LEFT;
			break;
		case Suffer::k_Control: return GLFW_KEY_LEFT_CONTROL;
			break;
		case Suffer::k_Alt: return GLFW_KEY_LEFT_ALT;
			break;
		case Suffer::k_Shift: return GLFW_KEY_LEFT_SHIFT;
			break;
		case Suffer::k_Keypad_0: return GLFW_KEY_KP_0;
			break;
		case Suffer::k_Keypad_1: return GLFW_KEY_KP_1;
			break;
		case Suffer::k_Keypad_2: return GLFW_KEY_KP_2;
			break;
		case Suffer::k_Keypad_3: return GLFW_KEY_KP_3;
			break;
		case Suffer::k_Keypad_4: return GLFW_KEY_KP_4;
			break;
		case Suffer::k_Keypad_5: return GLFW_KEY_KP_5;
			break;
		case Suffer::k_Keypad_6: return GLFW_KEY_KP_6;
			break;
		case Suffer::k_Keypad_7: return GLFW_KEY_KP_7;
			break;
		case Suffer::k_Keypad_8: return GLFW_KEY_KP_8;
			break;
		case Suffer::k_Keypad_9: return GLFW_KEY_KP_9;
			break;
		case Suffer::k_F1: return GLFW_KEY_F1;
			break;
		case Suffer::k_F2: return GLFW_KEY_F2;
			break;
		case Suffer::k_F3: return GLFW_KEY_F3;
			break;
		case Suffer::k_F4: return GLFW_KEY_F4;
			break;
		case Suffer::k_F5: return GLFW_KEY_F5;
			break;
		case Suffer::k_F6: return GLFW_KEY_F6;
			break;
		case Suffer::k_F7: return GLFW_KEY_F7;
			break;
		case Suffer::k_F8: return GLFW_KEY_F8;
			break;
		case Suffer::k_F9: return GLFW_KEY_F9;
			break;
		case Suffer::k_F10: return GLFW_KEY_F10;
			break;
		case Suffer::k_F11: return GLFW_KEY_F11;
			break;
		case Suffer::k_F12: return GLFW_KEY_F12;
			break;
		default: return -1;
			break;
	}

	return -1;

}

// --------------------------------------------------- //

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	inpKey = key;
	inpAction = action;
}

// --------------------------------------------------- //

void Suffer::InitInput(){
	
	if (init) return;
	init = true;

	glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallback);

}

// --------------------------------------------------- //

bool Suffer::IsKeyDown(Key key){

#ifdef ASSERT
	assert(init); // ¿Forget call Init() function?
#endif

	if (inpKey == GetGLFWKey(key) && inpAction == GLFW_PRESS) {
		inpKey = -1;
		return true;
	}

	return false;

}

// --------------------------------------------------- //

bool Suffer::IsKeyUp(Key key){
	
	if (inpKey == GetGLFWKey(key) && inpAction == GLFW_RELEASE) {
		inpKey = -1;
		return true;
	}

	return false;

}

// --------------------------------------------------- //

bool Suffer::MouseButtonDown(int id){

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

double Suffer::MousePositionX(){

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return x;

}

// --------------------------------------------------- //

double Suffer::MousePositionY(){

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	return y;

}

// --------------------------------------------------- //

glm::vec2 Suffer::MousePosition(){

	glm::vec2 result = glm::vec2(0.0f, 0.0f);

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

	result.x = x;
	result.y = y;

	return result;

}

// --------------------------------------------------- //

void Suffer::MousePosition(glm::vec2& out){

	glm::vec2 result = glm::vec2(0.0f, 0.0f);

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);

	out.x = x;
	out.y = y;

}

// --------------------------------------------------- //
