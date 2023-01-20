#pragma once

#include <fstream> 
#include <unordered_map> 
#include <string> 
#include <iostream>
#include <windows.h>
#include <vector>
#include <iostream> 

#include "queuecomponent.h"

/**
* @brief Used by `Keyboard` class for polling keyboard input from OS.
* Contains `wstring`s that are sent to `Script`, providing a layer 
* of abstraction from polling input from the OS. 
**/
struct Key {
    // Constructs a `Key` object and sets its `association`. 
    Key(std::wstring association)
        : association(association) { 
            cooldown = false; 
        }

    // True when the key is currently pressed, 
    bool cooldown; 

    // The `wstring` combination that is used to represent the key (e.g. "a"). 
    std::wstring association; 
};

/**
* @brief Provides methods for sending and reading keyboard input. 
**/
class Keyboard { 
public: 
    // Constructs a new `Keyboard` object.
    Keyboard(); 

    // Loads `input` wstring into `m_queue`.
    void queue(std::wstring input);

    // Loads `input` wstring into `m_queue` for `amount` number of times. 
    void queue(std::wstring input, unsigned int amount);

    // Loads the left arrow key into `m_queue` for `amount` number of times. 
    void queueLeft(unsigned int amount);

    // Loads the right arrow key into `m_queue` for `amount` number of times. 
    void queueRight(unsigned int amount);

    // Loads the backspace key into `m_queue` for `amount` number of times. 
    void queueBackSpace(unsigned int amount);

    // Simulates `m_queue` contents to the operating system. 
    void sendQueue();
    
    // Clears `m_queue` contents. 
    void clearQueue();                

    // Returns the key association string (see `m_keys`) for a `Key` object if the key is pressed and not previously pressed. 
    std::wstring poll();                                                       

private:
    // Links the "windows virtual key code" of a keyboard key to a `Key` object. Used by `poll` function.
    std::unordered_map<unsigned int, Key> m_keys{
        {65, Key(L"a")}, {66, Key(L"b")}, {67, Key(L"c")}, {68, Key(L"d")}, {69, Key(L"e")}, {70, Key(L"f")}, {71, Key(L"g")}, {72, Key(L"h")}, {73, Key(L"i")}, 
        {74, Key(L"j")}, {75, Key(L"k")}, {76, Key(L"l")}, {77, Key(L"m")}, {78, Key(L"n")}, {79, Key(L"o")}, {80, Key(L"p")}, {81, Key(L"q")}, {82, Key(L"r")}, 
        {83, Key(L"s")}, {84, Key(L"t")}, {85, Key(L"u")}, {86, Key(L"v")}, {87, Key(L"w")}, {88, Key(L"x")}, {89, Key(L"y")}, {90, Key(L"z")}, {9, Key(L"TAB")},
        {32, Key(L"SPACE")}
    };

    // A vector containing individual `QueueComponent`s. Sent to OS with the `sendQueue` function. 
    std::vector<QueueComponent> m_queue;

    // The total sum of `QueueComponent` keystrokes in `m_queue`. 
    unsigned int m_queueSize = 0; 
}; 