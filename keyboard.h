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
    std::string association; 
    Key(std::string association)
        : association(association) { 
            cooldown = false; 
        }
};

class Keyboard { 
    std::chrono::steady_clock m_clock; 
    unsigned int activeKey; 
    bool activeKeyEnable = false; 
    std::unordered_map<unsigned int, Key> m_keys{
        {65, Key("a")}, {66, Key("b")}, {67, Key("c")}, {68, Key("d")}, {69, Key("e")}, {70, Key("f")}, {71, Key("g")}, {72, Key("h")}, {73, Key("i")}, 
        {74, Key("j")}, {75, Key("k")}, {76, Key("l")}, {77, Key("m")}, {78, Key("n")}, {79, Key("o")}, {80, Key("p")}, {81, Key("q")}, {82, Key("r")}, 
        {83, Key("s")}, {84, Key("t")}, {85, Key("u")}, {86, Key("v")}, {87, Key("w")}, {88, Key("x")}, {89, Key("y")}, {90, Key("z")}, {9, Key("TAB")}
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

    std::string poll();                                     // Polls keyboard and returns a string of output                       

}; 