
#include "Nbody.hpp"

using namespace std;

namespace nb
{
    Universe u;
    extern sf::RenderWindow *windowPtr;
}

bool compXPos(CelestialBody c1, CelestialBody c2)
{
    return (c1.getXPosition() < c2.getXPosition());
}


Nbody::Nbody(string s, int time, int dTime)
{
    //ifstream input("./nbody/planets.txt");
    cout << s << endl;
    ifstream input(s);
    string ln1;
    string ln2;
    getline(input, ln1);
    getline(input, ln2);

    int i = stoi(ln1);
    double d = stod(ln2);
    //cout << ln1 << " " << ln2 << endl;
    Universe universe(i, d, &input);
    nb::u = universe;
    RunningLoop(universe,time,dTime);
}


void Nbody::RunningLoop(Universe ux, int t, int dt)
{
    int time = t;
    int deltaT = dt;
    int elapsedTime = 0;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Nbody");

    int index = 0;

    for (auto &cb : nb::u.celestialVec)
    {

        sf::Image tmp;

        if (!tmp.loadFromFile("./nbody/" + cb.getFilename()))
        {
            cout << "image loading error" << endl;
        }

        cb.setSpec(tmp);

        sf::Sprite sp = cb.getSprite();
        float fx = window.getSize().x / 2;
        float fy = window.getSize().y / 2;
        index++;
    }
    for (CelestialBody &cb : nb::u.celestialVec)
    {
        cb.setYPosition(cb.getYPosition() + cb.getYVelocity());
    }
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        if (elapsedTime < time)
        {

            for (auto &cb : nb::u.celestialVec)
            {
                cb.calcForces(&nb::u.celestialVec, (deltaT));
            }
            for (auto &cb : nb::u.celestialVec)
            {
                cb.calcPos((deltaT));
            }
            for (auto &cb : nb::u.celestialVec)
            {
                cb.stepPos(window.getSize().x / 2, window.getSize().y / 2);
            }
            elapsedTime += (deltaT);
            //cout << "\n";
        }
        else{;}
        for (auto &cb : nb::u.celestialVec)
        {
            window.draw(cb.spriteRef());
        }

        window.display();
    }
    cout << "xPos    yPos    xVel    yVel     mass       name" <<
    "\n-------------------------------------------------------" << endl;
    for (auto &cb : nb::u.celestialVec){
        cout << cb.getXPosition() << " " << cb.getYPosition() << " " << cb.getXVelocity() << " " << cb.getYVelocity() <<
        " " << cb.getMass() << " " << cb.getFilename() << endl;
    }

}

int main(int argc, char *argv[])
{
    string s;
    double time, dTime;
    
    if(argv[1] == NULL || argv[2] == NULL){
        time = 157788000.0;
        dTime = 25000.0;
    }
    else{
        time = strtod(argv[1],NULL);
        dTime = strtod(argv[2],NULL);
    }

    if(argc > 3){
        s=argv[3];
        s="./nbody/"+s;
    }
    else{
        s="./nbody/planets.txt";
    }

     cout << "Time: " << time << " dTime: " << dTime << "\n"
     << "argv's: " << endl;
     for (int i=0; i<argc; i++){
         cout<<i<<": "<<argv[i]<<endl;
     }
    Nbody n(s,time,dTime);
    cout << "1" << endl;


    return 0;
}