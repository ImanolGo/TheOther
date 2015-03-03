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


//=========================== class Seed ==============================
//============================================================================
/** \class Seed Seed.h
 *	\brief Represents a seed particle
 *	\details It represents its position and visualization
 */

class Seed: public BasicVisual
{
    
public:
    
    //! Constructor
    Seed(const ofVec3f& pos);
    
    //! Destructor
    virtual ~Seed();
    
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
