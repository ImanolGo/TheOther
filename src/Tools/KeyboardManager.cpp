/*
 *  KeyboardManager.cpp
 *  The Other
 *
 *  Created by Imanol Gomez on 23/02/15.
 *
 */


#include "KeyboardManager.h"
#include "StateMachine.h"


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
        ofEvent<string> changeStateEvent;
         //StateMachine::changeStateEvent changeState;
        //ofNotifyEvent(changeStateEvent, "SimpleVoronoiState");
	}

    else if(key == '2'){
		//ofNotifyEvent(StateMachine::changeStateEvent, "WallState");
	}
	else if(key == '3'){
		//ofNotifyEvent(StateMachine::changeStateEvent, "VoronoiTransformationState");
	}
	else if(key == '4'){
		//ofNotifyEvent(StateMachine::changeStateEvent, "ParticlesVoronoiState");
	}
}

void KeyboardManager::keyReleased(int key)
{
     //Intentionally left empty
}










