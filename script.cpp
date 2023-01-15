#include "script.h"

Script::Script () {} 


Script::run(std::string path) {
    init(path);
    while (true) { 
        auto keyEvent = m_keyboard.poll(); 
        if (keyEvent == "t") {
            m_keyboard.queue(m_macros[0].rawText); 
            m_keyboard.queueLeft(m_macros[0].rawText.length() - m_macros[0].m_waypoints[1]); 
            m_keyboard.sendQueue(); 
            m_keyboard.clearQueue(); 
        }

    }

} 

Script::init(std::string path) { 
      // Sets up input file stream 
    std::wifstream fin; 
    fin.open(path); 
    if (fin.fail()) { std::cout << "Error opening file: " << path << " \n"; }

    // Buffer for a full line and just a word
    std::wstring bufferLine, bufferWord; 
    
    while (std::getline(fin, bufferLine)) {                         // Set level of loop
        Macro macro; 
        std::wstringstream bufferStream(bufferLine); 
        bufferStream >> bufferWord;
            
        if (bufferWord == L"snippet") {     
                                // Individual macro level of loop
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
                            macro.m_waypoints[i] = position; 
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

    }
}