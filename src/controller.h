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

typedef struct{
    float servo_angles[4];
}angles;

typedef struct
{
    angles *servo_angles_concatenation;
    coord default_coord;

}leg;

typedef struct{
    leg* legs[6];
    int phase;
    int dir;
}robot;

void inverse_kinematics(float* servo_angles, coord dest);
void control(int dir);
void lift(robot* hexapedal);
void land(robot* hexapedal);
#endif