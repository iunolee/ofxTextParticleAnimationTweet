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

void particle::addScatteredForce(){
    frc.x = frc.x + scatterdForceX;
    frc.y = frc.y + scatterdForceY;
    frc.z = frc.z + scatterdForceZ;
    angle = angle + angleSpeed;
}

void particle::addRaindropForce(){
    frc.x = frc.x + raindropForceX;
    frc.y = frc.y + raindropForceY;
    frc.z = frc.z + raindropForceZ;
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
    cout << "X: " << vel.x << " Y: " << vel.y << " Z: " << vel.z << endl;
}

void particle::disappearOtherWords(){
    opacity = opacity - 2;
}

void particle::draw(ofxFontStash * particleFont){
    ofPushMatrix();
    ofSetColor(fontColor, opacity);
    ofTranslate(pos.x, pos.y, pos.z);
    ofRotate(angle, 0.015, 0.03, 0.05);
    particleFont->drawBatch(finalWord, particleFontSize, 0, 0);
    ofPopMatrix();
}
