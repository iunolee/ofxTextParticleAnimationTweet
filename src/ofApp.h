#pragma once

#include "ofMain.h"
#include "ofxSocketIO.h"
#include "ofxJSON.h"
#include "ofxFontStash.h"
#include "particle.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void eraseAll();
    void initTweetDataProcessing();
    void initTextParticle();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int fontSize;
    ofColor *colors;
//    ofTrueTypeFont font;
    ofxFontStash font;
    vector<particle> particles;

    float fx,fy,fz;
    
    bool otherWordsDisapper;
    bool rainDrop;

    
    vector<string> emotionKeywords;
    vector<string> joy;
    vector<string> trust;
    vector<string> fear;
    vector<string> surprise;
    vector<string> sadness;
    vector<string> disgust;
    vector<string> anger;
    vector<string> anticipation;
    
    vector<int> selectionPool;
    ofxJSONElement tweetData;
    vector<string> tweetText;
    string tweetTextFinal;


    //socket part
    ofxSocketIO socketIO;
    
    bool isConnected;
    void onConnection();
    void bindEvents();
    void gotEvent(std::string& name);
    void onServerEvent(ofxSocketIOData& data);
    
    ofEvent<ofxSocketIOData&> serverEvent;
    ofEvent<ofxSocketIOData&> pingEvent;
    ofEvent<ofxSocketIOData&> nspingEvent;
    
    std::string address;
    std::string status;
    
    

};
