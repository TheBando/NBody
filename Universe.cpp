




#include "Universe.hpp"

Universe::Universe(int i, float f, ifstream *s){
    //constructor
    string line;
    char idelim = 39;
    double rad = f;
    for (int i2 =0; i2<i; i2++){
        getline(*s, line, idelim);
        //cout << line << endl;
        CelestialBody c(line);
        c.setID(i2);
        c.setScale(rad/300);
        c.spriteRef().setPosition(c.getXPosition()/c.getScale(),c.getYPosition()/c.getScale());
        
        celestialVec.push_back(c);

    }
}



