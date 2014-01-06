#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground( 0, 0, 0 );
    ofSetVerticalSync(true);

    ofLog() << "Loading movie" << "movies/carsten.mp4";
    channel1.init(800, 600);
    channel1.loadMovie("movies/carsten.mp4");
    channel1.play();

    //channel2.init(800, 600);
}

//--------------------------------------------------------------
void testApp::update(){
    channel1.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    // Render the movie to OUTPUT
    //channel1.draw();
	ofDrawBitmapString("test", 10, 10);

    // Draw the output plz
    //channel1.output.draw(0,0);
    channel1.videoSlots[0].draw(0,0);

	ofDrawBitmapString("test", 500, 10);
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
