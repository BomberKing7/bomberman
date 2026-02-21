#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class field
{
    public:
        field(int length,int hight,int scale=20);


         int l,h,x,y;
        const static int space;
        static int space2;

        int  cell[];




        Texture ft;
    protected:

    private:
};

#endif // FIELD_H
