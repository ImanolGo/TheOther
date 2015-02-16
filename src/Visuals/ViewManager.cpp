/*
 *  ViewManager.cpp
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */


#include "BasicVisual.h"
#include "VisualEffectsManager.h"
#include "VisualEffects.h"
#include "ViewManager.h"

#include "../Main/AppManager.h"

#include "ofMain.h"


ViewManager::ViewManager(): m_showDebugInfo(false)
{
	// intentionally left empty
}

ViewManager::~ViewManager()
{
    ofLogNotice() <<"ViewManager::destructor";
}


void ViewManager::setup()
{
    if(m_initialized)
        return;

    Manager::setup();

    this->setupTextVisuals();
    this->addListeners();

    ofLogNotice() << "ViewManager::initialized ";
}

void ViewManager::setupTextVisuals()
{
    ofVec3f position(42,16);
    float fontSize = 16;
    float width = 256;
    float height = fontSize;
    string text = "";
    string fontName ="fonts/trade/TradeGothicLTStd.ttf";
    ofColor textColor = ofColor::black;

    m_frameRateText = ofPtr<TextVisual> (new TextVisual(position,width,height));
    m_frameRateText->setText(text,fontName,fontSize,textColor);
}

void ViewManager::addListeners()
{
    ofAddListener(ofEvents().keyPressed,this, &ViewManager::keyPressed);
}


void ViewManager::update()
{
    if(m_showDebugInfo){
        string text = "fps: " + ofToString(ofGetFrameRate(), 2);
        m_frameRateText->setText(text);
	}
}

void ViewManager::draw()
{
	this->drawOverlays();

	if(m_showDebugInfo){
        m_frameRateText->draw();
	}
}

void ViewManager::drawOverlays()
{
    for(OverlayList::reverse_iterator it = m_overlays.rbegin(); it != m_overlays.rend(); it++)
    {
		ofPushMatrix();
		it->second->draw();
		ofPopMatrix();
	}

}

void ViewManager::addOverlay(ofPtr<BasicVisual> visual,int zOrder)
{
    if(!visual){
        return;
    }

    if(isOverlayAlreadyAdded(visual)){
        return;
    }
    
	m_overlays.push_back(Overlay(zOrder,visual));
	m_overlays.sort();
}


void ViewManager::removeOverlay(ofPtr<BasicVisual> visual)
{
    if(!visual){
        return;
    }

	for(OverlayList::iterator it = m_overlays.begin(); it != m_overlays.end();) {
		if(it->second == visual) {
            AppManager::getInstance().getVisualEffectsManager()->removeAllVisualEffects(it->second);
			it = m_overlays.erase(it);
		}
		else {
			++it;
		}
	}
}

bool ViewManager::isOverlayAlreadyAdded(ofPtr<BasicVisual> visual)
{
    if(!visual)
        return true;

	for(OverlayList::iterator it = m_overlays.begin(); it != m_overlays.end(); ++it) {
		if(it->second == visual) {
           return true;
		}
	}

	return false;
}

void ViewManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    if(key == ' ') {
        m_showDebugInfo = !m_showDebugInfo;
    }
}




