/* 
 * File:   Integrator.h
 * Author: amin
 *
 * Created on September 11, 2015, 5:17 PM
 */

#ifndef INTEGRATOR_H
#define	INTEGRATOR_H
#include "Configure.h"
#include "Initial.h"
#include "Vector.h"

class Integrator {
public:
    Vector *pos;
    Vector *vel;
    Vector *ff;
    double *mass;
    
    Integrator(const Configure *conf, const Initial *init);
    Integrator(const Integrator& orig);
    virtual ~Integrator();
private:

};

#endif	/* INTEGRATOR_H */

