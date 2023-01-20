#include "keyboard.h"

Keyboard::Keyboard() {}

Keyboard::queue(std::wstring input) {
    QueueComponent qc(input); 
    m_queue.push_back(qc); 
    m_queueSize += input.length(); 
} 

std::wstring Keyboard::poll() {
    
    for (auto it = m_keys.begin(); it != m_keys.end(); it++) { 
        if (GetAsyncKeyState(it->first) && !it->second.cooldown) { 
            it->second.cooldown = true; 
            return it->second.association; 
            // Special case goes in here. If z is pressed, and CTRL is also pressed, 
            // then we return L"CTRLZ" 
        }
        if (!GetAsyncKeyState(it->first) && it->second.cooldown) { 
            it->second.cooldown = false; 
        }  
    }
    return L""; 
}

Keyboard::queueLeft(unsigned int amount) {
    QueueComponent qc(37, amount);  // 37 = Wincode for left arrow
    m_queue.push_back(qc); 
    m_queueSize += amount; 
}
Keyboard::queueRight(unsigned int amount) {
    QueueComponent qc(39, amount);  // 39 = Wincode for right arrow
    m_queue.push_back(qc); 
    m_queueSize += amount;
}
Keyboard::queueBackSpace(unsigned int amount) { 
    QueueComponent qc(8, amount);       // 8 = code for backspace
    m_queue.push_back(qc); 
    m_queueSize += amount; 
}


Keyboard::queue(std::wstring input, unsigned int amount) { 
    std::wstring tempString = L""; 
    for (int i = 0; i < amount; ++i) { 
        tempString += input; 
    }
    QueueComponent qc(tempString); 
    m_queue.push_back(qc); 
    m_queueSize += amount; 
}
Keyboard::sendQueue() {
    std::cout << "queue" << std::endl;
    
    auto keys = new INPUT[m_queueSize * 2]; 
    unsigned int keyIndex = 0; 
    for (auto qc : m_queue) { 
        if (qc.getType() == 1) { 
            for (unsigned int i = 0; i < qc.getWString().length(); ++i) { 
                if ((short)qc.getWString()[i] == 10) { 
                    keys[keyIndex].ki.wVk = VK_RETURN; 
                }
                else { 
                    keys[keyIndex].ki.wScan = (short)qc.getWString()[i];
                    keys[keyIndex].ki.dwFlags = KEYEVENTF_UNICODE; 
                }
                keys[keyIndex].type=INPUT_KEYBOARD;
                keys[keyIndex].ki.time=0;
                keys[keyIndex].ki.dwExtraInfo = GetMessageExtraInfo();
                std::cout << (int)qc.getWString()[i] << std::endl;
                keys[keyIndex + 1] = keys[keyIndex];
                keys[keyIndex + 1].ki.dwFlags |= KEYEVENTF_KEYUP;
                keyIndex += 2   ;
            }
        }
        else if (qc.getType() == 0) {
            for (unsigned int i = 0; i < qc.getWinCodeRepeat(); ++i) {
                keys[keyIndex].type=INPUT_KEYBOARD;
                keys[keyIndex].ki.wScan=0;
                keys[keyIndex].ki.dwFlags=0;
                keys[keyIndex].ki.time=0;
                keys[keyIndex].ki.dwExtraInfo=0;
                keys[keyIndex].ki.wVk=qc.getWinCode(); 
                keys[keyIndex + 1] = keys[keyIndex];
                keys[keyIndex + 1].ki.dwFlags |= KEYEVENTF_KEYUP;
                keyIndex += 2; 
            }
        }
    }
    SendInput(m_queueSize * 2,keys,sizeof(INPUT));
    delete[] keys; 
  
}               
Keyboard::clearQueue() {
    m_queue.clear(); 
    m_queueSize = 0; 
}           