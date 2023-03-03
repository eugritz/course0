#include "Header.hpp"

void step_clr(sf::Color & clr)
{
	clr.r = clr.r + 5 < 0x100 ? clr.r + 5 : 0xff;
	clr.g = clr.g + 3 < 0x100 ? clr.g + 5 : 0xff;
	clr.b = clr.b + 2 < 0x100 ? clr.b + 5 : 0xff;
}

void drawM(sf::Vector2<TYPE> x, sf::Vector2<TYPE> y)
{
	const TYPE epsilon = 0.005;
	sf::Vector2i sizewindow((int)((x.y - x.x) / epsilon), (int)((y.y - y.x) / epsilon));
	sf::RenderWindow window(sf::VideoMode(sizewindow.x, sizewindow.y), "Mandelbrot");
	sf::Image im;
	const int max_it = 250;
	const int infinity_sqr = 10000;
	im.create(sizewindow.x, sizewindow.y);

	sf::Color clr;
	int xim = 0, yim = 0;
	for (TYPE currx = x.x; currx <= x.y; currx += epsilon, ++xim)
	{
		yim = 0;
		while (xim >= sizewindow.x)
			--xim;
		for (TYPE curry = y.x; curry <= y.y; curry += epsilon, ++yim)
		{
			while (yim >= sizewindow.y)
				--yim;
			clr = sf::Color::Black;
			Complex<TYPE> curr;

            // Закрашиваем точку предварительно черным цветом (если пройдя все
            // итерации, окажется, что точка не превысила некоторое число
            // bail-out, то оно принадлежит множеству Мандельброта, и останется
            // черной).
			im.setPixel(xim, yim, sf::Color::Black);

			for (int i = 0; i < max_it; ++i)
			{
                // Сравнение модуля точки с некоторым числом bail-out: если
                // модуль точки выше этого числа, то орбита с данным приращением
                // стремится к бесконечности.
				if (curr.module_sqr() >= infinity_sqr)
				{
                    // Точка не принадлежит множеству: закрашиваем точку цветом,
                    // зависящим от количества итераций (чем меньше итераций,
                    // тем темнее).
					im.setPixel(xim, yim, clr);
					break;
				}
                // Итерируем далее, согласно формуле Z_(n+1)=(Z_n)^2+c
				curr = curr * curr + Complex<TYPE>(currx, curry);
				step_clr(clr);
			}
		}
	}

	sf::Sprite s;
	sf::Texture t;
	t.loadFromImage(im);
	s.setTexture(t);
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(s);
		window.display();
	}
}
