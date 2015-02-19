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

const int SeedsManager::NUMBER_OF_SEEDS= 50;

SeedsManager::SeedsManager()
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
    
    this->setupBillboardShader();
    this->createSeeds();
}


void SeedsManager::setupBillboardShader()
{
    billboards.getVertices().resize(NUM_BILLBOARDS);
    billboards.getColors().resize(NUM_BILLBOARDS);
    billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));
    
    // ------------------------- billboard particles
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
        billboards.getVertices()[i].set(ofRandom(-500, 500),
                                        ofRandom(-500, 500),
                                        ofRandom(-500, 500));
        
        //billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(96, 160), 255, 255));
        billboardSizeTarget[i] = ofRandom(4, 64);
        
    }
    
    
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    
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
    
    string resourceName = "Dot";
    texture = AppManager::getInstance().getResourceManager()->getTexture(resourceName);
}

void SeedsManager::draw()
{
    ofPushMatrix();
    ofSetColor(255);
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    texture->bind();
    billboards.draw();
    texture->unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    
    ofPopMatrix();
}

void SeedsManager::createSeeds()
{
    ofLogNotice() <<"SeedsManager::createSeeds";
    for (int i = 0; i < NUMBER_OF_SEEDS; i++){
        ofPtr<Seed> seed = ofPtr<Seed>(new Seed(ofVec3f(0,0,0)));
        m_seeds.push_back(seed);
        //AppManager::getInstance().getViewManager()->addVisual(seed);
    }
}

void SeedsManager::update()
{
    this->updateSeeds();
}

void SeedsManager::updateSeeds()
{
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    
    for (int i=0; i<NUM_BILLBOARDS; i++) {
        
        // noise
        ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                    ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
        
        vec *= 10 * ofGetLastFrameTime();
        billboardVels[i] += vec;
        billboards.getVertices()[i] += billboardVels[i];
        billboardVels[i] *= 0.94f;
        billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
    }
}









