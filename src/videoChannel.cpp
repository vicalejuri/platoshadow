#include "videoChannel.h"


VideoChannel::VideoChannel(){}
VideoChannel::~VideoChannel(){
    for(map<string,ofVideoPlayer>::iterator it = videoSlots.begin() ; it != videoSlots.end(); it++ ){
        ofVideoPlayer &vid = it->second;

        vid.closeMovie();
    }

    delete gui;
}


void VideoChannel::init( string name, int width, int height ){
    if(videoSlots.size() != 0){
        ofLogWarning("VideoChannel") << "VideoChannel: Already initialized. Cleaning all loaded videos.";
        videoSlots.clear();
    }

    this->name   = ofToString("C" + name);
    this->width = width;
    this->height = height;

    // FBO and texture
    output.allocate( width , height , GL_RGBA );
    out_tex = output.getTextureReference();

    active      = false;
    active_slot = "";
}

void VideoChannel::init_gui(ofxUICanvas *shared_res){
    gui = new ofxUISuperCanvas( name, 0, 0, CHANNEL_GUI_SIZE_W, CHANNEL_GUI_SIZE_H, shared_res, OFX_UI_FONT_MEDIUM );
    //gui->setAutoDraw(false);
    //gui->setDrawBack(false);
    gui->addSpacer();

    // Video Preview
    vid_preview = new ofxUIVideoChannel( float(320.0), float(240.0), &out_tex, name);
    gui->addWidgetDown( vid_preview );

    // Colors
    gui->addWidgetDown( new ofxUILabel("Color", OFX_UI_FONT_MEDIUM) );
    gui->addSlider("R", 0.0, 1.0, &color.r , SLIDER_SIZE_W, SLIDER_SIZE_H);
	gui->setWidgetPosition( OFX_UI_WIDGET_POSITION_RIGHT );
    gui->addSlider("G", 0.0, 1.0, &color.g , SLIDER_SIZE_W, SLIDER_SIZE_H);
    gui->addSlider("B", 0.0, 1.0, &color.b , SLIDER_SIZE_W, SLIDER_SIZE_H);
    gui->addSlider("A", 0.0, 1.0, &color.a , SLIDER_SIZE_W, SLIDER_SIZE_H);

    // Range and Speed
    ofxUIRangeSlider *ui_range = new ofxUIRangeSlider( "range", 0.0f, 1.0f, &playhead.start, &playhead.end, SLIDER_SIZE_H*2, SLIDER_SIZE_W );
    //gui->addWidgetWestOf( ui_range , "Color");
    gui->addWidgetDown(ui_range);

    ofxUIMinimalSlider *ui_playhead = new ofxUIMinimalSlider("Playhead", 0.0, 1.0f, &playhead.pos, SLIDER_SIZE_H*2, SLIDER_SIZE_W );
    //gui->addWidgetWestOf( ui_playhead, "G" );
    gui->addWidgetDown(ui_playhead);

    ofxUIMinimalSlider *ui_speed = new ofxUIMinimalSlider("Speed", -1.0, 2.0f, &playhead.speed, SLIDER_SIZE_H, SLIDER_SIZE_W );
    //gui->addWidgetWestOf(ui_speed, "B");
    gui->addWidgetDown(ui_speed);

    //gui->addSpacer(255-16,2);IDE
    //gui->addToggle("D_GRID", true, 16, 16);

    //gui->autoSizeToFitWidgets();
    ofAddListener( gui->newGUIEvent, this, &VideoChannel::guiEvent );
}

bool VideoChannel::loadMovie(string movie_path){
    /*
     * Creates a new instance of VideoPlayer.
     */
    ofVideoPlayer vid_player;
    //vid_player.setUseTexture( false );
    vid_player.loadMovie( movie_path );

    if(! vid_player.isLoaded()){
        ofLogWarning("VideoChannel") << "Could not load video: " << ofToString(movie_path) << std::endl;
        return false;
    }

    active_slot            = movie_path;
    videoSlots[movie_path] = vid_player;

    // Save videoName
    videoNames.push_back( movie_path );

    ofLog() << name << ": Loaded '" << movie_path << "' to slot " << videoNames.size()-1 << std::endl;

    return true;
}

void VideoChannel::play(){
    ofVideoPlayer &vid_player = videoSlots[active_slot];
    vid_player.play();
}

void VideoChannel::stop(){
    ofVideoPlayer &vid_player = videoSlots[active_slot];
    vid_player.stop();
}

void VideoChannel::begin(){
    ofVideoPlayer &vid_player = videoSlots[active_slot];
    vid_player.setPosition(0.0f);
}

void VideoChannel::end(){
    ofVideoPlayer &vid_player = videoSlots[active_slot];
    vid_player.setPosition(1.0f);
}

void VideoChannel::setSpeed(float x){
    ofVideoPlayer &vid_player = videoSlots[active_slot];

    vid_player.setSpeed( x );
    playhead.speed = x;

    return;
}

float VideoChannel::getSpeed(){
    return playhead.speed;
}

void VideoChannel::changeSlot(int c_slot){
    if( videoSlots.size() < c_slot ){
        ofLogWarning("VideoChannel") << this->name << ": Invalid Slot " << c_slot << endl;
        return;
    }

    // Pause previous slot
    ofVideoPlayer &c_player = videoSlots[active_slot];
    c_player.stop();

    // Play current video
    active_slot     = videoNames[c_slot];
    c_player        = videoSlots[active_slot];
    c_player.play();
}

void VideoChannel::changeSlot(string slot_name){
    //if( videoSlots. )
    return;
}

void VideoChannel::update(){
    ofVideoPlayer &vid_player = videoSlots[active_slot];

    // Update video, wee
    vid_player.update();

    // Update playhead pos
    playhead.pos = vid_player.getPosition();

    if(vid_player.isFrameNew()){
        //playhead.pos = vid_player.getPosition();
        //ofLog() << "new Frame" << endl;
    }

    //videoSlots[active_slot].update();
    ofPushStyle();
    output.begin();
        ofEnableAlphaBlending();

        ofSetColor( color );
        vid_player.draw( 0, 0 );

    output.end();
    ofPopStyle();

    return;
}

void VideoChannel::draw(){
    //output.draw(0,0);
}


void VideoChannel::saveSettings(){
    gui->saveSettings( ofToString("gui/" + this->name + ".xml"));
}

void VideoChannel::guiEvent(ofxUIEventArgs &e){
    ofLog() << "guIEvent sent to " << e.widget->getName();
    string w_name = e.widget->getName();
    if(w_name == "Speed"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        setSpeed( s->getScaledValue() );
    }
}
