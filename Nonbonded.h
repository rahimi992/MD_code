/* 
 * File:   Nonbonded.h
 * Author: amin
 *
 * Created on September 13, 2015, 4:21 PM
 */

#ifndef NONBONDED_H
#define	NONBONDED_H

#include "iostream"
#include "Integrator.h"

using namespace std;

class Nonbonded : public Integrator {
public:
    
    Nonbonded();
    void pp();
    Nonbonded(const Nonbonded& orig);
    virtual ~Nonbonded();
private:

};

#endif	/* NONBONDED_H */

