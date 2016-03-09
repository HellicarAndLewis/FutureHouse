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
	cctvSelfieHero.addLiveInput(0, topLeft9);
	scenes.push_back(cctvSelfieHero);

	//MiniLaunch
	Scene miniLaunch;
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
	heroLaunch.addVideo(vidNames, topLeft9);
	scenes.push_back(heroLaunch);

	//Mixed
	Scene mixed;
	mixed.addVideo(vidNames, topLeft4);
	mixed.addVideo(vidNames, topRight1);
	mixed.addVideo(vidNames, middleRight1);
	mixed.addVideo(vidNames, bottomRight1);
	mixed.addVideo(vidNames, bottomMiddle1);
	mixed.addVideo(vidNames, bottomLeft1);
	scenes.push_back(mixed);




	for (int i = 0; i < scenes.size(); i++) {
		scenes[i].setLiveInputs(&inputs);
		scenes[i].setVideoPlayers(&players);
	}

	for (int i = 0; i < NUM_PLAYERS; i++) {
		players.push_back(new ofxDSHapVideoPlayer());
//		players[i]->load(vidNames[7]);
//		players[i]->play();
//		players[i]->setPaused(false);
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
	/*
	for(auto input : this->inputs) {
		input->update();
	}
	for (int i = 0; i < NUM_PLAYERS; i++) {
		players[i]->update();
	}
	*/
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
	/*
	float x = 0; float y = 0;
	float width = ofGetScreenWidth() / 3; 
	float height = ofGetScreenHeight() / 3;
	ofSetColor(255);
/*	for(auto input : this->inputs) {
		input->draw(x, y, width, height);
		x += width;
		if (x >= ofGetWidth()) {
			x = 0;
			y += height;
		}
	}
	*/
	/*
	for (int i = 0; i < NUM_PLAYERS; i++) {
		players[i]->draw(x, y);
		ofPopMatrix();
		x += width;
		if (x >= ofGetScreenWidth()) {
			x = 0;
			y += height;
		}
	}

	if (this->inputs.empty()) {
		ofDrawBitmapString("No BlackMagic input devices found", 20, 20);
	}
	*/
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	sceneIndex++;
	sceneIndex %= scenes.size();
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
