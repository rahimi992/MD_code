/* 
 * File:   Integrator.cpp
 * Author: amin
 * 
 * Created on September 11, 2015, 5:17 PM
 */

#include "Integrator.h"
#include "Configure.h"
#include "Initial.h"
#include "Vector.h"
#include "Nonbonded.h"

using namespace std;

Integrator::Integrator(){
    
}
Integrator::Integrator(const Configure *conf, const Initial *init) {
    
    pos = new Vector[conf->numAtoms];
    mass = new double[conf->numAtoms];
    for (int ii=0; ii<conf->numAtoms; ii++){
        pos[ii] = init->pos[ii];
        mass[ii] = init->mass[ii];
    }
    cout << pos->x << endl;
    Nonbonded *non;
    non->pp();
    
}

Integrator::Integrator(const Integrator& orig) {
    
}

Integrator::~Integrator() {
}

