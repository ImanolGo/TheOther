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
    
    //! Enable jitter
    virtual void enableJitter(){m_jitter=true;}
    
    //! Enable jitter
    virtual void disableJitter(){m_jitter=false;}
    
    //! Enable orbit
    virtual void enableOrbit(){m_orbit=true; m_startOrbitTime = ofGetElapsedTimef();}
    
    //! Enable orbit
    virtual void disableOrbit(){m_orbit=false;}
    
    //! Enable magnifying
    virtual void enableMagnifying(){m_magnifying=true;}
    
    //! Enable magnifying
    virtual void disableMagnifying(){m_magnifying=false;}

private:
    
    //! Updates the voronoi visual
    virtual void createVoronoiVisual();
    
    //! Updates the Voronoi diagram
    virtual void updateVoronoi();
    
    //! Create a 3D Voronoi Tissue
    void createVoronoi(int _width, int _height, int _deep);
    
    virtual void setMagnifying(ofVec3f& vertex);
    
    virtual void setOrbit(ofVec3f& vertex, const ofVec3f& meshCentroid);
    
    virtual void setJitter(ofVec3f& vertex, int index);
    

private:

    ofPtr<VoronoiVisual>     m_voronoiVisual;
    bool                     m_jitter;
    bool                     m_orbit;
    bool                     m_magnifying;
    float                    m_startOrbitTime;
 
};

//==========================================================================


