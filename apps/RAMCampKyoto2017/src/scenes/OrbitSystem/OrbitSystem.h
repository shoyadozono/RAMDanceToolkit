//
//  Orbit.h
//
//  Created by Shoya DOZONO on 2017/10/26.
//
//

#pragma once

#include "ramMain.h"
#include "Orbit.h"
#include "VelocityManager.h"

class OrbitSystem final : public rdtk::BaseScene {
    
public:
    enum class Mode {STABLE, FOLLOW};
    
    void setup() override;
    void update() override;
    void draw() override;
    void drawActor(const rdtk::Actor& actor) override;
    void drawRigid(const rdtk::RigidBody &rigid) override;
    
    void drawImGui() override;
    
    string getName() const override { return "OrbitSystem"; }
    
private:
    // custom functions...
    void drawOrbit(const rdtk::NodeArray &nodeArray);
    void add();
    void reset();
    void randomize();
    void drum();
    
    Mode mMode;
    vector <Orbit> mOrbits;
    vector <int> mHands;
    vector <int> mHead;
    vector <int> mFeet;
    
    float easing;
    float bounce;
    ofPoint spring1,spring2,spring3,spring4, spring5;
    ofPoint pos1, pos2, pos3, pos4,pos5;
    
    VelocityManager mVelocity, lVelocity, rVelocity;
    
    float mScaleX, mScaleY, mScale, mSpeedLevel;
    
    bool mShowHelper {false};
    bool mShowDrum{false};
    
    ofDirectory mSoundDirectory;
    
    const float kCollideThreshold_ {100.0};
    float squareSize;
    float mSpeed;
    float mDrumSpeed;
    float headHeight;
    float boxSpeed;

    int soundLevel;
    ofPoint boxPos;
    
    
    float test;
    
//    ofSoundPlayer drum1, drum2, cymbal1,cymbal2;
};
