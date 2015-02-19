/*
 *  VoronoiVisual.h
 *  The Other
 *
 *  Created by Imanol Gómez on 19/02/15.
 *
 */


#pragma once


#include "BasicVisual.h"
#include "ImageVisual3D.h"


//=========================== class VoronoiVisual ==============================
//============================================================================
/** \class VoronoiVisual VoronoiVisual.h
 *	\brief Represents a Voronoi visual from a voronoi diagram
 *	\details It represents visualization
 */

class VoronoiVisual: public BasicVisual
{
    
public:
    
    //! Constructor
    VoronoiVisual(const ofVec3f& pos);
    
    //! Destructor
    virtual ~VoronoiVisual();
    
    //! Draws the Voronoi
    virtual void draw();

    //! set the DelaunayMesh
    virtual void setDelaunayMesh(const ofMesh& delaunayMesh);
    
    //! set the Cell Centroids
    virtual void setCellCentroids(const vector<ofPoint>& cellCentroids);
    
    //! set the Cell Radius
    virtual void setCellRadius(const vector<float>& cellRadius);
    
    //! set the Cell Meshes
    virtual void setCellMeshes(const vector<ofVboMesh>& cellMeshes);

    //! set the Cell Mesh Wireframes
    virtual void setCellMeshWireframes(const vector<ofVboMesh>& cellMeshWireframes);
    
    
protected:
    
    //! set-up the Voronoi
    virtual void setup();
    
    //! create the image visuals
    virtual void createImageVisuals();
    
    
protected:
    
    ofMesh              m_delaunayMesh; ///< mesh representing the delaunay triangulation
    vector<ofPoint>     m_cellCentroids;
    vector<float>       m_cellRadius;
    vector<ofVboMesh>   m_cellMeshes;
    vector<ofVboMesh>   m_cellMeshWireframes;
    
};
