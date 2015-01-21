//
//  dpScoreAnalyzeMean.h
//  dpScore
//
//  Created by YoshitoONISHI on 1/18/15.
//
//

#ifndef __dpScore__dpScoreAnalyzeMean__
#define __dpScore__dpScoreAnalyzeMean__

#include "dpScoreCommon.h"

DP_SCORE_NAMESPACE_BEGIN

class AnalyzeMean {
public:
    void update(ofVec4f mean);
    void draw();
    
    ofVec4f mMean;
    ofVec4f mMeanPrev;
    ofVec4f mMeanAddtion;
    floatInt mTotalAddition{0.f};
    float mMeanLimit{30.f};
    int mPrevScene{0};
    float mPrevSetSceneTime{0.f};
    float mMinSetSceneTime{60.f};
    float mLastUpdateSpan{0.f};
    float mLastFrameTime{0.f};
};

DP_SCORE_NAMESPACE_END

#endif /* defined(__dpScore__dpScoreAnalyzeMean__) */