#pragma once

#include "ofConstants.h"
#include "ofTexture.h"
#include "ofBaseTypes.h"
#include "ofTypes.h"
#include "ofGraphics.h"

#include "ofVideoPlayer.h"

#include "ofGstUtils.h"
#warning $(GST_VERSION_MAJOR)

class platoVideoPlayer {
    public:
        ofPtr<ofVideoPlayer>   player;

        struct {
            float start = 0.0f;
            float end   = 1.0f;
            float pos   = 0.0f;
            float speed = 1.0f;

            int start_frame = 0;
            int end_frame   = 0;
            ofLoopType loop_type = OF_LOOP_NORMAL;
        } playhead;

        float           volume = 0.0;
        ofVec2f         scale       = ofVec2f(1.0f,1.0f);
        ofFloatColor    color       = ofFloatColor(1.0f,1.0f,1.0f,1.0f);

        platoVideoPlayer(string movie_path);
        platoVideoPlayer(ofPtr<ofVideoPlayer> p);
        ~platoVideoPlayer();

        bool load_movie( string movie_path );

        void play();
        void pause();
        void stop();

        void update();

        void draw();
        void draw(float x, float y);

        bool isFrameNew();

        // You need to call this after updating video parameters,
        // to enable the changes
        void params_flush();

        void updatePlayheadBounds( float _low, float _high);
};
