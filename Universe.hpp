#ifndef _Universe
#define _Universe

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CelestialBody.hpp"

using namespace std;


class Universe{
    public:
        // i -> number of particles, r -> radius. 
        // i also corresponds to the number of rows to read
        Universe(int i, float r, ifstream *s);

        //blank constructor
        Universe(){};

        void addBody(string s);

        std::vector<CelestialBody> celestialVec;

    private:
};

#endif