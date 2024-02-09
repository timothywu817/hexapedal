#include "controller.h"
//set leg to zero position
void reset_legs(robot* hexapedal){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 4; j++){
            hexapedal->legs[i]->servo_angles_concatenation->servo_angles[j] = 0;
        }
    }
    hexapedal->phase = 0;
}


void spi(robot *hexapedal){
        for(int i = 0; i < 6; i++){
            for(int j = 0; j < 4; j++){
                printf("leg %d servo %d rotate to %f\n",i,j,hexapedal->legs[i]->servo_angles_concatenation->servo_angles[j]);
            }
        }
        
        

}

void inverse_kinematics(float* servo_angles, coord dest){
    for(int i = 0; i < 4; i ++){
        servo_angles[i] += (dest.x + dest.y + dest.z) * i;
    }
}

void lift_down(robot* hexapedal,bool upOrDown,int index){
    coord dest_up = {0, 0, 50};
    coord dest_down = {0, 0, -50};
    if(upOrDown){
        inverse_kinematics(hexapedal->legs[index]->servo_angles_concatenation->servo_angles, dest_up);
    }
    else{
        inverse_kinematics(hexapedal->legs[index]->servo_angles_concatenation->servo_angles, dest_down);
    }

}


void set_legs(robot* hexapedal){
    int tripod = hexapedal->phase % 2;
    coord move_dest = {0,0,0};
    switch(hexapedal->dir){
        case 0:{
            move_dest.x += 50;//forward
        }
        break;
        case 1:{
            move_dest.x -= 50;//backward
        }
        break;
        case 2:{
            move_dest.y -= 50;//left
        }
        break;
        case 3:{
            move_dest.y += 50;//right
        }
        break;
    }
    for(int i = 0; i < 6; i++){
        if((i % 2) == tripod){
            lift_down(hexapedal, 1, i);
            coord dest = {hexapedal->legs[i]->default_coord.x + move_dest.x, hexapedal->legs[i]->default_coord.y + move_dest.y, hexapedal->legs[i]->default_coord.z + move_dest.z};
            inverse_kinematics(hexapedal->legs[i]->servo_angles_concatenation->servo_angles, dest);
        }
        hexapedal->phase = 1 - hexapedal->phase;
    }
}

void control(int dir){
    if(dir != 0 && dir != 1 && dir != 2 && dir !=3){
        printf("Invalid direction\n");
        return;
    }
    //give each leg and each servo with the default angle
    robot *hexapedal = malloc(sizeof(robot));
    reset_legs(hexapedal);//set the legs to zero
    set_legs(hexapedal);
    spi(hexapedal);
    
}