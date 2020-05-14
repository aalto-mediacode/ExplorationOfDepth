//
//  StarTrailsLayer.h
//  ExplorationOfDepth
//
//  Created by Oskar Koli on 11.5.2020.
//

#ifndef StarTrailsLayer_h
#define StarTrailsLayer_h

#include "ofMain.h"
#include "Layer.h"

class StarTrailsLayer : public Layer {
    
    ofxShaderFilter revealShader;
public:
    
    void init(int height, int width) {
        revealShader.allocate(height, width);
        revealShader.load("grayscott.frag");
    }
    
    void draw(ofBaseHasTexture& depth, float minDepth, float maxDepth) {
        for (int i = 0; i < 3; i++)
            revealShader.render();
        revealShader.draw(0, 0);
        
    }
    
};

#endif /* StarTrailsLayer_h */
