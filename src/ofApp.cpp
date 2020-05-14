#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    

    depth.allocate(ofGetWidth(), ofGetHeight());
    fakeDepthFbo.allocate(ofGetWidth(), ofGetHeight());
    
    
    int countX = 100;
    int countY = 100;
    float spacingX = ofGetWidth() / (float) countX;
    float spacingY = ofGetWidth() / (float) countY;
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    for (int i = 0; i < countY; i++) {
        float top = spacingY * i;
        float bottom = spacingY * (i + 1);
        for (int j = 0; j < countX; j++) {
            float left = spacingX * j;
            float right = spacingX * (j + 1);
            
            if (i % 2 != 0) {
                left = ofGetWidth() - left;
                right = ofGetWidth() - right;
            }
            
            const float noisePosScaling = 0.005f;
            const float zVariance = 50.f;
            if (true) {
                glm::vec3 v1 = { left,top, ofNoise(left * noisePosScaling, top * noisePosScaling) * zVariance};
                glm::vec3 v2 = { right,bottom, ofNoise(right * noisePosScaling, bottom * noisePosScaling) * zVariance};
                glm::vec3 v3 = { right,top, ofNoise(right * noisePosScaling, top * noisePosScaling) * zVariance};
                
                glm::vec3 normal = glm::triangleNormal(v1, v2, v3);
                
                if (i % 2 != 0) {
                    float y = normal.y;
                    normal.y = normal.x;
                    normal.x = normal.y;
                }
                
                mesh.addVertex(v1);
                mesh.addTexCoord({left, top});
                mesh.addNormal(normal);
                
                mesh.addVertex(v2);
                mesh.addTexCoord({right, bottom});
                mesh.addNormal(normal);
                
                
                
                
                
                
            }
            else {
                mesh.addVertex({ right,top, ofNoise(right * noisePosScaling, top * noisePosScaling) * zVariance});
                mesh.addTexCoord({right, top});
                
                mesh.addVertex({ left,bottom, ofNoise(left * noisePosScaling, bottom * noisePosScaling) * zVariance});
                mesh.addTexCoord({left, bottom});
            }
        }
    }
    
    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));

    // specular color, the highlight/shininess color //
    pointLight.setSpecularColor( ofColor(255.f, 255.f, 0.f));
    pointLight.setPointLight();
    pointLight.setPosition(0, 0, 100.f);
    
    greenFieldShader.load("greenField");
    
    
    // Revers so that the first layers is drawn last (and thus on top).
    std::reverse(layers.begin(), layers.end());
    
    for (const auto& layer : layers) {
        layer->init(ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if (ofGetMousePressed()) {
        fakeDepthFbo.begin();
        ofPushMatrix();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(5, 5, 5);
        ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 25 + min(fakeDepthRadius, 200));
        ofDisableBlendMode();
        ofPopMatrix();
        fakeDepthFbo.end();
        fakeDepthRadius += 1;
        
        fakeDepthFbo.readToPixels(depthPixels);
        
        //depthDiff = depthColorImg;
    }
    
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
    
    /*
    ofPushMatrix();
    ofEnableDepthTest();
        cam.begin();
        ofTranslate(-ofGetWidth() / 2.f, -ofGetHeight() / 2.f, 0.f);
        ofEnableLighting();
        pointLight.enable();
        greenFieldShader.begin();
        mesh.draw();
        greenFieldShader.end();
        ofDisableLighting();
        
        pointLight.draw();
        cam.end();
    ofPopMatrix();
     */
    
    
    
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
    fakeDepthFbo.begin();
    ofClear(0, 0, 0, 0);
    fakeDepthFbo.end();
    fakeDepthRadius = 0;
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
