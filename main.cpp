/* 
 * File:   main.cpp
 * Author: amin
 *
 * Created on September 3, 2015, 1:33 PM
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <new>
#include "Configure.h"
#include "Molecule.h"
#include "Parameters.h"
#include "Initial.h"
#include "Integrator.h"

using namespace std;

int main(int argc, char** argv) {
    time_t t0 = time(0);
    char* cht = ctime(&t0);
    cout << "The local date and time is: " << cht ;  

    if (argc != 2){
        cout << "Error: Enter Input file" << endl;
        exit(1);
    }
    
    Configure conf(argv[1]);  // Read Configure file
    cout << "Input files : " << conf.pdbname << "  " << conf.psfname << "  " << conf.prmname << endl;
    cout << "Number of Atoms  = " << conf.numAtoms << endl;
    cout << "Number of bonds  = " << conf.numBonds << endl;
    cout << "Number of Angles = " << conf.numAngles << endl;
    
    Molecule mol(&conf); // Read PSF and PDB files
    Parameters params(&conf); // Read Parameter files
    
    Initial init(&conf,&mol,&params);
//    mol.~Molecule(); //Free memory
    
    Integrator run(&conf,&init);

    // Simulation Time
    time_t t1 = time(0);
    cht = ctime(&t1);
    cout << "The local date and time is: " << cht ; 
    time_t t2 = t1 - t0;
    cout << "Simulation Time: " << t2 << " seconds" << endl;
    struct tm *tt = gmtime ( &t2 );
    printf ("Simulation Time:  %2d:%02d:%02d\n", (tt->tm_hour)%24, tt->tm_min, tt->tm_sec);
    cout << "END PROGRAM" << endl;
    return 0;
}

