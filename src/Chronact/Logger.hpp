#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include "Logger.hpp"

#include <iostream>

#ifdef DEBUG
#define LogError(x) (std::cerr << "[ERROR]: " << (x) << std::endl)
#define LogWarning(x) (std::cout << "[WARNING]: " << (x) << std::endl)
#define LogInfo(x) (std::cout << "[INFO]: " << (x) << std::endl)
#else
#define LogError(x)
#define LogWarning(x)
#define LogInfo(x)
#endif

#endif // LOGGER_HPP_INCLUDED
