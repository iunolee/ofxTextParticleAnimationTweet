#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    fontSize = 20;
    forceValue = 0.005;
    
    //socket part
    isConnected = false;
    address = "http://67.205.153.66:9999";
    status = "not connected";
    socketIO.setup(address);
    ofAddListener(socketIO.notifyEvent, this, &ofApp::gotEvent);
    ofAddListener(socketIO.connectionEvent, this, &ofApp::onConnection);
    
    
    // screen setup
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofBackground(255);
    
    
    // set color list
    colors = new ofColor[9];
    
    // initial value
    colors[0].r = 0;
    colors[0].g = 0;
    colors[0].b = 0;
    
    // joy
    colors[1].r = 248;
    colors[1].g = 198;
    colors[1].b = 51;
    
    // trust
    colors[2].r = 178;
    colors[2].g = 187;
    colors[2].b = 58;
    
    // fear
    colors[3].r = 10;
    colors[3].g = 108;
    colors[3].b = 67;
    
    // surprise
    colors[4].r = 6;
    colors[4].g = 128;
    colors[4].b = 157;
    
    // sadness
    colors[5].r = 118;
    colors[5].g = 59;
    colors[5].b = 123;
    
    // disgust
    colors[6].r = 145;
    colors[6].g = 30;
    colors[6].b = 71;
    
    // anger
    colors[7].r = 186;
    colors[7].g = 39;
    colors[7].b = 58;
    
    // anticipation
    colors[8].r = 216;
    colors[8].g = 97;
    colors[8].b = 43;
    
    
    // emotion list
    emotionKeywords = {"confused", "rejected", "helpless", "submissive", "insecure", "anxious", "hurt", "hostile", "angry", "selfish", "hateful", "critical", "tired", "bored", "lonely", "depressed", "ashamed", "guilty", "gloomy", "excited", "sensuous", "energetic", "cheerful", "creative", "aware", "proud", "respected", "appreciated", "important", "faithful", "nurturing", "trusting", "loving", "intimate", "thoughtful", "content", "curious", "interest", "expect", "amaze", "astonish", "distract", "bored", "dislike", "loath"};
    
    joy = {"excited", "sensuous", "energetic", "cheerful", "creative"};
    trust = {"aware", "proud", "respected", "appreciated", "important", "faithful", "nurturing", "trusting", "loving", "intimate", "thoughtful", "content"};
    fear = {"confused", "rejected", "helpless", "submissive", "insecure", "anxious"};
    surprise = {"amaze", "astonish", "distract"};
    sadness = {"tired", "bored", "lonely", "depressed", "ashamed", "guilty", "gloomy"};
    disgust = {"bored", "dislike", "loath"};
    anger = {"hurt", "hostile", "angry", "selfish", "hateful", "critical"};
    anticipation = {"curious", "interest", "expect"};
    
    
    // set keycode
    otherWordsDisapper = false;
    rainDrop = false;
}

//--------------------------------------------------------------

void ofApp::initTweetDataProcessing() {
    
    // tweetData processingt
    bool parsingSuccessful = tweetData.open("tweetSearchData1113.json");
    
    if (parsingSuccessful)
    {
        for (int i=0; i < selectionPool.size(); i++) {
            string joySelection = joy[ofRandom(joy.size())];
            string trustSelection = trust[ofRandom(trust.size())];
            string fearSelection = fear[ofRandom(fear.size())];
            string surpriseSelection = surprise[ofRandom(surprise.size())];
            string sadnessSelection = sadness[ofRandom(sadness.size())];
            string disgustSelection = disgust[ofRandom(disgust.size())];
            string angerSelection = anger[ofRandom(anger.size())];
            string anticipationSelection = anticipation[ofRandom(anticipation.size())];
            
            int randomNum = int(ofRandom(10));
            
            if (selectionPool[i] == 1) {
                string temp = tweetData[joySelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 2) {
                string temp = tweetData[trustSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 3) {
                string temp = tweetData[fearSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 4) {
                string temp = tweetData[surpriseSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 5) {
                string temp = tweetData[sadnessSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 6) {
                string temp = tweetData[disgustSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 7) {
                string temp = tweetData[angerSelection][randomNum].asString();
                tweetText.push_back(temp);
            } else if (selectionPool[i] == 8) {
                string temp = tweetData[anticipationSelection][randomNum].asString();
                tweetText.push_back(temp);
            }
        }
        tweetTextFinal = accumulate(begin(tweetText), end(tweetText), tweetTextFinal);
        //        cout << tweetTextFinal << endl;
        cout<<"tweet data processing done"<<endl;
    }
    else
    {
        ofLogNotice("ofApp::setup")  << "Failed to parse JSON" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::initTextParticle(){
    /* init text particle */
    vector<string> letters;
    letters = ofSplitString(tweetTextFinal, " ");
    
    font.setup("BEBAS___.ttf", 1.0, 1024, false, 0, 1);
    
    //    make word particle
    ofRectangle firstbbox = font.getBBox(letters[0], fontSize, 0, 0);
    float fontHeight = firstbbox.height;
    
    float xPosition = -firstbbox.width;
    float yPosition = fontHeight/2;
    
    ofRectangle spacebbox = font.getBBox("s", fontSize, 0, 0);
    float space = spacebbox.width;
    cout << letters.size() << endl;
    
    for (int i = 0; i < letters.size(); i++){
        ofRectangle currentbbox = font.getBBox(letters[i], fontSize, 0, 0);
        float currentFontWidth = currentbbox.width;
        particle myParticle;
        myParticle.setInitialCondition(xPosition,yPosition,0, 0, 0, 0);
        myParticle.particleFontSize = fontSize;
        myParticle.angle = 0;
//        myParticle.angleSpeed = ofRandom(-0.5, 0.5);
        //        myParticle.damping = ofRandom(0.01, 0.04);
        myParticle.finalWord = letters[i];
        myParticle.opacity = 255;
        
        ofColor assignedColor;
        if(find(joy.begin(), joy.end(), letters[i]) != joy.end()) {
            myParticle.fontColor = colors[1];
            assignedColor = colors[1];
        } else if(find(trust.begin(), trust.end(), letters[i]) != trust.end()) {
            myParticle.fontColor = colors[2];
            assignedColor = colors[2];
        } else if(find(fear.begin(), fear.end(), letters[i]) != fear.end()) {
            myParticle.fontColor = colors[3];
            assignedColor = colors[3];
        } else if(find(surprise.begin(), surprise.end(), letters[i]) != surprise.end()) {
            myParticle.fontColor = colors[4];
            assignedColor = colors[4];
        } else if(find(sadness.begin(), sadness.end(), letters[i]) != sadness.end()) {
            myParticle.fontColor = colors[5];
            assignedColor = colors[5];
        } else if(find(disgust.begin(), disgust.end(), letters[i])!= disgust.end()) {
            myParticle.fontColor = colors[6];
            assignedColor = colors[6];
        } else if(find(anger.begin(), anger.end(), letters[i]) != anger.end()) {
            myParticle.fontColor = colors[7];
            assignedColor = colors[7];
        } else if(find(anticipation.begin(), anticipation.end(), letters[i]) != anticipation.end()) {
            myParticle.fontColor = colors[8];
            assignedColor = colors[8];
        } else {
            myParticle.fontColor = colors[0];
            assignedColor = colors[0];
        }
        
        
        //        make letter particle
        if(find(emotionKeywords.begin(), emotionKeywords.end(), letters[i]) != emotionKeywords.end()) {
            
            string currentLetter = letters[i];
            
            float xPositionLetter = xPosition;
            float yPositionLetter = yPosition;
            
            for(int j=0; j<currentLetter.size(); j++) {
                char s = currentLetter[j];
                string singleLetter = ofToString(s);
                ofRectangle letterbbox = font.getBBox(singleLetter, fontSize, 0, 0);
                float currentLetterWidth = letterbbox.width;
                particle letterParticle;
                letterParticle.setInitialCondition(xPositionLetter,yPositionLetter,0, 0, 0, 0);
                letterParticle.particleFontSize = fontSize;
                letterParticle.angle = 0;
                letterParticle.angleSpeed = ofRandom(-1.5, 1.5);
                letterParticle.scatterdForceX = ofRandom(-forceValue, forceValue);
                letterParticle.scatterdForceY = ofRandom(0, forceValue*2);
                letterParticle.scatterdForceZ = ofRandom(-forceValue, forceValue);
                letterParticle.raindropForceX = 0;
                letterParticle.raindropForceY = ofRandom(forceValue*0.5, forceValue);
                letterParticle.raindropForceZ = ofRandom(-forceValue*0.2, forceValue*0.2);
                letterParticle.damping = ofRandom(forceValue*0.01, forceValue*0.05);
                letterParticle.finalWord = singleLetter;
                letterParticle.opacity = 255;
                letterParticle.fontColor = assignedColor;
                letterParticles.push_back(letterParticle);
                
                xPositionLetter = xPositionLetter + currentLetterWidth;
            }
        }
        
        //        position each word
        if(xPosition > ofGetWindowSize()[0]) {
            yPosition = yPosition + fontHeight * 1.2;
            xPosition = 0;
        } else {
            xPosition = xPosition + currentFontWidth + space;
        }
        
        particles.push_back(myParticle);
    }
}

//--------------------------------------------------------------


void ofApp::update(){
//    for (int i = 0; i < particles.size(); i++){
//        particles[i].resetForce();
//        particles[i].addDampingForce();
//        particles[i].update();
//    }
    
    if(otherWordsDisapper) {
        for (int i = 0; i < particles.size(); i++){
            if(find(emotionKeywords.begin(), emotionKeywords.end(), particles[i].finalWord) == emotionKeywords.end()) {
                particles[i].disappearOtherWords();
                if(particles[i].opacity==0) {
                    particles.erase(particles.begin()+i);
                }
            }
        }
    }
    
    if(scattered) {
        for (int i = 0; i < letterParticles.size(); i++){
            letterParticles[i].resetForce();
            letterParticles[i].addScatteredForce();
            letterParticles[i].addDampingForce();
//            letterParticles[i].addRaindropForce();
            letterParticles[i].update();
        }
    }
    
    if(rainDrop) {
        for (int i = 0; i < letterParticles.size(); i++){
            letterParticles[i].resetForce();
            letterParticles[i].addRaindropForce();
            letterParticles[i].update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    font.beginBatch();
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw(&font);
    }
    
    if(scattered) {
        for (int i = 0; i < letterParticles.size(); i++){
            letterParticles[i].draw(&font);
        }
    }
    font.endBatch();
}

//--------------------------------------------------------------
void ofApp::eraseAllWordParticle(){
    particles.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 't') {
        initTweetDataProcessing();
    }
    if(key == 'p') {
        initTextParticle();
    }
    if(key == 'd') {
        otherWordsDisapper = !otherWordsDisapper;
    }
    if(key == 'r') {
        rainDrop = !rainDrop;
    }
    if(key == 'e') {
        scattered = !scattered;
        eraseAllWordParticle();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::onConnection () {
    isConnected = true;
    bindEvents();
}

void ofApp::bindEvents () {
    std::string serverEventName = "server-event";
    socketIO.bindEvent(serverEvent, serverEventName);
    ofAddListener(serverEvent, this, &ofApp::onServerEvent);
}

void ofApp::gotEvent(string& name) {
    status = name;
}

//--------------------------------------------------------------
void ofApp::onServerEvent (ofxSocketIOData& data) {
    int gotData = data.getIntValue("intData");
    for(int i=0; i<30; i++) {
        selectionPool.push_back(gotData);
    }
    
    cout << selectionPool.size() << endl;
    cout << selectionPool[selectionPool.size()-1] << endl;
}

