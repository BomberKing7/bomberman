#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class character
{public:
    character(int speed,int type=0);
    void setT(string a);
   // void print();
    int Type;
    int Speed;
    Texture t;
    //RectangleShape shape(sf::Vector2f(20,20));
     sf::RectangleShape s(sf::Vector2f(20.0f,20.0f));

    protected:

    private:
};

#endif // CHARACTER_H
