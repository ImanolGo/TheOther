/*
 *  TheOthersApp.cpp
 *  The Other
 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#include "AppManager.h"

#include "TheOtherApp.h"

//--------------------------------------------------------------
void TheOthersApp::setup(){
    AppManager::getInstance().setup();
}

//--------------------------------------------------------------
void TheOthersApp::update(){
    AppManager::getInstance().update();
}

//--------------------------------------------------------------
void TheOthersApp::draw(){
    AppManager::getInstance().draw();
}

void TheOthersApp::exit()
{
    ofLogNotice() <<"TheOthersApp::exit";

}

//--------------------------------------------------------------
void TheOthersApp::keyPressed(int key){

}

//--------------------------------------------------------------
void TheOthersApp::keyReleased(int key){

}

//--------------------------------------------------------------
void TheOthersApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void TheOthersApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOthersApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOthersApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void TheOthersApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void TheOthersApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void TheOthersApp::dragEvent(ofDragInfo dragInfo){

}
