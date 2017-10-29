  //
//  VelocityManager.cpp
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#include "VelocityManager.h"

VelocityManager::VelocityManager()
    : mBufferSize(30)
{;}

void VelocityManager::setVelocity(ofVec3f velocity)
{
    mVelocity = velocity;
}

bool VelocityManager::update()
{
    auto diff = mVelocity - mPrevVelocity;
    mPrevVelocity = mVelocity;
    
    mBuffer.push_back(diff);
    
    if ( mBuffer.size() > mBufferSize )
    {
        mBuffer.erase(mBuffer.begin());
    }
    
    mAverageVelocity = ofVec3f(0);
    
    if ( mBuffer.size() == mBufferSize )
    {
        for (int i=1; i < mBuffer.size(); i++)
        {
            mAverageVelocity += mBuffer[i];
        }
        mAverageVelocity /= (mBuffer.size()-1);
        
        return true;
    }
    
    return false;
}

void VelocityManager::clearBuffer()
{
    mBuffer.clear();
}

void VelocityManager::reset()
{
    this->clearBuffer();
    mVelocity           = ofVec3f(0);
    mPrevVelocity       = ofVec3f(0);
    mAverageVelocity    = ofVec3f(0);
}

ofVec3f & VelocityManager::getAverage()
{
    return mAverageVelocity;
}
