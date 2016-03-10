#include "scene.h"

void Scene::update() {
	for (int i = 0; i < videoOutputs.size(); i++) {
		if ((*videoPlayers)[videoOutputs[i].playerIndex]->isLoaded()) {
			(*videoPlayers)[videoOutputs[i].playerIndex]->update();
		}
		else {
			loadNewContent(&videoOutputs[i]);
		}
		if (ofGetElapsedTimef() - videoOutputs[i].timeOfLastSwap > videoOutputs[i].currentDuration) {
			loadNewContent(&videoOutputs[i]);
		}
		
	}
	for (auto liveOutput : liveOutputs) {
		(*liveInputs)[liveOutput.index]->update();
	}
}

void Scene::draw() {
	for (auto videoOutput : videoOutputs) {
		ofPushMatrix();
		ofTranslate(videoOutput.x, videoOutput.y);
		ofScale(videoOutput.width / (*videoPlayers)[videoOutput.playerIndex]->getWidth(), videoOutput.height / (*videoPlayers)[videoOutput.playerIndex]->getHeight());
		(*videoPlayers)[videoOutput.playerIndex]->draw(0, 0);
		ofPopMatrix();
	}
	for (auto liveOutput : liveOutputs) {
		(*liveInputs)[liveOutput.index]->draw(liveOutput.x, liveOutput.y, liveOutput.width, liveOutput.height);
	}
}

void Scene::loadNewContent(videoOutput* video) {
	video->videoFileIndex++;
	video->videoFileIndex %= video->vidPaths.size();
	string nextContentName = video->vidPaths[video->videoFileIndex];
	vector<string> splitString = ofSplitString(nextContentName, ".");
	if (splitString[1] == "avi") {
		(*videoPlayers)[video->playerIndex]->stop();
//		(*videoPlayers)[video.playerIndex]->close();
		(*videoPlayers)[video->playerIndex]->load(nextContentName);
		(*videoPlayers)[video->playerIndex]->play();
		(*videoPlayers)[video->playerIndex]->setPaused(false);
		(*videoPlayers)[video->playerIndex]->setVolume(0.0);
		float duration = (*videoPlayers)[video->playerIndex]->getDuration();
		video->currentDuration = duration;
		video->timeOfLastSwap = ofGetElapsedTimef();
	}
}

void Scene::addVideo(vector<string> videoNames, ofVec4f locAndSize) {
	addVideo(videoNames, locAndSize.x, locAndSize.y, locAndSize.z, locAndSize.w);
}

void Scene::addVideo(vector<string> videoNames, float x, float y, float w, float h) {
	videoOutput newVideo;
	newVideo.vidPaths = videoNames;
	newVideo.x = x;
	newVideo.y = y;
	newVideo.width = w;
	newVideo.height = h;
	newVideo.playerIndex = videoOutputs.size() % 9;
	newVideo.videoFileIndex = 0;
	newVideo.currentDuration = 1;
	newVideo.timeOfLastSwap = ofGetElapsedTimef();
	videoOutputs.push_back(newVideo);
}
void Scene::addLiveInput(int index, ofVec4f locAndSize) {
	addLiveInput(index, locAndSize.x, locAndSize.y, locAndSize.z, locAndSize.w);
}
void Scene::addLiveInput(int index, float x, float y, float w, float h) {
	liveOutput newLive;
	newLive.x = x;
	newLive.y = y;
	newLive.width = w;
	newLive.height = h;
	newLive.index = index;
	liveOutputs.push_back(newLive);
}
