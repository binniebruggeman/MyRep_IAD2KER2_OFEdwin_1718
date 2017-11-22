#include "ofApp.h"
#include "ofxOpenCv.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT);
    grabber_2.setup(GRABBER_WIDTH, GRABBER_HEIGHT);
    
    rgbImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    hsvImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    
    hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    saturation.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    value.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    
    filtered.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}


//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    grabber_2.update();
    if (grabber.isFrameNew()){
        rgbImage.setFromPixels(grabber.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
        rgbImage.mirror(false, true);
        hsvImage = rgbImage;
        hsvImage.convertRgbToHsv();
        
        hsvImage.convertToGrayscalePlanarImages(hue, saturation, value);
        
        for (int i=0; i< GRABBER_WIDTH*GRABBER_HEIGHT; i++){
            if (ofInRange(hue.getPixels()[i],
                          findHue - HUE_MARGIN,
                          findHue + HUE_MARGIN)) {
                filtered.getPixels()[i] = 255;
            } else{
                filtered.getPixels()[i] = 0;
            }
        }
        
        filtered.flagImageChanged(); //
        
        contours.findContours(filtered, MIN_SIZE,
                              GRABBER_WIDTH*GRABBER_HEIGHT/2,
                              1, false);
        
    }
    
    if (grabber_2.isFrameNew()){
        rgbImage.setFromPixels(grabber_2.getPixels().getData(), GRABBER_WIDTH, GRABBER_HEIGHT);
        rgbImage.mirror(false, true);
        hsvImage = rgbImage;
        hsvImage.convertRgbToHsv();
        
        hsvImage.convertToGrayscalePlanarImages(hue, saturation, value);
        
        for (int i=0; i< GRABBER_WIDTH*GRABBER_HEIGHT; i++){
            if (ofInRange(hue.getPixels()[i],
                          findHue_2 - HUE_MARGIN,
                          findHue_2 + HUE_MARGIN)) {
                filtered.getPixels()[i] = 255;
            } else{
                filtered.getPixels()[i] = 0;
            }
        }
        
        filtered.flagImageChanged(); //
        
        contours_2.findContours(filtered, MIN_SIZE,
                              GRABBER_WIDTH*GRABBER_HEIGHT/2,
                              1, false);
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (showVideo){
        rgbImage.draw(0,0,ofGetWidth(), ofGetHeight());
    }
    
    if (showHSVComponents) {
        hsvImage.draw(0,0);
        hue.draw(0,240);
        saturation.draw(320,240);
        value.draw(640,240);
    }
    
    if (showFiltered){
        filtered.draw(0, 480);
        if (showContours){
            contours.draw(0, 480);
        }
        if (showContours_2){
            contours_2.draw(0, 480);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'h'){
        showHSVComponents = !showHSVComponents;
    } else if (key == 'v') {
        showVideo = !showVideo;
    } else if (key == 'c') {
        showContours = !showContours;
    } else if (key == 'd') {
        showContours_2 = !showContours_2;
    } else if (key == 'f') {
        showFiltered = !showFiltered;
    }
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    findHue = hue.getPixels()[y * GRABBER_WIDTH + x];
    findHue_2 = hue.getPixels()[y * GRABBER_WIDTH + x];
    
}

