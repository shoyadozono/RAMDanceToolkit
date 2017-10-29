//
//  Orbit.cpp
//
//  Created by Shoya DOZONO & Yinan ZHANG on 2017/10/27.
//
//

#include "Orbit.h"

Orbit::Orbit()
    : mRadius(200)
    , mPosition(0)
    , mCenter(ofVec3f(0))
    , mRotate(ofVec3f(0))
    , mRotateSpeed(ofVec3f(0))
    , mSpeed(0)
    , mScaleX(1)
    , mScaleY(1)
    , mAxis(Axis::XY)
{
    mSoundPlayer.setLoop(false);
}

void Orbit::update()
{
    mPosition += mSpeed;
    if ( mPosition > 1.0 )      mPosition -= 1.0;
    else if ( mPosition < 0.0 ) mPosition += 1.0;
    
    mRotate += mRotateSpeed;
    
    mPolyline.clear();
    for (float i=0; i < 360.0; i+=2.0)
    {
        float x = 0;
        float y = mRadius * cos(ofDegToRad(i)) * mScaleX;
        float z = mRadius * sin(ofDegToRad(i)) * mScaleY;
        ofVec3f pt = ofVec3f(x, y, z);
        pt.rotate(mRotate.x, ofVec3f(1, 0, 0));
        pt.rotate(mRotate.y, ofVec3f(0, 1, 0));
        pt.rotate(mRotate.z, ofVec3f(0, 0, 1));
        mPolyline.addVertex(pt + mCenter);
    }
    mPolyline.close();
}

void Orbit::drawPlanet()
{
    ofDrawSphere(this->getPoint(), 3);
}

void Orbit::drawTrail()
{
    mPolyline.draw();
    
}

void Orbit::loadSound(string filePath)
{
    mSoundPlayer.unload();
    mSoundPlayer.load(filePath);
}

void Orbit::playSound()
{
    if ( !mSoundPlayer.isPlaying() && mSoundPlayer.isLoaded() )
    {
        mSoundPlayer.play();
    }
}

Orbit & Orbit::radius(float _radius)
{
    mRadius = _radius;
    return *this;
}

float Orbit::getRadius()
{
    return mRadius;
}

Orbit & Orbit::center(ofVec3f _center)
{
    mCenter = _center;
    return *this;
}

ofVec3f Orbit::getCenter()
{
    return mCenter;
}

Orbit & Orbit::position(float _position)
{
    mPosition = _position;
    return *this;
}

float Orbit::getPosition()
{
    return mPosition;
}

Orbit & Orbit::speed(float _speed)
{
    mSpeed = _speed;
    return *this;
}

Orbit & Orbit::rotate(ofVec3f _rotate)
{
    mRotate = _rotate;
    return *this;
}

ofVec3f Orbit::getRotate()
{
    return mRotate;
}

Orbit & Orbit::scale(float _scaleX,float _scaleY)
{
    mScaleX = _scaleX;
    mScaleY = _scaleY;
    return *this;
}

float Orbit::getScale()
{
    return mScale;
}

Orbit & Orbit::rotateSpeed(ofVec3f _rotateSpeed)
{
    mRotateSpeed = _rotateSpeed;
    return *this;
}

ofVec3f Orbit::getRotateSpeed()
{
    return mRotateSpeed;
}

float Orbit::getSpeed()
{
    return mSpeed;
}

ofVec3f Orbit::getPoint()
{
    return mPolyline.getPointAtPercent(mPosition);
}

bool Orbit::isSoundPlaying()
{
    return mSoundPlayer.isPlaying();
}
