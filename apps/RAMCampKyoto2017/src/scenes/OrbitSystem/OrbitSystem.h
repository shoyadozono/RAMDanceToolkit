//
//  Orbit.h
//
//  Created by Shoya DOZONO on 2017/10/26.
//
//

#pragma once

#include "ramMain.h"
#include "Orbit.h"

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
    
    Mode mMode;
    vector <Orbit> mOrbits;
    vector <int> mTargets;
    float mScale;
    
    bool mShowHelper {false};
    
    ofDirectory mSoundDirectory;
    
    const float kCollideThreshold_ {2.0};
};
