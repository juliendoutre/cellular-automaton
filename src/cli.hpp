#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

void banner();

sf::Vector2u getMapParameters();

int getRefreshFrequency();

void printDashboard(uint width, uint height, uint generation, uint livingCellsNumber);