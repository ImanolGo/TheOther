/*
 *  TheOthersApp.h
 *  The Other
 *
 *  Created by Imanol G�mez on 16/02/15.
 *
 */

#pragma once


#include "Manager.h"


#include "ResourceManager.h"
#include "ViewManager.h"
#include "VisualEffectsManager.h"
#include "LayoutManager.h"
#include "SettingsManager.h"
#include "VoronoiManager.h"
#include "SeedsManager.h"
#include "StateManager.h"
#include "KeyboardManager.h"

//========================== class AppManager ==============================
//============================================================================
/** \class AppManager AppManager.h
 *	\brief Class managing the whole application
 *	\details it set-ups, updates and renders all the different managers used for the application
 */

class AppManager: public Manager
{
public:

    //! Destructor
    ~AppManager();

    //! Returns the singleton instance.
    static AppManager& getInstance();

    //! Compares two transition objects
    void setup();

    //! updates the logic
    void update();

    //! calls the view manager to draw
    void draw();

    //! defines what happens if the key is pressed
    virtual void keyPressed(ofKeyEventArgs &e);

    //==========================================================================

    //! Returns the settings manager
    ofPtr<SettingsManager> getSettingsManager() { return m_settingsManager; }

       //! Returns the timer manager
    ofPtr<ResourceManager>  getResourceManager() { return m_resourceManager; }

    //! Returns the view manager
    ofPtr<ViewManager>    getViewManager() { return m_viewManager; }

    //! Returns the visual effects manager
    ofPtr<VisualEffectsManager>   getVisualEffectsManager() { return m_visualEffectsManager; }

    //! Returns the layout manager
    ofPtr<LayoutManager>   getLayoutManager() { return m_layoutManager; }
    
    //! Returns the voronoi manager
    ofPtr<VoronoiManager>   getVoronoiManager() { return m_voronoiManager; }
    
    //! Returns the seeds manager
    ofPtr<SeedsManager>   getSeedsManager() { return m_seedsManager; }
    
    //! Returns the state manager
    ofPtr<StateManager>   getStateManager() { return m_stateManager; }

private:

    //! Constructor
    AppManager();

	//! Stop the compiler generating methods of copy the object
	 AppManager(AppManager const& copy);              // Don't Implement

    //! Prevent operator= being generated.
     AppManager& operator=(AppManager const& copy);     // Don't implement

    //==========================================================================

    //! Create all the managers with shared pointers
    void createManagers();

    //! Set-up all the managers
    void setupManagers();

    //! Set-up openFrameworks
    void setupOF();

    //! update all the managers
    void updateManagers();


private:

    ofPtr<SettingsManager>          m_settingsManager;          ///< Manages the window settings
    ofPtr<ResourceManager>          m_resourceManager;          ///< Manages resources
    ofPtr<ViewManager>              m_viewManager;              ///< Manages visuals
    ofPtr<VisualEffectsManager>     m_visualEffectsManager;     ///< Manages visual effects
    ofPtr<LayoutManager>            m_layoutManager;            ///< Manages the layout
    ofPtr<VoronoiManager>           m_voronoiManager;           ///< Manages the voronoi diagram
    ofPtr<SeedsManager>             m_seedsManager;             ///< Manages the seeds diagram
    ofPtr<StateManager>             m_stateManager;             ///< Manages the stage machine
    ofPtr<KeyboardManager>          m_keyboardManager;          ///< Manages the keyboard

    bool                            m_logVerbose;
};

//==========================================================================


