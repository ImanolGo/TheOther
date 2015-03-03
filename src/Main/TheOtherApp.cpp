/*
 *  TheOtherApp.cpp
 *  The Other
 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#include "AppManager.h"

#include "TheOtherApp.h"

//--------------------------------------------------------------
void TheOtherApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void TheOtherApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void TheOtherApp::draw(){
    AppManager::getInstance().draw();
}

void TheOtherApp::exit()
{
    ofLogNotice() <<"TheOtherApp::exit";

}

//--------------------------------------------------------------
void TheOtherApp::keyPressed(int key){

}

//--------------------------------------------------------------
void TheOtherApp::keyReleased(int key){

}

//--------------------------------------------------------------
void TheOtherApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void TheOtherApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOtherApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOtherApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOtherApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void TheOtherApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void TheOtherApp::dragEvent(ofDragInfo dragInfo){

}
