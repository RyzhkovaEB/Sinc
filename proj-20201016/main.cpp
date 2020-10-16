/*
 * main.cpp
 *
 *  Created on: 16 окт. 2020 г.
 *      Author: erijkova
 */

#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>

#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 800, HEIGHT = 600;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Sinc(x)",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "При создании окна произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "При создании renderer-а произошла ошибка: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 48, 64, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(ren.get(), 255, 255, 255, 255);

		double cx = 800. / 2. , cy = 600. / 2.;

		for (double x = 0.; x < 800.; x += 1./10.) {
			int px, py;
			px = int(x);

			double normX = x - cx;
			double normY;
			double coef = 40.;

			if (normX == 0.)
			normY = coef;
			else
			normY = coef * ((sin (Pi*(normX / coef))) / (Pi*(normX / coef)));

			py = int (cy - normY);

			SDL_RenderDrawPoint(ren.get(), px, py);
		}

		SDL_RenderPresent(ren.get());
	}


	return 0;
}




