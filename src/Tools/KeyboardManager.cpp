/*
 *  KeyboardManager.cpp
 *  The Other
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include "KeyboardManager.h"
#include "StateManager.h"
#include "AppManager.h"


KeyboardManager::KeyboardManager(): Manager()
{
    //Intentionally left empty
}

KeyboardManager::~KeyboardManager()
{
   ofLogNotice() << "KeyboardManager::destructor";
}


//--------------------------------------------------------------

void KeyboardManager::setup()
{
    Manager::setup();
    
    if(m_initialized)
        return;
    
    ofLogNotice() <<"KeyboardManager::initialized" ;
}

void KeyboardManager::keyPressed(int key)
{
    if(key == '1'){
        AppManager::getInstance().getStateManager()->changeState("SimpleVoronoiState");
    }

    else if(key == '2'){
        AppManager::getInstance().getStateManager()->changeState("SimpleVoronoiState");
		//ofNotifyEvent(StateMachine::changeStateEvent, "WallState");
	}
	else if(key == '3'){
        AppManager::getInstance().getStateManager()->changeState("SimpleVoronoiState");
		//ofNotifyEvent(StateMachine::changeStateEvent, "VoronoiTransformationState");
	}
	else if(key == '4'){
       AppManager::getInstance().getStateManager()->changeState("SimpleVoronoiState");
		//ofNotifyEvent(StateMachine::changeStateEvent, "ParticlesVoronoiState");
	}
}

void KeyboardManager::keyReleased(int key)
{
     //Intentionally left empty
}










