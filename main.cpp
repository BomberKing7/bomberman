#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// fixed
// bomb moving conditions
// now it will never stop you at a bomb but in perfect cases
// fire spredding
// some conditions were wrong and fixed
// now program walls to expolde a littlebit better
// then program one monster and let him be simple
//    fix the music system
// program the superman power
// program the bomb controlling if you have new atari hand
// program the bomb controlling and you're done
using namespace sf;
using namespace std;
int gi(double n)
{
    int result;
    if (n >= 0 || (int)n == n)
    {
        result = (int)(n);
    }
    else
    {
        n = -n;
        result = -(int)(n + 1);
    }
    return result;
}
int k(double n, double r = 9)
{
    double t = n / r;
    return gi(t);
}
double s(double n, double r = 9)
{
    double s = n - r * k(n, r);
    return s;
}
int getscale(int a, int l)
{
    int ss = s(a, l), kk = (int)(a / l);
    return ss + 1 + (kk + 1) * (l + 2);
}

int main()
{
    srand(time(NULL));
    Color greencolor(56, 135, 0);
    int typesallowed = 5;
    Music main2, main1, winning, loosing;
    int movesoundtimer = 0;
    SoundBuffer getb, effectbuf[6];
    Sound sound1, effect[6];
    ///////  power ups
    int fire = 4, numberOfBombs = 3, speed = 2;
    bool ghostpower = 0, fireResistance = 1, movingThroughbombs = 0, bombscontrol = 1;
    bool superman = 0;
    ///////
    int vect = 0, z;
    int x = 700, y = 260, l = x / 20, h = y / 20, space = l * h, space2 = (l - 2) * (h - 2);
    int tectdiv = 2, tectdiv2 = 2, tectdiv3 = 5, tectdiv4 = 3, tectdiv5 = 2, tectdiv6 = 6;
    int windowx = x + 40, windowy = y + 40;
    ;
    bool breakwall[l][h] = {0};
    bool cwall[l][h] = {0};
    bool cbwall[6][space] = {0};

    int bombsaver[numberOfBombs];

    int x1 = 0, y1 = 0;
    int x2 = 10, y2 = 10;
    int x3[4] = {0}, y3[4] = {0};
    int realx = 0, realy = 0;
    int bombmovinglimit = 15; // for blocking moving through bombs
    x3[0] = bombmovinglimit;
    y3[0] = bombmovinglimit;
    x3[1] = 20 - bombmovinglimit;
    y3[1] = bombmovinglimit;
    x3[2] = bombmovinglimit;
    y3[2] = 20 - bombmovinglimit;
    x3[3] = 20 - bombmovinglimit;
    y3[3] = 20 - bombmovinglimit;

    bool rightwallcondition, leftwallcondition, upwallcondition, downwallcondition; // main movements

    main2.openFromFile("music/mainwin.ogg");
    main2.setLoop(1);
    main1.openFromFile("music/main1.ogg");
    main1.setLoop(1);
    winning.openFromFile("music/lvlcompleted.ogg");
    loosing.openFromFile("music/justdied.ogg");
    sound1.setVolume(5);
    getb.loadFromFile("music/bombex.ogg");
    effectbuf[0].loadFromFile("music/walk1.wav");
    effectbuf[1].loadFromFile("music/walk2.wav");
    effectbuf[2].loadFromFile("music/dropbomb.wav");
    effectbuf[3].loadFromFile("music/death.wav");
    effectbuf[4].loadFromFile("music/powertaken.wav");
    effectbuf[5].loadFromFile("music/alltaken.wav");
    for (int i = 0; i < 6; i++)
    {
        effect[i].setBuffer(effectbuf[i]);
    }
    sound1.setBuffer(getb);

    for (int i = 0; i < space; i++)
    {
        cbwall[0][i] = 1;
    } // set cb first wall changes texture

    bool ifdead = 0;
    int waittodie = 0;
    bool ifwin = 0;
    bool deathtext[5] = {0};
    deathtext[0] = 1;
    int set[4];
    long int ct = 0;
    int wallornot;
    int wallSets = 0;
    int wall_dev_int[space] = {0};

    int firestays = 16;
    bool stopwhenblocked[4] = {0};
    int firechange[4]; // the length
    firechange[0] = 4;
    firechange[1] = 3;
    firechange[2] = 2;
    firechange[3] = 1;
    int deathtimer = 0;
    int forfirespredding[space2] = {0};

    int bombtimtToExplode = 100;
    int timer[numberOfBombs] = {0};
    int bombsUsed = 0;
    bool ifbomb2[(l - 2) * (h - 2)] = {0};
    int chbomb[(h - 2) * (l - 2)] = {0}, chbomblimit = 7; // for bomb changing

    bool downchange[2] = {0};
    bool upchange[2] = {0};
    bool rightchange[2] = {0};
    bool leftchange[2] = {0};
    int bombtimer[(l - 2) * (h - 2)] = {0};
    int allowed[4] = {0};
    bool bombbolien[4][space2] = {0};
    for (int i = 0; i < space2; i++)
    {
        bombbolien[0][i] = 1;
    }

    int firetimer[space2] = {0};
    int firetaken = 1;
    bool firelimit[4][(l - 2) * (h - 2)] = {1};

    RenderWindow window(VideoMode(windowx, windowy), "Bomber Man");
    window.setFramerateLimit(30); // Add this line

    Texture unbreakablewall, breakablewall, way, bombtext, bombertexture, hfire, vfire, door, powerups, monstert;
    bool powerbool[space2] = {0};
    int powertype[space2] = {0};
    int doorornot = 0;
    int setpower = 10;
    int powerornot = 0;
    int setdoor = 0;
    bool doorbool[(l - 2) * (h - 2)] = {0};

    Image bomberimage, fireim, fireim2, bombim;
    bomberimage.loadFromFile("images/bomberall.png");
    bomberimage.createMaskFromColor(greencolor);

    monstert.loadFromFile("images/monstertext.png");
    powerups.loadFromFile("images/NES - Bomberman - Items.png");
    door.loadFromFile("images/door.png");

    bombim.loadFromFile("images/bomball.png");
    bombim.createMaskFromColor(greencolor);
    bombtext.loadFromImage(bombim);
    bombertexture.loadFromImage(bomberimage);

    fireim.loadFromFile("images/fireallhorizintal.png");
    fireim.createMaskFromColor(greencolor);
    hfire.loadFromImage(fireim);
    fireim2.loadFromFile("images/fireallvertical.png");
    fireim2.createMaskFromColor(greencolor);
    vfire.loadFromImage(fireim2);

    Image bawall;
    bawall.loadFromFile("images/wallchanging.png");
    bawall.createMaskFromColor(greencolor);
    breakablewall.loadFromImage(bawall);
    unbreakablewall.loadFromFile("images/unbreakablewallOriginal.png");
    way.loadFromFile("images/greenway.png");

    RectangleShape cell[space], cell2[space], cube(sf::Vector2f(20, 20)), bomb[(l - 2) * (h - 2)], bomb1[(l - 2) * (h - 2)], bomb2[(l - 2) * (h - 2)], Hfire[(l - 2) * (h - 2)], Vfire[(l - 2) * (h - 2)], Hfire1[(l - 2) * (h - 2)], Hfire3[(l - 2) * (h - 2)], Vfire2[(l - 2) * (h - 2)], Vfire4[(l - 2) * (h - 2)], Mfire[(l - 2) * (h - 2)], doorrect[space2], fireadd[space2];
    RectangleShape background[(h + 2) * (l + 2)];

    Sprite bomber(bombertexture);
    bomber.setScale(Vector2f(1.7, 1.2));
    for (int i = 0, k = 0, k1 = 0; i < (h + 2) * (l + 2); i++)
    {
        background[i] = cube;
        background[i].setTexture(&way);
        background[i].move(k * 20, k1 * 20);
        k++;
        if (k % (l + 2) == 0)
        {
            k = 0;
            k1++;
        }
    }

    for (int i = 0, k1 = 0, k2 = 0; i < space2; i++)
    { // setting textures
        bomb[i] = cube;
        bomb[i].move(40, 40);
        bomb[i].setTexture(&bombtext);
        bomb[i].move(k1, k2);
        bomb[i].setTextureRect(sf::IntRect(0, 0, 17, 16));
        bomb1[i] = cube;
        bomb1[i].move(40, 40);
        bomb1[i].setTexture(&bombtext);
        bomb1[i].move(k1, k2);
        bomb1[i].setTextureRect(sf::IntRect(17, 0, 17, 16));
        bomb2[i] = cube;
        bomb2[i].move(40, 40);
        bomb2[i].setTexture(&bombtext);
        bomb2[i].move(k1, k2);
        bomb2[i].setTextureRect(sf::IntRect(34, 0, 17, 16));
        Hfire[i] = cube;
        Hfire[i].move(40, 40);
        Hfire[i].setTexture(&hfire);
        Hfire[i].move(k1, k2);
        Hfire[i].setTextureRect(sf::IntRect(10, 1, 17, 14));
        Hfire1[i] = cube;
        Hfire1[i].move(40, 40);
        Hfire1[i].setTexture(&hfire);
        Hfire1[i].move(k1, k2);
        Hfire1[i].setTextureRect(sf::IntRect(0, 1, 17, 14));
        Hfire3[i] = cube;
        Hfire3[i].move(40, 40);
        Hfire3[i].setTexture(&hfire);
        Hfire3[i].move(k1, k2);
        Hfire3[i].setTextureRect(sf::IntRect(60, 1, 17, 14));
        Mfire[i] = cube;
        Mfire[i].move(40, 40);
        Mfire[i].setTexture(&hfire);
        Mfire[i].move(k1, k2);
        Mfire[i].setTextureRect(sf::IntRect(31, 1, 17, 14));
        Vfire[i] = cube;
        Vfire[i].move(40, 40);
        Vfire[i].setTexture(&vfire);
        Vfire[i].move(k1, k2);
        Vfire[i].setTextureRect(sf::IntRect(2, 7, 16, 14));
        Vfire2[i] = cube;
        Vfire2[i].move(40, 40);
        Vfire2[i].setTexture(&vfire);
        Vfire2[i].move(k1, k2);
        Vfire2[i].setTextureRect(sf::IntRect(2, 2, 16, 14));
        Vfire4[i] = cube;
        Vfire4[i].move(40, 40);
        Vfire4[i].setTexture(&vfire);
        Vfire4[i].move(k1, k2);
        Vfire4[i].setTextureRect(sf::IntRect(2, 64, 16, 14));
        doorrect[i] = cube;
        doorrect[i].move(40, 40);
        doorrect[i].setTexture(&door);
        doorrect[i].move(k1, k2);

        fireadd[i] = cube;
        fireadd[i].move(40, 40);
        fireadd[i].setTexture(&powerups);
        fireadd[i].move(k1, k2);
        fireadd[i].setTextureRect(sf::IntRect(15, 0, 15, 16));
        k1 += 20;
        if (k1 == x - 40)
        {
            k1 = 0;
            k2 += 20;
        }

    } // end of setting textures
    for (int i = 0; i < space; i++)
    {
        cell[i] = cube;
    } // make them in cubic form
    for (float i = 0, j = 0, k = 0; i < space; i++)
    {
        cell[(int)i].move(j, k);
        cell[(int)i].move(20, 20);
        j += 20;
        if (j == x)
        {
            j = 0;
            k += 20;
        }
    } // moving each cell to her position
    // cells contains ways and unbreakable walls   that will be first drawn
    for (int i = 0; i < space; i++)
    {
        cell2[i] = cell[i];
    } // move each second cell to first cell position
    // second cells contains breakable walls
    for (int i = 0; i < space; i++)
    { // first setting
        if (i % l == 0 || i % l == l - 1 || i / l == 0 || i < l || i > (h - 1) * l || (i % 2 == 0 && (i / l) % 2 == 0))
        {
            cell[i].setTexture(&unbreakablewall);
            breakwall[(int)i % l][(int)i / l] = 0;
        }
        else
        {
            wallornot = rand() % 4;
            if (wallornot != 0 || i == l + 1 || i == 2 * l + 1 || i == l + 2)
            {
                cell[i].setTexture(&way);
            }
            else
            {
                breakwall[(int)i % l][(int)i / l] = 1;
                cell2[i].setTexture(&breakablewall);
                cell2[i].setTextureRect(IntRect(0, 0, 16, 16));
                cell[i].setTexture(&way);
                wallSets++;
            }
        }
    } // the end
    while (setdoor == 0 || setpower >0)
    {   //   here we set the door and the power randomly inside some wall
        // the power will be print before the wall so it won't be visible
        // other settings are about  giving some informations to deal with them and how do they work
        for (int i = 0; i < space2; i++)
        { // set the door
            doorornot = rand() % 17;
            if (doorornot == 7 && breakwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l] == 1 && setdoor == 0 && powerbool[i] == 0)
            {
                doorbool[i] = 1;
                setdoor = 1;
            }
        }
        for (int i = 0; i < space2; i++)
        { // set the power
            powerornot = rand() % 13;
            if (powerornot == 7 && powerbool[i] == 0&& breakwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l] == 1 && setpower >0 && doorbool[i] == 0 && powerbool[i] == 0)
            {
                powerbool[i] = 1;
                powertype[i] = rand()%8+1;
                setpower --;
            }
        }
    }
    bomber.move(40, 40); // move the bomber to his place
    bomber.setTextureRect(sf::IntRect(65, 0, 12, 16));
    ////////enemies////////
    // 0   // 16 //  32
    //  48 // 64 //  80

    Image eimage1, eimage2, eimage3, eimage4, eimage5, eimage6, eimage7, eimage8;
    Texture e1, e2, e3, e4, e5, e6, e7, e8;

    eimage1.loadFromFile("images/ballon.png");
    eimage1.createMaskFromColor(greencolor);
    e1.loadFromImage(eimage1);
    eimage2.loadFromFile("images/water.png");
    eimage2.createMaskFromColor(greencolor);
    e2.loadFromImage(eimage2);
    eimage3.loadFromFile("images/trumbell.png");
    eimage3.createMaskFromColor(greencolor);
    e3.loadFromImage(eimage3);
    eimage4.loadFromFile("images/coin.png");
    eimage4.createMaskFromColor(greencolor);
    e4.loadFromImage(eimage4);
    eimage5.loadFromFile("images/snake.png");
    eimage5.createMaskFromColor(greencolor);
    e5.loadFromImage(eimage5);
    eimage6.loadFromFile("images/slowghost.png");
    eimage6.createMaskFromColor(greencolor);
    e6.loadFromImage(eimage6);
    eimage7.loadFromFile("images/fastghost.png");
    eimage7.createMaskFromColor(greencolor);
    e7.loadFromImage(eimage7);
    eimage8.loadFromFile("images/mastercoin.png");
    eimage8.createMaskFromColor(greencolor);
    e8.loadFromImage(eimage8);

    int nom = 20;         // number of monsters    can  go to 1000  -_-
    int typem[nom] = {1}; // monster type  [ 1 ; 8 ]
    for (int i = 0; i < nom; i++)
    {
        typem[i] = rand() % (typesallowed + 1);
    } // set it randomly in range [ 1 ; typesallowed ]
    Sprite ballon[nom];
    int xm[nom] = {0}, ym[nom] = {0};
    int vectm[nom] = {0};    // sprites and how i moved them
    bool ifdeadm[nom] = {0}; // monsters are all alive -_-

    for (int i = 0; i < nom; i++)
    {
        while (typem[i] == 0)
        {
            typem[i] = rand() % (typesallowed + 1);
        } // this is important ( they don't have to get 0 )
        switch (typem[i])
        {
        case 1:
        {
            ballon[i].setTexture(e1);
            break;
        }
        case 2:
        {
            ballon[i].setTexture(e2);
            break;
        }
        case 3:
        {
            ballon[i].setTexture(e3);
            break;
        }
        case 4:
        {
            ballon[i].setTexture(e4);
            break;
        }
        case 5:
        {
            ballon[i].setTexture(e5);
            break;
        }
        case 6:
        {
            ballon[i].setTexture(e6);
            break;
        }
        case 7:
        {
            ballon[i].setTexture(e7);
            break;
        }
        case 8:
        {
            ballon[i].setTexture(e8);
            break;
        }
        default:;
        }
        ballon[i].setTextureRect(IntRect(48, 0, 15, 17));
        ballon[i].setScale(Vector2f(1.2, 1));
        ballon[i].move(40, 40);
        xm[i] = (rand() % (l - 2));
        ym[i] = (rand() % (h - 2)); // set random first positions in certain conditions
        while (xm[i] % 2 == 1 && ym[i] % 2 == 1 || breakwall[xm[i] + 1][ym[i] + 1] == 1 || (xm[i] < 5 && ym[i] < 5))
        {
            xm[i] = (rand() % (l - 2));
            ym[i] = (rand() % (h - 2));
        }
        xm[i] *= 20;
        ym[i] *= 20;
        vectm[i] = rand() % 5;
        ballon[i].move(xm[i], ym[i]);
    } // end for i

    bool all_monsters_taken = 1; // if all monsters are taken "dead"
    bool changem[nom][3] = {0};
    bool splitm[nom] = {0};
    int dm[nom] = {0};
    for (int i = 0; i < nom; i++)
    {
        changem[i][0] = 1;
    }
    int zm[nom];
    int deathtimerm[nom];
    for (int i = 0; i < nom; i++)
    {
        deathtimerm[i] = 200;
    }
    int speedm = 1;
    int gwalkm = 0;
    int demofollowhim;
    bool effect5played = 0;
    bool forpausingmain = 0;
    ///////////////////////
    main1.play();
    while (window.isOpen())
    { // here we go

        sf::Event eeee;
        while(window.pollEvent(eeee)){
            if(eeee.type==sf::Event::Closed){
                window.close();
            }
        }
        // pause
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (main1.getStatus() == main1.Playing)
            {
                main1.pause();
                forpausingmain = 0;
            }
            else
            {
                main2.pause();
                forpausingmain = 1;
            }
            while (!(Keyboard::isKeyPressed(Keyboard::S)))
            {
                if (eeee.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            if (forpausingmain == 0)
            {
                main1.play();
            }
            else
            {
                main2.play();
            }
        }
        all_monsters_taken = 1;
        for (int i = 0; i < nom; i++)
        {
            if (dm[i] % tectdiv3 == 0)
            {
                if (ifdeadm[i] == 0)
                {
                    if (typem[i] == 8)
                    {
                        if (vectm[i] == 3 || vectm[i] == 4)
                        {
                            if (changem[i][0] == 1)
                            {
                                changem[i][0] = 0;
                                ballon[i].setTextureRect(IntRect(0, 0, 15, 17));
                                changem[i][1] = 1;
                            }
                            else if (changem[i][1] == 1)
                            {
                                changem[i][1] = 0;
                                ballon[i].setTextureRect(IntRect(48, 0, 15, 17));
                                changem[i][2] = 1;
                            }
                            else if (changem[i][2] == 1)
                            {
                                changem[i][2] = 0;
                                ballon[i].setTextureRect(IntRect(32, 0, 15, 17));
                            }
                            else
                            {
                                changem[i][0] = 1;
                                ballon[i].setTextureRect(IntRect(16, 0, 15, 17));
                            }
                        }
                        else
                        {
                            if (changem[i][0] == 1)
                            {
                                changem[i][0] = 0;
                                ballon[i].setTextureRect(IntRect(0, 0, 15, 17));
                                changem[i][1] = 1;
                            }
                            else if (changem[i][1] == 1)
                            {
                                changem[i][1] = 0;
                                ballon[i].setTextureRect(IntRect(16, 0, 15, 17));
                                changem[i][2] = 1;
                            }
                            else if (changem[i][2] == 1)
                            {
                                changem[i][2] = 0;
                                ballon[i].setTextureRect(IntRect(32, 0, 15, 17));
                            }
                            else
                            {
                                changem[i][0] = 1;
                                ballon[i].setTextureRect(IntRect(48, 0, 15, 17));
                            }
                        }
                    }
                    else
                    {
                        if (vectm[i] == 3 || vectm[i] == 4)
                        {
                            if (changem[i][0] == 1)
                            {
                                changem[i][0] = 0;
                                ballon[i].setTextureRect(IntRect(0, 0, 15, 17));
                                changem[i][1] = 1;
                            }
                            else if (changem[i][1] == 1)
                            {
                                changem[i][1] = 0;
                                ballon[i].setTextureRect(IntRect(16, 0, 15, 17));
                                if (splitm[i] == 0)
                                {
                                    changem[i][2] = 1;
                                    splitm[i] = !splitm[i];
                                }
                                else
                                {
                                    changem[i][0] = 1;
                                    splitm[i] = !splitm[i];
                                }
                            }
                            else if (changem[i][2] == 1)
                            {
                                changem[i][2] = 0;
                                changem[i][1] = 1;
                                ballon[i].setTextureRect(IntRect(32, 0, 15, 17));
                            }
                        }
                        else
                        {
                            if (changem[i][0] == 1)
                            {
                                changem[i][0] = 0;
                                ballon[i].setTextureRect(IntRect(48, 0, 15, 17));
                                changem[i][1] = 1;
                            }
                            else if (changem[i][1] == 1)
                            {
                                changem[i][1] = 0;
                                ballon[i].setTextureRect(IntRect(64, 0, 15, 17));
                                if (splitm[i] == 0)
                                {
                                    changem[i][2] = 1;
                                    splitm[i] = !splitm[i];
                                }
                                else
                                {
                                    changem[i][0] = 1;
                                    splitm[i] = !splitm[i];
                                }
                            }
                            else if (changem[i][2] == 1)
                            {
                                changem[i][2] = 0;
                                changem[i][1] = 1;
                                ballon[i].setTextureRect(IntRect(80, 0, 15, 17));
                            }
                        }
                    }
                }
                else if (deathtimerm[i] > 0)
                {
                    if (deathtimerm[i] > 150)
                    {
                        ballon[i].setTextureRect(IntRect(96, 0, 15, 17));
                        for (int j = 0; j < 3; j++)
                        {
                            changem[i][j] = 0;
                        }
                        changem[i][0] = 1;
                    }
                    else
                    {
                        if (changem[i][0] == 1)
                        {
                            changem[i][0] = 0;
                            ballon[i].setTextureRect(IntRect(112, 0, 15, 17));
                            changem[i][1] = 1;
                        }
                        else if (changem[i][1] == 1)
                        {
                            changem[i][1] = 0;
                            ballon[i].setTextureRect(IntRect(128, 0, 15, 17));
                            changem[i][2] = 1;
                        }
                        else if (changem[i][2] == 1)
                        {
                            changem[i][2] = 0;
                            changem[i][1] = 1;
                            ballon[i].setTextureRect(IntRect(144, 0, 15, 17));
                            deathtimerm[i] = -1;
                        }
                    }
                    deathtimerm[i] -= 5;
                }
            }
            dm[i] = (dm[i] + 1) % tectdiv3;
            if ((s(xm[i], 40) < 2 || s(ym[i], 40) < 2) && (rand()) % 200 == 0)
            {
                vectm[i] = 0;
            }
            if (typem[i] != 6 || (gwalkm % tectdiv5 == 0))
            {
                if (ifdeadm[i] == 0)
                {
                    while (vectm[i] == 0)
                    {
                        vectm[i] = rand() % 5;
                    }
                    switch (typem[i])
                    {
                    case 1:
                    {
                        speedm = 1;
                        demofollowhim = 60;
                        break;
                    }
                    case 2:
                    {
                        speedm = 2;
                        demofollowhim = 40;
                        break;
                    }
                    case 3:
                    {
                        speedm = 2;
                        demofollowhim = 30;
                        break;
                    }
                    case 4:
                    {
                        speedm = 3;
                        demofollowhim = 2;
                        break;
                    }
                    case 5:
                    {
                        speedm = 4;
                        demofollowhim = 2;
                        break;
                    }
                    case 6:
                    {
                        speedm = 1;
                        demofollowhim = 5;
                        break;
                    }
                    case 7:
                    {
                        speedm = 1;
                        demofollowhim = 7;
                        break;
                    }
                    case 8:
                    {
                        speedm = 3;
                        demofollowhim = 2;
                        break;
                    }
                    default:;
                    }
                    // attack !!!!!!
                    if (1)
                    { // follow that bomber guys
                        if (y1 < ym[i] && x2 / 20 == (xm[i] + 10) / 20 && (s(xm[i], 40) < 4 || (s(xm[i], 40) < 24 && s(xm[i], 40) >= 20)) && ((rand()) % demofollowhim == 0))
                        {
                            vectm[i] = 2;
                        }
                        if (y1 > ym[i] && x2 / 20 == (xm[i] + 10) / 20 && (s(xm[i], 40) < 4 || (s(xm[i], 40) < 24 && s(xm[i], 40) >= 20)) && ((rand()) % demofollowhim == 0))
                        {
                            vectm[i] = 4;
                        }
                        if (x1 < xm[i] && y2 / 20 == (ym[i] + 10) / 20 && (s(ym[i], 40) < 4 || (s(ym[i], 40) < 24 && s(ym[i], 40) >= 20)) && ((rand()) % demofollowhim == 0))
                        {
                            vectm[i] = 1;
                        }
                        if (x1 > xm[i] && y2 / 20 == (ym[i] + 10) / 20 && (s(ym[i], 40) < 4 || (s(ym[i], 40) < 24 && s(ym[i], 40) >= 20)) && ((rand()) % demofollowhim == 0))
                        {
                            vectm[i] = 3;
                        }
                    }
                    switch (vectm[i])
                    {
                    case 1:
                    {
                        if ((xm[i] - 1) >= 0 && (breakwall[(xm[i] - 1) / 20 + 1][(ym[i]) / 20 + 1] != 1 || typem[i] == 6 || typem[i] == 7 || typem[i] == 8) && (s(ym[i], 40) < 4) && (ifbomb2[(((xm[i] - 1) / 20) + (l - 2) * (ym[i] / 20))] == 0))
                        {
                            ballon[i].move(-speedm, 0);
                            xm[i] -= speedm;
                        }
                        else
                        {
                            vectm[i] = 0;
                        }
                        break;
                    }
                    case 2:
                    {
                        if ((ym[i] - 1) >= 0 && (breakwall[xm[i] / 20 + 1][(ym[i] - 1) / 20 + 1] != 1 || typem[i] == 6 || typem[i] == 7 || typem[i] == 8) && (s(xm[i], 40) < 4) && (ifbomb2[((xm[i] / 20) + (l - 2) * ((ym[i] - 1) / 20))] == 0))
                        {
                            ballon[i].move(0, -speedm);
                            ym[i] -= speedm;
                        }
                        else
                        {
                            vectm[i] = 0;
                        }
                        break;
                    }
                    case 3:
                    {
                        if ((xm[i] + 1) <= (l - 3) * 20 && (breakwall[(xm[i] + 19) / 20 + 1][(ym[i]) / 20 + 1] != 1 || typem[i] == 6 || typem[i] == 7 || typem[i] == 8) && (s(ym[i], 40) < 4) && (ifbomb2[(((xm[i] + 19) / 20) + (l - 2) * (ym[i] / 20))] == 0))
                        {
                            ballon[i].move(speedm, 0);
                            xm[i] += speedm;
                        }
                        else
                        {
                            vectm[i] = 0;
                        }
                        break;
                    }
                    case 4:
                    {
                        if ((ym[i] + 1) <= (h - 3) * 20 && (breakwall[(xm[i]) / 20 + 1][(ym[i] + 19) / 20 + 1] != 1 || typem[i] == 6 || typem[i] == 7 || typem[i] == 8) && (s(xm[i], 40) < 4) && (ifbomb2[((xm[i] / 20) + (l - 2) * ((ym[i] + 19) / 20))] == 0))
                        {
                            ballon[i].move(0, speedm);
                            ym[i] += speedm;
                        }
                        else
                        {
                            vectm[i] = 0;
                        }
                        break;
                    }
                    default:;
                    }
                }
            }
            zm[i] = (((xm[i] + 10) / 20) + (l - 2) * ((ym[i] + 10) / 20));
            if (firetimer[zm[i]] > 0)
            {
                ifdeadm[i] = 1;
            }
            all_monsters_taken = all_monsters_taken && (ifdeadm[i] == 1);
        }
        gwalkm = (gwalkm + 1) % 50;
        for (int i = 0; i < nom; i++)
        {
            if (zm[i] == z && (ifdeadm[i] == 0) && (superman == 0))
            {
                ifdead = 1;
            }
        }
        if (all_monsters_taken == 1 && (effect5played == 0))
        {
            effect[5].play();
            effect5played = 1;
        }
        /////////////////////////////////////////////////  up side moving
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ifdead != 1 && ifwin != 1)
        {
            if (movesoundtimer % tectdiv6 == 0)
            {
                effect[1].play();
            }
            movesoundtimer = (movesoundtimer + 1) % tectdiv6;
            while (s(x1, 40) > 0 && s(x1, 40) <= 8)
            {
                if (1)
                {
                    bomber.move(-1, 0);
                    x1 -= 1;
                    x2 -= 1;
                    for (int i = 0; i < 4; i++)
                    {
                        x3[i] -= 1;
                    }
                }
            }
            while (s(x1, 40) >= 32)
            {
                if (1)
                {
                    bomber.move(1, 0);
                    x1 += 1;
                    x2 += 1;
                    for (int i = 0; i < 4; i++)
                    {
                        x3[i] += 1;
                    }
                }
            }
            ct = x1 + (x - 40) * y1;
            if (allowed[1] % tectdiv == 0)
            {
                if (upchange[0] == 0)
                {
                    upchange[0] = !upchange[0];
                    set[0] = 66;
                    set[1] = 16;
                    set[2] = 11;
                    set[3] = 16;
                }
                else
                {
                    upchange[0] = !upchange[0];
                    if (upchange[1] == 0)
                    {
                        set[0] = 49;
                        set[1] = 16;
                        set[2] = 11;
                        set[3] = 16;
                        upchange[1] = !upchange[1];
                    }
                    else
                    {
                        set[0] = 82;
                        set[1] = 16;
                        set[2] = 12;
                        set[3] = 16;
                        upchange[1] = !upchange[1];
                    }
                }
                bomber.setTextureRect(sf::IntRect(set[0], set[1], set[2], set[3]));
            }
            allowed[1]++;
            allowed[1] = allowed[1] % tectdiv;
            upwallcondition = 1;
            for (int i = 0; i < 2; i++)
            {
                upwallcondition = upwallcondition && (breakwall[(x1 / 20 + 1)][(y1 - i) / 20 + 1] != 1 || ghostpower == 1);
            }
            if (s(y1, 20) < 2)
            {
                if (y3[2] >= 20 && y3[3] >= 20)
                {
                    upwallcondition = upwallcondition && (ifbomb2[(int)((int)(x3[2] / 20) + (l - 2) * ((int)((y3[2]) / 20 - 1)))] != 1) && (ifbomb2[((int)(x3[3] / 20) + (l - 2) * (int)((y3[3]) / 20 - 1))] != 1) || movingThroughbombs && upwallcondition != 0;
                }
            }
            if (upwallcondition == 1)
            {
                vect = 2;
            }
            else
            {
                vect = 0;
            }
        }
        else
            ///////////////////////////////////////////////////
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ifdead != 1 && ifwin != 1)
            {
                if (movesoundtimer % tectdiv6 == 0)
                {
                    effect[1].play();
                }
                movesoundtimer = (movesoundtimer + 1) % tectdiv6;
                while (s(x1, 40) > 0 && s(x1, 40) <= 8)
                {
                    if (1)
                    {
                        bomber.move(-1, 0);
                        x1 -= 1;
                        x2 -= 1;
                        for (int i = 0; i < 4; i++)
                        {
                            x3[i] -= 1;
                        }
                    }
                }
                while (s(x1, 40) >= 32)
                {
                    if (1)
                    {
                        bomber.move(1, 0);
                        x1 += 1;
                        x2 += 1;
                        for (int i = 0; i < 4; i++)
                        {
                            x3[i] += 1;
                        }
                    }
                }
                ct = x1 + (x - 40) * y1;
                if (allowed[3] % tectdiv == 0)
                {
                    if (downchange[0] == 0)
                    {
                        downchange[0] = !downchange[0];
                        set[0] = 65;
                        set[1] = 0;
                        set[2] = 12;
                        set[3] = 16;
                    }
                    else
                    {
                        downchange[0] = !downchange[0];
                        if (downchange[1] == 0)
                        {
                            set[0] = 49;
                            set[1] = 0;
                            set[2] = 12;
                            set[3] = 16;
                            downchange[1] = !downchange[1];
                        }
                        else
                        {
                            set[0] = 81;
                            set[1] = 0;
                            set[2] = 12;
                            set[3] = 16;
                            downchange[1] = !downchange[1];
                        }
                    }
                    bomber.setTextureRect(sf::IntRect(set[0], set[1], set[2], set[3]));
                }
                allowed[3]++;
                allowed[3] = allowed[3] % tectdiv;
                downwallcondition = 1;
                for (int i = 0; i < 20; i++)
                {
                    downwallcondition = downwallcondition && (breakwall[x1 / 20 + 1][(y1 + i) / 20 + 1] != 1 || ghostpower == 1);
                }
                if (s(y1, 20) < 2)
                {
                    if (y3[0] <= y - 20 && y3[1] <= y - 20)
                    {
                        downwallcondition = downwallcondition && (ifbomb2[(int)((int)(x3[0] / 20) + (l - 2) * ((int)((y3[0]) / 20 + 1)))] != 1) && (ifbomb2[((int)(x3[1] / 20) + (l - 2) * (int)((y3[1]) / 20 + 1))] != 1) || movingThroughbombs && downwallcondition != 0;
                    }
                }
                if (downwallcondition == 1)
                {
                    vect = 4;
                }
                else
                {
                    vect = 0;
                }
            }
            else
                ////////////////////////////////////////////////////
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ifdead != 1 && ifwin != 1)
                {
                    if (movesoundtimer % tectdiv6 == 0)
                    {
                        effect[0].play();
                    }
                    movesoundtimer = (movesoundtimer + 1) % tectdiv6;
                    while (s(y1, 40) > 0 && s(y1, 40) <= 8)
                    {
                        if (1)
                        {
                            bomber.move(0, -1);
                            y1 -= 1;
                            y2 -= 1;
                            for (int i = 0; i < 4; i++)
                            {
                                y3[i] -= 1;
                            }
                        }
                    }
                    while (s(y1, 40) >= 32)
                    {
                        if (1)
                        {
                            bomber.move(0, 1);
                            y1 += 1;
                            y2 += 1;
                            for (int i = 0; i < 4; i++)
                            {
                                y3[i] += 1;
                            }
                        }
                    }
                    ct = x1 + (x - 40) * y1;
                    if (allowed[2] % tectdiv2 == 0)
                    {
                        if (rightchange[0] == 0)
                        {
                            rightchange[0] = !rightchange[0];
                            set[0] = 18;
                            set[1] = 16;
                            set[2] = 12;
                            set[3] = 16;
                        }
                        else
                        {
                            rightchange[0] = !rightchange[0];
                            if (rightchange[1] == 0)
                            {
                                set[0] = 2;
                                set[1] = 16;
                                set[2] = 12;
                                set[3] = 16;
                                rightchange[1] = !rightchange[1];
                            }
                            else
                            {
                                set[0] = 34;
                                set[1] = 17;
                                set[2] = 12;
                                set[3] = 15;
                                rightchange[1] = !rightchange[1];
                            }
                        }
                        bomber.setTextureRect(sf::IntRect(set[0], set[1], set[2], set[3]));
                    }
                    allowed[2]++;
                    allowed[2] = allowed[2] % tectdiv2;
                    rightwallcondition = 1;
                    for (int i = 0; i < 20; i++)
                    {
                        rightwallcondition = rightwallcondition && (breakwall[(x1 + i) / 20 + 1][y1 / 20 + 1] != 1 || ghostpower == 1);
                    }
                    if (s(x1, 20) < 2)
                    {
                        if (x3[0] <= x - 20 && x3[2] <= x - 20)
                        {
                            rightwallcondition = rightwallcondition && (ifbomb2[(int)((int)((x3[0]) / 20 + 1) + (l - 2) * ((int)(y3[0] / 20)))] != 1) && (ifbomb2[((int)((x3[2]) / 20 + 1) + (l - 2) * (int)(y3[2] / 20))] != 1) || (movingThroughbombs && rightwallcondition != 0);
                        }
                    }
                    if (rightwallcondition == 1)
                    {
                        vect = 3;
                    }
                    else
                    {
                        vect = 0;
                    }
                }
                else
                    ////////////////////////////////////////////////////
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ifdead != 1 && ifwin != 1)
                    {
                        if (movesoundtimer % tectdiv6 == 0)
                        {
                            effect[0].play();
                        }
                        movesoundtimer = (movesoundtimer + 1) % tectdiv6;
                        while (s(y1, 40) > 0 && s(y1, 40) <= 8)
                        {
                            if (1)
                            {
                                bomber.move(0, -1);
                                y1 -= 1;
                                y2 -= 1;
                                for (int i = 0; i < 4; i++)
                                {
                                    y3[i] -= 1;
                                }
                            }
                        }
                        while (s(y1, 40) >= 32)
                        {
                            if (1)
                            {
                                bomber.move(0, 1);
                                y1 += 1;
                                y2 += 1;
                                for (int i = 0; i < 4; i++)
                                {
                                    y3[i] += 1;
                                }
                            }
                        }
                        ct = x1 + (x - 40) * y1;
                        if (allowed[0] % tectdiv2 == 0)
                        {
                            if (leftchange[0] == 0)
                            {
                                leftchange[0] = !leftchange[0];
                                set[0] = 17;
                                set[1] = 0;
                                set[2] = 12;
                                set[3] = 16;
                            }
                            else
                            {
                                leftchange[0] = !leftchange[0];
                                if (leftchange[1] == 0)
                                {
                                    set[0] = 33;
                                    set[1] = 0;
                                    set[2] = 12;
                                    set[3] = 16;
                                    leftchange[1] = !leftchange[1];
                                }
                                else
                                {
                                    set[0] = 1;
                                    set[1] = 0;
                                    set[2] = 12;
                                    set[3] = 16;
                                    leftchange[1] = !leftchange[1];
                                }
                            }
                            bomber.setTextureRect(sf::IntRect(set[0], set[1], set[2], set[3]));
                        }
                        allowed[0]++;
                        allowed[0] = allowed[0] % tectdiv2;
                        leftwallcondition = 1;
                        for (int i = 0; i < 2; i++)
                        {
                            leftwallcondition = leftwallcondition && (breakwall[(x1 - i) / 20 + 1][y1 / 20 + 1] != 1 || ghostpower == 1);
                        }
                        if (s(x1, 20) < 2)
                        {
                            if (x3[1] >= 20 && x3[3] >= 20)
                            {
                                leftwallcondition = leftwallcondition && (ifbomb2[(int)((int)((x3[1]) / 20 - 1) + (l - 2) * ((int)(y3[1] / 20)))] != 1) && (ifbomb2[((int)((x3[3]) / 20 - 1) + (l - 2) * (int)(y3[3] / 20))] != 1) || movingThroughbombs && leftwallcondition != 0;
                            }
                        }
                        if (leftwallcondition == 1)
                        {
                            vect = 1;
                        }
                        else
                        {
                            vect = 0;
                        }
                    }
                    else if (1)
                    {
                        vect = 0;
                    }
        ////////////////////////////////////////////////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ifdead != 1 && ifwin != 1)
        {
            if (bombsUsed < numberOfBombs && doorbool[((x1 + 10) / 20) + (l - 2) * ((y1 + 10) / (20))] == 0 && ifbomb2[((x1 + 10) / 20) + (l - 2) * ((y1 + 10) / (20))] == 0 && breakwall[((x1 + 30) / 20)][((y1 + 30) / 20)] == 0)
            {
                effect[2].play();
                bombsaver[bombsUsed] = ((x1 + 10) / 20) + (l - 2) * ((y1 + 10) / (20));
                ifbomb2[((x1 + 10) / 20) + (l - 2) * ((y1 + 10) / (20))] = 1;
                bombtimer[((x1 + 10) / 20) + (l - 2) * ((y1 + 10) / (20))] = bombtimtToExplode;
                bombsUsed++;
            }
            else
            {
            }
        }

        ////////////////////////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && bombsUsed > 0 && (bombscontrol == 1))
        {
            for (int i = 0; i < numberOfBombs;)
            {
                if (bombtimer[bombsaver[i]] > 0)
                {
                    bombtimer[bombsaver[i]] = -5;
                    break;
                }
                else
                {
                    for (int j = i; j < numberOfBombs - 1; j++)
                    {
                        bombsaver[j] = bombsaver[j + 1];
                    }
                }
                i++;
            }
            // for(int i=0;i<numberOfBombs-1;i++){bombsaver[i]=bombsaver[i+1];}
        }
        // breakwall[getscale(z)%l+1][getscale(z)/l]
        switch (vect)
        {
        case 1:
        {
            if (x1 - speed >= 0 && s(y1, 40) == 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    bomber.move(-speed, 0);
                    x1 -= speed;
                    x2 -= speed;
                    for (int i = 0; i < 4; i++)
                    {
                        x3[i] -= speed;
                    }
                }
            }
            break;
        }
        case 3:
        {
            if (x1 + speed <= x - 60 && s(y1, 40) == 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    bomber.move(speed, 0);
                    x1 += speed;
                    x2 += speed;
                    for (int i = 0; i < 4; i++)
                    {
                        x3[i] += speed;
                    }
                }
            }
            break;
        }
        case 2:
        {
            if (y1 - speed >= 0 && s(x1, 40) == 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    bomber.move(0, -speed);
                    y1 -= speed;
                    y2 -= speed;
                    for (int i = 0; i < 4; i++)
                    {
                        y3[i] -= speed;
                    }
                }
            }
            break;
        }
        case 4:
        {
            if (y1 + speed <= y - 60 && s(x1, 40) == 0)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    bomber.move(0, speed);
                    y1 += speed;
                    y2 += speed;
                    for (int i = 0; i < 4; i++)
                    {
                        y3[i] += speed;
                    }
                }
            }
            break;
        }
        default:;
        }
        ct = x1 + (x - 40) * y1;
        /////moving monsters
        ////////////////////////////////////////////////
        realx = x2 / 20;
        realy = y2 / 20;
        z = realx + (l - 2) * realy;
        if (powerbool[z] == 1 && (breakwall[((x1 + 30) / 20)][((y1 + 30) / 20)] == 0))
        {
            effect[4].play();
            main2.play();
            main1.stop();
            powerbool[z] = 0;
            switch (powertype[z])
            {
            case 1:
            {
                fire++;
                break;
            }
            case 2:
            {
                numberOfBombs++;
                break;
            }
            case 3:
            {
                speed += 1;
                break;
            }
            case 4:
            {
                ghostpower = 1;
                break;
            }
            case 5:
            {
                bombscontrol = 1;
                break;
            }
            case 6:
            {
                movingThroughbombs = 1;
                break;
            }
            case 7:
            {
                fireResistance = 1;
                break;
            }
            case 8:
            {
                superman = 1;
                break;
            }
            default:;
            }
        }
        if (doorbool[z] == 1 && ifwin == 0 && (breakwall[((x1 + 30) / 20)][((y1 + 30) / 20)] == 0) && (all_monsters_taken == 1))
        {
            main1.stop();
            main2.stop();
            sound1.stop();
            ifwin = 1;
            winning.play();
            
        }
        int d1, d2, d3, d4;
        if (firetimer[x2 / 20 + (y2 / 20) * (l - 2)] > 1 && (fireResistance == 0) && (superman == 0) && ifdead == 0 && ifwin == 0)
        {
            ifdead = 1;
        }
        if (ifdead == 1)
        {
            d3 = 12;
            d4 = 16;
            main1.stop();
            main2.stop();
            sound1.stop();
            if (deathtimer % 7 == 0)
            {
                if (deathtext[0])
                {
                    effect[3].play();
                    d1 = 34;
                    d2 = 32;
                    deathtext[0] = 0;
                    deathtext[1] = 1;
                }
                else if (deathtext[1])
                {
                    d1 = 49;
                    d2 = 32;
                    deathtext[1] = 0;
                    deathtext[2] = 1;
                }
                else if (deathtext[2])
                {
                    d1 = 63;
                    d2 = 32;
                    deathtext[2] = 0;
                    deathtext[3] = 1;
                }
                else if (deathtext[3])
                {
                    d1 = 80;
                    d2 = 32;
                    deathtext[3] = 0;
                    deathtext[4] = 1;
                }
                else if (deathtext[4])
                {
                    d1 = 94;
                    d2 = 32;
                    deathtext[4] = 0;
                }
                else
                {
                    // bomber.setTexture(&way);
                    waittodie++;
                    if (waittodie == 10)
                    {
                        loosing.play();
                    }
                }
                bomber.setTextureRect(sf::IntRect(d1, d2, d3, d4));
            }
        }
        deathtimer++;
        deathtimer = deathtimer % 100;
        window.clear();
        for (int kk = 0; kk < (l + 2) * (h + 2); kk++)
        {
            window.draw(background[kk]);
        }
        for (int i = 0; i < space; i++)
        {
            window.draw(cell[i]);
        }
        for (int j = 0, ll = 0; ll < space2;)
        {
            if (1)
            {
                firelimit[j][ll] = 1;
            }
            j++;
            if (j == 4)
            {
                j = 0;
                ll++;
            }
        }
        for (int i = 0; i < space2; i++)
        {
            switch (forfirespredding[i])
            {
            case 1:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Hfire1[i].setTextureRect(sf::IntRect(1, 1, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Hfire1[i].setTextureRect(sf::IntRect(1, 17, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Hfire1[i].setTextureRect(sf::IntRect(1, 34, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Hfire1[i].setTextureRect(sf::IntRect(1, 47, 17, 14));
                    }
                    window.draw(Hfire1[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 2:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Vfire2[i].setTextureRect(sf::IntRect(2, 2, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Vfire2[i].setTextureRect(sf::IntRect(21, 2, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Vfire2[i].setTextureRect(sf::IntRect(58, 2, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Vfire2[i].setTextureRect(sf::IntRect(40, 6, 16, 14));
                    }
                    window.draw(Vfire2[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 3:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Hfire3[i].setTextureRect(sf::IntRect(60, 1, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Hfire3[i].setTextureRect(sf::IntRect(60, 17, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Hfire3[i].setTextureRect(sf::IntRect(60, 34, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Hfire3[i].setTextureRect(sf::IntRect(60, 47, 17, 14));
                    }
                    window.draw(Hfire3[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 4:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Vfire4[i].setTextureRect(sf::IntRect(2, 66, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Vfire4[i].setTextureRect(sf::IntRect(22, 66, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Vfire4[i].setTextureRect(sf::IntRect(58, 66, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Vfire4[i].setTextureRect(sf::IntRect(40, 63, 16, 14));
                    }
                    window.draw(Vfire4[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 5:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Hfire[i].setTextureRect(sf::IntRect(10, 1, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Hfire[i].setTextureRect(sf::IntRect(10, 17, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Hfire[i].setTextureRect(sf::IntRect(10, 34, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Hfire[i].setTextureRect(sf::IntRect(10, 47, 17, 14));
                    }
                    window.draw(Hfire[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 6:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Vfire[i].setTextureRect(sf::IntRect(2, 7, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Vfire[i].setTextureRect(sf::IntRect(21, 8, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Vfire[i].setTextureRect(sf::IntRect(58, 8, 16, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Vfire[i].setTextureRect(sf::IntRect(40, 8, 16, 14));
                    }
                    window.draw(Vfire[i]);
                    firetimer[i]--;
                }
                break;
            }
            case 7:
            {
                if (firetimer[i] > 0)
                {
                    if (firetimer[i] <= firestays && firetimer[i] >= firechange[0])
                    {
                        Mfire[i].setTextureRect(sf::IntRect(31, 1, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[0] && firetimer[i] >= firechange[1])
                    {
                        Mfire[i].setTextureRect(sf::IntRect(30, 17, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[1] && firetimer[i] >= firechange[2])
                    {
                        Mfire[i].setTextureRect(sf::IntRect(31, 35, 17, 14));
                    }
                    else if (firetimer[i] <= firechange[2] && firetimer[i] >= -1)
                    {
                        Mfire[i].setTextureRect(sf::IntRect(31, 48, 17, 14));
                    }
                    window.draw(Mfire[i]);
                    firetimer[i]--;
                }
                break;
            }
            default:;
            } // end of fire texture
            if (ifbomb2[i] == 1)
            {
                if (bombbolien[0][i] == 1)
                {
                    window.draw(bomb[i]);
                    if (chbomb[i] % chbomblimit == 0)
                    {
                        chbomb[i]++;
                        bombbolien[0][i] = 0;
                        bombbolien[1][i] = 1;
                    }
                }
                if (bombbolien[1][i] == 1)
                {
                    window.draw(bomb1[i]);
                    if (chbomb[i] % chbomblimit == 0)
                    {
                        chbomb[i]++;
                        if (bombbolien[3][i] == 0)
                        {
                            bombbolien[1][i] = 0;
                            bombbolien[2][i] = 1;
                            bombbolien[3][i] = 1;
                        }
                        else
                        {
                            bombbolien[1][i] = 0;
                            bombbolien[0][i] = 1;
                            bombbolien[3][i] = 0;
                        }
                    }
                }
                if (bombbolien[2][i] == 1)
                {
                    window.draw(bomb2[i]);
                    if (chbomb[i] % chbomblimit == 0)
                    {
                        chbomb[i]++;
                        bombbolien[2][i] = 0;
                        bombbolien[1][i] = 1;
                    }
                }
                chbomb[i] = chbomb[i] % chbomblimit;
                chbomb[i]++;
                if ((bombscontrol == 0))
                {
                    bombtimer[i]--;
                }
                if ((bombtimer[i] <= 0 || firetimer[i] > 0))
                {
                    ifbomb2[i] = 0;
                    if (sound1.getStatus() == sound1.Stopped && ifwin == 0)
                    {
                        sound1.play();
                    }
                    forfirespredding[i] = 7;
                    firetimer[i] = firestays;
                    bombsUsed--;
                    firetaken = 1;
                    for (int hh = 0; hh < 4; hh++)
                    {
                        stopwhenblocked[hh] = 0;
                    }
                    for (int k = 1; k <= fire; k++)
                    { // fix it for walls in the field
                        // right fire
                        if ((i + k) % (l - 2) == 0)
                        {
                            stopwhenblocked[0] = 1;
                        }
                        int bombebb = 40;
                        if ((i / (l - 2)) % 2 != 1 && (stopwhenblocked[0] == 0))
                        {
                            if (breakwall[getscale(i, l - 2) % l + k][getscale(i, l - 2) / l] == 1 && firelimit[0][i] && (getscale(i, l - 2) % l + k <= l) && ((i) % (l - 2) != l - 3))
                            {
                                stopwhenblocked[0] = 1;
                                cwall[getscale(i, l - 2) % l + k][getscale(i, l - 2) / l] = 1;
                                forfirespredding[i + k] = 3;
                                firetimer[i + k] = firestays;
                                firelimit[0][i] = 0;
                            }
                            else if (ifbomb2[i + k] == 1 && firelimit[0][i] && (i % (l - 2) != l - 3))
                            {
                                stopwhenblocked[0] = 1;
                                bombtimer[i + k] = bombebb;
                                forfirespredding[i + k] = 3;
                                firetimer[i + k] = firestays;
                                firelimit[0][i] = 0;
                            }
                            else if (k == fire && (i % (l - 2) != l - 3))
                            {
                                forfirespredding[i + k] = 3;
                                firetimer[i + k] = firestays;
                            }
                            else if (k != fire && (i % (l - 2) != l - 3))
                            {
                                forfirespredding[i + k] = 5;
                                firetimer[i + k] = firestays;
                            }
                        } // left
                        if ((i / (l - 2)) % 2 != 1 && (stopwhenblocked[1] == 0))
                        {
                            if (breakwall[getscale(i, l - 2) % l - k][getscale(i, l - 2) / l] != 0 && firelimit[1][i] && (getscale(i, l - 2) % l - k >= 0) && (i % (l - 2) != 0))
                            {
                                stopwhenblocked[1] = 1;
                                cwall[getscale(i, l - 2) % l - k][getscale(i, l - 2) / l] = 1;
                                forfirespredding[i - k] = 1;
                                firetimer[i - k] = firestays;
                                firelimit[1][i] = 0;
                            }
                            else if (ifbomb2[i - k] == 1 && firelimit[1][i] && (i % (l - 2) != 0))
                            {
                                stopwhenblocked[1] = 1;
                                bombtimer[i - k] = bombebb;
                                forfirespredding[i - k] = 1;
                                firetimer[i - k] = firestays;
                                firelimit[1][i] = 0;
                            }
                            else if (k == fire && (i % (l - 2) != 0))
                            {
                                forfirespredding[i - k] = 1;
                                firetimer[i - k] = firestays;
                            }
                            else if (k != fire && (i % (l - 2) != 0))
                            {
                                forfirespredding[i - k] = 5;
                                firetimer[i - k] = firestays;
                            }
                            if (s((i - k), (l - 2)) == 0)
                            {
                                stopwhenblocked[1] = 1;
                            }
                        } // down
                        if ((i % (l - 2)) % 2 != 1 && (stopwhenblocked[2] == 0))
                        {
                            if (breakwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l + k] == 1 && firelimit[2][i] && (getscale(i, l - 2) / l + k <= h) && (i / (l - 2) != h - 3))
                            {
                                stopwhenblocked[2] = 1;
                                cwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l + k] = 1;
                                forfirespredding[i + k * (l - 2)] = 4;
                                firetimer[i + k * (l - 2)] = firestays;
                                firelimit[2][i] = 0;
                            }
                            else if (ifbomb2[i + (l - 2) * k] == 1 && firelimit[2][i] && (i / (l - 2) != h - 3))
                            {
                                stopwhenblocked[2] = 1;
                                bombtimer[i + (l - 2) * k] = bombebb;
                                forfirespredding[i + k * (l - 2)] = 4;
                                firetimer[i + k * (l - 2)] = firestays;
                                firelimit[2][i] = 0;
                            }
                            else if (k == fire && (i / (l - 2) != h - 3))
                            {
                                forfirespredding[i + k * (l - 2)] = 4;
                                firetimer[i + k * (l - 2)] = firestays;
                            }
                            else if (k != fire && (i / (l - 2) != h - 3))
                            {
                                forfirespredding[i + k * (l - 2)] = 6;
                                firetimer[i + k * (l - 2)] = firestays;
                            }
                            if ((i + k * (l - 2)) / (l - 2) >= h - 3)
                            {
                                stopwhenblocked[2] = 1;
                            }
                        } // up
                        if ((i % (l - 2)) % 2 != 1 && (stopwhenblocked[3] == 0))
                        {
                            if (breakwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l - k] == 1 && firelimit[3][i] && (getscale(i, l - 2) / l - k >= 0) && (i % (l - 2) != 1))
                            {
                                stopwhenblocked[3] = 1;
                                cwall[getscale(i, l - 2) % l][getscale(i, l - 2) / l - k] = 1;
                                forfirespredding[i - k * (l - 2)] = 2;
                                firetimer[i - k * (l - 2)] = firestays;
                                firelimit[3][i] = 0;
                            }
                            else if (ifbomb2[i - (l - 2) * k] == 1 && firelimit[3][i] && (i / (l - 2) != 0))
                            {
                                stopwhenblocked[3] = 1;
                                bombtimer[i - (l - 2) * k] = bombebb;
                                forfirespredding[i - k * (l - 2)] = 2;
                                firetimer[i - k * (l - 2)] = firestays;
                                firelimit[3][i] = 0;
                            }
                            else if (k == fire && (i / (l - 2) != 0))
                            {
                                forfirespredding[i - k * (l - 2)] = 2;
                                firetimer[i - k * (l - 2)] = firestays;
                            }
                            else if (k != fire && (i / (l - 2) != 0))
                            {
                                forfirespredding[i - k * (l - 2)] = 6;
                                firetimer[i - k * (l - 2)] = firestays;
                            }
                            if ((i - k * (l - 2)) / (l - 2) <= 0)
                            {
                                stopwhenblocked[3] = 1;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < space2; i++)
        {
            if (doorbool[i] == 1)
            {
                window.draw(doorrect[i]);
            }
            if (powerbool[i] == 1)
            {
                switch (powertype[i])
                {
                case 1:
                {
                    fireadd[i].setTextureRect(sf::IntRect(15, 0, 15, 16));
                    break;
                }
                case 2:
                {
                    fireadd[i].setTextureRect(sf::IntRect(0, 0, 15, 16));
                    break;
                }
                case 3:
                {
                    fireadd[i].setTextureRect(sf::IntRect(31, 0, 15, 16));
                    break;
                }
                case 4:
                {
                    fireadd[i].setTextureRect(sf::IntRect(46, 0, 15, 16));
                    break;
                }
                case 5:
                {
                    fireadd[i].setTextureRect(sf::IntRect(62, 0, 15, 16));
                    break;
                }
                case 6:
                {
                    fireadd[i].setTextureRect(sf::IntRect(80, 0, 15, 16));
                    break;
                }
                case 7:
                {
                    fireadd[i].setTextureRect(sf::IntRect(96, 0, 15, 16));
                    break;
                }
                case 8:
                {
                    fireadd[i].setTextureRect(sf::IntRect(112, 0, 13, 16));
                    break;
                }
                default:;
                }
                window.draw(fireadd[i]);
            }
        }
        for (int i = 0; i < space; i++)
        {
            if (cwall[i % l][i / l] == 1)
            {
                if (wall_dev_int[i] % tectdiv4 == 0)
                {
                    if (cbwall[0][i] == 1)
                    {
                        cbwall[0][i] = 0;
                        cell2[i].setTextureRect(IntRect(16, 0, 16, 16));
                        cbwall[1][i] = 1;
                    }
                    else if (cbwall[1][i] == 1)
                    {
                        cbwall[1][i] = 0;
                        cell2[i].setTextureRect(IntRect(32, 0, 16, 16));
                        cbwall[2][i] = 1;
                    }
                    else if (cbwall[2][i] == 1)
                    {
                        cbwall[2][i] = 0;
                        cell2[i].setTextureRect(IntRect(48, 0, 16, 16));
                        cbwall[3][i] = 1;
                    }
                    else if (cbwall[3][i] == 1)
                    {
                        cbwall[3][i] = 0;
                        cell2[i].setTextureRect(IntRect(64, 0, 16, 16));
                        cbwall[4][i] = 1;
                    }
                    else if (cbwall[4][i] == 1)
                    {
                        cbwall[4][i] = 0;
                        cell2[i].setTextureRect(IntRect(80, 0, 16, 16));
                        cbwall[5][i] = 1;
                    }
                    else if (cbwall[5][i] == 1)
                    {
                        cbwall[5][i] = 0;
                        cell2[i].setTextureRect(IntRect(96, 0, 16, 16));
                    }
                    else
                    {
                        breakwall[i % l][i / l] = 0;
                        cwall[i % l][i / l] = 0;
                    }
                }
                wall_dev_int[i] = (wall_dev_int[i] + 1) % tectdiv4;
            }
            if (breakwall[i % l][i / l])
            {
                window.draw(cell2[i]);
            }
        }
        window.draw(bomber);
        for (int i = 0; i < nom; i++)
        {
            if (deathtimerm[i] > 0)
            {
                window.draw(ballon[i]);
            }
        }

        if (ifwin == 0 && waittodie < 10)
        {
            window.display();
        }
    }
}


//g++ main.cpp -o program -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./program