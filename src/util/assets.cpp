#include <string>
#include <fstream>

#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "assets.h"

std::string getExecPath() {
#define PATH_MAX 256
#ifdef WINDOWS
  char result[PATH_MAX];
  return std::string(result, GetModuleFileName(NULL, result, PATH_MAX));
#else
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::string(result, (count > 0) ? count : 0);
#endif
}

std::string readFile(std::string path) {
  std::string fullPath =
      getExecPath().substr(0, getExecPath().find_last_of("\\/") + 1) + path;
  std::string data = "";
  std::ifstream fileStream(fullPath);
  std::string raw;
  while (std::getline(fileStream, raw)) {
    data += raw + "\n";
  }
  fileStream.close();
  return data;
}
