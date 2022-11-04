#pragma once

#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

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


namespace Win {


    struct WindowCallbackStruct {
        unsigned int message;
        WPARAM wParam;
        LPARAM lParam;
    };
    typedef LRESULT CALLBACK WindowEvent;

    

    inline void ErrorMessage(const wchar_t* message) {
        MessageBox(NULL, message, L"Error!",
            MB_ICONEXCLAMATION | MB_OK);
    }

    class WindowException {
    public:
        WindowException(const wchar_t* message) {
            _1_message = std::wstring(message);
            
        }

        void DisplayErrorPrompt(const wchar_t* msg = 0) {
            if (msg == 0) {
                ErrorMessage(_1_message.c_str());
                return;
            }

            ErrorMessage(msg);
            return;
        }

        const wchar_t* what() {
            return _1_message.c_str();
        }

    private:
        std::wstring _1_message;
    };

    
    inline int MessageLoop() {
        MSG Msg;
        while (GetMessage(&Msg, NULL, 0, 0) > 0) {
            TranslateMessage(&Msg);
            DispatchMessage(&Msg);
        }
        return Msg.wParam;
    }



        LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        class Window;
        std::vector<Window*> WindowList = {};

    class Window {
    public:
        Window(const wchar_t* name = L"Basic Window", int startingX = CW_USEDEFAULT, int startingY = CW_USEDEFAULT, int startingWidth = 800, int startingHeight = 800, HINSTANCE hInstance = GetModuleHandle(0)) {
            WindowList.push_back(this);
            wc.cbSize = sizeof(WNDCLASSEX);
            wc.style = CS_DBLCLKS;
            wc.lpfnWndProc = WndProc;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hInstance = hInstance;
            wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wc.lpszMenuName = NULL;
            wc.lpszClassName = name;
            wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

            if (!RegisterClassEx(&wc)) {
                throw(WindowException(L"Window Registration Failed!"));
            }

            hwnd = CreateWindowEx(
                WS_EX_CLIENTEDGE,
                name,
                name,
                WS_OVERLAPPEDWINDOW,
                startingX, startingY, startingWidth, startingHeight,
                NULL, NULL, hInstance, NULL);

            if (hwnd == NULL) {
                throw(WindowException(L"Window Creation Failed!"));

            }
        }

        bool Show(int nCmdShow = 1){ return ShowWindow(hwnd, nCmdShow); }
        bool Update(){ return UpdateWindow(hwnd); }

        inline const HWND& GetHWND() {
            return hwnd;
        }

        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma region AddingCallbacks
        //adds for any window message you give it
        inline void AddGenericCallback(const UINT& MessageToHandle, std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            if (CallbackList.find(MessageToHandle) == CallbackList.end()) {
                CallbackList.insert(std::make_pair(MessageToHandle, std::vector<std::function<void(const WPARAM&, const LPARAM&, Window&)>>(1,foo)));
            } else {
                CallbackList.at(MessageToHandle).push_back(foo);
            }

        }//std::vector<void(*)(const WPARAM&, const LPARAM&)>(foo);

        //set premade unordered map that already has all the callbacks preset
        inline void SetCallbacks(const std::unordered_map<UINT, std::vector<std::function<void(const WPARAM&, const LPARAM&, Window&)>>>& umap) {
            CallbackList = umap;
        }

        //Called when user wants to close the window
        inline void AddCloseCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_CLOSE, foo);
        }

        //Called when window is ready to paint
        inline void AddPaintCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_PAINT, foo);
        }

        //Called when keyboard button is a char and pressed
        inline void AddKeyboardCharacterCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_CHAR, foo);
        }

        //Called when keyboard button is a char and depressed(it's ok keyboard character, it'll be better)
        inline void AddKeyboardCharacterUpCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_DEADCHAR, foo);
        }

        //called when any key is down
        inline void AddKeyboardButtonDownCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_KEYDOWN, foo);
        }


        //called when any key is up
        inline void AddKeyboardButtonUpCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_KEYUP, foo);
        }

        //called when left mouse button is down
        inline void AddLeftMouseDown(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_LBUTTONDOWN, foo);
        }
        //called when left mouse button is up
        inline void AddLeftMouseUp(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_LBUTTONUP, foo);
        }

        //called when right mouse button is down
        inline void AddRightMouseDown(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_RBUTTONDOWN, foo);
        }

        //called when right mouse button is up
        inline void AddRightMouseUp(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_RBUTTONUP, foo);
        }

        inline void AddMiddleMouseDown(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_MBUTTONDOWN, foo);
        }

        inline void AddMiddleMouseUp(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_MBUTTONUP, foo);
        }

        inline void AddLeftDoubleClick(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_LBUTTONDBLCLK, foo);

        }

        inline void AddRightDoubleClick(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_RBUTTONDBLCLK, foo);

        }

        inline void AddMiddleDoubleClick(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_MBUTTONDBLCLK, foo);

        }

        inline void AddResizeCallback(std::function<void(const WPARAM&, const LPARAM&, Window&)> foo) {
            AddGenericCallback(WM_SIZE, foo);

        }
        
#pragma endregion
        
        inline const HWND GetHwnd()const { return hwnd; }
        inline const HDC GetHDC() const { return GetDC(hwnd); }

        void SwapWindowBuffers() const {
            SwapBuffers(GetHDC());
        }

        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    protected:
#pragma region PrivateMembers
        WNDCLASSEX wc;
        HWND hwnd;
        std::unordered_map<UINT, std::vector<std::function<void(const WPARAM&, const LPARAM&, Window&)>>> CallbackList;


        WindowEvent Procedure(const UINT& msg, const WPARAM& wParam, const LPARAM& lParam) {
            if (CallbackList.find(msg) != CallbackList.end()){
                std::vector< std::function<void(const WPARAM&, const LPARAM&, Window&)>> temp = CallbackList[msg];
                for (auto temp2 : temp) {
                    temp2(wParam, lParam, *this);
                }

            }else {
                switch (msg) {
                case WM_CLOSE:
                    DestroyWindow(hwnd);
                    break;
                case WM_DESTROY:
                    PostQuitMessage(0);
                    break;
                default:
                    return DefWindowProc(hwnd, msg, wParam, lParam);
                }
                return 0;
            }
        }

#pragma endregion
    };


        

        LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

            for (auto& w : WindowList) {
                if (hwnd == w->hwnd) {
                    return w->Procedure(msg, wParam, lParam);
                }
            }

            switch (msg) {
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
            }
            return 0;
        }

    
}