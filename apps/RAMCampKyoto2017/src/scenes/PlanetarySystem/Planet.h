//
//  Planet.h
//
//  Created by Shoya DOZONO on 2017/10/27.
//
//

#pragma once

#include "ofMain.h"

class Planet {
    
public:
    Planet();
    virtual ~Planet() = default;
    
    void update();
    void drawPlanet(float opacity=1.0);
    void drawTrail(float opacity=1.0);
    
    Planet & radius(float _radius);
    float getRadius();
    
    Planet & center(ofVec3f _center);
    ofVec3f getCenter();
    
    Planet & position(float _position);
    float getPosition();
    
    Planet & rotate(ofVec3f _rotate);
    ofVec3f & getRotate();
    
    Planet & rotateSpeed(ofVec3f _rotateSpeed);
    ofVec3f getRotateSpeed();
    
    Planet & expandSpeed(float _expandSpeed);
    float getExpandSpeed();
    
    Planet & scale(float _scale);
    float getScale();
    
    Planet & speed(float _speed);
    float getSpeed();
    
    Planet & color(ofColor _color);
    ofColor getColor();
    
    Planet & opacity(float _opacity);
    float getOpacity();
    
    Planet & joint(int _joint);
    int getJoint();
    
    bool isAlive();
    
    ofVec3f getPoint();
    
private:
    int mJoint;
    ofColor mColor;
    float mOpacity;
    float mExpandSpeed;
    ofVec3f mCenter;
    ofVec3f mRotate;
    ofVec3f mRotateSpeed;
    float mRadius;
    float mScale;
    float mPosition;
    float mSpeed;
    float mLineWidth;
    bool mWillDead;
    bool mIsAlive;
    ofPolyline mPolyline;
};
