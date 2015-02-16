/*
 *  SettingsManager.cpp
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */


#include "ofMain.h"

#include "SettingsManager.h"

SettingsManager::SettingsManager(): m_appHeight(0.0), m_appWidth(0.0)
{
	///create all managers
}


SettingsManager::~SettingsManager()
{
    //this->saveButtonSettings();
    ofLogNotice() <<"SettingsManager::Destructor" ;
}


void SettingsManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"SettingsManager::initialized" ;

	Manager::setup();

    if(this->loadSettingsFile()){
        this->loadAllSettings();
    }
}

void SettingsManager::loadAllSettings()
{
    this->setWindowProperties();
    this->setDebugProperties();
    this->setNetworkProperties();
    this->loadTextureSettings();
    this->loadSvgSettings();
}

bool SettingsManager::loadSettingsFile()
{
	string settingsFilePath = "xmls/settings.xml";

	if(!m_xmlSettings.load(settingsFilePath)){
        ofLogNotice() <<"SettingsManager::loadSettingsFile-> unable to load file: " << settingsFilePath ;
        return false;
    }

    ofLogNotice() <<"SettingsManager::loadSettingsFile->  successfully loaded settings.xml " ;
    return true;
}

void SettingsManager::setDebugProperties()
{
    m_xmlSettings.setTo("//");

    string ofPath = "//of_settings/debug";
    if(m_xmlSettings.exists(ofPath)) {
        m_xmlSettings.setTo(ofPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xmlSettings.getAttributes();

        bool showCursor = ofToBool(attributes["showCursor"]);
        if(showCursor){
            ofShowCursor();
        }
        else{
            ofHideCursor();
        }

        bool setVerbose = ofToBool(attributes["setVerbose"]);
        if(setVerbose){
            ofSetLogLevel(OF_LOG_VERBOSE);
        }
        else{
            ofSetLogLevel(OF_LOG_NOTICE);
        }


        ofLogNotice() <<"SettingsManager::setDebugProperties->  successfully loaded the OF general settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::setOFProperties->  path not found: " << ofPath ;
}

void SettingsManager::setWindowProperties()
{
    m_xmlSettings.setTo("//");

    string windowPath = "//of_settings/window";
    if(m_xmlSettings.exists(windowPath)) {
        m_xmlSettings.setTo(windowPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xmlSettings.getAttributes();
        string title = attributes["title"];
        m_appWidth = ofToInt(attributes["width"]);
        m_appHeight= ofToInt(attributes["height"]);
        int x = ofToInt(attributes["x"]);
        int y = ofToInt(attributes["y"]);
        bool fullscreen = ofToBool(attributes["fullscreen"]);

        ofSetFullscreen(fullscreen);
        ofSetWindowShape(m_appWidth,m_appHeight);
        if(!fullscreen){
            ofSetWindowPosition(x,y);
        }
        ofSetWindowTitle(title);

        ofLogNotice() <<"SettingsManager::setWindowProperties->  successfully loaded the window settings" ;
        ofLogNotice() <<"SettingsManager::setWindowProperties->  title = "<< title<<", width = " << m_appWidth <<", height = "
        <<m_appHeight <<", x = "<<x<<", y = "<<y;
        return;
    }

    ofLogNotice() <<"SettingsManager::setWindowProperties->  path not found: " << windowPath ;
}
void SettingsManager::setNetworkProperties()
{
    m_xmlSettings.setTo("//");

    string networkPath = "//of_settings/network";
    if(m_xmlSettings.exists(networkPath)) {
        m_xmlSettings.setTo(networkPath);
        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes = m_xmlSettings.getAttributes();

        m_udpPort  = ofToInt(attributes["udpPort"]);


        ofLogNotice() <<"SettingsManager::setNetworkProperties->  successfully loaded the network settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::setNetworkProperties->  path not found: " << networkPath ;
}


void SettingsManager::loadTextureSettings()
{
    m_xmlSettings.setTo("//");

    string resourcesPath = "//textures";
    if(m_xmlSettings.exists(resourcesPath)) {

        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;

        resourcesPath = "//textures/texture[0]";
        m_xmlSettings.setTo(resourcesPath);
        do {

            attributes = m_xmlSettings.getAttributes();
            m_texturesPath[attributes["name"]] = attributes["path"];

            ofLogNotice() <<"SettingsManager::loadTextureSettings->  texture = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xmlSettings.setToSibling()); // go to the next texture


        ofLogNotice() <<"SettingsManager::loadTextureSettings->  successfully loaded the resource settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::loadTextureSettings->  path not found: " << resourcesPath ;
}


void SettingsManager::loadSvgSettings()
{
    m_xmlSettings.setTo("//");

    string svgPath = "//svgs";
    if(m_xmlSettings.exists(svgPath)) {

        typedef   std::map<string, string>   AttributesMap;
        AttributesMap attributes;

        svgPath = "//svgs/svg[0]";
        m_xmlSettings.setTo(svgPath);
        do {

            attributes = m_xmlSettings.getAttributes();
            m_svgResourcesPath[attributes["name"]] = attributes["path"];

            ofLogNotice() <<"SettingsManager::loadSvgSettings->  svg = " << attributes["name"]
            <<", path = "<< attributes["path"] ;
        }
        while(m_xmlSettings.setToSibling()); // go to the next svg


        ofLogNotice() <<"SettingsManager::loadSvgSettings->  successfully loaded the resource settings" ;
        return;
    }

    ofLogNotice() <<"SettingsManager::loadSvgSettings->  path not found: " << svgPath ;
}












