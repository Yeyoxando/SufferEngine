/*
 * Author: Pablo Bano Benito <banyobe@esat-alumni.com>
 * Date: 10-14-2019
 * Input Header
 */

#ifndef __INPUT_H__
#define __INPUT_H__

#include "vector2.h"
#include "data_types.h"
#include "referenced.h"
#include "scoped_array.h"
#include "common_definitions.h"

namespace Suffer {

    class InputManager {

        friend class SufferManager;

    public:

        struct State{
            State() {
                pressed_ = false;
                released_ = false;
                recently_pressed_ = false;
                recently_released_ = false;
            }
            bool pressed_;
            bool released_;
            bool recently_pressed_;
            bool recently_released_;
        };

        enum Key {
            k_A = 0,
            k_B,
            k_C,
            k_D,
            k_E,
            k_F,
            k_G,
            k_H,
            k_I,
            k_J,
            k_K,
            k_L,
            k_M,
            k_N,
            k_O,
            k_P,
            k_Q,
            k_R,
            k_S,
            k_T,
            k_U,
            k_V,
            k_W,
            k_X,
            k_Y,
            k_Z,
            k_Space,
            k_Enter,
            k_Tab,
            k_Escape,
            k_Delete,
            k_Backspace,
            k_Up,
            k_Down,
            k_Right,
            k_Left,
            k_Control,
            k_Alt,
            k_Shift,
            k_Keypad_0,
            k_Keypad_1,
            k_Keypad_2,
            k_Keypad_3,
            k_Keypad_4,
            k_Keypad_5,
            k_Keypad_6,
            k_Keypad_7,
            k_Keypad_8,
            k_Keypad_9,
            k_F1,
            k_F2,
            k_F3,
            k_F4,
            k_F5,
            k_F6,
            k_F7,
            k_F8,
            k_F9,
            k_F10,
            k_F11,
            k_F12,
        };

        void StartUp();
        void ShutDown();

        bool IsKeyUp(Key key);
        bool IsKeyDown(Key key);
        bool IsKeyPressed(Key key);

        // 0 = left  1 = right
        bool MouseButtonDown(int id);

        double MousePositionX();
        double MousePositionY();
        mathmorra::Vector2 MousePosition();
        void MousePosition(mathmorra::Vector2& out);

        struct KeyBuffer {
            Suffer::InputManager::State state_;
        };
        Array<KeyBuffer> input_events_;

    private:

        InputManager();
        ~InputManager();

        struct Data;
        Data* data_;

        void Update();



    };

}

#endif // __INPUT_H__