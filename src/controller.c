#include "controller.h"
//set leg to zero position



void reset_legs(robot* hexapedal){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            hexapedal->legs[i]->servo_angles[j] = 0;
        }
    }
    hexapedal->phase = 0;
}


void spi(robot *hexapedal){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            printf("leg %d servo %d rotate to %f\n",i,j,hexapedal->legs[i]->servo_angles[j]);
        }
    }
}

void inverse_kinematics(float* servo_angles, coord dest){
    for(int i = 0; i < 4; i ++){
        servo_angles[i] += (dest.x * 0.5 + dest.y * 0.7 + dest.z * 0.2 - dest.x * 0.3 + dest.y * 0.5 - dest.z * 0.7 + dest.x * 0.8 + dest.y * 0.1 + dest.z * 0.15) * (i + 0.3);
    }
    printf("dest: %f%f%f\n",dest.x,dest.y,dest.z);
    printf("After IK: %f, %f, %f, %f\n", servo_angles[0], servo_angles[1], servo_angles[2], servo_angles[3]);
}

void lift_up_down(robot* hexapedal,bool upOrDown,int index){
    coord dest_up = {0, 0, 45};
    coord dest_down = {0, 0, -50};
    if(upOrDown){
        printf("moving up\n");
        inverse_kinematics(hexapedal->legs[index]->servo_angles, dest_up);
    }
    else{
        printf("moving down\n");
        inverse_kinematics(hexapedal->legs[index]->servo_angles, dest_down);
    }

}

void set_legs(robot* hexapedal){
    // printf("dir %d\n",hexapedal->dir);
    int tripod = hexapedal->phase % 2;
    coord move_dest = {0,0,0};
    switch(hexapedal->dir){
        case 0:{
            move_dest.x += 50;//forward
        }
        break;
        case 1:{
            move_dest.x -= 30;//backward
        }
        break;
        case 2:{
            move_dest.y -= 45;//left
        }
        break;
        case 3:{
            move_dest.y += 25;//right
        }
        break;
    }
    printf("%f %f %f\n",move_dest.x,move_dest.y,move_dest.z);
    
    for(int i = 0; i < 6; i++){
        if((i % 2) == tripod){
            // printf("leg %d \n",i);
            lift_up_down(hexapedal, 1, i);//lift
            coord dest = {hexapedal->legs[i]->default_coord.x + move_dest.x, hexapedal->legs[i]->default_coord.y + move_dest.y, hexapedal->legs[i]->default_coord.z + move_dest.z};
            printf("%f %f %f",dest.x,dest.y,dest.z);
            inverse_kinematics(hexapedal->legs[i]->servo_angles, dest);
            lift_up_down(hexapedal, 0, i);//land
            coord dest_back = {hexapedal->legs[i]->default_coord.x - move_dest.x, hexapedal->legs[i]->default_coord.y - move_dest.y, hexapedal->legs[i]->default_coord.z - move_dest.z};
            printf("%f %f %f\n",dest_back.x,dest_back.y,dest_back.z);

            inverse_kinematics(hexapedal->legs[i]->servo_angles, dest_back);
            // spi(hexapedal);
        }
        hexapedal->phase = 1 - hexapedal->phase;

    }
}

void control(int dir){
    // printf("%d\n", dir);
    if(dir != 0 && dir != 1 && dir != 2 && dir !=3){
        printf("Invalid direction\n");
        return;
    }
    //give each leg and each servo with the default angle
    robot hexapedal;
    for(int i = 0; i < 6; i++) {
        hexapedal.legs[i] = malloc(sizeof(leg));
        if(hexapedal.legs[i] == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Failed to allocate memory for leg %d\n", i);
            // Cleanup already allocated legs before exiting
            for(int j = 0; j < i; j++) {
                free(hexapedal.legs[j]);
            }
            return;
        }
    }
    hexapedal.dir = dir;
    reset_legs(&hexapedal);//set the legs to zero
    set_legs(&hexapedal);
}