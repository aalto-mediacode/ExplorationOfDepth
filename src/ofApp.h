#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxShader.h"
#include "layers/Layer.h"
#include "layers/RevealLayer.h"
#include "layers/StarFieldLayer.h"

#define KINECT 1


enum State {
    CALIBRATING,
    RUNNING
};

class ofApp : public ofBaseApp{
    
    vector<shared_ptr<Layer>> layers = {
        make_shared<RevealLayer>(),
        make_shared<StarFieldLayer>()
    };
    
	public:
        ofxCvGrayscaleImage depth;
        State state = CALIBRATING;
    
		void setup();
		void update();
		void draw();
    
        void setupControl();
        void drawControl(ofEventArgs & args);

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
