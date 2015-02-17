/*
 *  VoronoiManager.h
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#pragma once

#include "Manager.h"
#include "SeedVisual.h"

//========================== class VoronoiManager ==============================
//============================================================================
/** \class VoronoiManager VoronoiManager.h
 *	\brief Class managing the layout of the voronoi visuals
 *	\details It creates and draws the voronoi visuals
 */

class VoronoiManager: public Manager
{
    
    static const int NUMBER_OF_CELLS;
    
public:

    //! Constructor
    VoronoiManager();

    //! Destructor
    ~VoronoiManager();

    //! Set-up the Voronoi manager
    virtual void setup();
    
    //! Update the voronoi manager
    virtual void update();
    
    //! Draw the voronoi manager
    virtual void draw();

private:
    
    //! Updates the the Voronoi diagram
    virtual void updateVoronoi();
    
    //! Create the seed visuals
    virtual void createSeeds();
    
    //! Updates the seed visuals
    virtual void updateSeeds();
    
    //! Create a 3D Voronoi Tissue
    void createVoronoi(int _width, int _height, int _deep);

private:

    typedef vector< ofPtr<SeedVisual> >      SeedVector;            ///< defines a vector of seeds
    SeedVector              m_seeds; ///< voroni seeds
    ofMesh                  m_delaunayMesh; ///< mesh representing the delaunay triangulation
    
    vector<ofPoint>     m_cellCentroids;
    vector<float>       m_cellRadius;
    vector<ofVboMesh>   m_cellMeshes;
    vector<ofVboMesh>   m_cellMeshWireframes;

};

//==========================================================================


