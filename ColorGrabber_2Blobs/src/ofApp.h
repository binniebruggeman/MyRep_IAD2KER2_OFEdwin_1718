#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

#define GRABBER_WIDTH 320
#define GRABBER_HEIGHT 240
#define HUE_MARGIN 5
#define MIN_SIZE 50


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    ofVideoGrabber grabber;
    ofVideoGrabber grabber_2;
    
    ofxCvColorImage rgbImage;
    ofxCvColorImage hsvImage;
    
    ofxCvGrayscaleImage hue;
    ofxCvGrayscaleImage saturation;
    ofxCvGrayscaleImage value; //==brightness
    
    ofxCvGrayscaleImage filtered;
    ofxCvGrayscaleImage filtered_2;

    
    ofxCvContourFinder contours;
    ofxCvContourFinder contours_2;
    
    bool showHSVComponents = false;
    bool showVideo = true;
    bool showFiltered = true;
    bool showFiltered_2 = true;
    bool showContours = true;
    bool showContours_2 = true;
    
    bool firstMouse = true;
    bool secondMouse = false;
    
    int findHue;
    int findHue_2;
};
