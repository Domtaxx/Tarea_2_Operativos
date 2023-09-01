#include "stb_image.h"
#include "stb_image_write.h"
#include "color.h"
#include <stdio.h>
int clas_color(char* read_from_path, char* output_filename, char* write_to_path) {
    char* file_path_2 = NULL; // Ruta a tu imagen
    char* out_filename = NULL; // con extensión
    char* output_path = NULL;
    file_path_2 = read_from_path;
    out_filename = output_filename;

    int width, height, channels;
    unsigned char *image = stbi_load(file_path_2, &width, &height, &channels, 0);

    if (!image) {
        printf("No se pudo cargar la imagen.\n");
        return -1;
    }

    int greenPixels = 0;
    int redPixels = 0;
    int bluePixels = 0;

    // Itera sobre cada píxel de la imagen
    for (int i = 0; i < width * height * channels; i += channels) {
        redPixels += image[i];       // Canal azul
        greenPixels += image[i + 1];  // Canal verde
        bluePixels += image[i + 2];    // Canal rojo
    }

    // Clasifica la imagen
    char imagePath[100];
    if (greenPixels > bluePixels && greenPixels > redPixels) {
        snprintf(imagePath, sizeof(imagePath), "%s%s%s", write_to_path, "verde/", out_filename);
        stbi_write_jpg(imagePath, width, height, channels, image, 100);
    } else if (redPixels > bluePixels && redPixels > greenPixels ) {
        snprintf(imagePath, sizeof(imagePath), "%s%s%s", write_to_path, "rojo/", out_filename);
        stbi_write_jpg(imagePath, width, height, channels, image, 100);
    } else if (bluePixels > greenPixels && bluePixels > redPixels ) {
        snprintf(imagePath, sizeof(imagePath), "%s%s%s", write_to_path,"azul/", out_filename);
        stbi_write_jpg(imagePath, width, height, channels, image, 100);
    } else {
        printf("No se pudo clasificar la imagen en ninguna categoría.\n");
    }

    stbi_image_free(image);
    return 1;

}
