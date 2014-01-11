#include "videoChannel.h"

VideoChannel::VideoChannel(){}

void VideoChannel::init( string name, int width, int height ){
    if(videoSlots.size() != 0){
        ofLogWarning("VideoChannel") << "VideoChannel: Already initialized. Cleaning all loaded videos.";
        videoSlots.clear();
    }

    this->name   = name;
    this->width = width;
    this->height = height;

    // FBO
    output.allocate( width, height , GL_RGBA );

    active      = false;
    active_slot = "";
}

void VideoChannel::init_gui(ofxUICanvas *shared_res){
    gui = new ofxUISuperCanvas( "C01", 10, 10, 320, 560, shared_res, OFX_UI_FONT_MEDIUM );
    gui->setAutoDraw(false);
    gui->addSpacer();

    ofxUIVideoChannel *vid_preview = ofxUIVideoChannel(320, 240, output , "C01");
    gui->addWidgetDown( vid_preview );

    gui->addMinimalSlider("A", 0.0, 1.0 , 1.0 );
    gui->addToggleMatrix("Slots", 1, 8,"slots");

    gui->autoSizeToFitWidgets();
    ofAddListener( gui->newGUIEvent, this, &VideoChannel::guiEvent );
}

bool VideoChannel::loadMovie(string movie_path){
    ofVideoPlayer vid_player;
    vid_player.loadMovie( movie_path );

    if(! vid_player.isLoaded()){
        ofLogWarning("VideoChannel") << "Could not load video: " << ofToString(movie_path) << std::endl;
        return false;
    }

    ofLog() << "Loaded " << movie_path << std::endl;
    ofLog() << movie_path;

    active_slot = movie_path;
    videoSlots[movie_path] = vid_player;
    //videoSlots.push_back( vid_player );
    return true;
}

void VideoChannel::play(){
    videoSlots[active_slot].play();
}

void VideoChannel::stop(){
    videoSlots[active_slot].stop();
}

void VideoChannel::update(){
    videoSlots[active_slot].update();

    output.begin();
        videoSlots[active_slot].draw( 0, 0 );
    output.end();

    return;
}

void VideoChannel::draw(){
    //output.draw(0,0);
}

void VideoChannel::guiEvent(ofxUIEventArgs &e){
    ofLog() << "guIEvent sent to " << e.widget->getName();
}
