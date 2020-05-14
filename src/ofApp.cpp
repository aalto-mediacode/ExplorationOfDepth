#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    depth.allocate(ofGetWidth(), ofGetHeight());
   
    // Revers so that the first layers is drawn last (and thus on top).
    std::reverse(layers.begin(), layers.end());
    
    for (const auto& layer : layers) {
        layer->init(ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    if (state == CALIBRATING) {
        ofPushStyle();
            ofSetColor(ofColor::red);
            ofDrawCircle(5, 5, 5);
            ofDrawCircle(ofGetWidth() - 5, 5, 5);
            ofDrawCircle(ofGetWidth() - 5, ofGetHeight() - 5, 5);
            ofDrawCircle(5, ofGetHeight() - 5, 5);
        ofPopStyle();
    } else if (state == RUNNING) {
        
        int stepSize = 255.f / (layers.size() + 1);
        int min = 0;
        depth.updateTexture();
        for (const auto& layer : layers) {
            ofPushStyle();
            layer->draw(depth, min, min + stepSize);
            ofPopStyle();
            min += stepSize;
        }
        
         
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
