//
//  Planet.cpp
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#include "Planet.h"

Planet::Planet()
    : mRadius(200)
    , mPosition(0)
    , mCenter(ofVec3f(0))
    , mRotate(ofVec3f(0))
    , mRotateSpeed(ofVec3f(0))
    , mSpeed(0)
    , mScale(1)
    , mColor(ofColor(255))
    , mOpacity(1)
    , mJoint(-1)
    , mExpandSpeed(0.1)
    , mLineWidth(3.0)
    , mIsAlive(true)
    , mWillDead(false)
{;}

void Planet::update()
{
    mPosition += mSpeed;
    if ( mPosition > 1.0 )      mPosition -= 1.0;
    else if ( mPosition < 0.0 ) mPosition += 1.0;
    
    mRotate += mRotateSpeed;
    
    mRadius += mExpandSpeed;
    
    if ( mRadius < 50 )
    {
        mOpacity = ofMap(mRadius, 0.0, 50.0, 0.0, 1.0);
    }
    else if ( mRadius > 200 )
    {
        mOpacity -= 0.01;
        if ( mOpacity < 0 )
        {
            mOpacity = 0.0;
            mIsAlive = false;
        }
    }
    
    mPolyline.clear();
    
    for (float i=0; i < 360.0; i+=2.0)
    {
        float x = mRadius * cos(ofDegToRad(i)) * mScale;
        float y = mRadius * sin(ofDegToRad(i)) * mScale;
        float z = 0;
        ofVec3f pt = ofVec3f(x, y, z);
        pt.rotate(mRotate.x, ofVec3f(1, 0, 0));
        pt.rotate(mRotate.y, ofVec3f(0, 1, 0));
        pt.rotate(mRotate.z, ofVec3f(0, 0, 1));
        mPolyline.addVertex(pt + mCenter);
    }
    mPolyline.close();
}

void Planet::drawPlanet(float opacity)
{
    float a = 255.f * mOpacity * opacity;
    if ( a > 0.0 )
    {
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(mColor, a);
        ofDrawSphere(this->getPoint(), 3);
        ofPopStyle();
        ofPopMatrix();
    }
}

void Planet::drawTrail(float opacity)
{
    float a = 128.f * mOpacity * opacity;
    if ( a > 0.0 )
    {
        ofPushMatrix();
        ofPushStyle();
        ofSetColor(mColor, a);
        ofSetLineWidth(mLineWidth);
        mPolyline.draw();
        ofPopStyle();
        ofPopMatrix();
    }
}

Planet & Planet::radius(float _radius)
{
    mRadius = _radius;
    return *this;
}

float Planet::getRadius()
{
    return mRadius;
}

Planet & Planet::center(ofVec3f _center)
{
    mCenter = _center;
    return *this;
}

ofVec3f Planet::getCenter()
{
    return mCenter;
}

Planet & Planet::position(float _position)
{
    mPosition = _position;
    return *this;
}

float Planet::getPosition()
{
    return mPosition;
}

Planet & Planet::speed(float _speed)
{
    mSpeed = _speed;
    return *this;
}

Planet & Planet::rotate(ofVec3f _rotate)
{
    mRotate = _rotate;
    return *this;
}

ofVec3f & Planet::getRotate()
{
    return mRotate;
}

Planet & Planet::scale(float _scale)
{
    mScale = _scale;
    return *this;
}

float Planet::getScale()
{
    return mScale;
}

Planet & Planet::expandSpeed(float _expandSpeed)
{
    mExpandSpeed = _expandSpeed;
    return *this;
}

float Planet::getExpandSpeed()
{
    return mExpandSpeed;
}

Planet & Planet::rotateSpeed(ofVec3f _rotateSpeed)
{
    mRotateSpeed = _rotateSpeed;
    return *this;
}

ofVec3f Planet::getRotateSpeed()
{
    return mRotateSpeed;
}

float Planet::getSpeed()
{
    return mSpeed;
}

Planet & Planet::color(ofColor _color)
{
    mColor = _color;
    return *this;
}

ofColor Planet::getColor()
{
    return mColor;
}

Planet & Planet::opacity(float _opacity)
{
    mOpacity = _opacity;
    return *this;
}

float Planet::getOpacity()
{
    return mOpacity;
}

Planet & Planet::joint(int _joint)
{
    mJoint = _joint;
}

int Planet::getJoint()
{
    return mJoint;
}

bool Planet::isAlive()
{
    return mIsAlive;
}

ofVec3f Planet::getPoint()
{
    return mPolyline.getPointAtPercent(mPosition);
}
