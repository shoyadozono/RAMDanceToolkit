//
//  Orbit.h
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#pragma once

#include "ofMain.h"

class Orbit {
    
public:
    enum class Axis { XY, XZ, YZ };
    
    Orbit();
    virtual ~Orbit() = default;
    
    void update();
    void drawPlanet();
    void drawTrail();
    
    void loadSound(string filePath);
    void playSound();
    
    Orbit & radius(float _radius);
    float getRadius();
    
    Orbit & center(ofVec3f _center);
    ofVec3f getCenter();
    
    Orbit & position(float _position);
    float getPosition();
    
    Orbit & rotate(ofVec3f _rotate);
    ofVec3f getRotate();
    
    Orbit & rotateSpeed(ofVec3f _rotateSpeed);
    ofVec3f getRotateSpeed();
    
    Orbit & scale(float _scaleX, float _scaleY);
    float getScale();
    
    Orbit & speed(float _speed);
    float getSpeed();
    
    ofVec3f getPoint();
    
    bool isSoundPlaying();
    
    
private:
    ofVec3f mCenter;
    ofVec3f mRotate;
    ofVec3f mRotateSpeed;
    float mRadius;
    float mScaleX, mScaleY, mScale;
    Axis mAxis;
    float mPosition;
    float mSpeed;
    ofPolyline mPolyline;
    
    ofSoundPlayer mSoundPlayer;
};
