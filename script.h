#pragma once

#include <string>
#include <fstream> 
#include <iostream> 
#include <vector>
#include <sstream> 

#include "keyboard.h"
#include "macro.h"

struct Script { 
    Script(); 
    run(std::string path); 
    init(std::string path); 
    std::vector<Macro> m_macros;
    std::wstring m_buffer; 
    Keyboard m_keyboard; 
    void expandMacro(const Macro & macro); 
}; 