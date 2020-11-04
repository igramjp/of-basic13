#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 48000;
    bufferSize = 256;
    inputs = 0;
    outputs = 2;
    amp = 0.5;
    pan = 0.5;
    phase = 0;
    frequency = 440;
    waveSharpe = 1;
    ofSetFrameRate(30);
    ofBackground(ofColor::black);
    
    ofSoundStreamSettings settings;
    settings.setInListener(this);
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numInputChannels = 0;
    settings.numOutputChannels = 2;
    settings.bufferSize = 512;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float audioHeight = ofGetHeight() / 2.0f;
    float phaseDiff = ofGetWidth() / float(bufferSize);
    
    ofSetColor(255, 255, 255);
    ofNoFill();
    ofSetLineWidth(1);
    
    ofBeginShape();
    for (int i=0; i<bufferSize; i++) {
        ofVertex(i * phaseDiff, audioHeight/2 + lAudio[i] * audioHeight);
    }
    ofEndShape();
    
    ofBeginShape();
    for (int i=0; i<bufferSize; i++) {
        ofVertex(i * phaseDiff, audioHeight/2 * 3 + rAudio[i] * audioHeight);
    }
    ofEndShape();

    ofSetColor(ofColor::white);
    ofDrawBitmapString("L: " + ofToString(lAudio[0]), 10, 20);
    ofDrawBitmapString("R: " + ofToString(rAudio[0]), 10, 35);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '-':
            amp -= 0.05;
            amp = MAX(amp, 0);
            break;
        case '+':
            amp += 0.05;
            amp = MIN(amp, 1);
            break;
        case '1':
            waveSharpe = 1;
            break;
        case '2':
            waveSharpe = 2;
            break;
        case '3':
            waveSharpe = 3;
            break;
        case '4':
            waveSharpe = 4;
            break;
        case '5':
            waveSharpe = 5;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pan = (float)x / (float)ofGetWidth();
    
    float heightPct = (float(ofGetHeight() - y) / float(ofGetHeight()));
    frequency = 4000.0f * heightPct;
    if (frequency < 20) {
        frequency = 20;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
/*
void ofApp::audioRequested(float* output, int bufferSize, int nChannels){
    float sample;
    float phaseDiff;
    
    phaseDiff = TWO_PI * frequency / sampleRate;
    
    for (int i=0; i<bufferSize; i++) {
        phase += phaseDiff;
        while (phase > TWO_PI) {
            phase -= TWO_PI;
        }
        
        //sample = sin(phase);
        
        switch (waveSharpe) {
            case 1:
                sample = sin(phase);
                break;
            case 2:
                sample = - phase / PI + 1;
                break;
            case 3:
                sample = (phase < PI) ? -1: 1;
                break;
            case 4:
                sample = (phase < PI) ? -2 / PI * phase + 1: 2 / PI * phase - 3;
                break;
            case 5:
                sample = ofRandom(-1, 1);
        }
        
        lAudio[i] = output[i * nChannels] = sample * (1.0 - pan) * amp;
        rAudio[i] = output[i * nChannels + 1] = sample * pan * amp;
    }
}
*/

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &output){
    const int frames = output.getNumFrames();
    const int channels = output.getNumChannels();
    float sample;
    float phaseDiff;
    
    phaseDiff = TWO_PI * frequency / sampleRate;
    
    for (int i=0; i<frames; i++) {
        phase += phaseDiff;
        while (phase > TWO_PI) {
            phase -= TWO_PI;
        }
        
        //sample = sin(phase);
        
        switch (waveSharpe) {
            case 1:
                sample = sin(phase);
                break;
            case 2:
                sample = - phase / PI + 1;
                break;
            case 3:
                sample = (phase < PI) ? -1: 1;
                break;
            case 4:
                sample = (phase < PI) ? -2 / PI * phase + 1: 2 / PI * phase - 3;
                break;
            case 5:
                sample = ofRandom(-1, 1);
        }
        
        lAudio[i] = output[i * channels] = sample * (1.0 - pan) * amp;
        rAudio[i] = output[i * channels + 1] = sample * pan * amp;
    }
}
