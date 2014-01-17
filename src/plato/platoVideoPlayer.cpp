#include "platoVideoPlayer.h"

platoVideoPlayer::platoVideoPlayer(ofPtr<ofVideoPlayer> p){
    player = p;
};

platoVideoPlayer::platoVideoPlayer(string movie_p){

    if(player == NULL){
        player = ofPtr<ofVideoPlayer>(new ofVideoPlayer);
        player->setPixelFormat( OF_PIXELS_RGB );
        //player->setUseTexture( false );
    }
    load_movie( movie_p );
}

platoVideoPlayer::~platoVideoPlayer(){
    player->close();
}

/*
 * Load a movie from disk
 */
bool platoVideoPlayer::load_movie(string movie_path){
    ofLogNotice("platoVideoPlayer") << "Loading..." << movie_path << endl;
    bool _loaded = player->loadMovie(movie_path);
    if(! _loaded ){
        ofLogError("platoVideoPlayer") << "Couldnt load video: " << movie_path.c_str() << endl;
        return _loaded;
    }

    ofLogNotice("platoVideoPlayer:") << movie_path << "dimensions: " << player->width << "x" << player->height << endl;
    ofLogNotice("platoVideoPlayer:") << movie_path << "duration: " << player->getDuration() << " seconds" << endl;

    this->params_flush();

    //player->play();
    player->setLoopState( OF_LOOP_NONE );
    player->setPaused(true);

    return _loaded;
}

void platoVideoPlayer::update(){

    /*
     * Go front or backwards ?
     */
    player->update();

    playhead.pos = player->getPosition();
}

void platoVideoPlayer::draw(){
    this->draw(0.0f, 0.0f);
}

void platoVideoPlayer::draw(float x, float y){
    int time = ofGetElapsedTimeMicros();

    ofPushMatrix();
    ofPushStyle();
        ofSetColor( color );
        ofScale( scale.x, scale.y );

        //glDrawPixels(player->getWidth(),player->getHeight(),GL_RGB, GL_UNSIGNED_BYTE, player->getPixels());
        player->draw(0,0);
    ofPopStyle();
    ofPopMatrix();

    ofLogVerbose("platoVideoPlayer:perf:draw") << ofGetElapsedTimeMicros() - time << endl;
}

bool platoVideoPlayer::isFrameNew(){
    return player->isFrameNew();
}


void platoVideoPlayer::play(){
    player->setPaused(false);
}

void platoVideoPlayer::pause(){
    player->setPaused(false);
}

void platoVideoPlayer::stop(){
    player->setPaused(true);
}

void platoVideoPlayer::params_flush(){
    player->setVolume( volume );
    player->setSpeed( playhead.speed );
}

void platoVideoPlayer::updatePlayheadBounds( float _low, float _high){
    int frame_start = floor(_low * player->getTotalNumFrames());
    int frame_end   = floor(_high * player->getTotalNumFrames());

    playhead.start = _low;
    playhead.end   = _high;
    playhead.start_frame = frame_start;
    playhead.end_frame   = frame_end;

    return;
}
