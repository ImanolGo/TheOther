/*
 *  SeedsManager.cpp
 *  The Other
 *
 *  Created by Imanol Gómez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "ViewManager.h"
#include "ResourceManager.h"


#include "SeedsManager.h"


SeedsManager::SeedsManager(): Manager()
{
	//Intentionally left empty
}


SeedsManager::~SeedsManager()
{
    ofLogNotice() <<"SeedsManager::Destructor";
}


void SeedsManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"SeedsManager::initialized";

	Manager::setup();
    
    this->createReferenceVisual();
    this->createSeeds();
    this->setupBillboardShader();
    
}

void SeedsManager::createReferenceVisual()
{
    m_referenceVisual = ofPtr<BasicVisual>(new BasicVisual());
    ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColor2");
    m_referenceVisual->setColor(color);
}

void SeedsManager::setupBillboardShader()
{
    // load the billboard shader
    // this is used to change the
    // size of the particle
    if(ofGetGLProgrammableRenderer()){
        billboardShader.load("shaders/shadersGL3/Billboard");
    }else{
        billboardShader.load("shaders/shadersGL2/Billboard");
    }
    
    // we need to disable ARB textures in order to use normalized texcoords
    ofDisableArbTex();
    //image.loadImage("images/general/dot.png");
    image.loadImage("images/watercolors/water_color_textures_02.png");
    string resourceName = "Dot";
    texture = AppManager::getInstance().getResourceManager()->getTexture(resourceName);
}

void SeedsManager::draw()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    ofPushMatrix();
    ofSetColor(255);
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    //texture->bind();
    //billboards.draw();
    //texture->unbind();
    
    image.getTextureReference().bind();
    m_seeds.draw();
    image.getTextureReference().unbind();
    
    
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    
    ofPopMatrix();
    glDisable(GL_ALPHA_TEST);
}

void SeedsManager::createSeeds()
{
    int size = std::max(ofGetHeight(), ofGetWidth())*0.6;
    
    m_seeds.getVertices().resize(NUMBER_OF_SEEDS);
    m_seeds.getColors().resize(NUMBER_OF_SEEDS);
    m_seeds.getNormals().resize(NUMBER_OF_SEEDS,ofVec3f(0));
    
    // ------------------------- billboard particles
    for (int i=0; i<NUMBER_OF_SEEDS; i++) {
        
        m_seedsVels[i].set(ofRandomf(), -1.0, 0);
        /*billboards.getVertices()[i].set(ofRandom(-size, size),
         ofRandom(-size, size),
         ofRandom(-size, size));*/
        
        m_seeds.getVertices()[i].set(ofRandom(-size, size),
                                        ofRandom(-size, size),
                                        0);
        
        
        m_seeds.getColors()[i].set(m_referenceVisual->getColor());
        m_seedsSizeTarget[i] = ofRandom(10, 12);
        
    }
    
    
    m_seeds.setUsage( GL_DYNAMIC_DRAW );
    m_seeds.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);

}

void SeedsManager::update()
{
    this->updateSeeds();
}

void SeedsManager::updateSeeds()
{
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    //div = 550.0;
    
    for (int i=0; i<NUMBER_OF_SEEDS; i++) {
        
        // noise
        /*ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));*/
        
        ofVec3f vec(ofSignedNoise(t, m_seeds.getVertex(i).y/div, m_seeds.getVertex(i).z/div),
                    ofSignedNoise(m_seeds.getVertex(i).x/div, t, m_seeds.getVertex(i).z/div),
                    0);
        
        vec *= 10 * ofGetLastFrameTime();
        m_seedsVels[i] += vec;
        m_seeds.getVertices()[i] += m_seedsVels[i];
        m_seedsVels[i] *= 0.94f;
        //billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
        m_seeds.setNormal(i,ofVec3f(12 + m_seedsSizeTarget[i],0,0));
    }
}









