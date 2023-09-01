#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

int height = 0;
int width = 0;
unsigned char** image;
// const char* filename_path = "../images/1.jpg"; // Ruta a tu imagen
char* file_path = NULL; // Ruta a tu imagen
char* filename = NULL; // con extensión
// const char* img_extension = ".png";
// char* output_path = "../output_image/";
char* output_path = NULL;


unsigned char** crateArray(int height, int width) {
    unsigned char** array = (unsigned char**)malloc(height * sizeof(unsigned char*));
    for (int i = 0; i < height; i++) {
        array[i] = (unsigned char*)malloc(width * sizeof(unsigned char));
    }
    return array;
}

unsigned char* convertToSingleArray(unsigned char** arrayOfPointers, size_t numRows, size_t numCols) {
    if (arrayOfPointers == NULL || numRows == 0 || numCols == 0) {
        return NULL;
    }

    // Calcula el tamaño total del arreglo unidimensional
    size_t totalSize = numRows * numCols;

    // Reserva memoria para el nuevo arreglo unidimensional
    unsigned char* singleArray = (unsigned char*)malloc(totalSize * sizeof(unsigned char));
    if (singleArray == NULL) {
        return NULL; // Error de asignación de memoria
    }

    // Copia los datos de los arreglos bidimensionales al nuevo arreglo unidimensional
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            singleArray[i * numCols + j] = arrayOfPointers[i][j];
        }
    }

    return singleArray;
}

void getImage() {
    //int width, height, 
     int channels;

    // Carga la imagen usando stb_image
    unsigned char* image_data = stbi_load(file_path, &width, &height, &channels, 0);


    if (!image_data) {
        printf("Error al cargar la imagen.\n");
        // return 1;
    }

    // Convierte la imagen en escala de grises y almacénala en una matriz
    image = crateArray(height, width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Calcula el índice en el arreglo de imagen
            int index = (y * width + x) * channels;

            // Convierte los canales de color a escala de grises
            unsigned char r = image_data[index];
            unsigned char g = image_data[index + 1];
            unsigned char b = image_data[index + 2];

            // Calcula la intensidad promedio y asigna a la matriz en escala de grises
            image[y][x] = (r + g + b) / 3;
        }
    }

    // Ahora "grayscale_image" contiene la matriz de píxeles en escala de grises
    // ...

    // Libera la memoria de la imagen cargada
    stbi_image_free(image_data);
}


// Función para realizar la ecualización de histograma
void equalizeHistogram(int histogram[], int width, int height) {
    int totalPixels = width * height;
    float normalizedHistogram[256];
    float cumulativeDistribution[256];

    // Calcula el histograma normalizado
    for (int i = 0; i < 256; i++) {
        normalizedHistogram[i] = (float)histogram[i] / totalPixels;
    }

    // Calcula la función de distribución acumulativa
    cumulativeDistribution[0] = normalizedHistogram[0];
    for (int i = 1; i < 256; i++) {
        cumulativeDistribution[i] = cumulativeDistribution[i - 1] + normalizedHistogram[i];
    }


    // Mapea los valores de intensidad
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int intensity = image[y][x]; // Supongamos que "image" es tu matriz de píxeles
            int newIntensity = (int)(cumulativeDistribution[intensity] * 255);
            image[y][x] = newIntensity;
        }
    }
}

int hist_equa(char* read_from_path, char* input_filename, char* write_to_path) {
    file_path = read_from_path;
    filename = input_filename;
    output_path = write_to_path;

    // Supongamos que ya tienes la matriz de píxeles cargada en "image"
    getImage(image);
    int histogram[256] = {0}; // Inicializa el histograma con ceros

    // Calcula el histograma de la imagen
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int intensity = image[y][x];
            histogram[intensity]++;
        }
    }

    // Realiza la ecualización de histograma
    equalizeHistogram(histogram, width, height);

    // Ahora "image" contiene la imagen con el histograma ecualizado
    unsigned char *singleArray = convertToSingleArray(image, height, width);

    char imagePath[100];
    snprintf(imagePath, sizeof(imagePath), "%s%s", output_path, filename);
    // printf("Image will be saved at: %s\n", imagePath);
    stbi_write_png(imagePath, width, height, 1, singleArray, width);

    return 0;
}