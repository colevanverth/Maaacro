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
    Keyboard m_keyboard;  
}; 