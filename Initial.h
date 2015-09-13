/* 
 * File:   Initial.h
 * Author: amin
 *
 * Created on September 10, 2015, 11:28 AM
 */

#ifndef INITIAL_H
#define	INITIAL_H

#include "Configure.h"
#include "Molecule.h"
#include "Vector.h"
#include "Parameters.h"

struct BondElem {
  int atom1, atom2;
  double x0;
  double k;
};

struct AngleElem {
  int atom1, atom2, atom3;
  double k, theta0;
};

struct VdwElem {
    double epsi, rmin;
    double charge;
    int *exclist;
};

class Initial {
public:
    
    Vector *pos;
    double *mass;
    
    BondElem *bonds;
    AngleElem *angles;
    VdwElem *vdw;
    
    void build_bondlist(const Configure *conf, const Molecule *mol, const Parameters *params);
    void build_anglelist(const Configure *conf, const Molecule *mol, const Parameters *params);
    void build_vdwlist(const Configure *conf, const Molecule *mol, const Parameters *params);
    
    Initial(const Configure *conf, const Molecule *mol, const Parameters *params);
    Initial(const Initial& orig);
    virtual ~Initial();
private:

};

#endif	/* INITIAL_H */

