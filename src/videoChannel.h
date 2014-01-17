#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxPSBlend.h"

#include "plato/platoVideoPlayer.h"
#include "gui/ofxUIVideoChannel.h"

// Gui Panel size
#define CHANNEL_GUI_W   340
#define CHANNEL_GUI_H   540

// Slider Size.
#define GUI_SLIDER_BWIDTH  180
#define GUI_SLIDER_BHEIGHT 16

/*
 *  Size in case of Horizontal or vertical
 */
#define GUI_SLIDER_W(ORIENT)     (ORIENT == 'H' ? GUI_SLIDER_BWIDTH : GUI_SLIDER_BHEIGHT )

#define GUI_SLIDER_H(ORIENT)     (ORIENT == 'H' ? GUI_SLIDER_BHEIGHT : GUI_SLIDER_BWIDTH )

class VideoChannel {
    /*
     * A video channel. Can contain many slots, each slot
     * is a video with its control parameters.
     *
     * Can play each slot at the time.
     */
    public:

        // size and name of Video ;Channel
        int width, height;;
        string name;

        /*
         * Output of this VideoChannel
         */
        ofFbo                   output;
        ofTexture               out_tex;

        // Gui Parameters
        ofxUISuperCanvas               *gui;
        ofxUIVideoChannel               *vid_preview;

        // Active slot
        bool   active;
        string active_slot;

        // Videos slots and its parameters
        vector<string>                   videos;
        map<string,platoVideoPlayer*>    videoSlots;

        // Blendmode
        vector<string> blend_mode_list;
        ofBlendMode blend_mode = OF_BLENDMODE_ALPHA;

        int ofx_blend_mode = 0;
        ofxPSBlend psBlend;

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

        platoVideoPlayer* getActivePlayer();

        void play();
        void stop();
        void begin();
        void end();

        void update();
        void draw();
};
