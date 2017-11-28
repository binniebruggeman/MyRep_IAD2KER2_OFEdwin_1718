#include "ColourTracker.hpp"

ColourTracker::ColourTracker() {}

void ColourTracker::setup() {
    grabber.setup(GRABBER_WIDTH, GRABBER_HEIGHT, true);
    cameraImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    hue.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
    filteredImage.allocate(GRABBER_WIDTH, GRABBER_HEIGHT);
}

void ColourTracker::update() {
    grabber.update();
    if (grabber.isFrameNew()) {
        cameraImage = grabber.getPixels();
        cameraImage.mirror(false, true);
        cameraImage.convertRgbToHsv();
        cameraImage.convertToGrayscalePlanarImage(hue, 0); // only interested in hue
        
        for (int i = 0; i < GRABBER_WIDTH * GRABBER_HEIGHT; i++) {
            if (ofInRange(hue.getPixels()[i], selectedHue - HUE_MARGIN, selectedHue + HUE_MARGIN)) {
                filteredImage.getPixels()[i] = 255;
            } else {
                filteredImage.getPixels()[i] = 0;
            }
        }
        filteredImage.flagImageChanged();
        
        contours.findContours(filteredImage, 50, GRABBER_WIDTH * GRABBER_HEIGHT / 2, 1, false);
    }
}

void ColourTracker::draw() {
    ofSetColor(ofColor::white);
    if (showSetup) {
        cameraImage.draw(0, 0);
        filteredImage.draw(0, 240);
    }
    
    if (showBlobs) {
        contours.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(ofColor::blue, 100);
        ofFill();
        for (auto& blob : contours.blobs) {
            ofDrawCircle(blob.centroid.x * ofGetWidth() / GRABBER_WIDTH,
                         blob.centroid.y * ofGetHeight() / GRABBER_HEIGHT,
                         20);
        }
        ofSetColor(ofColor::white);
    }
}

ofPoint ColourTracker::getCentroid() {
    if (haveBlobs()) {
        return contours.blobs[0].centroid;
    }
}

void ColourTracker::selectColor(int x, int y) {
    selectedHue = hue.getPixels()[y * GRABBER_WIDTH + x];
}

void ColourTracker::toggleSetup() {
    showSetup = !showSetup;
}

void ColourTracker::toggleBlobs() {
    showBlobs = !showBlobs;
}

bool ColourTracker::haveBlobs() {
    cout << selectedHue << endl;
    return selectedHue != -1 && contours.blobs.size() > 0;
}
