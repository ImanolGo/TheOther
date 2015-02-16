/*
 *  ViewManager.h
 *  The Other
 *
 *  Created by Imanol G—mez on 16/02/15.
 *
 */

#pragma once

#include "ofMain.h"
#include "../Main/Manager.h"
#include "../Visuals/TextVisual.h"


class BasicVisual;

//========================== class ViewManager ==============================
//============================================================================
/** \class ViewManager ViewManager.h
 *  \brief Class managing the visualization of the application
 *  \details it uses the events to make visuals and transitions
 */

class ViewManager: public Manager
{
public:

    //! Constructor
    ViewManager();

    //! Destructor
    ~ViewManager();

    //! Setups the logic
    void setup();

    //! renders all the graphics
    void draw();

    //! updates the date manager
    void update();

    //! Adds a visual as an overlay with the specified z-ordering.
    void addOverlay(ofPtr<BasicVisual> visual,  int zOrder = 0);

    //! Removes an overlay to the list of elements that are rendered
    void removeOverlay(ofPtr<BasicVisual> visual);

    //==========================================================================

private:

    //! Adds the events to be listen to
    void addListeners();

    //! Function called when a key is pressed
    void keyPressed(ofKeyEventArgs &e);

    //! Draws all the visual overlays
    void drawOverlays();

    //! Set-ups the manager's text visuals
    void setupTextVisuals();

    //! Returns if the overlay has already been added
    bool isOverlayAlreadyAdded(ofPtr<BasicVisual> visual);

private:

    typedef std::pair<int, ofPtr<BasicVisual> > Overlay;        ///< pair<zOrder,ofPtr<BasicVisual>> defines an overlay elemet
    typedef std::list<Overlay>      OverlayList;    ///< list of overlay elements

    OverlayList             m_overlays;         ///< list of all overlays that are rendered each frame
    ofPtr<TextVisual>       m_frameRateText;    ///< font displaying the frame rate

    bool                    m_showDebugInfo;    ///< it tells if you should or should not show debug information

};

