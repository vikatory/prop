#ifndef __SYS_H__
#define __SYS_H__

#include <string>

std::string getCurAppPath();
std::string& replaceAll(std::string& str, const std::string& old_value, const std::string& new_value);
std::string getAppPath();

#endif // __SYS_H__
