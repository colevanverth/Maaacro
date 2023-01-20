#pragma once

#include <string> 
/**
* @brief Represents a portion of a `Keyboard` output queue 
* (e.g. 5 left arrow presses, a wstring, 10 delete keys, a wstring repeated 10 times).
* Can be used in a `vector` to represent an entire output queue. 
**/
class QueueComponent { 
public: 
    // Constructs a `QueueComponent` representing a virtual key code. 
    QueueComponent (unsigned int winCode, unsigned int winCodeRepeat) 
        : m_winCode(winCode), m_winCodeRepeat(winCodeRepeat) {
            m_type = 0;
        } 
    
    // Constructs a `QueueComponent` representing a `wstring`.
    QueueComponent(std::wstring string) 
        : m_wstring(string) {
            m_type = 1; 
        }

    // Returns `m_type`. 
    unsigned int getType() { 
        return m_type; 
    }

    // Returns `m_winCode`. 
    unsigned int getWinCode() { 
        return m_winCode; 
    }

    // Returns `m_winCodeRepeat`.
    unsigned int getWinCodeRepeat() { 
        return m_winCodeRepeat; 
    }

    // Represents `m_wstring`.
    std::wstring getWString() { 
        return m_wstring; 
    }

 private:
    // If 0: `QueueComponent` represents a windows key code repition. If 1: `QueueComponent` represents a `wstring`.
    unsigned int m_type;

    // The windows virtual key code; only used if `m_type` == 0.  
    unsigned int m_winCode;

    // The repitions of `m_winCode`; only used if `m_type` == 0. 
    unsigned int m_winCodeRepeat;  
    
    // The `wstring`; only used if `m_type` == 1; 
    std::wstring m_wstring;
}; 