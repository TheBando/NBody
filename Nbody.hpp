#ifndef _Nbody
#define _Nbody

#include "Universe.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>



#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


using namespace std;

namespace nb{
    extern Universe u;
    extern sf::RenderWindow *windowPtr;
}

class Nbody{
    public:
        Nbody();
        Nbody(string s, int, int);

        void RunningLoop(Universe u, int, int);

        //Universe getUniverse(){return *universe;}
    private:
        //Universe *universe;
};

#endif