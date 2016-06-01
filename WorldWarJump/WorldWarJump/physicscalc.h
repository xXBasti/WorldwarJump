#ifndef PHYSICSCLAC_H
#define PHYSICSCLAC_H
/*
 * eul[1] =x
 * eul[2] =y
 * pol[1] =r
 * pol[2] =fi
 */

class PhysicsCalc
{
public:
    PhysicsCalc();
    //Basti
    void eulToPol(double * eul, double* pol);
    void polToEul(double * pol, double* eul);
    //Basti
};

#endif // PHYSICSCLAC_H
