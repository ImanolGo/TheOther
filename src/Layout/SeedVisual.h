/*
 *  Seed.h
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */


#pragma once


#include "BasicVisual.h"
#include "ImageVisual3D.h"


//=========================== class SeedVisual ==============================
//============================================================================
/** \class SeedVisual SeedVisual.h
 *	\brief Represents a seed visual from a voronoi diagram
 *	\details It represents its position and visualization
 */

class SeedVisual: public BasicVisual
{
    
public:
    
    //! Constructor
    SeedVisual(const ofVec3f& pos);
    
    //! Destructor
    virtual ~SeedVisual();
    
    //! Draws the seed
    virtual void draw();
    
protected:
    
    //! set-up the seed
    virtual void setup();
    
    //! create the image visuals
    virtual void createImageVisuals();
    
    
protected:
    
    typedef vector<ofPtr<ImageVisual3D> >      ImageVector;            ///< defines a vector of images
    
    ImageVector         m_images;           ///< vector storing the image visuals
    
};
