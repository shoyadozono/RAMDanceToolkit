//
//  OrbitSystem.cpp
//
//  Created by Shoya DOZONO on 2017/10/26.
//
//

#include "OrbitSystem.h"

void OrbitSystem::setup()
{
    mMode = Mode::FOLLOW;
    mScale = 1.0;
    
    mOrbits.resize(3);
    
    for ( auto &o : mOrbits )
    {
        o.speed(0.001);
    }
    
    mSoundDirectory.listDir("soundfiles/beep");
    
    mOrbits[0].radius(200.0);
    mOrbits[0].rotate(ofVec3f(0.0, 0.0, 30.0));
    mOrbits[0].rotateSpeed(ofVec3f(0.0, 0.0, 0.01));
    mOrbits[0].loadSound(mSoundDirectory.getFile(0).getAbsolutePath());
    
    mOrbits[1].radius(300.0);
    mOrbits[1].rotate(ofVec3f(0.0, -30.0, 0.0));
    mOrbits[1].rotateSpeed(ofVec3f(0.0, 0.01, 0.0));
    mOrbits[1].loadSound(mSoundDirectory.getFile(1).getAbsolutePath());
    
    mOrbits[2].radius(100.0);
    mOrbits[2].rotate(ofVec3f(0.0, 0.0, 30.0));
    mOrbits[2].rotateSpeed(ofVec3f(0.0, 0.01, 0.0));
    mOrbits[2].loadSound(mSoundDirectory.getFile(2).getAbsolutePath());
    
    mTargets.push_back(rdtk::Actor::JOINT_LEFT_HAND);
    mTargets.push_back(rdtk::Actor::JOINT_RIGHT_HAND);
}

void OrbitSystem::update()
{
    
}

void OrbitSystem::draw()
{
    
}

void OrbitSystem::drawOrbit(const rdtk::NodeArray &nodeArray)
{
    const rdtk::Node& node = nodeArray.getNode(rdtk::Actor::JOINT_ABDOMEN);
    
    for ( auto &o : mOrbits )
    {
        if ( mMode == Mode::FOLLOW ) {
            o.center(node.getGlobalPosition());
        }
        else if ( mMode == Mode::STABLE ) {
            o.center(ofVec3f(0, 100, 0));
        }
        o.scale(mScale);
        o.update();
        
        ofPushMatrix();
        {
            ofColor color = rdtk::Color::RED_LIGHT;
            if ( o.isSoundPlaying() ) color = rdtk::Color::BLUE_LIGHT;
            
            // draw planet
            ofPushStyle();
            ofSetColor(color);
            o.drawPlanet();
            ofPopStyle();
            
            // draw trail
            ofPushStyle();
            ofSetColor(color);
            ofSetLineWidth(3.0);
            o.drawTrail();
            ofPopStyle();
        }
        ofPopMatrix();
        
        for ( auto &t : mTargets )
        {
            auto target = nodeArray.getNode(t);
            
            if ( abs(target.getGlobalPosition().z - o.getPoint().z) < kCollideThreshold_ )
            {
                o.playSound();
            }
        }
    }
    
    if ( mShowHelper )
    {
        // show planes
        for ( auto &t : mTargets )
        {
            auto target = nodeArray.getNode(t);
            float size = 800.0;
            vector <ofVec3f> verts = {
                ofVec3f(-size/2, -size/2, 0.0) + target.getGlobalPosition(),
                ofVec3f( size/2, -size/2, 0.0) + target.getGlobalPosition(),
                ofVec3f( size/2,  size/2, 0.0) + target.getGlobalPosition(),
                ofVec3f(-size/2,  size/2, 0.0) + target.getGlobalPosition(),
            };
            
            ofPushStyle();
            ofSetColor(rdtk::Color::BLUE_LIGHT, 64);
            ofBeginShape();
            for ( auto &v : verts)
            {
                ofVertex(v);
            }
            ofEndShape(true);
            ofPopStyle();
        }
    }
    
}

void OrbitSystem::add()
{
    Orbit o;
    o.speed(ofRandom(0.001, 0.003));
    o.radius(ofRandom(50, 350));
    o.rotate(ofVec3f(0.0, ofRandom(-60.0, 60.0), ofRandom(-60.0, 60.0)));
    o.rotateSpeed(ofVec3f(0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0));
    o.loadSound(mSoundDirectory.getFile(mOrbits.size() % mSoundDirectory.getFiles().size()).getAbsolutePath());
    mOrbits.push_back(o);
}

void OrbitSystem::randomize()
{
    for ( auto &o : mOrbits )
    {
        o.speed(ofRandom(0.001, 0.003));
        o.radius(ofRandom(50, 350));
        o.rotate(ofVec3f(0.0, ofRandom(-60.0, 60.0), ofRandom(-60.0, 60.0)));
        o.rotateSpeed(ofVec3f(0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0));
        o.loadSound(mSoundDirectory.getFile(ofRandom(mSoundDirectory.getFiles().size())).getAbsolutePath());
    }
}

void OrbitSystem::reset()
{
    mOrbits.clear();
}

void OrbitSystem::drawActor(const rdtk::Actor& actor)
{
    this->drawOrbit(actor);
}

void OrbitSystem::drawRigid(const rdtk::RigidBody &rigid)
{
    
}

void OrbitSystem::drawImGui()
{
    if ( ImGui::Button("Reset") )
    {
        this->reset();
    }
    
    ImGui::SameLine();
    
    if ( ImGui::Button("Add") )
    {
        this->add();
    }
    
    ImGui::SameLine();
    
    if ( ImGui::Button("Randomize") )
    {
        this->randomize();
    }
    
    static int mode = 1;
    if ( ImGui::Combo("Mode", &mode, "STABLE\0FOLLOW\0\0") )
    {
        if ( mode == 0 ) mMode = Mode::STABLE;
        if ( mode == 1 ) mMode = Mode::FOLLOW;
    }
    
    ImGui::SliderFloat("Scale", &mScale, 0.0, 2.0);
    
    ImGui::Checkbox("Show Helper", &mShowHelper);
}
