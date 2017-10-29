//
//  OrbitSystem.cpp
//
//  Created by Shoya DOZONO & Yinan ZHANG on 2017/10/26.
//
//

#include "OrbitSystem.h"

void OrbitSystem::setup()
{
    //mMode = Mode::STABLE;
    mScaleX=0;
    mScaleY=0;
    mScale=1.0;
    //mOrbits.resize(3);
    mSpeed=0.002;
    squareSize = 150.0;
    
    easing=0.99;
    bounce=0.008;

    
//    for ( auto &o : mOrbits )
//    {
//        o.speed(mSpeed);
//    }
    
    mSoundDirectory.listDir("soundfiles/01");
    
    mHands.push_back(rdtk::Actor::JOINT_LEFT_HAND);
    mHands.push_back(rdtk::Actor::JOINT_RIGHT_HAND);
    mFeet.push_back(rdtk::Actor::JOINT_LEFT_TOE);
    mFeet.push_back(rdtk::Actor::JOINT_RIGHT_TOE);
    mHead.push_back(rdtk::Actor::JOINT_HEAD);
}

void OrbitSystem::update()
{
    
}

void OrbitSystem::draw()
{
    
}

void OrbitSystem::drawOrbit(const rdtk::NodeArray &nodeArray)
{
   
    // left hand
    auto leftHand = nodeArray.getNode(mHands[0]);
    spring2.x= (spring2.x + (leftHand.getGlobalPosition().x-pos2.x)*bounce)*easing;
    spring2.y= (spring2.y + (leftHand.getGlobalPosition().y-pos2.y)*bounce)*easing;
    spring2.z= (spring2.z + (leftHand.getGlobalPosition().z-pos2.z)*bounce)*easing;
    pos2.x+=spring2.x;
    pos2.y+=spring2.y;
    pos2.z+=spring2.z;
    ofDrawBox(pos2,20);
    
     // right hand
    auto rightHand = nodeArray.getNode(mHands[1]);
    spring3.x= (spring3.x + (rightHand.getGlobalPosition().x-pos3.x)*bounce)*easing;
    spring3.y= (spring3.y + (rightHand.getGlobalPosition().y-pos3.y)*bounce)*easing;
    spring3.z= (spring3.z + (rightHand.getGlobalPosition().z-pos3.z)*bounce)*easing;
    pos3.x+=spring3.x;
    pos3.y+=spring3.y;
    pos3.z+=spring3.z;
    ofDrawBox(pos3,20);
    
    
    // left foot
    auto leftFoot = nodeArray.getNode(mFeet[0]);
    spring4.x= (spring4.x + (leftFoot.getGlobalPosition().x-pos4.x)*bounce)*easing;
    spring4.y= (spring4.y + (leftFoot.getGlobalPosition().y-pos4.y)*bounce)*easing;
    spring4.z= (spring4.z + (leftFoot.getGlobalPosition().z-pos4.z)*bounce)*easing;
    pos4.x+=spring4.x;
    pos4.y+=spring4.y;
    pos4.z+=spring4.z;
    ofDrawBox(pos4,20);
    
    // right foot
    auto rightFoot = nodeArray.getNode(mFeet[1]);
    spring5.x= (spring5.x + (rightFoot.getGlobalPosition().x-pos5.x)*bounce)*easing;
    spring5.y= (spring5.y + (rightFoot.getGlobalPosition().y-pos5.y)*bounce)*easing;
    spring5.z= (spring5.z + (rightFoot.getGlobalPosition().z-pos5.z)*bounce)*easing;
    pos5.x+=spring5.x;
    pos5.y+=spring5.y;
    pos5.z+=spring5.z;
    ofDrawBox(pos5,20);
    
    
    
    
    const rdtk::Node& node = nodeArray.getNode(rdtk::Actor::JOINT_ABDOMEN);
    
    
    for ( auto &o : mOrbits )
    {
        
        o.center(ofVec3f(0, 100, 0));
        mVelocity.setVelocity(node.getVelocity());
        
        o.scale(mScale+mScaleX, mScale+mScaleY);
        o.speed(mSpeed);
        o.update();
        
        ofPushMatrix();
        {
            ofColor color = rdtk::Color::WHITE;

            // draw planet
            ofPushStyle();
            ofSetColor(color);
            o.drawPlanet();
            ofPopStyle();
            
            
            // draw trail
            ofPushStyle();
            ofSetColor(color);
            ofSetLineWidth(1);
            o.drawTrail();
            ofPopStyle();
        }
        ofPopMatrix();
        
        
    
        
        
        if (
        
            ofDist(pos2.x,pos2.y,pos2.z, o.getPoint().x,o.getPoint().y,o.getPoint().z) < kCollideThreshold_
            ||
            
            ofDist(pos3.x,pos3.y,pos3.z, o.getPoint().x,o.getPoint().y,o.getPoint().z) < kCollideThreshold_
            ||
            
            ofDist(pos4.x,pos4.y,pos4.z, o.getPoint().x,o.getPoint().y,o.getPoint().z) < kCollideThreshold_
            ||
            
            ofDist(pos5.x,pos5.y,pos5.z, o.getPoint().x,o.getPoint().y,o.getPoint().z) < kCollideThreshold_
        
            )
        {
            o.playSound();
        }
        
        
        
            
//       if ( abs(pos2.z - o.getPoint().z ) < kCollideThreshold_  ||
//           abs(pos3.z - o.getPoint().z ) < kCollideThreshold_  ||
//           abs(pos4.z - o.getPoint().z ) < kCollideThreshold_  ||
//           abs(pos5.z - o.getPoint().z ) < kCollideThreshold_  )
//       {
//                o.playSound();
//       }
        
        
        
    }
    
}




void OrbitSystem::add()
{
    Orbit o;
    o.radius(ofRandom(150, 650));
   o.rotate(ofVec3f(0.0, ofRandom(-90.0, 90.0), 0));
   o.rotateSpeed(ofVec3f(0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0, ofRandomuf() > 0.5 ? 0.01 : 0.0));
    o.loadSound(mSoundDirectory.getFile(mOrbits.size() % mSoundDirectory.getFiles().size()).getAbsolutePath());
    mOrbits.push_back(o);
}

void OrbitSystem::randomize()
{

    for ( auto &o : mOrbits )
    {
        o.speed(mSpeed);
        o.radius(ofRandom(150, 650));
        o.rotate(ofVec3f(0.0, ofRandom(-90.0, 90.0), 0));
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
        
    ImGui::SliderFloat("Easing", &easing, 0.9, 1.0);
    ImGui::SliderFloat("Bounce", &bounce, 0.0, 0.1);
    ImGui::SliderFloat("Scale", &mScale, 0.0, 30);
    
}
