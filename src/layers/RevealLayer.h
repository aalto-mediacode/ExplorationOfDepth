#ifndef RevealLayer_h
#define RevealLayer_h

#include "Layer.h"
#include "ofxShaderFilter.h"

class RevealLayer : public Layer {
    
    ofxShaderFilter revealShader;
    ofxShaderFilter revealOutlineShader;
public:
    
    void init(int height, int width) {
        revealShader.allocate(height, width);
        revealShader.load("reveal.frag");
        revealOutlineShader.allocate(height, width);
        revealOutlineShader.load("revealOutline.frag");
    }
    
    void draw(ofBaseHasTexture& depth, float minDepth, float maxDepth) {
        
        // Calculates the portal hole based on the depth texture. Using blend mode "multiply" only the hole will be visible from the StarField layer.
        revealShader.setUniformTexture("depthTexture", depth);
        revealShader.render();
        ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
        revealShader.draw(0, 0);
        ofDisableBlendMode();
        
        
        // Draws the outline of the hole.
        revealOutlineShader.setUniformTexture("revealTexture", revealShader);
        revealOutlineShader.render();
        
        //ofEnableBlendMode(OF_BLENDMODE_ADD);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        revealOutlineShader.draw(0, 0);
        glDisable(GL_BLEND);
        //ofDisableBlendMode();
        
    }
    
};

#endif /* RevealLayer_h */
