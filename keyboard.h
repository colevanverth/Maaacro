#pragma once

#include <fstream> 
#include <unordered_map> 
#include <string> 
#include <iostream>
#include <windows.h>
#include <vector>
#include <iostream> 
#include <chrono>

class QueueComponent { 
    unsigned int m_type;            // 0: Represents windows key code, 1: Represents wstring
    unsigned int m_winCode;         // Windows virtual key code
    unsigned int m_winCodeRepeat;   // Repitions of windows virtual key code
    std::wstring m_wstring;         // Unicode string
public: 
    QueueComponent () {}
    QueueComponent (unsigned int winCode, unsigned int winCodeRepeat) 
        : m_winCode(winCode), m_winCodeRepeat(winCodeRepeat) {
            m_type = 0;     // QueueComponent represents virtual key codes
        } 
    QueueComponent(std::wstring string) 
        : m_wstring(string) {
            m_type = 1;    // QueueComponent represents strings
        }
    unsigned int getType() { 
        return m_type; 
    }
    unsigned int getWinCode() { 
        return m_winCode; 
    }
    unsigned int getWinCodeRepeat() { 
        return m_winCodeRepeat; 
    }
    std::wstring getWString() { 
        return m_wstring; 
    }
}; 

struct Key {
    bool cooldown; 
    std::wstring association; 
    Key(std::wstring association)
        : association(association) { 
            cooldown = false; 
        }
};

class Keyboard { 
    std::chrono::steady_clock m_clock; 
    unsigned int activeKey; 
    bool activeKeyEnable = false; 
    std::unordered_map<unsigned int, Key> m_keys{
        {65, Key(L"a")}, {66, Key(L"b")}, {67, Key(L"c")}, {68, Key(L"d")}, {69, Key(L"e")}, {70, Key(L"f")}, {71, Key(L"g")}, {72, Key(L"h")}, {73, Key(L"i")}, 
        {74, Key(L"j")}, {75, Key(L"k")}, {76, Key(L"l")}, {77, Key(L"m")}, {78, Key(L"n")}, {79, Key(L"o")}, {80, Key(L"p")}, {81, Key(L"q")}, {82, Key(L"r")}, 
        {83, Key(L"s")}, {84, Key(L"t")}, {85, Key(L"u")}, {86, Key(L"v")}, {87, Key(L"w")}, {88, Key(L"x")}, {89, Key(L"y")}, {90, Key(L"z")}, {9, Key(L"TAB")},
        {32, Key(L"SPACE")}
    };

    std::vector<QueueComponent> m_queue;
    unsigned int m_queueSize = 0; 
public: 
    Keyboard(); 
    queue(std::wstring input);                              // Loads a string into output queue
    queue(std::wstring input, unsigned int amount);         // Replicates "input" for an "amount" number of times
    queueLeft(unsigned int amount);                         // Queues the left arrow "amount" number of times 
    queueRight(unsigned int amount);                        // Queues the right arrow "amount" number of times
    queueBackSpace(unsigned int amount);                    // Queues the backspace "amount" number of times
    sendQueue();                                            // Sends the output queue
    clearQueue();                                           // Clears the output queue

    std::wstring poll();                                     // Polls keyboard and returns a string of output                       

}; 