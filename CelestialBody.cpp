
#include <iostream>
#include <fstream>
#include <sstream>

#include "CelestialBody.hpp"

using namespace std;
namespace nb
{
    extern sf::RenderWindow *windowPtr;
}

CelestialBody::CelestialBody(double xP, double yP, double xV, double yV, double m, string filename)
{
    xPos = xP;
    yPos = yP;
    xVel = xV;
    yVel = yV;
    mass = m;

    if (!img.loadFromFile(filename))
    {
        cout << "Problem in loading CelestialBody: " << filename << endl;
    }
}

CelestialBody::CelestialBody(string s)
{
    std::vector<string> sVec = splitString(s);

    double *temp[] = {&xPos, &yPos, &xVel, &yVel, &mass};
    int index = 0;
    for (string s : sVec)
    {
        if (index > 4)
        {
            file = s;
        }
        else
        {
            istringstream ss(s);
            double f;
            ss >> f;
            //cout << f << endl;
            *temp[index] = strtod(s.c_str(), NULL);
            index++;
        }
    }

    if (!img.loadFromFile("./nbody/" + file))
    {
        cout << "Problem in loading CelestialBody: " << file << "\n There may be graphic issues present" << endl;
    }
}

void CelestialBody::calcForces(std::vector<CelestialBody> *v, int dT)
{
    double dx, dy, d, r, F;
    for (CelestialBody &cb : *v)
    {
        if (!(cb.getID() == ID))
        {
            dx = (cb.getXPosition()-getXPosition());
            dy = (cb.getYPosition()-getYPosition());


            d = ((dx*dx)+(dy*dy));
            r = sqrt(d);
            F = (G *(mass * cb.getMass()) / pow(r, 2));

            xForce += ((F * (dx / r)));
            yForce += ((F * (dy / r)));

        }
    }
    double Vx = (getXVelocity()+(dT*(xForce/mass)));
    double Vy = (getYVelocity()+(dT*(yForce/mass)));
    //cout << " Vy: " << Vy << " Vx: " << Vx << endl;
    setXVelocity(Vx);
    setYVelocity(Vy);
    //cout << "  " << dT*(yForce/mass) << "  " << dT*(xForce/mass) << endl;
    xForce = 0;
    yForce = 0;
}


void CelestialBody::calcPos(int dT){ // dT = delta time
    double px = getXPosition();  // px = X position
    double py = getYPosition();  // py = Y position
    px = px + (dT*getXVelocity());
    py = py + (dT*getYVelocity());
    this->setXPosition(px);
    this->setYPosition(py);
}

// xO - x offset, yO - y offset (both for drawing)
void CelestialBody::stepPos(int xO, int yO)
{
    double cX = (xVel / uScale);
    double cY = (yVel / uScale);
    spriteRef().setPosition((getXPosition()/uScale)+xO,(getYPosition()/uScale)+yO);
}

void CelestialBody::setSpec(sf::Image t)
{
    tex.loadFromImage(t);
    sprite.setTexture(tex);
    //sprite.setPosition(xPos,yPos);
}

std::vector<string> CelestialBody::splitString(string s)
{
    std::vector<string> v;

    string word = "";
    for (char x : s)
    {
        //cout << x;
        if (x == 32)
        {
            v.push_back(word);
            //cout << word << endl;
            word = "";
        }
        else
        {
            word = word + x;
        }
    }

    return v;
}

