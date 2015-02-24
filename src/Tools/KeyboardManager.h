/*
 *  KeyboardManager.h
 *  The Other
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#pragma once

#include "ofMain.h"
#include "Manager.h"

//========================== class KeyboardManager =======================================
//==============================================================================
/** \class KeyboardManager KeyboardManager.h
 *	\brief class for managing the keyboard events
 *	\details It reads all the keyboard events and create the proper application events
 */


class KeyboardManager: public Manager
{

public:
    //! Constructor
    KeyboardManager();

    //! Destructor
    virtual ~KeyboardManager();

    //! setups the day watcher
    void setup();

    //! handles a pressed key
    void keyPressed  (int key);

    //! handles a released key
    void keyReleased (int key);


protected:

};

