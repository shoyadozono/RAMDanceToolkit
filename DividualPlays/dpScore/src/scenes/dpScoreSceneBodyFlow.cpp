//
//  dpScoreSceneBodyFlow.cpp
//  dpScore
//
//  Created by YoshitoONISHI on 1/10/15.
//
//

#include "dpScoreSceneBodyFlow.h"

DP_SCORE_NAMESPACE_BEGIN

SceneBodyFlow::Points::Points()
{
    for (int i=0; i<30; i++) {
        p0.push_back(randVec3f() * 30.f);
    }
    for (int i=0; i<20; i++) {
        p1.push_back(randVec3f() * 20.f);
    }
    for (int i=0; i<10; i++) {
        p2.push_back(randVec3f() * 10.f);
    }
    v0.setVertexData(&p0.at(0), p0.size(), GL_DYNAMIC_DRAW);
    v1.setVertexData(&p1.at(0), p1.size(), GL_DYNAMIC_DRAW);
    v2.setVertexData(&p2.at(0), p2.size(), GL_DYNAMIC_DRAW);
}

SceneBodyFlow::Points::~Points()
{
    p0.clear();
    p1.clear();
    p2.clear();
}

void SceneBodyFlow::Points::update()
{
    for (auto& p : p0) {
        p += randVec3f() * 0.3f;
    }
    for (auto& p : p1) {
        p += randVec3f() * 0.2f;
    }
    for (auto& p : p2) {
        p += randVec3f() * 0.1f;
    }
    v0.updateVertexData(&p0.at(0), p0.size());
    v1.updateVertexData(&p1.at(0), p1.size());
    v2.updateVertexData(&p2.at(0), p2.size());
}

void SceneBodyFlow::Points::draw()
{
    glPointSize(3.f);
    v0.draw(GL_POINTS, 0, p0.size());
    glPointSize(2.f);
    v1.draw(GL_POINTS, 0, p1.size());
    glPointSize(1.f);
    v2.draw(GL_POINTS, 0, p2.size());
}

void SceneBodyFlow::initialize()
{
    dpDebugFunc();
    
    mUICanvas = new ofxUICanvas();
    mUICanvas->setName(getShortName());
    mUICanvas->addLabel(getShortName(), OFX_UI_FONT_SMALL);
    mUICanvas->addSpacer();
    
    mCam.setDistance(200);
    mCam.disableMouseInput();
}

void SceneBodyFlow::shutDown()
{
    dpDebugFunc();
    
    if (mUICanvas) {
        delete mUICanvas;
        mUICanvas = nullptr;
    }
}

void SceneBodyFlow::enter()
{
    dpDebugFunc();
    
    ofAddListener(ofxMotioner::updateSkeletonEvent,
                  this,
                  &SceneBodyFlow::onUpdateSkeleton);
    mCam.enableMouseInput();
    
    mPoints.assign(kNumSkeletons, ofPtr<Points>());
    for (auto& p : mPoints) {
        p = ofPtr<Points>(new Points());
    }
    mSkeletonName = "";
}

void SceneBodyFlow::exit()
{
    dpDebugFunc();
    
    ofRemoveListener(ofxMotioner::updateSkeletonEvent,
                     this,
                     &SceneBodyFlow::onUpdateSkeleton);
    mCam.disableMouseInput();
    
    mPoints.clear();
    mSkeletons.clear();
}

void SceneBodyFlow::update(ofxEventMessage& m)
{
    if (m.getAddress() == kOscAddrMotioner) {
        for (auto p : mPoints) p->update();
    }
}

void SceneBodyFlow::drawSkeleton(int indx)
{
    ofPushMatrix();
    ofPushStyle();
    
    auto& joints = mSkeletons.at(indx)->getJoints();
    
    ofNoFill();
    const float s{1.f + indx / 200.f * 3.f};
    ofScale(s, s, s);
    
    for (size_t i=0; i<joints.size(); i++) {
        ofSetLineWidth(1.0f);
        auto& n = mSkeletons.at(indx)->getJoint(i);
        if (i == ofxMot::JOINT_HIPS) n.setGlobalPosition(ofVec3f::zero());
        n.transformGL();
        mPoints.at(i)->draw();
        n.restoreTransformGL();
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}

void SceneBodyFlow::draw()
{
    mCam.begin();
    ofPushMatrix();
    ofTranslate(100.f, 0.f);
    ofRotateX(13.f);
    ofRotateY(47.f);
    
    ofTranslate(200.f, -60.f, -200.f - mSkeletons.size() * 10.f);
    
    for (int i=0; i<mSkeletons.size(); i++) {
        ofTranslate(0.f,
                    0.f,
                    10.f);
        ofSetColor(ofColor::white, 64);
        drawSkeleton(i);
    }
    ofPopMatrix();
    mCam.end();
}

#pragma mark ___________________________________________________________________
void SceneBodyFlow::onUpdateSkeleton(ofxMotioner::EventArgs &e)
{
    auto skl = e.skeleton;
    
    if (mSkeletonName=="") mSkeletonName = skl->getName();
    
    if (mSkeletonName == skl->getName()) {
        auto copy = ofxMot::Skeleton::copy(skl);
        mSkeletons.push_back(copy);
        
        while (mSkeletons.size() > kNumSkeletons) {
            mSkeletons.pop_front();
        }
    }
}

DP_SCORE_NAMESPACE_END