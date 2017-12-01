#include "output.h"

#include <stdio.h>
int writeImagePpm(const char* filename, int width, int height, unsigned char *buffer) {
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    fwrite(buffer, 1, 3 * width * height, fp);
    fclose(fp);
    return 0;
}

#include <SOIL.h>
int writeImageBmp(const char* filename, int width, int height, unsigned char* buffer) {
    return SOIL_save_image
    (
        filename,
        SOIL_SAVE_TYPE_BMP,
        width, height, 3,
        buffer
    );
}

