#include "input.h"
#include "glfw3.h"

struct Suffer::InputManager::Data {

    u32 GetGLFWKey(Suffer::InputManager::Key key);
    void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

    struct KeyBuffer {
        Suffer::InputManager::State state_;
    };
    Array<KeyBuffer> input_events_;


};