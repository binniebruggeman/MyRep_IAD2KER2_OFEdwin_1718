#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(ofColor::black);
    ofSetCircleResolution(30);
}

void ofApp::update() {
    paddleY = MIN(MAX(mouseY - PADDLE_HEIGHT / 2, 0), ofGetHeight() - PADDLE_HEIGHT);
    bool wasReset = ball.update(paddleY);
    if (wasReset) {
        missedCount++;
    }
}

void ofApp::draw() {
    ball.draw();
    
    ofDrawRectangle(ofGetWidth() - PADDLE_WIDTH,
                    paddleY,
                    PADDLE_WIDTH, PADDLE_HEIGHT);
    
    ofDrawBitmapString("Missed: " + ofToString(missedCount), 10, 10);
}

void ofApp::keyPressed(int key) {
    ball.reset();
}
