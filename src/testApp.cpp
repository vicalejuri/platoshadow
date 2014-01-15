#include "testApp.h"


void testApp::setup_gui(){
    gui = new ofxUICanvas();
    //gui->setAutoDraw(false);
    //gui->setDrawBack(false);
    gui->setFont("gui/Inconsolata-Regular.ttf");
    gui->setFontSize( OFX_UI_FONT_LARGE , 10 );
    gui->setFontSize( OFX_UI_FONT_MEDIUM , 8 );
    gui->setFontSize( OFX_UI_FONT_SMALL,   6 );

    //gui->addLabel("Plato", OFX_UI_FONT_LARGE);
    //gui->addSpacer();
    //gui->addFPSSlider("FPS");

    // Autosize and register events
    gui->autoSizeToFitWidgets();
    ofAddListener( gui->newGUIEvent, this, &testApp::guiEvent );
    gui->loadSettings("gui/settings.xml");
}



void testApp::setup_videochannels(){
    /*
     * Load videoChannels
     */
    //VideoChannel *first_channel = new VideoChannel();

    //first_channel->init("1",800,600);
    //first_channel->init_gui( gui );
    //first_channel->gui->getRect()->setX( 320 );

    //first_channel->loadMovie( "movies/carsten.mp4" );
    //first_channel->play();

    VideoChannel *second = new VideoChannel();

    second->init("2",800,600);
    second->init_gui( gui );
    second->gui->getRect()->setX( 640 + 20 );
    second->loadMovie("movies/pi2.mov");
    second->play();

    // Save channel
    //channels.push_back( first_channel );;
    channels.push_back( second );
}

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground( ofColor(233,52,27) );
    //ofSetVerticalSync(false);
    ofEnableSmoothing();
    ofSetLogLevel( OF_LOG_VERBOSE );

    setup_gui();
    setup_videochannels();
}

void testApp::exit(){

    vector<VideoChannel*>::iterator it;
    for(it=channels.begin(); it != channels.end() ; it++){
        VideoChannel *chan = *(it);
        delete chan;
    }

    gui->saveSettings("gui/settings.xml");
    delete gui;
}

//--------------------------------------------------------------
void testApp::update(){

    // Update every video channel
    vector<VideoChannel*>::iterator it;
    for(it=channels.begin(); it != channels.end() ; it++){
        VideoChannel *chan = (*it);
        chan->update();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();

    // Render the movie to OUTPUT
    //channel1.draw();

    // Draw the output plz
    vector<VideoChannel*>::iterator it;
    for(it=channels.begin(); it != channels.end() ; it++){
        VideoChannel *chan = (*it);
        chan->draw();
    }

	ofDrawBitmapString("Hello World", 300, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    //}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}


void testApp::guiEvent( ofxUIEventArgs &e ){
    return;
}
