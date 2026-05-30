#ifndef FORMATTING_H
#define FORMATTING_H

#include<iostream>

std::string padRight(std::string s, size_t width);
std::string padLeft(std::string s, size_t width);
std::string center(std::string s, size_t width);

std::string to_energy(int n);


void clearScreen();

#endif