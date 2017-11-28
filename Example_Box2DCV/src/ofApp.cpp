#include "ofApp.h"


void ofApp::setup() {
    ofSetFrameRate(30);
    
    ofBackground(ofColor::black);
    
    tracker.setup();
    
    box2d.init();
    box2d.setFPS(30);
    
    box2d.createGround();
    box2d.createBounds();
    
    box2d.registerGrabbing();
    
    myCircle = shared_ptr<ofxBox2dCircle>(new MyCircle());
    myCircle->density = 0.f;
    myCircle->setup(box2d.getWorld(), 0, 100, 100);
}

void ofApp::update() {
    tracker.update();
    if (tracker.haveBlobs()) {
        ofPoint blobPos = tracker.getCentroid();
        int scaledX = blobPos.x * ofGetWidth() / GRABBER_WIDTH;
        int scaledY = blobPos.y * ofGetHeight() / GRABBER_HEIGHT;
        myCircle->setPosition(scaledX, scaledY);
    }
    
    box2d.update();
}

void ofApp::draw() {
    tracker.draw();
    
    if (tracker.haveBlobs()) {
        myCircle->draw();
    }
    
    for (auto& circle : circles) {
        circle->draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == ' ') {
        auto circle = shared_ptr<ofxBox2dCircle>(new MyCircle());
        circle->setPhysics(3.0, 0.5, 0.1);
        circle->setup(box2d.getWorld(), mouseX, mouseY, ofRandom(20, 60));
        circle->addForce(ofVec2f(ofRandom(-10, 10), ofRandom(-20, 0)), 100);
        circles.push_back(circle);
    } else if (key == OF_KEY_RETURN) {
        box2d.setGravity(0, 0);
    } else if (key == OF_KEY_UP) {
        box2d.setGravity(0, -5);
    } else if (key == OF_KEY_DOWN) {
        box2d.setGravity(0, 5);
    } else if (key == 's') {
        tracker.toggleSetup();
    } else if (key == 'b') {
        tracker.toggleBlobs();
    }
}

void ofApp::mouseDragged(int x, int y, int button) {
    if (tracker.haveBlobs() && button == OF_MOUSE_BUTTON_LEFT) {
        myCircle->setPosition(x, y);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    if (tracker.haveBlobs() && button == OF_MOUSE_BUTTON_LEFT) {
        myCircle->setPosition(x, y);
    } else if (button == OF_MOUSE_BUTTON_RIGHT) {
        tracker.selectColor(x, y);
    }
}
