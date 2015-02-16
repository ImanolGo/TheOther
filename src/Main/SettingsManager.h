/*
 *  SettingsManager.h
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */


#pragma once

#include "Manager.h"

//========================== class SettingsManager ==============================
//============================================================================
/** \class SettingsManager SettingsManager.h
 *	\brief Class managing the whole settings of the application
 *	\details it reads from an xml settings file and provides access to the information
 */

typedef             map<string,string>               ResourcesPathMap;       ///< defines a map of path attached to the resources name

class SettingsManager: public Manager
{
    public:

        //! Constructor
        SettingsManager();

        //! Destructor
        ~SettingsManager();

        //! Compares two transition objects
        void setup();

        const ResourcesPathMap& getTextureResourcesPath() const {return m_texturesPath;}

        const ResourcesPathMap& getSvgResourcesPath() const {return m_svgResourcesPath;}


        float getAppWidth() const {return m_appWidth;}

        float getAppHeight() const {return m_appHeight;}

        int getUdpPort() const {return m_udpPort;}


    private:

        //! Loads the settings file
        bool loadSettingsFile();

        //! Loads all the settings
        void loadAllSettings();

        //! Sets all the debug properties
        void setDebugProperties();

        //! Sets all the network properties
        void setNetworkProperties();

        //! Sets all the window properties
        void setWindowProperties();


        //! Loads all the textures settings
        void loadTextureSettings();

        //! Loads all the svg images settings
        void loadSvgSettings();


    private:

        ofXml		            m_xmlSettings;          ///< instance of the xml parser
        ResourcesPathMap        m_texturesPath;         ///< stores the texture paths
        ResourcesPathMap        m_svgResourcesPath;     ///< stores the resources paths
        float                   m_appWidth;             ///< stores the applications width
        float                   m_appHeight;            ///< stores the applications height
        int                     m_udpPort;              ///< stores the UDP port used for the TUIO communications
};



