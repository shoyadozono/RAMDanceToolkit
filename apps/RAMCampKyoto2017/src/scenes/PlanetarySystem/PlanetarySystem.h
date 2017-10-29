//
//  PlanetarySystem.h
//
//  Created by Shoya DOZONO on 2017/10/26.
//
//

#pragma once

#include "ramMain.h"
#include "ofxOsc.h"
#include "Planet.h"
#include "VelocityManager2.h"

#define USE_MOTIONER

class PlanetarySystem final : public rdtk::BaseScene {
    
public:
    PlanetarySystem();
    
    void setup() override;
    void update() override;
    void draw() override;
    void drawActor(const rdtk::Actor& actor) override;
    void drawRigid(const rdtk::RigidBody &rigid) override;

    void drawImGui() override;
    
    string getName() const override { return "Planetary System"; }
    
private:
    enum class Mode     {STABLE, FOLLOW, PARTS};
    enum class Camera   {MANUAL, ROTATION, FOLLOW};
    
    // custom functions...
    void drawPlanet(const rdtk::NodeArray &nodeArray);
    ofPtr<Planet> addPlanet();
    void reset();
    void randomize();
    
    Mode mMode;
    int mMaxNumPlanets;
    vector < ofPtr<Planet> > mPlanets;
    vector <int> mTargets;
    vector <VelocityManager2> mVelocityManagers;
    float mScale;
    float mExapandSpeed;
    float mVelocityThreshold;
    
    ofPrimitiveMode mLineMode;
    
    Camera mCamera;
    float mCamRotateSpeed;
    float mCamZoom;
    
    float mTrailOpacity;
    float mLineOpacity;
    
    bool mShowHelpers {false};
    
    // for performance
    ofxOscReceiver mOscReceiver;
};
