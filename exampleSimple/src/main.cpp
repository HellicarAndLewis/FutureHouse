#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
	ofAppGLFWWindow window;
	window.setMultiDisplayFullscreen(true);
	ofSetupOpenGL(&window, 1920 * 2, 1080, OF_WINDOW);			// <-------- setup the GL context

																// this kicks off the running of my app
																// can be OF_WINDOW or OF_FULLSCREEN
																// pass in width and height too:
	ofRunApp(new ofApp());

}
