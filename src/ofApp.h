#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        /*
        void audioRequested(float * output, int bufferSize, int nChannels);
        */
        void audioOut(ofSoundBuffer &output);
    
        ofSoundStream soundStream;
        int sampleRate;
        int bufferSize;
        int inputs;
        int outputs;
        float pan;
        float amp;
        float phase;
        float frequency;
        int waveSharpe;
        float lAudio[256];
        float rAudio[256];
};
