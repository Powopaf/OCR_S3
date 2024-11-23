#include "../NeuralNetwork.h"

int main(int argc, char** argv)
{
    char* _train = "train";
    char* _test = "test";
    if(argc>1)
    {
        train(100);
        return 0;
    }
    else if(argc<=1)
    {
        printf("Success: %f\n",testData());
        return 0;
    }
    else
    {
        printf("Wrong Argument: %s\n",argv[1]);
        return 0;
    }
}