//
//  Layer.hpp
//  ExplorationOfDepth
//
//  Created by Oskar Koli on 11.5.2020.
//

#ifndef Layer_hpp
#define Layer_hpp

#include "ofxOpenCv.h"

class Layer {
        
    
public:
    virtual void init(int height, int width) = 0;
    virtual void draw(ofBaseHasTexture& depth, float minDepth, float maxDepth) = 0;
};

#endif /* Layer_hpp */
