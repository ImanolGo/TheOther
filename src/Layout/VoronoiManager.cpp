/*
 *  VoronoiManager.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "ViewManager.h"

#include "ofxVoro.h"


#include "VoronoiManager.h"


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
    
    this->createVoronoiVisual();
    
}

void VoronoiManager::createVoronoiVisual()
{
    ofVec3f initialPosition = ofVec3f(0,0,0);
    m_voronoiVisual = ofPtr<VoronoiVisual> (new VoronoiVisual(initialPosition));
    AppManager::getInstance().getViewManager()->addVisual(m_voronoiVisual);
}

void VoronoiManager::draw()
{
    ofPushMatrix();
        //m_voronoiVisual->draw();
    ofPopMatrix();
}

void VoronoiManager::update()
{
    this->updateVoronoi();
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


void VoronoiManager::createVoronoi(int _width, int _height, int _deep){
    
    
    //  Define a container
    //
    
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    
    m_voronoiVisual->setCellMeshes(getCellsFromContainer(con,0.0));
    m_voronoiVisual->setCellMeshWireframes(getCellsFromContainer(con,0.0,true));
    m_voronoiVisual->setCellRadius(getCellsRadius(con));
    m_voronoiVisual->setCellCentroids(getCellsCentroids(con));
}




