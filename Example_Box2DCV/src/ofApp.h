#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "MyCircle.h"
#include "ColourTracker.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button) override;
    void mouseDragged(int x, int y, int button) override;
    
    ofxBox2d box2d;
    vector<shared_ptr<ofxBox2dCircle>> circles;
    shared_ptr<ofxBox2dCircle> myCircle;
    
    ColourTracker tracker;
};
