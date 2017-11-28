#pragma once

#include "ofMain.h"
#include "Ball.h"


class ofApp : public ofBaseApp {
    
public:
    void setup();
    
    void update();
    
    void draw();
    
    void keyPressed(int key);
    
    static const int PADDLE_WIDTH = 20;
    static const int PADDLE_HEIGHT = 250;
    
private:
    Ball ball;
    int missedCount;
    int paddleY;
};
