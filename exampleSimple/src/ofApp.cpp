#include "ofApp.h"

#define PREVIEW_WIDTH 1280
#define PREVIEW_HEIGHT 720

//--------------------------------------------------------------
void ofApp::setup(){
	auto deviceList = ofxBlackmagic::Iterator::getDeviceList();

	sceneIndex = 0;

	buffer.allocate(1920, 1080);
	ofxNestedFileLoader loader;
	vector<string> vidNames = loader.load("hapVideos");
	loader.printPaths();

	//Useful constants
	float gridWidth = ofGetScreenWidth() / 3;
	float gridHeight = ofGetScreenHeight() / 3;
	float left = 0.;
	float middleX = gridWidth;
	float right = gridWidth * 2;
	float top = 0.;
	float middleY = gridHeight;
	float bottom = gridHeight * 2;

	ofVec4f topLeft1 = ofVec4f(left, top, gridWidth, gridHeight);
	ofVec4f topLeft4 = ofVec4f(left, top, gridWidth*2, gridHeight*2);
	ofVec4f topLeft9 = ofVec4f(left, top, gridWidth*3, gridHeight*3);
	ofVec4f topMiddle1 = ofVec4f(middleX, top, gridWidth, gridHeight);
	ofVec4f topMiddle4 = ofVec4f(middleX, top, gridWidth*2, gridHeight*2);
	ofVec4f topRight1 = ofVec4f(right, top, gridWidth, gridHeight);
	ofVec4f middleLeft1 = ofVec4f(left, middleY, gridWidth, gridHeight);
	ofVec4f middleLeft4 = ofVec4f(left, middleY, gridWidth*2, gridHeight*2);
	ofVec4f middleMiddle1 = ofVec4f(middleX, middleY, gridWidth, gridHeight);
	ofVec4f middleMiddle4 = ofVec4f(middleX, middleY, gridWidth*2, gridHeight*2);
	ofVec4f middleRight1 = ofVec4f(right, middleY, gridWidth, gridHeight);
	ofVec4f bottomLeft1 = ofVec4f(left, bottom, gridWidth, gridHeight);
	ofVec4f bottomMiddle1 = ofVec4f(middleX, bottom, gridWidth, gridHeight);
	ofVec4f bottomRight1 = ofVec4f(right, bottom, gridWidth, gridHeight);

	//Scene construction //
	//CCTV
	Scene cctv;
	cctv.setName("CCTV");
	cctv.addLiveInput(0, topLeft1);
	cctv.addVideo(vidNames, topMiddle1);
	cctv.addLiveInput(1, topRight1);
	cctv.addVideo(vidNames, middleLeft1);
	cctv.addLiveInput(2, middleMiddle1);
	cctv.addVideo(vidNames, middleRight1);
	cctv.addLiveInput(3, bottomLeft1);
	cctv.addVideo(vidNames, bottomMiddle1);
	cctv.addVideo(vidNames, bottomRight1);
	scenes.push_back(cctv);

	//CCTVCamera Repeats
	Scene cctvCameraRepeats;
	cctvCameraRepeats.setName("CCTVCamRepeats");
	cctvCameraRepeats.addLiveInput(0, topLeft1);
	cctvCameraRepeats.addLiveInput(3, topMiddle1);
	cctvCameraRepeats.addLiveInput(0, topRight1);
	cctvCameraRepeats.addLiveInput(1, middleLeft1);
	cctvCameraRepeats.addLiveInput(3, middleMiddle1);
	cctvCameraRepeats.addLiveInput(1, middleRight1);
	cctvCameraRepeats.addLiveInput(2, bottomLeft1);
	cctvCameraRepeats.addLiveInput(3, bottomMiddle1);
	cctvCameraRepeats.addLiveInput(2, bottomRight1);
	scenes.push_back(cctvCameraRepeats);

	//CCTV SelfieGrid
	Scene cctvSelfieGrid;
	cctvSelfieGrid.setName("SelfieGrid");
	cctvSelfieGrid.addLiveInput(0, topLeft1);
	cctvSelfieGrid.addLiveInput(0, topMiddle1);
	cctvSelfieGrid.addLiveInput(0, topRight1);
	cctvSelfieGrid.addLiveInput(0, middleLeft1);
	cctvSelfieGrid.addLiveInput(0, middleMiddle1);
	cctvSelfieGrid.addLiveInput(0, middleRight1);
	cctvSelfieGrid.addLiveInput(0, bottomLeft1);
	cctvSelfieGrid.addLiveInput(0, bottomMiddle1);
	cctvSelfieGrid.addLiveInput(0, bottomRight1);
	scenes.push_back(cctvSelfieGrid);

	//CCTV Hero Grid
	Scene cctvSelfieHero;
	cctvSelfieHero.setName("SelfieHero");
	cctvSelfieHero.addLiveInput(0, topLeft9);
	scenes.push_back(cctvSelfieHero);

	//MiniLaunch
	Scene miniLaunch;
	miniLaunch.setName("Mini Launch");
	miniLaunch.addLiveInput(0, topLeft1);
	miniLaunch.addVideo(vidNames, topMiddle1);
	miniLaunch.addLiveInput(0, topRight1);
	miniLaunch.addVideo(vidNames, middleLeft1);
	miniLaunch.addVideo(vidNames, middleMiddle1);
	miniLaunch.addVideo(vidNames, middleRight1);
	miniLaunch.addLiveInput(0, bottomLeft1);
	miniLaunch.addVideo(vidNames, bottomMiddle1);
	miniLaunch.addLiveInput(0, bottomRight1);
	scenes.push_back(miniLaunch);

	//Hero Launch
	Scene heroLaunch;
	heroLaunch.setName("Hero Launch");
	heroLaunch.addVideo(vidNames, topLeft9);
	scenes.push_back(heroLaunch);

	//Mixed
	Scene mixed;
	mixed.setName("Mixed");
	mixed.addVideo(vidNames, topLeft4);
	mixed.addVideo(vidNames, topRight1);
	mixed.addVideo(vidNames, middleRight1);
	mixed.addVideo(vidNames, bottomRight1);
	mixed.addVideo(vidNames, bottomMiddle1);
	mixed.addVideo(vidNames, bottomLeft1);
	scenes.push_back(mixed);

	//Infleuncer Yuki
	Scene influencerYuki;
	influencerYuki.setName("Influencer Yuki");
	influencerYuki.addVideo(vidNames, topLeft4);
	influencerYuki.addVideo(vidNames, topRight1);
	influencerYuki.addVideo(vidNames, middleRight1);
	influencerYuki.addVideo(vidNames, bottomRight1);
	influencerYuki.addVideo(vidNames, bottomMiddle1);
	influencerYuki.addVideo(vidNames, bottomLeft1);
	scenes.push_back(influencerYuki);

	//Infleuncer Iman
	Scene influencerIman;
	influencerIman.setName("Influencer Iman");
	influencerIman.addVideo(vidNames, topLeft4);
	influencerIman.addVideo(vidNames, topRight1);
	influencerIman.addVideo(vidNames, middleRight1);
	influencerIman.addVideo(vidNames, bottomRight1);
	influencerIman.addVideo(vidNames, bottomMiddle1);
	influencerIman.addVideo(vidNames, bottomLeft1);
	scenes.push_back(influencerIman);

	//Infleuncer Luka
	Scene influencerLuka;
	influencerLuka.setName("Influencer Luka");
	influencerLuka.addVideo(vidNames, topLeft4);
	influencerLuka.addVideo(vidNames, topRight1);
	influencerLuka.addVideo(vidNames, middleRight1);
	influencerLuka.addVideo(vidNames, bottomRight1);
	influencerLuka.addVideo(vidNames, bottomMiddle1);
	influencerLuka.addVideo(vidNames, bottomLeft1);
	scenes.push_back(influencerLuka);

	//Infleuncer ButlerReese
	Scene influencerButlerReese;
	influencerButlerReese.setName("Influencer Butler&Reese");
	influencerButlerReese.addVideo(vidNames, topLeft4);
	influencerButlerReese.addVideo(vidNames, topRight1);
	influencerButlerReese.addVideo(vidNames, middleRight1);
	influencerButlerReese.addVideo(vidNames, bottomRight1);
	influencerButlerReese.addVideo(vidNames, bottomMiddle1);
	influencerButlerReese.addVideo(vidNames, bottomLeft1);
	scenes.push_back(influencerButlerReese);

	//myFuture
	Scene myfutureIs;
	myfutureIs.setName("#MYFUTUREIS");
	myfutureIs.addVideo(vidNames, topLeft1);
	myfutureIs.addVideo(vidNames, topRight1);
	myfutureIs.addVideo(vidNames, bottomMiddle1);
	myfutureIs.addLiveInput(0, topMiddle1);
	myfutureIs.addLiveInput(1, bottomLeft1);
	myfutureIs.addLiveInput(2, bottomRight1);
	myfutureIs.addVideo(vidNames, left, middleY, 3 * gridWidth, gridHeight);
	scenes.push_back(myfutureIs);

	//Hero Launch
	Scene screenSaver;
	screenSaver.setName("ScreenSaver");
	screenSaver.addVideo(vidNames, topLeft9);
	scenes.push_back(screenSaver);

	gui.setup("Main", "scenes.xml");

	scenesToggleGroup.setName("Scenes");
	for (int i = 0; i < scenes.size(); i++) {
		scenes[i].setLiveInputs(&inputs);
		scenes[i].setVideoPlayers(&players);
		scenes[i].setIndex(i);
		scenes[i].setName(ofToString(i) + ". " + scenes[i].getName());
		scenesToggleGroup.add(*scenes[i].getToggleButton());
	}

	gui.add(scenesToggleGroup);
	gui.add(sceneIndex.set("Scene Number", 0, 0, scenes.size()-1));

	playlist experienceplaylist;
	experienceplaylist.name = "Experience";
	experienceplaylist.scenesAndDurations.push_back(make_pair(30., 0));
	experienceplaylist.scenesAndDurations.push_back(make_pair(15., 7));
	experienceplaylist.scenesAndDurations.push_back(make_pair(10., 11));
	experienceplaylist.scenesAndDurations.push_back(make_pair(30., 0));

	playlists.push_back(experienceplaylist);

	playlistToggleGroup.setName("playlists");
	for (int i = 0; i < playlists.size(); i++) {
		ofParameter<bool> playlistToggle;
		playlists[i].index = i;
		playlists[i].internalIndex = 0;
		playlistToggleGroup.add(playlistToggle.set(playlists[i].name, false));
	}
	playlistIndex.set("playlist Number", 0, 0, playlists.size() - 1);
	gui.add(playlistToggleGroup);
	gui.add(playlistIndex);
	gui.add(autoPlay.set("Auto Play", false));

	ofAddListener(scenesToggleGroup.parameterChangedE(), this, &ofApp::onSceneChanged);

	for (int i = 0; i < NUM_PLAYERS; i++) {
		players.push_back(new ofxDSHapVideoPlayer());
	}

	for(auto device : deviceList) {
		auto input = shared_ptr<ofxBlackmagic::Input>(new ofxBlackmagic::Input());
		auto mode = bmdModeHD1080i50;
		input->startCapture(device, mode);
		input->setUseTexture(true);
		this->inputs.push_back(input);
	}

	ofBackground(127);
}

//--------------------------------------------------------------
void ofApp::update(){
	scenes[sceneIndex].update();
	if (autoPlay) {
		playlist* activePlaylist = &playlists[playlistIndex];
		pair<float, int> currentPair = activePlaylist->scenesAndDurations[activePlaylist->internalIndex];
		float timeSinceLastSwap = ofGetElapsedTimef() - timeOfLastSceneSwap;
		if (timeSinceLastSwap > currentPair.first) {
			activePlaylist->internalIndex++;
			activePlaylist->internalIndex %= activePlaylist->scenesAndDurations.size();
			scenesToggleGroup.getBool(activePlaylist->scenesAndDurations[activePlaylist->internalIndex].second).set(true);
		}
		cout << activePlaylist->internalIndex << endl;
		cout << currentPair.first - timeSinceLastSwap << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	buffer.begin();
		ofClear(0);
		scenes[sceneIndex].draw();
	buffer.end();
	ofPushMatrix();
	ofTranslate(ofGetScreenWidth(), 0);
		buffer.draw(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(ofGetScreenWidth() / 2 - PREVIEW_WIDTH / 2, ofGetScreenHeight() / 2 - PREVIEW_HEIGHT / 2);
	buffer.draw(0, 0, PREVIEW_WIDTH, PREVIEW_HEIGHT);
	ofPopMatrix();
	gui.draw();

	ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetScreenWidth() - 100, ofGetScreenHeight() - 100);
}

//--------------------------------------------------------------
void ofApp::onSceneChanged(ofAbstractParameter & param) {
	string clickedName = param.getName();
	for (auto it = scenes.begin(); it != scenes.end(); it++) {
		string name = it->getName();
		if (name == clickedName) {
			scenesToggleGroup.getBool(name).setWithoutEventNotifications(true);
			sceneIndex = it->getIndex();
		}
		else {
			scenesToggleGroup.getBool(name).setWithoutEventNotifications(false);
		}
	}
	timeOfLastSceneSwap = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::onPlaylistChanged(ofAbstractParameter & param) {
	string clickedName = param.getName();
	for (auto it = playlists.begin(); it != playlists .end(); it++) {
		string name = it->name;
		if (name == clickedName) {
			playlistToggleGroup.getBool(name).setWithoutEventNotifications(true);
			sceneIndex = it->index;
		}
		else {
			playlistToggleGroup.getBool(name).setWithoutEventNotifications(false);
		}
	}
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
