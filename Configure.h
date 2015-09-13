/* 
 * File:   Configure.h
 * Author: amin
 *
 * Created on September 3, 2015, 5:36 PM
 */

#ifndef CONFIGURE_H
#define	CONFIGURE_H

class Configure {
public:
    char pdbname[10];
    char psfname[10];
    char prmname[10];
    
    int numAtoms;
    int numBonds;
    int numAngles;
  
    double cutoff;
    double switchdist;
    double pairlistdist;

    int nsteps;
    double timestep;   // in fs

    double box[3];
    
    Configure();
    Configure(char *input);
    Configure(const Configure& orig);
    virtual ~Configure();
private:

};

#endif	/* CONFIGURE_H */

