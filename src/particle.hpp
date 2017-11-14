//
//  particle.hpp
//  textAnimParticle2
//
//  Created by Youn ho Lee on 11/8/17.
//

#ifndef particle_hpp
#define particle_hpp

#include "ofMain.h"
#include "ofxFontStash.h"

class particle{
    
public:
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f frc;
    
    particle();
    
    void resetForce();
    void addForce(float x, float y, float z);
    void addDampingForce();
    void disappearOtherWords();
    void setInitialCondition(float px, float py, float pz, float vx, float vy, float vz);
    void update();
    void draw(ofxFontStash * particleFont);

    float damping;
    int particleFontSize;
    string finalWord;
    ofColor fontColor;
    float angle;
    float angleSpeed;
    float opacity;
};

#endif /* particle_hpp */

