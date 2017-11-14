#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//        ofSetupOpenGL(1280,720,OF_WINDOW);            // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    
    // for bigscreen
    ofGLFWWindowSettings settings;
    settings.windowMode = OF_FULLSCREEN;
    settings.multiMonitorFullScreen = true;
    ofCreateWindow(settings);
//
    ofRunApp(new ofApp());
    
}

