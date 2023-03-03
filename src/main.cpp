#include "Header.hpp"

#include "draw.cpp"
#include <iostream>

int main()
{
	TYPE x1, x2, y1, y2;

	x1 = -2.5;
	x2 = 2;

	y1 = -1.5;
	y2 = 1.5;
	drawM(sf::Vector2<TYPE>(x1, x2), sf::Vector2<TYPE>(y1, y2));
}
