#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
typedef struct{
    double x;
    double y;
    double z;
}coord;

typedef struct
{
    float servo_1_angle;
    float servo_2_angle;
    float servo_3_angle;
    float servo_4_angle;
    coord default_coord;

}leg;
void inverse_kinematics(leg* legx,  coord dest);
void control(int dir);

#endif