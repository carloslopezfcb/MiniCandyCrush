#include <SDL\SDL.h>
#include <SDL\SDL_image.h>

int main(int, char*[]) {
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw SDL_GetError();

		const Uint8 imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

		if (!(IMG_Init(imgFlags) & imgFlags)) throw IMG_GetError();

		//WINDOW//
		const int WIDTH = 640, HEIGHT = 480;
		SDL_Window *window = SDL_CreateWindow("HELLO WORLD",                  // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			WIDTH,                            // width, in pixels
			HEIGHT,                           // height, in pixels
			SDL_WINDOW_SHOWN);

		if (window == nullptr) throw SDL_GetError();

		//RENDERER//
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (renderer == nullptr) throw SDL_GetError();

		//SPRITES//

		SDL_Texture *bgTexture = IMG_LoadTexture(renderer, "../../res/gfx/bg.jpg");
		if (bgTexture == nullptr) throw SDL_GetError();
		SDL_Rect bgRect = {0, 0, WIDTH, HEIGHT};

		//GAME LOOP//
		SDL_Event evnt;
		for (bool isRunning = true; isRunning;) {
			//INPUT HANDLER//
			while (SDL_PollEvent(&evnt))
			{
				switch (evnt.type){
					case SDL_QUIT: isRunning = false; break;
					default:;
				}
			}
			//DRAW//
			SDL_RenderCopy(renderer, bgTexture, nullptr, &bgRect);
			SDL_RenderPresent(renderer);
		}

		//DESTROY//
		SDL_DestroyTexture(bgTexture);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		
	}

	catch (const char *msg) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", msg);
	}
	IMG_Quit();
	SDL_Quit();
	return 0;
}
