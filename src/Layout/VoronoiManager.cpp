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
    
    this->setupVoronoi();
}

void VoronoiManager::draw()
{
    ofPushMatrix();
    
    for (int i = 0; i < m_cellCentroids.size(); i++){
        ofSetColor(0);
        ofSphere(m_cellCentroids[i], m_cellRadius[i]*0.15);
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


void VoronoiManager::setupVoronoi()
{
    float appWidth =  AppManager::getInstance().getSettingsManager()->getAppWidth();
    float appHeight = AppManager::getInstance().getSettingsManager()->getAppHeight();
    int voronoiWidth = appWidth*0.9;
    int voronoiHeight = appHeight*0.9;
    int voronoiDepth = 20;
    
    this->createTissue(NUMBER_OF_CELLS, voronoiWidth, voronoiHeight, voronoiDepth);
    
}


void VoronoiManager::createTissue(int _nCells, int _width, int _height, int _deep){
    
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
    
    
    //  Add walls (un comment one pair if you like to shape the container)
    //
    //voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
    //con.add_wall(cyl);
    
    //voro::wall_sphere sph(0, 0, 0, min(_width*0.5, _height*0.5) );
    //con.add_wall(sph);
    
    //voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
    //con.add_wall(cone);
    
    //  Add the cell seed to the container
    //
    for(int i = 0; i < _nCells;i++){
        ofPoint newCell = ofPoint(ofRandom(-_width*0.5,_width*0.5),
                                  ofRandom(-_height*0.5,_height*0.5),
                                  ofRandom(-_deep*0.5,_deep*0.5));
        
        addCellSeed(con, newCell, i, true);
    }
    
    
    
    m_cellMeshes = getCellsFromContainer(con,0.0);
    m_cellMeshWireframes = getCellsFromContainer(con,0.0,true);
    m_cellRadius = getCellsRadius(con);
    m_cellCentroids = getCellsCentroids(con);
}




