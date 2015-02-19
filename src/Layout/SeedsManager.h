/*
 *  SeedsManager.h
 *  The Other
 *
 *  Created by Imanol Gómez on 19/02/15.
 *
 */

#pragma once

#include "Manager.h"
#include "Seed.h"

#define NUM_BILLBOARDS 500

//========================== class SeedsManager ==============================
//============================================================================
/** \class SeedsManager SeedsManager.h
 *	\brief Class managing the Seeds system
 *	\details It creates and draws a particle system of Seeds
 */

class SeedsManager: public Manager
{
    
    static const int NUMBER_OF_SEEDS;
    
public:

    //! Constructor
    SeedsManager();

    //! Destructor
    ~SeedsManager();

    virtual void setup();
    
    virtual void update();
    
    virtual void draw();
    
    vector<ofVec3f>&  getBillboardsVertices(){return billboards.getVertices();}

private:
    
    //! Updates the each seed position
    virtual void updateSeeds();
    
    //! Create the seed visuals
    virtual void createSeeds();
    
    virtual void setupBillboardShader();
    

private:

    typedef vector< ofPtr<Seed> >      SeedVector;            ///< defines a vector of seeds
    SeedVector              m_seeds; ///< voroni seeds
    
    // billboard particles
    float billboardSizeTarget[NUM_BILLBOARDS];
    
    ofShader billboardShader;
    ofPtr<ofTexture> texture;
    
    ofVboMesh billboards;
    ofVec3f billboardVels[NUM_BILLBOARDS];
};

//==========================================================================


