#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground( ofColor(233,52,27));
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    gui = new ofxUICanvas();
    gui->setFont("gui/Inconsolata-Regular.ttf");
    gui->setFontSize( OFX_UI_FONT_LARGE , 10 );
    gui->setFontSize( OFX_UI_FONT_MEDIUM , 8 );
    gui->setFontSize( OFX_UI_FONT_SMALL,   6 );

    gui->addLabel("Plato", OFX_UI_FONT_LARGE);
    gui->addSpacer();
    gui->addFPSSlider("FPS");

    // Autosize and register events
    gui->autoSizeToFitWidgets();
    ofAddListener( gui->newGUIEvent, this, &testApp::guiEvent );
    gui->loadSettings("gui/settings.xml");

    ofLog() << "Loading movie" << "movies/carsten.mp4";

    channel1.init("1", 800, 600);
    channel1.init_gui( gui );
    channel1.gui->getRect()->setX( 320 );

    channel1.loadMovie( "movies/carsten.mp4" );
    channel1.play();

    //channel2.init(800, 600);
}

void testApp::exit(){
    gui->saveSettings("gui/settings.xml");
    delete gui;
}

//--------------------------------------------------------------
void testApp::update(){
    channel1.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableAlphaBlending();

    // Render the movie to OUTPUT
    //channel1.draw();
	ofDrawBitmapString("test", 10, 10);

    // Draw the output plz
    channel1.output.draw(0,0);
    //channel1.output.draw( 500,0);
    //channel1.videoSlots[0].draw(0,0);

	//ofDrawBitmapString("test", 500, 10);.
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
