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

void contrast_light(SDL_Surface* img) {
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

void contrast_hard(SDL_Surface* img) {
	const int M = 128;
	const int k = 3;
	for (int i = 0; i < img->h; i++) {
		for (int j = 0; j < img->w; j++) {
			Uint8* pix = (Uint8*)img->pixels + i * img->pitch + j * img->format->BytesPerPixel;
			int d = M + (k * (pix[0] - M));
			if (d < 0) {
				d = 0;
			}
			else if (d > 255) {
				d = 255;
			}
			pix[0] =(Uint8) d;
			pix[1] = (Uint8)d;
			pix[2] = (Uint8)d;
		}
	}
}
