#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class MyCircle : public ofxBox2dCircle {
public:
    MyCircle();
    
    void setup();
    void draw();
    
    ofColor color;
    ofColor colorRim;
};
