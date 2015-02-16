/*
 *  TheOthersApp.cpp
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#include "AppManager.h"

#include "TheOtherApp.h"

//--------------------------------------------------------------
void OpenCommonsApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void OpenCommonsApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void OpenCommonsApp::draw(){
    AppManager::getInstance().draw();
}

void OpenCommonsApp::exit()
{
    ofLogNotice() <<"TheOthersApp::exit";

}

//--------------------------------------------------------------
void OpenCommonsApp::keyPressed(int key){

}

//--------------------------------------------------------------
void OpenCommonsApp::keyReleased(int key){

}

//--------------------------------------------------------------
void OpenCommonsApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void OpenCommonsApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void OpenCommonsApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void OpenCommonsApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void OpenCommonsApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void OpenCommonsApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void OpenCommonsApp::dragEvent(ofDragInfo dragInfo){

}
