#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    int begin = atoi(argv[1]);
    int end = atoi(argv[2]);

    for (int i = begin; i < end + 1; i++){
        printf("%d\n", i);
    }

    return 0;
}