#include "controller.h"

int main(){
    while(true){
        int dir;
        printf("Where do you wanna go?\n");
        scanf("%d", &dir);
        control(dir);
    }
}