#include<iostream>
#include "SFML/Graphics.hpp"
#include"globals.h"
#include"ghost.h"
using namespace std;


int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(1920, 1080), "PacMan"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick2.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    sf::Texture pr;
    pr.loadFromFile("Portal R.png");
    sf::Sprite warpr;
    warpr.setTexture(pr);

    sf::Texture pl;
    pl.loadFromFile("Portal l.png");
    sf::Sprite warpl;
    warpl.setTexture(pl);

    //sf::Texture pacman;
    //pacman.loadFromFile("pacman.png");
    //sf::IntRect pac(0, 0, 70, 70);
    //sf::Sprite playerImg(pacman, pac);

    int map[30][24] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,
        1,0,1,1,1,0,1,1,0,1,0,0,0,0,1,1,1,0,1,1,0,1,0,1,
        3,0,1,0,0,0,1,0,0,0,0,1,1,0,1,0,0,0,0,1,0,1,0,2,
        1,0,1,0,1,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,0,0,1,
        1,1,0,0,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,0,0,1,0,1,
        3,0,0,1,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1,0,0,0,2,
        1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,0,1,1,1,0,1,1,1,
        1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,1,1,0,0,1,0,1,
        1,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,1,
        1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,1,0,1,0,1,
        1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,1,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    //player set up
    int xpos = 85;
    int ypos = 85;
    int vx = 0;
    int vy = 0;
    int radius = 35;
    sf::CircleShape dot(7);
    sf::CircleShape player(35);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    dot.setFillColor(sf::Color(0, 250, 100));
    ghost Blinky;
    Blinky.initGhost(400, 654, 1, 0, 1, 0);
    ghost Dami;
    Dami.initGhost(1205, 805, 1, 0, 1, 0);


    bool keys[] = { false, false, false, false };

    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

        }//end event loop---------------------------------------------------------------
           //move Mr. Pac
        if (keys[LEFT] == true)
            vx = -5;
        else if (keys[RIGHT] == true)
            vx = 5;
        else
            vx = 0;
        if (keys[DOWN] == true)
            vy = 5;
        else if (keys[UP] == true)
            vy = -5;
        else
            vy = 0;

        //right collision!
        if (vx > 0 &&
            ((map[(ypos + 5) / 80]
                 [(xpos + (radius * 2) + 5) / 80] == 1) ||
             (map[(ypos + (radius * 2) - 5) / 80]
                 [(xpos + (radius * 2) + 5) / 80] == 1)))
        {
                vx = 0;
        }
        //left collision
        else if (vx < 0 &&
            ((map[(ypos + 5) / 80]
                [(xpos - 5) / 80] == 1) ||
                (map[(ypos + (radius * 2) - 5) / 80]
                    [(xpos - 5) / 80] == 1)))

        {
            vx = 0;
        }
        //down collision
        if (vy > 0 &&
            ((map[(ypos + (radius * 2) + 5) / 80]
                 [(xpos) / 80] == 1) ||
             (map[(ypos + (radius * 2) + 5) / 80]
                 [(xpos + (radius * 2)) / 80] == 1))) {
            vy = 0;
        }
        //up collision
        else if (vy < 0 &&
            ((map[(ypos - 5) / 80]
                 [(xpos + 5) / 80] == 1) ||
             (map[(ypos - 5) / 80]
                 [(xpos + (radius * 2) - 4) / 80] == 1))) {
            vy = 0;
        }
        //update player position
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        //eating dot
        if (map[ypos / 80][xpos / 80] == 0)
            map[ypos / 80][xpos / 80] = -1;
        cout << xpos << " , " << ypos << endl;

        //warp zone
        if (xpos < -50 && ypos >= 240 && ypos < 300)
            xpos = 1840;
        else if (xpos < -50 && ypos >= 480 && ypos < 500)
            xpos = 1840;
        if (xpos > 1840 && ypos >= 240 && ypos < 300)
            xpos = 0;
        else if (xpos > 1840 && ypos >= 480 && ypos < 500)
            xpos = 0;
        
        Blinky.chase1(xpos, ypos, map);
        Dami.chase2(xpos, ypos, map);
        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (int rows = 0; rows < 30; rows++)
            for (int cols = 0; cols < 24; cols++) {
                
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 80+40, rows * 80+40);
                    screen.draw(dot);
                }
                if (map[rows][cols] == 2) {
                    warpr.setPosition(cols * 80, rows * 80);
                    screen.draw(warpr);
                }
                if (map[rows][cols] == 3) {
                    warpl.setPosition(cols * 80, rows * 80);
                    screen.draw(warpl);
                }
                
            }
        screen.draw(player);
        screen.draw(dot);
        Blinky.drawGhost(screen);
        Dami.drawGhost(screen);
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "Thanks for playing!" << endl;
} //end of main
