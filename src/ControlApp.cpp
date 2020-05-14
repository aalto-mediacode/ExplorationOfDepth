//
//  ControlApp.cpp
//  ExplorationOfDepth
//
//  Created by Oskar Koli on 13.5.2020.
//

#include "ControlApp.h"

//--------------------------------------------------------------
void ControlApp::setup(){
    ofDisableArbTex();
    
    Settings::get().load();
    
    if (Settings::exists("calibration")) {
        for (int i = 0; i < 4; i++) {
            ofVec2f p = Settings::getVec2("calibration/" + std::to_string(i + 1));
            calibrationPoints.push_back(ofPoint(p.x, p.y));
        }
        state = RUNNING;
        app->state = RUNNING;
    }
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    else {
        ofLogError() << "Failed to connect to Kinect!";
        OF_EXIT_APP(0)
    }
    
    
    depth.allocate(kinect.width, kinect.height);
    baseLineDepth.allocate(appWindowSize.x, appWindowSize.y);
    depthDiff.allocate(appWindowSize.x, appWindowSize.y);

    ofSetWindowShape(kinect.width, kinect.height);
}

//--------------------------------------------------------------
void ControlApp::update(){
    kinect.update();
    
    if (kinect.isFrameNew()) {
        if (state == RUNNING) {
            depth.setFromPixels(kinect.getDepthPixels());
            
            
            
            ofPoint outputQuad[4];
            outputQuad[0] = ofPoint(0.f, 0.f);
            outputQuad[1] = ofPoint(appWindowSize.x, 0.f);
            outputQuad[2] = ofPoint(appWindowSize.x, appWindowSize.y);
            outputQuad[3] = ofPoint(0.f, appWindowSize.y);
            
            
            depthDiff.warpIntoMe(depth, &*calibrationPoints.begin(), outputQuad);
            
            if (!baselineSet) {
                baselineSet = true;
                baseLineDepth = depthDiff;
            }
            
            //depthDiff = depth;
            depthDiff.absDiff(baseLineDepth);
            
            unsigned char* pixelData = depthDiff.getPixels().getData();
            
            // Reckon the total number of bytes to examine.
            // This is the image's width times its height,
            // times 3 -- because each pixel requires 3 bytes
            // to store its R, G, and B color components.
            int nTotalBytes = depthDiff.getWidth() * depthDiff.getHeight();
            
            const int MINV = 2;
            const int MAXV = 10;
            // For every byte of the RGB image data,
            for(int i=0; i<nTotalBytes; i++){

                // pixelData[i] is the i'th byte of the image;
                // subtract it from 255, to make a "photo negative"
                pixelData[i] = ofMap(std::min(std::max(MINV, (int) pixelData[i]), MAXV), MINV, MAXV, 0.f, 255.f) ;
            }
            
            app->depth = depthDiff;
        }
    }
    
}

//--------------------------------------------------------------
void ControlApp::draw(){
    if (state == CALIBRATING) {
        kinect.draw(0,0);
        
        ofPushStyle();
        ofSetColor(ofColor::green);
        for (ofPoint& point : calibrationPoints) {
            ofDrawCircle(point.x, point.y, 2);
        }
        ofPopStyle();
    }
    else {
        depth.draw(0, 0);
    }
}

//--------------------------------------------------------------
void ControlApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ControlApp::keyReleased(int key){
    if (key == 99) { // C = calibration
        calibrationPoints.clear();
        state = CALIBRATING;
        app->state = CALIBRATING;
    }
}

//--------------------------------------------------------------
void ControlApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ControlApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ControlApp::mousePressed(int x, int y, int button){
    ofColor color = depth.getPixels().getColor(x, y);
    ofLogNotice() << color.getBrightness() << " : " << color.getSaturation();
}

//--------------------------------------------------------------
void ControlApp::mouseReleased(int x, int y, int button){
    if (state == CALIBRATING) {
        calibrationPoints.push_back(ofPoint(x, y));
        Settings::getVec2("calibration/" + std::to_string(calibrationPoints.size())) = ofVec2f(x, y);
        if (calibrationPoints.size() == 4) {
            Settings::get().save();
            state = RUNNING;
            app->state = RUNNING;
        }
    }
}

//--------------------------------------------------------------
void ControlApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ControlApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ControlApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ControlApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ControlApp::dragEvent(ofDragInfo dragInfo){

}
