#include <SDL2/SDL.h>
#include <err.h>
#include <unistd.h>

//comment to run project uncomment to run noise reduction functions
#include "../Utils/sdl_utils.h"
#include "../GreyScale/greyscale.h"
#include "../Contrast/contrast.h"
//////////////////////////////////////////////////////////////////////

void applyMedianFilter(SDL_Surface *image) {
    const int kernelSize = 3;
    const int halfKernel = kernelSize / 2;
	const int kernelLength = kernelSize * kernelSize;
    SDL_LockSurface(image);
    for (int y = halfKernel; y < image->h - halfKernel; y++) {
        for (int x = halfKernel; x < image->w - halfKernel; x++) {
            int values[kernelLength];
            int k = 0;
            for (int ky = -halfKernel; ky <= halfKernel; ky++) {
                for (int kx = -halfKernel; kx <= halfKernel; kx++) {
                    Uint8* p = (Uint8*)image->pixels + (y + ky) * image->pitch + (x + kx) * image->format->BytesPerPixel;
                    values[k] = p[0];
					k++;
                }
            }
            for (int i = 0; i < kernelLength; i++) {
                for (int j = i + 1; j < kernelLength; j++) {
                    if (values[j] < values[i]) {
                        int temp = values[i];
                        values[i] = values[j];
                        values[j] = temp;
                    }
                }
            }
            Uint8* pix = (Uint8*)image->pixels + y * image->pitch + x * image->format->BytesPerPixel;
            pix[0] = values[4];
            pix[1] = values[4];
            pix[2] = values[4];
        }
    }

    SDL_UnlockSurface(image);
}


//comment to run project uncomment to run noise reduction function
void test_noise(int a) {
    char filename[2048];
    SDL_Surface* surface = SDL_LoadBMP("i.bmp");
    greyscale(surface);
    SDL_SaveBMP(surface, "img0.bmp");
    SDL_FreeSurface(surface);
    double sig = 0.5;
    for (int i = 0; i < a; i++) {
        printf("Sig: %lf | Lap: %d\n", sig, i);
        SDL_Surface* s = SDL_LoadBMP("img0.bmp");
        //contrast(s);
		applyMedianFilter(s);
        //gauss(s, sig);
		//median(s);
		contrast_light(s);
		contrast_hard(s);
		//contrast(s);	
		sprintf(filename, "img%d.bmp", i + 1);
        SDL_SaveBMP(s, filename);
        SDL_FreeSurface(s);
        sig = sig + 0.001;
    }
}

int main(int argc, char* argv[]) {
    sdl_setup();
    if (argc >= 1) {
        test_noise(atoi(argv[1]));
        sdl_close();
    }
    else {
        sdl_close();
        return EXIT_FAILURE; 
    }
    return EXIT_SUCCESS;
}

