#include "script.h"

Script::Script (std::string pathname) 
    : m_scriptPath(pathname) {} 

void Script::expandMacro(const Macro & macro) {
    m_keyboard.queueBackSpace(macro.trigger.length() + 1); // We add one to get rid of the tab
    m_keyboard.queue(macro.rawText); // Queues the initial raw text. 
    m_keyboard.queueLeft(macro.rawText.length() - macro.m_waypoints.at(1)); // Move caret to initial waypoint. 
    m_keyboard.sendQueue(); 
    m_keyboard.clearQueue();
 
    unsigned int waypointCounter = 2; // Starts at two because caret is already at first waypoint.
    while (waypointCounter <= macro.m_waypoints.size()) { 
        if (m_keyboard.poll() == L"TAB") { 
            m_keyboard.queueBackSpace(1); // Deletes the tab
            m_keyboard.queueRight(macro.m_waypoints.at(waypointCounter) - macro.m_waypoints.at(waypointCounter - 1)); 
            m_keyboard.sendQueue(); 
            m_keyboard.clearQueue(); 
            waypointCounter++; 
        }
        // TODO (Cole): Break while loop on mouse click
        // TODO: Break on CTRL A ()
        // TODO: Break on CTRL Z (Make a buffer in the Keyboard::poll() functioon)
        // TODO: Break on Escape
        // TODO: Add support for mirrors
        // TODO: (Cole) Add special case for doing tabs so it doesnt break in some programs. 
    }
}

void Script::run() {
    init();
    while (true) { 
        auto keyEvent = m_keyboard.poll();
        std::wcout << keyEvent; 
        if (keyEvent == L"TAB") {
            for (auto macro : m_macros) {
                //std::wcout << "Buffer: " << m_buffer << std::endl; 
                //std::wcout << "Substr buffer: " << selection << std::endl;
                if (m_buffer.length() >= macro.trigger.length()) {
                    std::wstring selection = m_buffer.substr(m_buffer.length() - macro.trigger.length(), macro.trigger.length());
                    if (macro.trigger == selection) { 
                        
                        m_buffer.clear(); 
                        expandMacro(macro);
                        break; 
                    }
                }
            }
        }
        else if (keyEvent == L"SPACE") { 
            m_buffer.clear(); 
        }
        else {
            m_buffer += keyEvent; 
        }

    }

} 

void Script::init() { 
    std::wifstream fin; 
    fin.open(m_scriptPath); 
    if (fin.fail()) { std::cout << "Error opening file: " << m_scriptPath << " \n"; } 
    std::wstring bufferLine, bufferWord; // Buffers for full line and whitespace separated words. 
    
    while (std::getline(fin, bufferLine)) { // Set level of loop
        Macro macro; 
        std::wstringstream bufferStream(bufferLine); 
        bufferStream >> bufferWord;
            
        if (bufferWord == L"snippet") { // Individual macro level of loop
            bufferStream >> bufferWord; 
            macro.trigger = bufferWord; 
            std::getline(fin, bufferLine); 
            bufferStream << bufferLine; 
            unsigned int position = 0; 

            while (bufferLine != L"endsnippet") {
                bool capture = false; 
                std::wstring captureString; 

                for (unsigned int i = 0; i < bufferLine.length(); ++i) { // Individual line
                    if (i > 0) {
                        if (bufferLine[i - 1] == '"' && bufferLine[i] == '$') { 
                            macro.rawText.pop_back(); 
                            position--; 
                            capture = true; 
                        }
                    }
                    if (capture) {
                        captureString += bufferLine[i];   
                        if (bufferLine[i] == '"') { 
                            capture = false;
                            captureString = captureString.substr(1, captureString.length() - 2); // Remove dollar sign and quotation mark
                            auto indice = std::stoi(captureString); 
                            //std::cout << position << std::endl; 
                            macro.m_waypoints[indice] = position; 
                        }
                    }
                    else { 
                        macro.rawText += bufferLine[i]; 
                        position++; 
                    }
                }  
                std::getline(fin, bufferLine);
                position++; 
                macro.rawText += L"\n"; 
            }
             macro.rawText.pop_back(); // Removes the extra end of line
        }
        std::wofstream fout; 
        fout.open("snippetoutput.txt"); 
        fout << macro.rawText; 
        m_macros.push_back(macro); 
        //std::wcout << "Raw text: " << macro.rawText << "\n"; 
        //std::wcout << "Trigger word: " << macro.trigger << "\n"; 
    }
}