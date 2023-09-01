#ifndef HIST_H
#define HIST_H
#include <math.h>
#include <time.h>
#include <stdio.h>
unsigned char** crateArray(int height, int width) ;

unsigned char* convertToSingleArray(unsigned char** arrayOfPointers, size_t numRows, size_t numCols) ;

void getImage();

int clas_color(char* read_from_path, char* output_filename, char* write_to_path);
// Función para realizar la ecualización de histograma
void equalizeHistogram(int histogram[], int width, int height) ;

int hist_equa(char* read_from_path, char* input_filename, char* write_to_path) ;
#endif