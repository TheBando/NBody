#ifndef _CelestialBody
#define _CelestialBody

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <math.h>

using namespace std;

class CelestialBody : sf::Drawable
{
public:
    CelestialBody(double xP, double yP, double xV, double yV, double m, string filename);
    CelestialBody(string filename);

    std::vector<string> splitString(string s);

    sf::Sprite& spriteRef() {return sprite;}

    double& getForceX(){return xForce;}

    void setSpec(sf::Image t);
    void resetPos(){this->getSprite().setPosition(xPos,yPos);}

    void updateSpritePos(float fx, float fy, sf::Sprite &sp){
        sp.setPosition(fx,fy);
    }
    sf::Image getImage() { return img; }
    void setImage(sf::Image im) { img = im; }

    double getXPosition() { return xPos; }
    void setXPosition(double x) { xPos = x; }

    double getYPosition() { return yPos; }
    void setYPosition(double y) { yPos = y; }

    double getXVelocity() { return xVel; }
    void setXVelocity(double x) { xVel = x; }

    double getYVelocity() { return yVel; }
    void setYVelocity(double y) { yVel = y; }

    double getMass() { return mass; }
    void setMass(double m) { mass = m; }

    string getFilename(){return file;}
    void setFilename(string s){file=s;}

    sf::Texture getTexture() { return tex; }
    void setTexture(sf::Texture t) { tex = t; }

    sf::Sprite getSprite() { return sprite; }
    void setSprite(sf::Sprite s) { sprite = s; }

    int getID(){return ID;}
    void setID(int i){ID = i;}

    double getXForce(){return xForce;}
    double getYForce(){return yForce;}

    void calcForces(std::vector<CelestialBody> *v, int dT);
    void calcPos(int dT);
    void stepPos(int xO = 0, int yO=0);

    double getScale(){return uScale;}
    void setScale(double d){uScale = d;}

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {  
        states.texture = &tex;
        target.draw(sprite, states);
    }
    // ID
    int ID;

    //info
    double xPos, yPos;
    double xVel, yVel;
    double mass;

    double uScale = 1.0;

    //forces
    double xForce, yForce;
    double G = 6.67e-11;
    //default val for file, to prevent crash... didnt work.
    string file;
    sf::Image img;
    sf::Texture tex;
    sf::Sprite sprite;
};

#endif