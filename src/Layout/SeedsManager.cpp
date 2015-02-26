/*
 *  SeedsManager.cpp
 *  The Other
 *
 *  Created by Imanol Gomez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "ViewManager.h"
#include "ResourceManager.h"
#include "VisualEffectsManager.h"
#include "BasicVisual.h"

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
    
    this->createReferenceVisuals();
    this->createSeeds();
    this->createParticles();
    this->setupBillboardShader();
    
}

void SeedsManager::createReferenceVisuals()
{
    m_referenceSeed = ofPtr<BasicVisual>(new BasicVisual());
    ofColor color = AppManager::getInstance().getSettingsManager()->getColor("RockColor1");
    m_referenceSeed->setColor(color);
    
    m_referenceParticle = ofPtr<BasicVisual>(new BasicVisual());
    color = AppManager::getInstance().getSettingsManager()->getColor("RockColorBlack");
    m_referenceParticle->setColor(color);
    m_referenceParticle->setScale(ofVec3f(0.3));
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
    drawParticles();
    drawSeeds();
}

void SeedsManager::drawSeeds()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255);
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    
    image.getTextureReference().bind();
    m_seeds.draw();
    image.getTextureReference().unbind();
    
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    
    ofPopStyle();
    ofPopMatrix();
    glDisable(GL_ALPHA_TEST);
}



void SeedsManager::drawParticles()
{
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.1f);
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(255);
    
    // bind the shader so that wee can change the
    // size of the points via the vert shader
    billboardShader.begin();
    
    ofEnablePointSprites(); // not needed for GL3/4
    
    image.getTextureReference().bind();
    m_particles.draw();
    image.getTextureReference().unbind();
    
    ofDisablePointSprites(); // not needed for GL3/4
    
    billboardShader.end();
    
    ofPopStyle();
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
        
        m_seeds.getVertices()[i].set(ofRandom(-size, size),
                                        ofRandom(-size, size),
                                        0);
        
        
        m_seeds.getColors()[i].set(m_referenceSeed->getColor());
        m_seedsSizeTarget[i] = m_referenceSeed->getScale()[0]*12;
        
    }
    
    
    m_seeds.setUsage( GL_DYNAMIC_DRAW );
    m_seeds.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
}

void SeedsManager::createParticles()
{
    int size = std::max(ofGetHeight(), ofGetWidth())*0.6;
    
    m_particles.getVertices().resize(NUMBER_OF_PARTICLES);
    m_particles.getColors().resize(NUMBER_OF_PARTICLES);
    m_particles.getNormals().resize(NUMBER_OF_PARTICLES,ofVec3f(0));
    
    // ------------------------- billboard particles
    for (int i=0; i<NUMBER_OF_PARTICLES; i++) {
        
        m_particlesVels[i].set(ofRandomf(), -1.0, 0);
        
        m_particles.getVertices()[i].set(ofRandom(-size, size),
                                     ofRandom(-size, size),
                                     -1);
        
        
        m_particles.getColors()[i].set(m_referenceParticle->getColor());
        m_particlesSizeTarget[i] = m_referenceParticle->getScale()[0]*12;
        
    }
    
    
    m_particles.setUsage( GL_DYNAMIC_DRAW );
    m_particles.setMode(OF_PRIMITIVE_POINTS);
    //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
    
}

void SeedsManager::update()
{
    this->updateSeeds();
    this->updateParticles();
}

void SeedsManager::updateSeeds()
{
    float t = (ofGetElapsedTimef()) * 0.9f;
    float div = 250.0;
    //div = 550.0;
    
    for (int i=0; i<NUMBER_OF_SEEDS; i++) {
        
        ofVec3f vec(ofSignedNoise(t, m_seeds.getVertex(i).y/div, m_seeds.getVertex(i).z/div),
                    ofSignedNoise(m_seeds.getVertex(i).x/div, t, m_seeds.getVertex(i).z/div),
                    0);
        
        vec *= 10 * ofGetLastFrameTime();
        m_seedsVels[i] += vec;
        m_seeds.getVertices()[i] += m_seedsVels[i];
        m_seedsVels[i] *= 0.94f;
        //billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
        m_seeds.setNormal(i,ofVec3f(m_seedsSizeTarget[i],0,0));
        m_seeds.getColors()[i].set(m_referenceSeed->getColor());
        m_seedsSizeTarget[i] = m_referenceSeed->getScale()[0];
    }
}

void SeedsManager::updateParticles()
{
    float t = (ofGetElapsedTimef()) * 0.7f;
    float div = 250.0;
    div = 550.0;
    
    for (int i=0; i<NUMBER_OF_PARTICLES; i++) {
        
        ofVec3f vec(ofSignedNoise(t, m_particles.getVertex(i).y/div, m_particles.getVertex(i).z/div),
                    ofSignedNoise(m_particles.getVertex(i).x/div, t, m_particles.getVertex(i).z/div),
                    0);
        
        vec *= 10 * ofGetLastFrameTime();
        m_particlesVels[i] += vec;
        m_particles.getVertices()[i] += m_particlesVels[i];
        m_particlesVels[i] *= 0.94f;
        //billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
        m_particles.setNormal(i,ofVec3f(m_particlesSizeTarget[i],0,0));
        m_particles.getColors()[i].set(m_referenceParticle->getColor());
        m_particlesSizeTarget[i] = m_referenceParticle->getScale()[0];
    }
}


void SeedsManager::setColor(const ofColor& color)
{
    AppManager::getInstance().getVisualEffectsManager()->createColorEffect(m_referenceSeed, color, 0, 1);
    AppManager::getInstance().getVisualEffectsManager()->createColorEffect(m_referenceParticle, color, 0, 1);
}

void SeedsManager::setSeedsScale(float scale)
{
    AppManager::getInstance().getVisualEffectsManager()->createScaleEffect(m_referenceSeed, ofVec3f(scale), 0, 1);
}

void SeedsManager::setParticlesScale(float scale)
{
    AppManager::getInstance().getVisualEffectsManager()->createScaleEffect(m_referenceParticle, ofVec3f(scale), 0, 1);
}









