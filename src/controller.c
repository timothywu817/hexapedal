#include "controller.h"


void spi(int leg_num, leg* legx, bool ready){
        printf("%f for leg %d servo 1, %d\n",legx->servo_1_angle, leg_num,ready);
        printf("%f for leg %d servo 2, %d\n",legx->servo_2_angle, leg_num,ready);
        printf("%f for leg %d servo 3, %d\n",legx->servo_3_angle, leg_num,ready);
        printf("%f for leg %d servo 4, %d\n",legx->servo_4_angle, leg_num,!ready);
}

void inverse_kinematics(leg* leg1,  coord dest){
    leg1->servo_1_angle += 15/M_PI;
    leg1->servo_2_angle += 60/M_PI;
    leg1->servo_3_angle += 100/M_PI;
    leg1->servo_4_angle -= 70/M_PI;
}

void moving_around(coord dest, leg* leg1,leg* leg2,leg* leg3){
    inverse_kinematics(leg1, dest);
    spi(1, leg1, 0);
}

void control(int dir){
    leg* left_front = malloc(sizeof(leg));
    leg* left_mid = malloc(sizeof(leg));
    leg* left_back = malloc(sizeof(leg));
    leg* right_front = malloc(sizeof(leg));
    leg* right_mid = malloc(sizeof(leg));
    leg* right_back = malloc(sizeof(leg));
    //give each leg and each servo with the default angle
    left_front->default_coord.x = -250;
    left_front->default_coord.y = 331;
    left_front->default_coord.z = 5;
    left_front->servo_1_angle = 15;
    left_front->servo_2_angle = 5;
    left_front->servo_3_angle = 133.131203-180;
    left_front->servo_4_angle = 180-37.164102;
    // left_mid ->default_coord.x = -305.07;
    // left_mid ->default_coord.y = -82.11;
    // left_mid ->default_coord.z = -133.33;
    // left_back ->default_coord.x = -251.99;
    // left_back ->default_coord.y = -368.37;
    // left_back ->default_coord.z = -130.24;


    //designed the landpoint for moving forward
    coord dest;
    dest.x = 0;
    dest.y = 0;
    dest.z = 0;
    coord dest_forward = {0, 115.7, 0};
    coord dest_backward = {0, -115.7, 0};
    switch(dir){
        case 0: {
            moving_around(dest_forward,left_front, left_back, right_mid);
            // moving_around(dest_backward,left_front, left_back, right_mid);
            // moving_around(dest_forward, left_mid, right_front, right_back);
            // moving_around(dest_backward, left_mid, right_front, right_back);
        }
    }
}