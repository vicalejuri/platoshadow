#include "videoChannel.h"

VideoChannel::VideoChannel(){}

void VideoChannel::init( int width, int height){
    if(videoSlots.size() != 0){
        ofLogWarning("VideoChannel") << "VideoChannel: Already initialized. Cleaning all loaded videos.";
        videoSlots.clear();
    }

    this->width = width;
    this->height = height;
    output.allocate( width, height , GL_RGBA );

    active      = true;
    active_slot = 0;
}

bool VideoChannel::loadMovie(string movie_path){
    ofVideoPlayer vid_player;
    vid_player.loadMovie( movie_path );

    if(! vid_player.isLoaded()){
        ofLogWarning("VideoChannel") << "Could not load video: " << ofToString(movie_path) << std::endl;
        return false;
    }

    ofLog() << "Loaded " << movie_path << std::endl;

    videoSlots.push_back( vid_player );
    return true;
}

void VideoChannel::play(int new_slot){
    if(new_slot < 0 && new_slot > videoSlots.size()){
        ofLogWarning("VideoChannel") << "Could not change to video slot " << ofToString(new_slot) << std::endl;
        return;
    }

    int old_slot = active_slot;
    active_slot  = new_slot;

    videoSlots[old_slot].stop();
    videoSlots[active_slot].play();
}

void VideoChannel::play(){
    videoSlots[active_slot].play();
}

void VideoChannel::stop(){
    videoSlots[active_slot].stop();
}

void VideoChannel::update(){
    videoSlots[active_slot].update();
}

void VideoChannel::draw(){
    output.begin();
    videoSlots[active_slot].draw(0,0);
    output.end();
}

