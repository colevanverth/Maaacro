#pragma once

#include <string> 
#include <vector>
#include <map> 

struct Macro { 
    std::wstring trigger; 
    std::wstring rawText; 
    std::map<unsigned int, unsigned int> m_waypoints; // Indice, x value position
    std::map<unsigned int, std::vector<unsigned int>> m_mirrors; // Indice, vector of x positions 
};