#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "ofMain.h"
#include "ofApp.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxShader.h"
#include "ofxJsonSettings.h"

#define KINECT 1


class ControlApp : public ofBaseApp{
    
    State state = CALIBRATING;

    ofxKinect kinect;
    
    bool baselineSet = false;
    vector<ofPixels> baselineDepthFrames;
    
    ofxCvGrayscaleImage baseLineDepth;
    ofxCvGrayscaleImage depth;
    ofxCvGrayscaleImage depthDiff;
    
    vector<ofPoint> calibrationPoints;
    
    
    
    public:
        shared_ptr<ofApp> app;
        glm::vec2 appWindowSize;
    
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
        
};
