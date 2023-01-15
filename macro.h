#pragma once

#include <string> 
#include <vector>
#include <map> 

struct Macro { 
    std::wstring trigger; 
    std::wstring rawText; 
    std::map<unsigned int, unsigned int> m_waypoints; 
}; 