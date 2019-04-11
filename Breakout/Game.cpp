//
//  Game.cpp
//  Breakout
//
//  Created by Suliman Alsaid on 4/10/19.
//  Copyright © 2019 Suliman Alsaid. All rights reserved.
//

#include "Game.hpp"
#include <iostream>

const float stot = 0.707;
bool run = true;

Game::Game(): window(sf::VideoMode(WIDTH, HEIGHT), "Breakout") {
    window.setFramerateLimit(60);
    int widthInc = 128;
    int heightInc = 50;
    sf::RectangleShape placeHolder;
    for(int i = 0; i < WIDTH/widthInc; i++) {
        for(int j = 0; j < 200/heightInc; j++) {
            placeHolder.setSize({static_cast<float>(widthInc), static_cast<float>(heightInc)});
            placeHolder.setPosition(i*widthInc, j*heightInc);
            placeHolder.setFillColor(sf::Color::Green);
            placeHolder.setOutlineColor(sf::Color::Black);
            placeHolder.setOutlineThickness(1);
            rects.push_back(placeHolder);
        }
    }
    
    paddle.setSize({static_cast<float>(widthInc), static_cast<float>(heightInc)});
    paddle.setPosition(640/2 - 64, 450);
    paddle.setFillColor(sf::Color::Green);
    
    ball.setRadius(10);
    ball.setOrigin(10, 10);
    ball.setPosition(640/2, 480/2);
    ball.setFillColor(sf::Color::White);
    ballVelocity = {-5*stot, 5*stot};
    left = false;
    right = false;
    
}

void Game::play() {
    
    
    
    while (run) {
        
        input();
        update();
        draw();
    }
    
}

void Game::draw() {
    window.clear();
    for(sf::RectangleShape& rect : rects) {
        window.draw(rect);
    }
    window.draw(paddle);
    window.draw(ball);
    window.display();
}

void Game::input() {
    sf::Event e;
    while(window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            run = false;
        }
        else if(e.type == sf::Event::KeyPressed) {
            if(e.key.code == sf::Keyboard::Left)
                left = true;
            else if (e.key.code == sf::Keyboard::Right)
                right = true;
            
        } else if (e.type == sf::Event::KeyReleased) {
            if(e.key.code == sf::Keyboard::Left)
                left = false;
            else if (e.key.code == sf::Keyboard::Right)
                right = false;
        }
        
        
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x - 64 > 0)
//        {
//            paddle.move(-20, 0);
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x + 64 < 640)
//        {
//            paddle.move(+5, 0);
//        }
        
    }
    
}


void Game::update() {
    ball.move(ballVelocity);
    
    if(ball.getPosition().y > 480 ) {
        run = false;
    }
    if(ball.getPosition().x -10 <= 0 || ball.getPosition().x +10 >= 640)
        ballVelocity.x *=  -1;
    if(ball.getPosition().y -10 <= 0 ) {
        ballVelocity.y *= -1;
    }
    
    collision();
    
    
    
    
    if(left && paddle.getPosition().x  > 0) {
        if(paddle.getPosition().x - 5 < 0)
            paddle.move(0-paddle.getPosition().x, 0);
        else
            paddle.move(-10, 0);
        
        
    }
    else if(right && paddle.getPosition().x +64 < 640) {
        if(paddle.getPosition().x + 128 + 10 > 640)
            paddle.move(640-paddle.getPosition().x-128, 0);
        else
            paddle.move(10, 0);
        
        
    }
    
    
}

struct Point {
    float x;
    float y;
};


bool Game::topHit(sf::RectangleShape rec) {

    if(ball.getPosition().y+10 >= rec.getPosition().y && ball.getPosition().x + 10 > rec.getPosition().x && ball.getPosition().x - 10 < rec.getPosition().x + 128) {
        ballVelocity.y = -5*stot;
        return true;
    }
    
    return false;
}

bool Game::bottomHit(sf::RectangleShape rec) {
    if(ball.getPosition().y - 10 <= rec.getPosition().y+50 && ball.getPosition().x + 10 > rec.getPosition().x && ball.getPosition().x - 10 < rec.getPosition().x + 128) {
        ballVelocity.y = 5*stot;
        std::cout << "bottom\n";
        return true;
    }
    
    return false;
}

bool Game::leftHit(sf::RectangleShape rec) {
    return false;
}

bool Game::rightHit(sf::RectangleShape rec) {
    return false;
}

void Game::collision() {
    Point ballp1 = {ball.getPosition().x -10, ball.getPosition().y -10};
    Point ballp2 = {ball.getPosition().x +10, ball.getPosition().y +10};
    
    topHit(paddle);
    
    
    if(ball.getPosition().y - 10 <= 200) {
        for(int i = 0; i < rects.size(); i++) {
            if(topHit(rects[i]) || bottomHit(rects[i]) || leftHit(rects[i]) || rightHit(rects[i])) {
                std::cout << "Erasing element " << i << "\n";
                rects.erase(rects.begin() + i);
            }
            
        }
    }
    
   
    

}
