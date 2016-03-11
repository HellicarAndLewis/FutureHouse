#pragma once

#include "ofxBlackmagic.h"
#include "ofMain.h"
#include "ofxNestedFileLoader.h"
#include "ofxDSHapVideoPlayer.h"
#include "scene.h"
#include "ofxGui.h"

#define NUM_PLAYERS 9

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	struct playlist {
		string name;
		int index;
		int internalIndex;
		vector< pair<float, int> > scenesAndDurations;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void exit();
	void onSceneChanged(ofAbstractParameter & param);
	void onPlaylistChanged(ofAbstractParameter & param);


	vector<shared_ptr<ofxBlackmagic::Input> > inputs;

	vector<ofxDSHapVideoPlayer*> players;

	vector<Scene> scenes;

	ofxPanel gui;
	ofParameterGroup scenesToggleGroup;
	ofParameterGroup playlistToggleGroup;
	ofParameter<int> sceneIndex;
	ofParameter<bool> autoPlay;
	ofParameter<int> playlistIndex;
	ofParameter<float> timeUntilNextSwap;
	ofParameter<int> currentPlaylistIndex;

	float timeOfLastSceneSwap;

	vector<playlist> playlists;

	ofFbo buffer;
};

