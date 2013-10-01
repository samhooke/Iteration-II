#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <iostream>

#ifdef DEBUG
#define LogError(x) (std::cerr << "[ERROR]: " << (x))
#define LogWarning(x) (std::cout << "[WARNING]: " << (x))
#define LogInfo(x) (std::cout << "[INFO]: " << (x))
#else
#define LogError(x)
#define LogWarning(x)
#define LogInfo(x)
#endif

#endif // LOGGER_HPP_INCLUDED
