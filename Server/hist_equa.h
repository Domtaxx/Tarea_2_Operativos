#ifndef SERVER_H
#define SERVER_H
#include "stb_image_write.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "stb_image.h"
unsigned char** crateArray(int height, int width) ;

char* getCurrentTimeAndDay() ;

unsigned char* convertToSingleArray(unsigned char** arrayOfPointers, size_t numRows, size_t numCols) ;
    // Calcula el tamaño total del arreglo unidimensional

void getImage() ;


// Función para realizar la ecualización de histograma
void equalizeHistogram(int histogram[], int width, int height) ;

int main() ;
int height = 0;
int width = 0;

#endif