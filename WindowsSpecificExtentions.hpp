#pragma once
#include <Windows.h>
#include <string>

#include <iostream>
namespace WinControls {
	inline unsigned int SendKey(const char& button) {
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));
        if (button >= 'a' && button <= 'z') {
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = 0x41 + (button - 'a');

            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 0x41 + (button - 'a');
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        } else if (button >= 'A' && button <= 'Z') {
            INPUT altinputs[4] = {};

            altinputs[0].type = INPUT_KEYBOARD;
            altinputs[0].ki.wVk = VK_LSHIFT;

            altinputs[1].type = INPUT_KEYBOARD;
            altinputs[1].ki.wVk = 0x41 + (button - 'A');
            
            altinputs[2].type = INPUT_KEYBOARD;
            altinputs[2].ki.wVk = 0x41 + (button - 'A');
            altinputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

            altinputs[3].type = INPUT_KEYBOARD;
            altinputs[3].ki.wVk = VK_LSHIFT;
            altinputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            return SendInput(4, altinputs, sizeof(INPUT));
        } else if (button >= '0' && button <= '9') {
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = 0x30 + (button - '0');

            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = 0x30 + (button - '0');
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        }else if (button == ' ') {
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_SPACE;

            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_SPACE;
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        } else if (button == '\n') {
            inputs[0].type = INPUT_KEYBOARD;
            inputs[0].ki.wVk = VK_RETURN;

            inputs[1].type = INPUT_KEYBOARD;
            inputs[1].ki.wVk = VK_RETURN;
            inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
        } else if (button >= '!' && button <= '&') {
            INPUT altinputs[4] = {};

            altinputs[0].type = INPUT_KEYBOARD;
            altinputs[0].ki.wVk = VK_LSHIFT;

            altinputs[1].type = INPUT_KEYBOARD;
            altinputs[1].ki.wVk = 0x31 + (button - '!');

            altinputs[2].type = INPUT_KEYBOARD;
            altinputs[2].ki.wVk = 0x31 + (button - '!');
            altinputs[2].ki.dwFlags = KEYEVENTF_KEYUP;

            altinputs[3].type = INPUT_KEYBOARD;
            altinputs[3].ki.wVk = VK_LSHIFT;
            altinputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
            return SendInput(4, altinputs, sizeof(INPUT));
        }
        
        return SendInput(2, inputs, sizeof(INPUT));
	}

    inline unsigned int ShiftDown() {
        INPUT inputs[1] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LSHIFT;

        return SendInput(1, inputs, sizeof(INPUT));

    }
    inline unsigned int ShiftUp() {
        INPUT inputs[1] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_LSHIFT;
        inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

        return SendInput(1, inputs, sizeof(INPUT));

    }

     unsigned int SendString(const std::string& _string) {

         for (const char& a : _string) {
             
                 SendKey(a);
                 Sleep(1);
             
           }
         return 0;
       }


    unsigned int ToggleMedia() {
        INPUT inputs[2] = {};
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = VK_MEDIA_PLAY_PAUSE;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = VK_MEDIA_PLAY_PAUSE;
        inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

        return SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    }

  
}