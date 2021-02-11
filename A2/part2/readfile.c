#include <stdio.h>

int main(){

    // declare variables
    int i;
    double d;
    char c;
    float f;

    // open file for reading
    FILE * file;
    file = fopen("little_bin_file", "rb");
    if(file == NULL){
      perror("Error opening file");
      return(-1);
    }

    // read from binary file
    int count_i = fread(&i, sizeof(int), 1, file);
    int count_d = fread(&d, sizeof(double), 1, file);
    int count_c = fread(&c, sizeof(char), 1, file);
    int count_f = fread(&f, sizeof(float), 1, file);

    // print results
    printf("%d\n", i);
    printf("%f\n", d);
    printf("%c\n", c);
    printf("%f\n", f);

    fclose(file);
    return 0;
}