#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#include "gui/ofxUIVideoChannel.h"

#define CHANNEL_GUI_SIZE_W 340
#define CHANNEL_GUI_SIZE_H 540

#define SLIDER_SIZE_W 16
#define SLIDER_SIZE_H 80

class VideoChannel {
    /*
     * A video channel. Can contain at least 4 videos
     */
    public:
        ofFbo                   output;
        ofTexture               out_tex;

        // hash: Name of Video, VideoPlayer
        map<string,ofVideoPlayer>   videoSlots;
        std::vector<string>         videoNames;

        // Gui Parameters
        ofxUISuperCanvas               *gui;
        ofxUIVideoChannel               *vid_preview;

        // Active slot
        bool active;
        string active_slot;

        // size and name of Video Channel
        int width, height;
        string name;

        ofFloatColor color = ofFloatColor(1.0f,1.0f,1.0f,1.0f);

        struct {
            float start = 0.0f;
            float end   = 1.0f;
            float pos   = 0.0f;
            float speed = 1.0f;
        } playhead;


        VideoChannel();
        ~VideoChannel();

        // Allocate FBO
        void init(string name, int width, int height);

        // Start GUI
        void init_gui( ofxUICanvas *shared_res );


        /*
         * Callbacks
         */
        void saveSettings();
        void guiEvent(ofxUIEventArgs &e);


        /*
         * Actions
         *
         */
        bool loadMovie(string movie_path);

        void changeSlot(string slot_name);
        void changeSlot(int slot_index );

        void play();
        void stop();
        void begin();
        void end();

        void setSpeed(float x);
        float getSpeed();

        void update();
        void draw();
};
