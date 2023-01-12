#include "script.h"
#include "string"
#include <iostream> 

int main (int argc, char** argv) { 
    std::string pathName = argv[1];
    Script script; 
    script.run(pathName); 
}