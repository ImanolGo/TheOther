/*
 *  VoronoiManager.h
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#pragma once

#include "Manager.h"
#include "Seed.h"

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
    
    //! Set-up the layout
    virtual void draw();

private:
    
    //! Set-up the Voronoi diagram
    virtual void setupVoronoi();
    
    
    //! Create a 3D Voronoi Tissue
    void createTissue(int _nCells, int _width, int _height, int _deep);

private:

    typedef vector< ofPtr<Seed> >      SeedVector;            ///< defines a vector of seeds
    SeedVector              m_seeds; ///< voroni seeds
    ofMesh                  m_delaunayMesh; ///< mesh representing the delaunay triangulation
    
    vector<ofPoint>     m_cellCentroids;
    vector<float>       m_cellRadius;
    vector<ofVboMesh>   m_cellMeshes;
    vector<ofVboMesh>   m_cellMeshWireframes;

};

//==========================================================================


