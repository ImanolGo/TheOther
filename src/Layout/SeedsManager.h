/*
 *  SeedsManager.h
 *  The Other
 *
 *  Created by Imanol Gomez on 19/02/15.
 *
 */

#pragma once

#include "Manager.h"
#include "Seed.h"

#define NUMBER_OF_SEEDS 100
#define NUMBER_OF_PARTICLES 2000

//========================== class SeedsManager ==============================
//============================================================================
/** \class SeedsManager SeedsManager.h
 *	\brief Class managing the Seeds system
 *	\details It creates and draws a particle system of Seeds
 */


class SeedsManager: public Manager
{
    
public:

    //! Constructor
    SeedsManager();

    //! Destructor
    ~SeedsManager();

    virtual void setup();
    
    virtual void update();
    
    virtual void draw();
    
    vector<ofVec3f>&  getSeedsVertices(){return m_seeds.getVertices();}
    
    virtual void setColor(const ofColor& color);
    
    virtual void setSeedsScale(float scale);
    
    virtual void setParticlesScale(float scale);

private:
    
    virtual void drawSeeds();
    
    virtual void drawParticles();
    
    
    //! Updates the each seed position
    virtual void updateSeeds();
    
    //! Create the seed visuals
    virtual void updateParticles();
    
    //! Create the seed visuals
    virtual void createSeeds();
    
    //! Create the seed visuals
    virtual void createParticles();
    
    virtual void setupBillboardShader();
    
    virtual void createReferenceVisuals();
    

private:

    //typedef vector< ofPtr<Seed> >      SeedVector;            ///< defines a vector of seeds
    //SeedVector              m_seeds; ///< voroni seeds
    
    // billboard particles
    
    
    ofShader billboardShader;
    ofPtr<ofTexture> texture;
    
    float m_seedsSizeTarget[NUMBER_OF_SEEDS];
    ofVboMesh m_seeds;
    ofVec3f m_seedsVels[NUMBER_OF_SEEDS];
    
    float m_particlesSizeTarget[NUMBER_OF_PARTICLES];
    ofVboMesh m_particles;
    ofVec3f m_particlesVels[NUMBER_OF_PARTICLES];
    
    ofImage image;
    
    ofPtr<BasicVisual> m_referenceSeed;
    ofPtr<BasicVisual> m_referenceParticle;
};

//==========================================================================


