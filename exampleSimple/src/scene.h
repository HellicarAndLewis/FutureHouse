// Scene class for controlling output grid

#pragma once

#include "ofxBlackmagic.h"
#include "ofMain.h"
#include "ofxNestedFileLoader.h"
#include "ofxDSHapVideoPlayer.h"


class Scene {
public:
	Scene() {};
	//Getters
	float getDuration() { return duration; };

	//Setters
	void setVideoPlayers(vector<ofxDSHapVideoPlayer*>* _players) { videoPlayers = _players; };
	void setLiveInputs(vector<shared_ptr<ofxBlackmagic::Input> >* _inputs) { liveInputs = _inputs; };
	float setDuration(float _duration) { duration = _duration; };

	//Functionality
	void update();
	void draw();
	void addVideo(vector<string> vidPaths, float x = 0, float y = 0, float w = ofGetScreenWidth()/3, float h = ofGetHeight()/3);
	void addVideo(vector<string> vidPaths, ofVec4f locAndSize);
	void addLiveInput(int index, float x = 0, float y = 0, float w = ofGetScreenWidth() / 3, float h = ofGetHeight() / 3);
	void addLiveInput(int index, ofVec4f locAndSize);

private:
	struct videoOutput {
		float x, y, width, height;
		vector<string> vidPaths;
		int playerIndex;
		int videoFileIndex;
		float currentDuration;
		float timeOfLastSwap = 0;
	};

	struct liveOutput {
		float x, y, width, height;
		shared_ptr<ofxBlackmagic::Input>* input;
		int index;
	};

	float duration;

	vector<ofxDSHapVideoPlayer*>* videoPlayers;
	vector< shared_ptr<ofxBlackmagic::Input> >* liveInputs;

	vector<videoOutput> videoOutputs;
	vector<liveOutput> liveOutputs;

	void loadNewContent(videoOutput* video);
};
