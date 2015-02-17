/*
 *  VoronoiManager.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"
#include "ViewManager.h"

#include "ofxVoro.h"


#include "VoronoiManager.h"

const int VoronoiManager::NUMBER_OF_CELLS = 100;

VoronoiManager::VoronoiManager()
{
	//Intentionally left empty
}


VoronoiManager::~VoronoiManager()
{
    ofLogNotice() <<"VoronoiManager::Destructor";
}


void VoronoiManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"VoronoiManager::initialized";

	Manager::setup();
    
    this->createSeeds();
}

void VoronoiManager::draw()
{
    ofPushMatrix();
    
    for (int i = 0; i < m_cellCentroids.size(); i++){
        ofSetColor(0);
        ofSphere(m_cellCentroids[i], m_cellRadius[i]*0.15);
        m_seeds[i]->draw();
    }
    
    for (int i = 0; i < m_seeds.size(); i++){
       // ofPushMatrix();
        //ofTranslate(m_seeds[i]->getPosition());
        m_seeds[i]->draw();
        //ofPopMatrix();
    }
    
    for(int i = 0; i < m_cellMeshes.size(); i++){
        ofSetColor(100,0,0,30);
        //ofSetColor(ofRandom(255),30);
        m_cellMeshes[i].drawFaces();
        
        ofPushStyle();
        ofSetLineWidth(3);
        ofSetColor(100);
        m_cellMeshWireframes[i].draw();
        ofPopStyle();
    }
    
    ofPopMatrix();
}

void VoronoiManager::update()
{
    this->updateSeeds();
    this->updateVoronoi();
}

void VoronoiManager::updateSeeds()
{
    float movementSpeed = .05;
    float cloudSize = ofGetWidth() / 2;
    float spacing = 1;
    
    
    for(int i = 0; i < m_seeds.size(); i++) {
        ofPushMatrix();
        
        float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
        ofVec3f pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    0);
        
        pos *= cloudSize;
        m_seeds[i]->setPosition(pos);
    }
}


void VoronoiManager::updateVoronoi()
{
    float appWidth =  AppManager::getInstance().getSettingsManager()->getAppWidth();
    float appHeight = AppManager::getInstance().getSettingsManager()->getAppHeight();
    int voronoiWidth = appWidth*1.2;
    int voronoiHeight = appHeight*1.2;
    int voronoiDepth = 30;
    
    this->createVoronoi(voronoiWidth, voronoiHeight, voronoiDepth);
}

void VoronoiManager::createSeeds()
{
    ofLogNotice() <<"VoronoiManager::createSeeds";
    for (int i = 0; i < NUMBER_OF_CELLS; i++){
        ofPtr<SeedVisual> seed = ofPtr<SeedVisual>(new SeedVisual(ofVec3f(0,0,0)));
        m_seeds.push_back(seed);
    }
}


void VoronoiManager::createVoronoi(int _width, int _height, int _deep){
    
    //  Fresh begining
    //
    m_cellMeshes.clear();
    m_cellCentroids.clear();
    m_cellRadius.clear();
    
    //  Define a container
    //
    
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    
    //  Add the cell seed to the container
    //
    for(int i = 0; i < m_seeds.size();i++){
        ofPoint newCell = m_seeds[i]->getPosition();
        addCellSeed(con, newCell, i, true);
    }
    
    
    
    m_cellMeshes = getCellsFromContainer(con,0.0);
    m_cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    m_cellRadius = getCellsRadius(con);
    m_cellCentroids = getCellsCentroids(con);
}




