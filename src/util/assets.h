#pragma once

#include <string>
#include <fstream>

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string getExecPath();

std::string readFile(std::string path);
