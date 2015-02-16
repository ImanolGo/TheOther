#include "ofMain.h"
#include "ofAppGLFWWindow.h"
#include "TheOtherApp.h"

//========================================================================
int main( ){

    ofAppGLFWWindow window;
	ofSetupOpenGL(&window,1024,648,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new OpenCommonsApp());

}
