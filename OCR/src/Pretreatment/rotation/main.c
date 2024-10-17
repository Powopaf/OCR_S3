#include "rotate.h"

int main(int argc, char* argv[])
{
    sdl_setup();
    
    if(argc!=1)
    {
        rotation(argv[1],45.0,argv[1]);
    }
    
    sdl_close();
    return 0;
}
