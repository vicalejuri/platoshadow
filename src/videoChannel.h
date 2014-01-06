#pragma once

#include "ofMain.h"

class VideoChannel {
    /*
     * A video channel. Can contain at least 4 videos
     */
    public:
        ofFbo                 output;
        vector<ofVideoPlayer> videoSlots;

        int width, height;
        int active_slot;            // Active slot
        bool active;

        VideoChannel();
        void init(int width, int height);

        bool loadMovie(string movie_path);

        void play();
        void play(int new_slot);
        void stop();

        void update();
        void draw();
};
