#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#include "gui/ofxUIVideoChannel.h"

class VideoChannel {
    /*
     * A video channel. Can contain at least 4 videos
     */
    public:
        ofFbo                 output;
        // vector<ofVideoPlayer> videoSlots;

        // hash: Name of Video, VideoPlayer
        map<string,ofVideoPlayer> videoSlots;

        // Gui Parameters
        ofxUISuperCanvas               *gui;
        int width, height;
        string name;

        // Active slot
        bool active;
        string active_slot;

        VideoChannel();

        void init(string name, int width, int height);
        void init_gui( ofxUICanvas *shared_res );
        bool loadMovie(string movie_path);

        void guiEvent(ofxUIEventArgs &e);

        void play();
        void stop();

        void update();
        void draw();
};
