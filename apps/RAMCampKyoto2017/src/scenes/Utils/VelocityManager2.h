//
//  VelocityManager2.h
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#pragma once

#include "ramMain.h"

class VelocityManager2 {
    
public:
    VelocityManager2();
    virtual ~VelocityManager2() = default;
    
    void setVelocity(ofVec3f velocity);
    bool update();
    void clearBuffer();
    void reset();
    
    bool isComputeAverage();
    
    ofVec3f & get();
    ofVec3f & getAverage();
    
private:
    ofVec3f mVelocity;
    ofVec3f mPrevVelocity;
    ofVec3f mAverageVelocity;
    vector <ofVec3f> mBuffer;
    int mBufferSize;
};
