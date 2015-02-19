/*
 *  AppManager.cpp
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#include "ofMain.h"


#include "AppManager.h"

AppManager& AppManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly
	static AppManager    m_instance;
    return m_instance;

}

AppManager::AppManager(): m_logVerbose(false)
{
    this->createManagers();
}


AppManager::~AppManager()
{
    ofLogNotice() <<"AppManager::Destructor";
}


void AppManager::createManagers()
{
    m_settingsManager = ofPtr<SettingsManager>(new SettingsManager());
	m_resourceManager = ofPtr<ResourceManager>(new ResourceManager());
	m_visualEffectsManager = ofPtr<VisualEffectsManager>(new VisualEffectsManager());
	m_viewManager = ofPtr<ViewManager>(new ViewManager());
    m_layoutManager = ofPtr<LayoutManager>(new LayoutManager());
    m_voronoiManager = ofPtr<VoronoiManager>(new VoronoiManager());
    m_seedsManager = ofPtr<SeedsManager>(new SeedsManager());

}

void AppManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() << "AppManager::initialized";

	Manager::setup();

    this->setupOF();
	this->setupManagers();
}

void AppManager::setupOF()
{
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    //ofLogToFile("LogFile.txt");
    ofTrueTypeFont::setGlobalDpi(96);

    ofAddListener(ofEvents().keyPressed, this, &AppManager::keyPressed);
}


void AppManager::setupManagers()
{
    m_settingsManager->setup();
    m_viewManager->setup();
    m_resourceManager->setup();
    m_visualEffectsManager->setup();
    m_layoutManager->setup();
    m_voronoiManager->setup();
    m_seedsManager->setup();
}

void AppManager::update()
{
    m_seedsManager->update();
    m_voronoiManager->update();
    m_visualEffectsManager->update();
    m_viewManager->update();
    
}


void AppManager::draw()
{
     m_viewManager->draw();
}

void AppManager::keyPressed(ofKeyEventArgs &e)
{
    int key = e.key;
    if(key == ' ') {
        m_logVerbose = !m_logVerbose;
        if(m_logVerbose){
             ofSetLogLevel(OF_LOG_VERBOSE);
        }
        else{
             ofSetLogLevel(OF_LOG_NOTICE);
        }

    }
}


