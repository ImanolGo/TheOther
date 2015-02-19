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

//========================== class SeedsManager ==============================
//============================================================================
/** \class SeedsManager SeedsManager.h
 *	\brief Class managing the seeds system
 *	\details It creates and draws a particle system of seeds
 */

class SeedsManager: public Manager
{
    
    static const int NUMBER_OF_SEEDS;
    
public:

    //! Constructor
    SeedsManager();

    //! Destructor
    ~SeedsManager();

    //! Set-up the Voronoi manager
    virtual void setup();
    
    //! Update the voronoi manager
    virtual void update();
    
    //! Draw the voronoi manager
    virtual void draw();

private:

     //! Create the seed particles
    void createSeeds();
    
    //! Updates the each seed position
    virtual void updateSeeds();
    
    //! Create the seed visuals
    virtual void createSeed();
    
private:

    typedef vector< ofPtr<Seed> >      SeedVector;            ///< defines a vector of seeds
    SeedVector              m_seeds; ///< voroni seeds

};

//==========================================================================


