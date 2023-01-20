#pragma once

#include <string>
#include <fstream> 
#include <iostream> 
#include <vector>
#include <sstream> 

#include "keyboard.h"
#include "macro.h"

/**
* @brief All snippet logic is implemented here by interacting with
* the `Keyboard` class. Must be instantiated with a `std::string` representing 
* a pathname to a scriptfile. 
**/
class Script {
public: 
    // Constructs a new `Script` object. 
    Script(std::string pathname); 

    // Handles `init` function call, captures keyboard input, and calls `expandMacro` when neccesary.  
    void run(); 

    // Parses the scriptfile from `path` into macros that are placed in `m_macros` vector. 
    void init();

    // Handles all macro expansion logic from `macro`. 
    void expandMacro(const Macro & macro); 

private:
    // Vector of `Macro` objects.
    std::vector<Macro> m_macros;

    // Utilized for temporary capture of `Keyboard::poll()` to check for macro trigger words. 
    std::wstring m_buffer; 

    // `Keyboard` object. Provides methods for reading and sending keyboard input. 
    Keyboard m_keyboard; 

    // Represents a path name to a scriptfile. Set on class instantiation and used by `init` function. 
    std::string m_scriptPath; 
}; 