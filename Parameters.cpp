/* 
 * File:   Parameters.cpp
 * Author: amin
 * 
 * Created on September 9, 2015, 5:16 PM
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include "Parameters.h"
#include "Configure.h"

using namespace std;

Parameters::Parameters(const Configure *conf) {
    
    read_params(conf->prmname);
//    cout << bond_str.size() << endl;
//    cout << bond_str[1] << endl;
}

void Parameters::read_params(const char *filename){
    string str;
    size_t found;
    ifstream infile;
    infile.open(filename);
    while(!infile.eof()) {
	getline(infile, str);
        if (str != ""){
            found=str.find("BOND");
            if (found!=std::string::npos) {
                bond_str.push_back(str);
            }
            found=str.find("ANGLE");
            if (found!=std::string::npos) {
                angle_str.push_back(str);
            }
            found=str.find("LJ");
            if (found!=std::string::npos) {
                vdw_str.push_back(str);
            }
        }
    }
}

Parameters::Parameters(const Parameters& orig) {
}

Parameters::~Parameters() {
}

