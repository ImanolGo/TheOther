/*
 *  SeedVisual.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"

#include "SeedVisual.h"


SeedVisual::SeedVisual(const ofVec3f& pos): BasicVisual(pos, 0, 0)
{
    this->setup();
}

SeedVisual::~SeedVisual()
{
    //Intentionally left empty
}

void SeedVisual::setup()
{
    this->createImageVisuals();
}

void SeedVisual::createImageVisuals()
{
    string resourceName = "WaterColorTexture8";
    ofPtr<ImageVisual> imageVisual = ofPtr<ImageVisual>(new ImageVisual(m_position,resourceName, true));
    ofColor color = AppManager::getInstance().getSettingsManager()->getColor("OuterRockColor");
    imageVisual->setColor(color);
    m_images.push_back(imageVisual);
}


void SeedVisual::draw()
{
    for(ImageVector::iterator it = m_images.begin(); it!= m_images.end(); ++it){
        (*it)->draw();
    }
}

