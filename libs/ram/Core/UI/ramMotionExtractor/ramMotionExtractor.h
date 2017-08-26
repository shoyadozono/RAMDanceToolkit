//
//  ramMotionExtractor.h
//  RAMDanceToolkit
//
//  Created by Ovis aries on 2014/12/26.
//
//

#ifndef __RAMDanceToolkit__ramMotionExtractor__
#define __RAMDanceToolkit__ramMotionExtractor__

#include "ramMain.h"

namespace rdtk{
	
	class MotionPort;
	
	class MotionExtractor{
	public:
		
		/*=== Must call for use ===*/
		void setupControlPanel(BaseScene* scene_,
							   ofVec2f canvasPos = ofVec2f(240,30));
		void update();
		void draw();
		
		/*=== Getter ===*/
		int				getNumPort();
		bool			getIsExist(int port);
		
		Node			getNodeAt(int port);
		string			getActorNameAt(int port);
		string			getJointNameAt(int port);
		int				getJointIdAt(int port);
		int				getActorIndexAt(int port);
		
		ofVec3f			getPositionAt(int port,bool fixPosition = false);
		ofQuaternion	getRotationAt(int port);
		
		ofVec3f			getVelocityAt(int port);
		float			getVelocitySpeedAt(int port);
		ofQuaternion	getRotateVelocityAt(int port);
		float			getDistanceAt(int port_A, int port_B);
		float			getAreaAt(int port_A, int port_B, int port_C);
		
		/*=== Utilities ===*/
		void clearPorts();
		void save(string file);
		void load(string file);
		
		void pushFromID(int actorId, int jointId);
		void pushPort(MotionPort *mp, int actorId = -1);
		void popPort(NodeFinder &nf);
		void setActorList(vector<string>* lst);
		void refleshActorFromList();
		void mouseReleased(ofMouseEventArgs &arg);
		
		vector<MotionPort*>	mMotionPort;
		ofxUISortableList*		actorList;
		
	protected:
		void guiEvent(ofxUIEventArgs &e);
		int getIndexFromName(string name);
		
		ofxUICanvasPlus*		parentGui;
		ofxUICanvas*			mGui;
		BaseScene*			mScenePtr;
		ofVec2f					mCurrentCanvasPos;
		float					mMotionSmooth;
		int						lastNumNodeArray;
		
		OscReceiveTag	receiver;
		bool				bEnableSync;
	};
	
	
	class MotionPort{
	public:
		
		MotionPort(const NodeIdentifer &nodeIdent){
			init(nodeIdent);
		}
		~MotionPort(){
			
		}
		
		void			init(NodeFinder nodeF);
		void			update(float smooth);
		void			refleshActorFromIndex();
		void			refleshActorFromName();
		
		bool			vecInitialize;
		bool			isBlank;
		
		int				mActorIndex;
		NodeFinder	mFinder;
		
		ofNode			mCurrentNode;
		ofNode			mBefNode;
		
		ofVec3f			mVelocity;
		ofVec3f			mVelocitySmoothed;
		ofQuaternion	mRotateVec;
		ofQuaternion	mRotateVecSmoothed;
		
	};

}

typedef rdtk::MotionExtractor RAMDEPRECATED(ramMotionExtractor);
typedef rdtk::MotionPort RAMDEPRECATED(ramMotionPort);

#endif /* defined(__RAMDanceToolkit__ramMotionExtractor__) */