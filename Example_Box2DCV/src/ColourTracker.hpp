#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define GRABBER_HEIGHT 240
#define GRABBER_WIDTH 320
#define HUE_MARGIN 5

class ColourTracker {
public:
    ColourTracker();
    void setup();
    void update();
    void draw();
    void selectColor(int x, int y);
    ofPoint getCentroid();
    void toggleSetup();
    void toggleBlobs();
    bool haveBlobs();
    
private:
    ofVideoGrabber grabber;
    
    ofxCvColorImage cameraImage;
    ofxCvGrayscaleImage hue;
    ofxCvGrayscaleImage filteredImage;
    
    ofxCvContourFinder contours;
    
    bool showSetup = false;
    bool showBlobs = false;
    int selectedHue = -1;
};
