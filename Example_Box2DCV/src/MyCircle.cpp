#include "MyCircle.hpp"

MyCircle::MyCircle() {
    setup();
}

void MyCircle::setup() {
    color.r = ofRandom(20, 100);
    color.g = ofRandom(60, 150);
    color.b = ofRandom(200, 255);
    
    colorRim = color;
    colorRim.setHueAngle(colorRim.getHueAngle() + ofRandom(-0.2, 0.2));
}

void MyCircle::draw() {
    float radius = getRadius();
    ofPoint position = getPosition();
    
    ofFill();
    ofSetColor(colorRim, 100);
    ofDrawCircle(position.x, position.y, radius * 1.2);
    
    ofSetColor(color, 150);
    ofDrawCircle(position.x, position.y, radius * 0.8);
}
