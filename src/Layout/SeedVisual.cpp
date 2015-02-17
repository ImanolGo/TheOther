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
    string resourceName = "SeedTexture";
    ofPtr<ImageVisual3D> imageVisual = ofPtr<ImageVisual3D>(new ImageVisual3D(m_position,resourceName));
    ofColor color = AppManager::getInstance().getSettingsManager()->getColor("OuterRockColor");
    imageVisual->setScale(ofVec3f(0.1,0.1,1));
    m_images.push_back(imageVisual);
    
    /*resourceName = "WaterColorTexture8";
    imageVisual = ofPtr<ImageVisual3D>(new ImageVisual3D(m_position,resourceName));
    color = AppManager::getInstance().getSettingsManager()->getColor("MiddleRockColor");
    imageVisual->setColor(color);
    imageVisual->setScale(ofVec3f(0.1,0.1,1));
    m_images.push_back(imageVisual);
    
    resourceName = "WaterColorTexture8";
    imageVisual = ofPtr<ImageVisual3D>(new ImageVisual3D(m_position,resourceName));
    color = AppManager::getInstance().getSettingsManager()->getColor("InnerRockColor");
    imageVisual->setColor(color);
    imageVisual->setScale(ofVec3f(0.08,0.08,1));
    m_images.push_back(imageVisual);*/

}


void SeedVisual::draw()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    for(ImageVector::iterator it = m_images.begin(); it!= m_images.end(); ++it){
        (*it)->draw();
    }

    glDisable(GL_ALPHA_TEST);
}

