/*
 *  VoronoiVisual.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 19/02/15.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"

#include "VoronoiVisual.h"


VoronoiVisual::VoronoiVisual(const ofVec3f& pos): BasicVisual(pos, 0, 0)
{
    this->setup();
}

VoronoiVisual::~VoronoiVisual()
{
    //Intentionally left empty
}

void VoronoiVisual::setup()
{
    this->setupColors();
}

void VoronoiVisual::setupColors()
{
    m_facesColor = AppManager::getInstance().getSettingsManager()->getColor("VoronoiFaces");
    m_wireFramesColor = AppManager::getInstance().getSettingsManager()->getColor("VoronoiWireframes");
}


void VoronoiVisual::draw()
{
    ofPushMatrix();
        
        ofTranslate(m_position);
        for(int i = 0; i < m_cellMeshes.size(); i++){
            //ofSetColor(m_facesColor);
            //m_cellMeshes[i].drawFaces();
        
            ofPushStyle();
            ofSetLineWidth(3);
            ofSetColor(m_wireFramesColor);
            m_cellMeshWireframes[i].draw();
            ofPopStyle();
        }
    
    ofPopMatrix();
}

void VoronoiVisual::setDelaunayMesh(const ofMesh& delaunayMesh) {
    m_delaunayMesh.clear();
    m_delaunayMesh = delaunayMesh;
}

void VoronoiVisual::setCellCentroids(const vector<ofPoint>& cellCentroids) {
    m_cellCentroids.clear();
    m_cellCentroids = cellCentroids;
}

void VoronoiVisual::setCellRadius(const vector<float>& cellRadius) {
    m_cellRadius.clear();
    m_cellRadius = cellRadius;
}

void VoronoiVisual::setCellMeshes(const vector<ofVboMesh>& cellMeshes) {
    m_cellMeshes.clear();
    m_cellMeshes = cellMeshes;
}

void VoronoiVisual::setCellMeshWireframes(const vector<ofVboMesh>& cellMeshWireframes) {
    m_cellMeshWireframes.clear();
    m_cellMeshWireframes = cellMeshWireframes;
}

