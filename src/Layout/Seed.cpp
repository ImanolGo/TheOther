/*
 *  Seed.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */


#include "ofMain.h"

#include "AppManager.h"
#include "SettingsManager.h"

#include "Seed.h"


Seed::Seed(const ofVec3f& pos): BasicVisual(pos, 0, 0)
{
    this->setup();
}

Seed::~Seed()
{
    //Intentionally left empty
}

void Seed::setup()
{
    this->createImageVisuals();
}

void Seed::createImageVisuals()
{
    
    int index = (int) ofRandom(24) + 1;
    string resourceName = "WaterColorTexture" + ofToString(index);
    ofPtr<ImageVisual3D> imageVisual = ofPtr<ImageVisual3D>(new ImageVisual3D(m_position,resourceName));
    index = (int) ofRandom(3) + 1;
    string colorName = "RockColor" + ofToString(index);
    ofColor color = AppManager::getInstance().getSettingsManager()->getColor(colorName);
    imageVisual->setColor(color);
    imageVisual->setScale(ofVec3f(0.5,0.5,5));
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


void Seed::draw()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    for(ImageVector::iterator it = m_images.begin(); it!= m_images.end(); ++it){
        ofPushMatrix();
        ofTranslate(m_position);
        (*it)->draw();
        ofPopMatrix();
    }

    glDisable(GL_ALPHA_TEST);
}

