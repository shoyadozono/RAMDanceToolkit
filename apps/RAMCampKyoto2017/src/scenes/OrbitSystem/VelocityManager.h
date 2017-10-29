//
//  VelocityManager.h
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#pragma once

#include "ramMain.h"


class VelocityManager {
    
public:
    VelocityManager();
    virtual ~VelocityManager() = default;
    
    void setVelocity(ofVec3f velocity);
    bool update();
    void clearBuffer();
    void reset();
    
    ofVec3f & getAverage();
    
    ofVec3f mVelocity;
    ofVec3f mPrevVelocity;
    ofVec3f mAverageVelocity;
    vector <ofVec3f> mBuffer;
    int mBufferSize;
    
};
