/* 
 * File:   Configure.cpp
 * Author: amin
 * 
 * Created on September 3, 2015, 5:36 PM
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Configure.h"

using namespace std;

Configure::Configure(char *input) {
    string str;
    char   seg[256];
    char  *pch;
    ifstream infile;
    infile.open(input);
    while(!infile.eof()) {
	getline(infile, str);
	if (str!="") {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            string word(pch);
	    if (word == "structure") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(psfname,pch);
            } 
            else if (word == "coordinates") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(pdbname,pch);
            }
            else if (word == "parameters") {
                char *pch = strtok (NULL, " ,:=");
                strcpy(prmname,pch);
            }
            else if (word == "cutoff"){
                char *pch = strtok (NULL, " ,:=");
                cutoff = stof(pch);
            }
            else if (word == "switchdist"){
                char *pch = strtok (NULL, " ,:=");
                switchdist = stof(pch);
            }
            else if (word == "pairlistdist"){
                char *pch = strtok (NULL, " ,:=");
                pairlistdist = stof(pch);
            }
            else if (word == "box"){
                for (int ii; ii<3; ii++){
                    char *pch = strtok (NULL, " ,:=");
                    box[ii] = stof(pch);
                }
                
            }
            
        }
    }
    infile.close();
    
    // Read the number of atoms, bonds, angles from psf file
    infile.open(psfname);
    size_t found;
    while(!infile.eof()) {
	getline(infile, str);        

        found=str.find("NATOM");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numAtoms = stoi(pch);
        }
        
        found=str.find("NBOND");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numBonds = stoi(pch);
        }
        
        found=str.find("NTHETA");
        if (found!=std::string::npos) {
            strncpy(seg, str.c_str(), sizeof(seg));
            seg[sizeof(seg) - 1] = 0;
            pch = strtok (seg," ,:=");
            numAngles = stoi(pch);
        }
        
    }
    infile.close();
}

Configure::Configure(const Configure& orig) {
}

Configure::~Configure() {
}

