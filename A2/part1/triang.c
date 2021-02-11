#include <stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        perror("Wrong format of function call");
        return(-1);
    }

    // collect input
    int row = atoi(argv[1]);
    int col = row;

    for(int n=0; n<row; n++){
        double pascal = 1;
        for(int k=0; k<col; k++){
            if(k == 0){
                pascal = (double) pascal*1;
            } else {
                pascal = pascal*((double)(n+1-k)/k);
            }
            if(pascal == 0){
                printf("%2c ", ' ');
            } else {
                printf("%2d ", (int) pascal);
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}