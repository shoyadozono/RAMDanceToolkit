//
//  VelocityManager2.cpp
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#include "VelocityManager2.h"

VelocityManager2::VelocityManager2()
    : mBufferSize(20)
{;}

void VelocityManager2::setVelocity(ofVec3f velocity)
{
    mVelocity = velocity;
}

bool VelocityManager2::update()
{
    auto diff = mVelocity - mPrevVelocity;
    mPrevVelocity = mVelocity;
    
    mBuffer.push_back(diff);
    
    if ( mBuffer.size() > mBufferSize )
    {
        mBuffer.erase(mBuffer.begin());
    }
    
    mAverageVelocity = ofVec3f(0);
    
    if ( mBuffer.size() >= mBufferSize )
    {
        for (int i=1; i < mBuffer.size(); i++)
        {
            mAverageVelocity += mBuffer[i];
        }
        mAverageVelocity /= (mBuffer.size()-1);
        mAverageVelocity *= -1.0;
        
        return true;
    }
    
    return false;
}

void VelocityManager2::clearBuffer()
{
    mBuffer.clear();
}

void VelocityManager2::reset()
{
    this->clearBuffer();
    mVelocity           = ofVec3f(0);
    mPrevVelocity       = ofVec3f(0);
    mAverageVelocity    = ofVec3f(0);
}

bool VelocityManager2::isComputeAverage()
{
    return mBuffer.size() >= mBufferSize;
}

ofVec3f & VelocityManager2::get()
{
    return mVelocity;
}

ofVec3f & VelocityManager2::getAverage()
{
    return mAverageVelocity;
}
