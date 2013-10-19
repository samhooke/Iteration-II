#ifndef GENERAL_HPP_INCLUDED
#define GENERAL_HPP_INCLUDED

#include <string>
#include <vector>

std::string Timestamp(int time);
std::vector<std::string> Explode(std::string str, char split);
bool StringToInt(std::string &s, int &i);

#endif // GENERAL_HPP_INCLUDED
