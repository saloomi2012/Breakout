//
//  Game.hpp
//  Breakout
//
//  Created by Suliman Alsaid on 4/10/19.
//  Copyright © 2019 Suliman Alsaid. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

const int WIDTH = 640;
const int HEIGHT = 480;



class Game {
    void input();
    void draw();
    void update();
    void collision();
    bool bottomHit(sf::RectangleShape rec);
    bool topHit(sf::RectangleShape rec);
    bool leftHit(sf::RectangleShape rec);
    bool rightHit(sf::RectangleShape rec);
    
    
    sf::RenderWindow window;
    std::vector<sf::RectangleShape> rects;
    sf::RectangleShape paddle;
    sf::CircleShape ball;
    sf::Vector2f ballVelocity;
    bool left;
    bool right;
    
public:
    Game();
    void play();
    
};
#endif /* Game_hpp */
