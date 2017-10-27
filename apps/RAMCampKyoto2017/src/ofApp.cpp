#include "ofApp.h"

#pragma mark - oF methods
//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	/// ram setup
	// ------------------
	rdtk::Initialize(10000, true);
	
	/// scenes setup
	// ------------------
	rdtk::SceneManager& sceneManager = rdtk::SceneManager::instance();

  // add your scene at here
    sceneManager.addScene<OrbitSystem>();
}

//--------------------------------------------------------------
void ofApp::update()
{
    ofSetWindowTitle("fps: " + ofToString(ofGetFrameRate(), 1));
}

//--------------------------------------------------------------
void ofApp::draw()
{
	
}



#pragma mark - ram methods
//--------------------------------------------------------------
void ofApp::drawActor(const rdtk::Actor &actor)
{
	
}

//--------------------------------------------------------------
void ofApp::drawRigid(const rdtk::RigidBody &rigid)
{
	
}

#pragma mark - ram Events

//--------------------------------------------------------------
void ofApp::onActorSetup(const rdtk::Actor &actor)
{
	
}

//--------------------------------------------------------------
void ofApp::onActorExit(const rdtk::Actor &actor)
{

}

//--------------------------------------------------------------
void ofApp::onRigidSetup(const rdtk::RigidBody &rigid)
{

}

//--------------------------------------------------------------
void ofApp::onRigidExit(const rdtk::RigidBody &rigid)
{

}



#pragma mark - of Event
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if ( key == 'f' )
    {
        ofToggleFullscreen();
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
	
}
