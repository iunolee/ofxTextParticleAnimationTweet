//
//  particle.cpp
//  textAnimParticle2
//
//  Created by Youn ho Lee on 11/8/17.
//

#include "particle.hpp"
particle::particle() {
}

void particle::resetForce(){
    frc.set(0, 0, 0);
}

void particle::addForce(float x, float y, float z){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
    frc.z = frc.z + z;
    angle = angle + angleSpeed;
}

void particle::addDampingForce(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
    frc.z = frc.z - vel.z * damping;
//    angle = angle - angleSpeed * damping;
}

void particle::setInitialCondition(float px, float py, float pz, float vx, float vy, float vz){
    pos.set(px, py, pz);
    vel.set(vx, vy, vz);
}

void particle::update(){
    vel = vel + frc;
    pos = pos + vel;
}

void particle::disappearOtherWords(){
    opacity = opacity - 2;
}

void particle::draw(ofxFontStash * particleFont){
    ofPushMatrix();
    ofSetColor(fontColor, opacity);
    ofTranslate(pos.x, pos.y, pos.z);
    ofRotate(angle, 0.15, 0.3, 0.5);
    particleFont->draw(finalWord, particleFontSize, 0, 0);
    ofPopMatrix();
}
