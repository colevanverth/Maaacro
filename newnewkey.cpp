#include <windows.h>

int main() {
    Sleep(3000);
    INPUT in;
    in.type=INPUT_KEYBOARD;
    in.ki.wScan=0;
    in.ki.dwFlags=0;
    in.ki.time=0;
    in.ki.dwExtraInfo=0;
    in.ki.wScan = 10; 
    in.ki.dwFlags |= KEYEVENTF_UNICODE;
    in.ki.wVk = 0;
    SendInput(1,&in,sizeof(INPUT));
}