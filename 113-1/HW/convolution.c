#include <stdio.h>
#include <stdlib.h>

void flip_horizontally(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size / 2; j++) {
            int temp = matrix[i][j];
            matrix[i][j] = matrix[i][size - j - 1];
            matrix[i][size - j - 1] = temp;
        }
    }
}

void convolution(int **input, int **kernel, int **output, int imageSize, int filterSize) {
    int outputSize = imageSize - filterSize + 1;
    for (int i = 0; i < outputSize; i++) {
        for (int j = 0; j < outputSize; j++) {
            int sum = 0;
            for (int ki = 0; ki < filterSize; ki++) {
                for (int kj = 0; kj < filterSize; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = sum;
        }
    }
}

int main() {
    int times, imageSize, filterSize, threshold;
    scanf("%d", &times);
    for (int t = 0; t < times; t++) {
        scanf("%d %d %d", &imageSize, &filterSize, &threshold);
        
        int **input = (int **)malloc(imageSize * sizeof(int *));
        for (int i = 0; i < imageSize; i++) {
            input[i] = (int *)malloc(imageSize * sizeof(int));
        }

        int **kernel = (int **)malloc(filterSize * sizeof(int *));
        for (int i = 0; i < filterSize; i++) {
            kernel[i] = (int *)malloc(filterSize * sizeof(int));
        }

        for (int i = 0; i < imageSize; i++) {
            for (int j = 0; j < imageSize; j++) {
                scanf("%d", &input[i][j]);
            }
        }

        for (int i = 0; i < filterSize; i++) {
            for (int j = 0; j < filterSize; j++) {
                scanf("%d", &kernel[i][j]);
            }
        }

        int outputSize = imageSize - filterSize + 1;
        int **output = (int **)malloc(outputSize * sizeof(int *));
        for (int i = 0; i < outputSize; i++) {
            output[i] = (int *)malloc(outputSize * sizeof(int));
        }

        flip_horizontally(input, imageSize);

        convolution(input, kernel, output, imageSize, filterSize);

        int count = 0;
        for (int i = 0; i < outputSize; i++) {
            for (int j = 0; j < outputSize; j++) {
                if (output[i][j] > threshold) {
                    count++;
                }
            }
        }

        printf("%d\n", count);

        for (int i = 0; i < imageSize; i++) {
            free(input[i]);
        }
        free(input);

        for (int i = 0; i < filterSize; i++) {
            free(kernel[i]);
        }
        free(kernel);

        for (int i = 0; i < outputSize; i++) {
            free(output[i]);
        }
        free(output);
    }

    //printf("Thank you.\n");
    return 0;
}