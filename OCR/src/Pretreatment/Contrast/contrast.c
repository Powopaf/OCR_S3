#include <SDL2/SDL.h>
#include <err.h>

void MinMaxPixel(SDL_Surface* img, Uint8 res[2]) {

	for (int i = 0; i < img->h; i++) {
		for (int j = 0; j < img->w; j++) {
			Uint8* pix = (Uint8*)img->pixels + i * img->pitch + j * img->format->BytesPerPixel;
			if (pix[0] < res[0]) {
				res[0] = pix[0];
			}
			else if (pix[0] > res[1]) {
				res[1] = pix[0];
			}
		}
	}
}

void contrast(SDL_Surface* img) {
	Uint8 m[2] = { (Uint8)255, (Uint8)255 };
	MinMaxPixel(img, m);
	if (m[0] == m[1]) {
		return;
	}
	for (int i = 0; i < img->h; i++) {
		for (int j = 0; j < img->w; j++) {
			Uint8* pix = (Uint8*)img->pixels + i * img->pitch + j * img->format->BytesPerPixel;
			double v = (double)(pix[0] - m[0]) / (m[1] - m[0]) * 255;
			Uint8 new = (Uint8)v;
			pix[0] = new;
			pix[1] = new;
			pix[2] = new;
		}
	}
}
