//
//  GrayScottLayer.h
//  ExplorationOfDepth
//
//  Created by Oskar Koli on 11.5.2020.
//

#ifndef GrayScottLayer_h
#define GrayScottLayer_h

#include "ofMain.h"
#include "Layer.h"

class StarFieldLayer : public Layer {
    
    ofxShaderFilter revealShader;
public:
    
    void init(int height, int width) {
        revealShader.allocate(height, width);
        revealShader.load("starfield.frag");
    }
    
    void draw(ofBaseHasTexture& depth, float minDepth, float maxDepth) {
        //for (int i = 0; i < 5; i++)
        revealShader.render();
        revealShader.draw(0, 0);
        
    }
    
};

#endif /* GrayScottLayer_h */
