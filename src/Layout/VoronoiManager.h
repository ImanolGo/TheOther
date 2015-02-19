/*
 *  VoronoiManager.h
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#pragma once

#include "Manager.h"
#include "VoronoiVisual.h"

//========================== class VoronoiManager ==============================
//============================================================================
/** \class VoronoiManager VoronoiManager.h
 *	\brief Class managing the layout of the voronoi visuals
 *	\details It creates and draws the voronoi visuals
 */

class VoronoiManager: public Manager
{
    
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
    
    //! Updates the voronoi visual
    virtual void createVoronoiVisual();
    
    //! Updates the Voronoi diagram
    virtual void updateVoronoi();
    
    //! Create a 3D Voronoi Tissue
    void createVoronoi(int _width, int _height, int _deep);
    

private:

    ofPtr<VoronoiVisual>     m_voronoiVisual;
 
};

//==========================================================================


