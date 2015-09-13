/* 
 * File:   Initial.cpp
 * Author: amin
 * 
 * Created on September 10, 2015, 11:28 AM
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm> 
#include "Initial.h"
#include "Configure.h"
#include "Molecule.h"
#include "Parameters.h"

using namespace std;

Initial::Initial(const Configure *conf, const Molecule *mol, const Parameters *params) {
    
    bonds = new BondElem[conf->numBonds];
    memset((void *)bonds, 0, conf->numBonds*sizeof(BondElem));
    build_bondlist(conf,mol,params);
    
    angles = new AngleElem[conf->numAngles];
    memset((void *)angles, 0, conf->numAngles*sizeof(AngleElem));
    build_anglelist(conf,mol,params);
    
    vdw = new VdwElem[conf->numAtoms];
    memset((void *)vdw, 0, conf->numAtoms*sizeof(VdwElem));
    build_vdwlist(conf,mol,params);
    
    pos = new Vector[conf->numAtoms];
    mass = new double[conf->numAtoms];
    for (int ii=0; ii<conf->numAtoms; ii++){
        pos[ii].x = mol->atoms[ii].coor[0];
        pos[ii].y = mol->atoms[ii].coor[1];
        pos[ii].z = mol->atoms[ii].coor[2];
        
        mass[ii] = mol->atoms[ii].mass;
    }
    
    // I need to add another subroutine to initialize the velocity from random generator or input file 
}

void Initial::build_bondlist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch;
    size_t found1, found2;
    
    
    for (int ii=0; ii<conf->numBonds; ii++){ 
        bonds[ii].atom1 = mol->bonds[ii].atom1;
        bonds[ii].atom2 = mol->bonds[ii].atom2;
        
        for (int jj=0; jj < params->bond_str.size(); jj++){
            str = params->bond_str[jj];
            string atype1(mol->atoms[bonds[ii].atom1].atomtype); // Atom1 type
            string atype2(mol->atoms[bonds[ii].atom2].atomtype); // Atom2 type
            
            found1=str.find(atype1); //find atom1 in the str
            if (found1!=std::string::npos) {
                str.replace(found1,atype1.length(),""); //remove the atom1 from str 
                found2=str.find(atype2); //find atom1 in the str
                if (found2!=std::string::npos) {
                    strncpy(seg, str.c_str(), sizeof(seg));
                    seg[sizeof(seg) - 1] = 0;
                    pch = strtok (seg," ,:=");pch = strtok (NULL," ,:="); // Jumb two columns 
                    bonds[ii].k = stof(strtok (NULL," ,:="));
                    bonds[ii].x0 = stof(strtok (NULL," ,:="));
                }
            }    
        } // Loops all bonds parameters
        
        if (bonds[ii].k==0 || bonds[ii].x0==0) {
            cout << "ERROR : NO BOND PARAMETER FOR BOND BETWEEN ATOM " << bonds[ii].atom1+1 << " AND " << bonds[ii].atom2+1 << endl;
        }
        
    } // Loops all bonds    
}

void Initial::build_anglelist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch1, *pch2, *pch3;
    
    for (int ii=0; ii<conf->numAngles; ii++){ 
        angles[ii].atom1 = mol->angles[ii].atom1;
        angles[ii].atom2 = mol->angles[ii].atom2;
        angles[ii].atom3 = mol->angles[ii].atom3;
        
        char *atype1 = mol->atoms[angles[ii].atom1].atomtype; // Atom1 type
        char *atype2 = mol->atoms[angles[ii].atom2].atomtype; // Atom2 type
        char *atype3 = mol->atoms[angles[ii].atom3].atomtype; // Atom3 type
        
        for (int jj=0; jj < params->angle_str.size(); jj++){
            str = params->angle_str[jj];
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch1 = strtok (seg," ,:=");pch1 = strtok (NULL," ,:=");
            pch2 = strtok (NULL," ,:=");
            pch3 = strtok (NULL," ,:=");
            
            if (strcmp(atype2,pch2)==0){
                if ((strcmp(atype1,pch1)==0 && strcmp(atype3,pch3)==0)||(strcmp(atype1,pch3)==0 && strcmp(atype3,pch1)==0)){
                    angles[ii].k = stof(strtok (NULL," ,:="));
                    angles[ii].theta0 = stof(strtok (NULL," ,:="));
                }
            }
        }
        if (angles[ii].k==0 || angles[ii].theta0==0) {
            cout << "ERROR : NO ANGLE PARAMETER FOR ANGLE BETWEEN ATOM " << angles[ii].atom1+1 << " AND " 
                                                                         << angles[ii].atom2+1 << " AND "
                                                                         << angles[ii].atom3+1 << endl;
        }
    }    
}

void Initial::build_vdwlist(const Configure *conf, const Molecule *mol, const Parameters *params){
    string str;
    char   seg[256];
    char  *pch;
    size_t found;
    
    for (int ii=0; ii<conf->numAtoms; ii++){
        string atype1(mol->atoms[ii].atomtype);
        for (int jj=0; jj<params->vdw_str.size(); jj++){
            str = params->vdw_str[jj];
            found=str.find(atype1);
            if (found!=std::string::npos) {
                strncpy(seg, str.c_str(), sizeof(seg));
                seg[sizeof(seg) - 1] = 0;
                pch = strtok (seg," ,:="); pch = strtok (NULL," ,:="); // Jump two columns 
                vdw[ii].epsi = stof(strtok (NULL," ,:="));
                vdw[ii].rmin = stof(strtok (NULL," ,:="));
                vdw[ii].charge = mol->atoms->charge;
            }
        }
    }
    
    // find excluded atoms for nonbonded calculation
    int a1, a2, a3;
    int con[conf->numAtoms][20]; // Save the list of all connections
    int ind[conf->numAtoms];     // Save the number of connections
    memset(ind, 0, sizeof ind);
    memset(con, 0, sizeof con);
    
    for (int ii=0; ii<conf->numBonds; ii++){ // Loop over all bonds
        a1 = bonds[ii].atom1;
        a2 = bonds[ii].atom2;
        
        con[a1][ind[a1]] = a2; ind[a1]++; // Save the connection for atom1
        con[a2][ind[a2]] = a1; ind[a2]++;
    }
    for (int ii=0; ii<conf->numAngles; ii++){ //Loop over all angles
        a1 = angles[ii].atom1;
        a2 = angles[ii].atom2;
        a3 = angles[ii].atom3;
        // No need to save atom2 since the bond connections for atom2 was saved in bond section
        con[a1][ind[a1]] = a3; ind[a1]++; // Save the connection for atom1
        con[a3][ind[a3]] = a1; ind[a3]++; // Save the connection for atom1
    }
    
    for (int ii=0; ii<conf->numAtoms; ii++){ // Loop over all atoms to save connections
        vector<int> temp(con[ii],con[ii]+ind[ii]);
        
        sort(temp.begin(),temp.end()); // Sort connections
        vdw[ii].exclist = new int[ind[ii]]; // Allocate memory to save all connections
        
        for (int jj=0; jj<ind[ii]; jj++){
            vdw[ii].exclist[jj] = temp[jj];
        }
/*        cout << ii << endl;
        for (int ai : temp) {
            cout << ai << " ";
        }
        cout << endl; */
    }
    
//    for (int ai : ind) cout << ai << endl;
}
Initial::Initial(const Initial& orig) {
}

Initial::~Initial() {
}

