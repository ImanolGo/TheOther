/*
 *  SeedsManager.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "ViewManager.h"


#include "SeedsManager.h"

const int SeedsManager::NUMBER_OF_SEEDS= 50;

SeedsManager::SeedsManager()
{
	//Intentionally left empty
}


SeedsManager::~SeedsManager()
{
    ofLogNotice() <<"SeedsManager::Destructor";
}


void SeedsManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"SeedsManager::initialized";

	Manager::setup();
    
    this->createSeeds();
}


void SeedsManager::createSeeds()
{
    ofLogNotice() <<"SeedsManager::createSeeds";
    for (int i = 0; i < NUMBER_OF_SEEDS; i++){
        ofPtr<Seed> seed = ofPtr<Seed>(new Seed(ofVec3f(0,0,0)));
        m_seeds.push_back(seed);
        AppManager::getInstance().getViewManager()->addVisual(seed);
    }
}

void SeedsManager::draw()
{
    
    ofPushMatrix();
    
    for (int i = 0; i < m_seeds.size(); i++){
        //this->billboardBegin();
        m_seeds[i]->draw();
        //this->billboardEnd();
    }
    
    ofPopMatrix();
}

void SeedsManager::update()
{
    this->updateSeeds();
}

void SeedsManager::updateSeeds()
{
    float movementSpeed = .05;
    float cloudSize = ofGetWidth() / 2;
    float spacing = 1;
    
    
    for(int i = 0; i < m_seeds.size(); i++) {
        
        float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
        ofPoint pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    ofSignedNoise(0, 0, 0));
        
        pos *= cloudSize;
        m_seeds[i]->setPosition(pos);
    }
}









