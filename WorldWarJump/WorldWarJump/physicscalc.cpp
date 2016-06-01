#include "physicscalc.h"
//#include <QtMath>
#include <cmath>


PhysicsCalc::PhysicsCalc()
{

}
/**
 * @brief PhysicsCalc::eulToPol
 * @param eul
 * @param pol
 */
void PhysicsCalc::eulToPol(double * eul, double* pol){
    pol[0]=sqrt(eul[0]*eul[0]+eul[1]*eul[1]);
    if(eul[0]>0){
        if(eul[1]>=0){
            pol[1]=atan(eul[1]/eul[0]);
        }
        if(eul[1]<0){
            pol[1]=atan(eul[1]/eul[0]+2*M_PI);
        }
    }
    if(eul[0]<0){
        pol[1]=atan(eul[1]/eul[0]+M_PI);
    }
    if(eul[0]==0){
        if(eul[1]>0){
           pol[1]=M_PI/2;
        }
        if(eul[1]<0){
            pol[1]=((3*M_PI)/2);
        }
    }
}
/**
 * @brief PhysicsCalc::polToEul
 * @param pol
 * @param eul
 */
void PhysicsCalc::polToEul(double * pol, double* eul){
    eul[0]=round(pol[0]*cos(pol[1])*100)/100;
    eul[1]=round(pol[0]*sin(pol[1])*100)/100;
}
