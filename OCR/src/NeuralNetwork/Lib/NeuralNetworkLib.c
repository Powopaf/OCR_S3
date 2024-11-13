#include "../NeuralNetwork.h"

// Sigmoid function
double sigmoid(double x) {
    return 1 / (1 + exp(-x));
}

// Derivative of the sigmoid function
double dsigmoid(double x) {
    double r = sigmoid(x);
    return r * (1 - r);
}

// Read integer from string
int ReadInt(char str[]) {
    int result = 0, sign = 1, i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            err(1, "The value is not an int: %c\n", str[i]);
        }
        i++;
    }
    return result * sign;
}

// Read double from string
double ReadDouble(char str[]) {
    double result = 0.0, fraction = 0.0;
    int sign = 1, fractional_part = 0, i = 0;
    double divisor = 10.0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] != '\0') {
        if (str[i] == '.') {
            fractional_part = 1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (!fractional_part) {
                result = result * 10 + (str[i] - '0');
            } else {
                fraction = fraction + (str[i] - '0') / divisor;
                divisor *= 10;
            }
        } else {
            err(1, "The value is not a double: %c in string: %s\n", str[i], str);
        }
        i++;
    }
    return sign * (result + fraction);
}

// Allocate 1D array
void MallocArray(double **arr, int size) {
    *arr = (double *)malloc(size * sizeof(double));
    if (*arr == NULL) {
        err(1, "Memory allocation error\n");
    }
}

// Allocate 2D matrix
void MallocMatrix(double ***arr, int sizex, int sizey) {
    *arr = (double **)malloc(sizex * sizeof(double *));
    if (*arr == NULL) {
        err(1, "Memory allocation error\n");
    }

    for (int i = 0; i < sizex; i++) {
        (*arr)[i] = (double *)malloc(sizey * sizeof(double));
        if ((*arr)[i] == NULL) {
            err(1, "Memory allocation error for row %i", i);
        }
    }
}

// Free 2D matrix
void FreeMatrix(double **arr, int sizex) {
    for (int i = 0; i < sizex; i++) {
        free(arr[i]);
    }
    free(arr);
}

// Split string by delimiter
char **Split(char *str, int *size) {
    const char delimiter = '|';
    char *strCopy = strdup(str);
    char *token = strtok(strCopy, &delimiter);
    int count = 0;

    while (token != NULL) {
        count++;
        token = strtok(NULL, &delimiter);
    }

    char **result = (char **)malloc(count * sizeof(char *));
    free(strCopy);
    strCopy = strdup(str);
    token = strtok(strCopy, &delimiter);
    int index = 0;

    while (token != NULL) {
        result[index++] = strdup(token);
        token = strtok(NULL, &delimiter);
    }

    *size = count;
    free(strCopy);

    return result;
}

// Free split array
void FreeSplitArray(char **arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

// Load data from file
void LoadData(char filename[], double **hiddenLayerBias, double **outputLayerBias, 
              double ***hiddenWeights, double ***outputWeights, int *nbInputs, 
              int *nbHiddenNodes, int *nbOutputs, double *LearningRate) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        err(1, "Error opening file %s\n", filename);
    }

    char line[16384];
    int size;
    char **arr;

    // Read network configuration
    fgets(line, sizeof(line), file);
    arr = Split(line, &size);
    *nbInputs = ReadInt(arr[0]);
    *nbHiddenNodes = ReadInt(arr[1]);
    *nbOutputs = ReadInt(arr[2]);
    *LearningRate = ReadDouble(arr[3]);
    FreeSplitArray(arr, size);

    // Read hidden layer biases
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    arr = Split(line, &size);
    MallocArray(hiddenLayerBias, *nbHiddenNodes);

    if (size < *nbHiddenNodes) 
    {
        err(1, "Unexpected number of elements in line: expected %d, got %d\n", *nbHiddenNodes, size);
    }

    for (int i = 0; i < *nbHiddenNodes; i++) {
        (*hiddenLayerBias)[i] = ReadDouble(arr[i]);
    }
    FreeSplitArray(arr, size);

    // Read hidden weights
    MallocMatrix(hiddenWeights, *nbInputs, *nbHiddenNodes);
    for (int i = 0; i < *nbInputs; i++) {
        fgets(line, sizeof(line), file);
        arr = Split(line, &size);
        for (int j = 0; j < *nbHiddenNodes; j++) {
            (*hiddenWeights)[i][j] = ReadDouble(arr[j]);
        }
        FreeSplitArray(arr, size);
    }

    // Read output layer biases
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    arr = Split(line, &size);
    MallocArray(outputLayerBias, *nbOutputs);
    for (int i = 0; i < *nbOutputs; i++) {
        (*outputLayerBias)[i] = ReadDouble(arr[i]);
    }
    FreeSplitArray(arr, size);

    // Read output weights
    MallocMatrix(outputWeights, *nbHiddenNodes, *nbOutputs);
    for (int i = 0; i < *nbHiddenNodes; i++) {
        fgets(line, sizeof(line), file);
        arr = Split(line, &size);
        for (int j = 0; j < *nbOutputs; j++) {
            (*outputWeights)[i][j] = ReadDouble(arr[j]);
        }
        FreeSplitArray(arr, size);
    }

    fclose(file);
}

void WriteData(char filename[], double *hiddenLayerBias, double *outputLayerBias, double **hiddenWeights, double **outputWeights, int nbInputs, int nbHiddenNodes, int nbOutputs, double LearningRate) 
{
    FILE *file = fopen(filename, "w");
    const char com1[] = "// Hidden layer data, first line for bias, others for weights\n";
    const char com2[] = "// Output layer data, first line for bias, others for weights\n";

    if (file == NULL) {
        err(1, "Error opening file %s\n", filename);
    }

    // Write network structure details and learning rate
    fprintf(file, "%i|%i|%i|%f|\n", nbInputs, nbHiddenNodes, nbOutputs, LearningRate);
    fprintf(file, "%s", com1);

    // Write hidden layer biases
    for (int i = 0; i < nbHiddenNodes; i++) {
        fprintf(file, "%f|", hiddenLayerBias[i]);
    }
    fprintf(file, "\n");

    // Write hidden layer weights
    for (int i = 0; i < nbInputs; i++) {
        for (int j = 0; j < nbHiddenNodes; j++) {
            fprintf(file, "%f|", hiddenWeights[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "%s", com2);

    // Write output layer biases
    for (int i = 0; i < nbOutputs; i++) {
        fprintf(file, "%f|", outputLayerBias[i]);
    }
    fprintf(file, "\n");

    // Write output layer weights
    for (int i = 0; i < nbHiddenNodes; i++) {
        for (int j = 0; j < nbOutputs; j++) {
            fprintf(file, "%f|", outputWeights[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


