#include "videoChannel.h"


VideoChannel::VideoChannel(){}
VideoChannel::~VideoChannel(){
    for(map<string,platoVideoPlayer*>::iterator it = videoSlots.begin() ; it != videoSlots.end(); it++ ){
        platoVideoPlayer *vid = it->second;

        delete vid;
    }

    delete gui;
}

void VideoChannel::init( string name , int width, int height){
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

    // Blend modes
    this->blend_mode_list.push_back("normal");
    this->blend_mode_list.push_back("multiply");
    this->blend_mode_list.push_back("average");
    this->blend_mode_list.push_back("add");
    this->blend_mode_list.push_back("subtract");
    this->blend_mode_list.push_back("difference");
    this->blend_mode_list.push_back("negation");
    this->blend_mode_list.push_back("exclusion");
    this->blend_mode_list.push_back("screen");
    this->blend_mode_list.push_back("overlay");
    this->blend_mode_list.push_back("softlight");
    this->blend_mode_list.push_back("hardlight");
    this->blend_mode_list.push_back("colordodge");
    this->blend_mode_list.push_back("colorburn");
    this->blend_mode_list.push_back("linearlight");
    this->blend_mode_list.push_back("vividlight");
    psBlend.setup( output.getWidth(), output.getHeight() );

    active      = false;
    active_slot = "";
}

void VideoChannel::init_gui(ofxUICanvas *shared_res){
    gui = new ofxUISuperCanvas( name, 0, 0, CHANNEL_GUI_W, CHANNEL_GUI_H, shared_res, OFX_UI_FONT_MEDIUM );
    //gui->setAutoDraw(false);
    //gui->setDrawBack(false);
    gui->addSpacer();

    // Video Preview
    vid_preview = new ofxUIVideoChannel( float(320.0), float(240.0), &out_tex, name);
    gui->addWidgetDown( vid_preview );

    // Colors
    gui->addWidgetDown( new ofxUILabel("Color", OFX_UI_FONT_MEDIUM) );
    gui->addSlider("R", 0.0, 1.0, 1.0f , \
            GUI_SLIDER_W('V'), GUI_SLIDER_H('V'));
	gui->setWidgetPosition( OFX_UI_WIDGET_POSITION_RIGHT );
    gui->addSlider("G", 0.0, 1.0, 1.0f , \
            GUI_SLIDER_W('V'), GUI_SLIDER_H('V'));
    gui->addSlider("B", 0.0, 1.0, 1.0f , \
            GUI_SLIDER_W('V'), GUI_SLIDER_H('V'));
    gui->addSlider("A", 0.0, 1.0, 1.0f , \
            GUI_SLIDER_W('V'), GUI_SLIDER_H('V'));

	gui->setWidgetPosition( OFX_UI_WIDGET_POSITION_DOWN );

    /*
    // Range and Speed
    ofxUIRangeSlider *ui_range = new ofxUIRangeSlider( "Range", 0.0f, 1.0f,  \
                                                                0.0f, 1.0f, \
                                            GUI_SLIDER_W('H')*2, GUI_SLIDER_H('H'));
    //gui->addWidgetWestOf( ui_range , "Color");
    gui->addWidgetDown(ui_range);

    ofxUIMinimalSlider *ui_playhead = new ofxUIMinimalSlider("Playhead", 0.0, 1.0f, 0.0f, \
                                            GUI_SLIDER_W('H')*2, GUI_SLIDER_H('H'));
    //gui->addWidgetWestOf( ui_playhead, "G" );
    gui->addWidgetDown(ui_playhead);

    ofxUIMinimalSlider *ui_speed = new ofxUIMinimalSlider("Speed", -1.0, 2.0f, 1.0f, \
                                            GUI_SLIDER_W('H'), GUI_SLIDER_H('H'));
    //gui->addWidgetWestOf(ui_speed, "B");
    gui->addWidgetDown(ui_speed);

    */

    // Add Blend mode
    ofxUIDropDownList *ui_blend = new ofxUIDropDownList("BLEND", blend_mode_list, GUI_SLIDER_W('H'));
    ui_blend->setAutoClose(true);
    ui_blend->setShowCurrentSelected(true);
    gui->addWidgetDown( ui_blend );

    //gui->addSpacer(255-16,2);IDE
    //gui->addToggle("D_GRID", true, 16, 16);

    gui->autoSizeToFitWidgets();
    ofAddListener( gui->newGUIEvent, this, &VideoChannel::guiEvent );
}

bool VideoChannel::loadMovie(string movie_path){
    /*
     * Creates a new instance of platoVideoPlayer.
     *
     *
     */
    platoVideoPlayer *p         = new platoVideoPlayer( movie_path );

    // Store the movie name
    active_slot            = movie_path;
    videos.push_back( movie_path );

    // Store on a new slot, with key = movie_path
    videoSlots[movie_path] = p;

    ofLog(OF_LOG_NOTICE) << "VideoChannel:" << name << ": Loaded '" << movie_path << "' to slot " << videos.size()-1 << endl;

    return true;
}






platoVideoPlayer* VideoChannel::getActivePlayer(){
    return videoSlots[active_slot];
}





void VideoChannel::play(){
    getActivePlayer()->play();
}

void VideoChannel::stop(){
    getActivePlayer()->stop();
}

void VideoChannel::begin(){
    getActivePlayer()->playhead.pos = 0.0f;
    getActivePlayer()->params_flush();
}

void VideoChannel::end(){
    getActivePlayer()->playhead.end = 0.0f;
    getActivePlayer()->params_flush();
}






void VideoChannel::changeSlot(int c_slot){
    if( videoSlots.size() < c_slot ){
        ofLogWarning("VideoChannel") << this->name << ": Invalid Slot " << c_slot << endl;
        return;
    }

    // Pause previous slot
    getActivePlayer()->pause();

    // Change active player
    active_slot     = videos[c_slot];

    getActivePlayer()->play();
}

void VideoChannel::changeSlot(string slot_name){
    //if( videoSlots. )
    return;
}

void VideoChannel::update(){
    platoVideoPlayer *vid_player = getActivePlayer();

    // Update video, wee
    vid_player->update();

    return;
}






void VideoChannel::draw(){
    platoVideoPlayer *vid_player = getActivePlayer();

    output.begin();
        vid_player->draw();
    output.end();

    return;
}


















void VideoChannel::saveSettings(){
    gui->saveSettings( ofToString("gui/" + this->name + ".xml"));
}

void VideoChannel::guiEvent(ofxUIEventArgs &e){
    ofLog() << "guiEvent sent to " << e.widget->getName();
    string w_name = e.widget->getName();

    platoVideoPlayer *p = getActivePlayer();
    float speed = 0.0f;
    float r,g,b,a;
    float range_start, range_end;

    // _dirty implies
    bool _dirty = false;

    // Apply the changes to the movie
    if(w_name == "Speed"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        p->playhead.speed = s->getScaledValue();
    }else if(w_name == "Range"){
        ofxUIRangeSlider *s = (ofxUIRangeSlider *)(e.widget);

        float ss = (s->getScaledValueLow());
        float ee = (s->getScaledValueHigh());

        p->updatePlayheadBounds(ss,ee);

    /*
     * Colors
     */
    }else if(w_name == "R"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        p->color.r = s->getScaledValue();
    }else if(w_name == "G"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        p->color.g = s->getScaledValue();
    }else if(w_name == "B"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        p->color.b = s->getScaledValue();
    }else if(w_name == "A"){
        ofxUISlider *s = (ofxUISlider *)(e.widget);
        p->color.a = s->getScaledValue();

    /*
     * Blend mode
     */
    }else if(w_name == "BLEND"){
        ofxUIDropDownList *s = (ofxUIDropDownList *)(e.widget);
        vector<int> t = (s->getSelectedIndeces());

        if(t.size() < 1)
            return;

        ofLogNotice() << blend_mode_list[t[0]] << endl;
        string blend_mode_str = blend_mode_list[t[0]];

        if(blend_mode_str == "normal"){
            blend_mode = OF_BLENDMODE_ALPHA;
            ofx_blend_mode = 0;
        } else if(blend_mode_str == "multiply"){
            blend_mode = OF_BLENDMODE_ADD;
            ofx_blend_mode = 1;
        } else if(blend_mode_str == "average"){
            blend_mode = OF_BLENDMODE_ADD;
            ofx_blend_mode = 2;
        } else if(blend_mode_str == "add"){
            blend_mode = OF_BLENDMODE_ADD;
            ofx_blend_mode = 3;
        } else if(blend_mode_str == "subtract"){
            blend_mode = OF_BLENDMODE_ADD;
            ofx_blend_mode = 4;
        }else {
            blend_mode = OF_BLENDMODE_DISABLED;
            ofx_blend_mode = 0;
        }
    }

    /*
     *  Update the values of current movie
     */
    p->params_flush();
}
