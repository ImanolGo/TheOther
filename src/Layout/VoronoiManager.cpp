/*
 *  VoronoiManager.cpp
 *  The Other
 *
 *  Created by Imanol G√≥mez on 16/02/15.
 *
 */

#include "ofMain.h"

#include "AppManager.h"
#include "ViewManager.h"
#include "SeedsManager.h"

#include "ofxVoro.h"


#include "VoronoiManager.h"


VoronoiManager::VoronoiManager(): Manager(), m_magnifying(false), m_orbit(false),m_jitter(false), m_startOrbitTime(0)
{
	//Intentionally left empty
}


VoronoiManager::~VoronoiManager()
{
    ofLogNotice() <<"VoronoiManager::Destructor";
}


void VoronoiManager::setup()
{
	if(m_initialized)
		return;

    ofLogNotice() <<"VoronoiManager::initialized";

	Manager::setup();
    
    this->createVoronoiVisual();
    
}

void VoronoiManager::createVoronoiVisual()
{
    ofVec3f initialPosition = ofVec3f(0,0,0);
    m_voronoiVisual = ofPtr<VoronoiVisual> (new VoronoiVisual(initialPosition));
    AppManager::getInstance().getViewManager()->addVisual(m_voronoiVisual);
}

void VoronoiManager::draw()
{
    ofPushMatrix();
        //m_voronoiVisual->draw();
    ofPopMatrix();
}

void VoronoiManager::update()
{
    this->updateVoronoi();
}

void VoronoiManager::updateVoronoi()
{
    float appWidth =  AppManager::getInstance().getSettingsManager()->getAppWidth();
    float appHeight = AppManager::getInstance().getSettingsManager()->getAppHeight();
    int voronoiWidth = appWidth*2;
    int voronoiHeight = appHeight*2;
    int voronoiDepth = 1;
    
    this->createVoronoi(voronoiWidth, voronoiHeight, voronoiDepth);
}


void VoronoiManager::createVoronoi(int _width, int _height, int _deep){
    
    
    //  Define a container
    //
    
    voro::container con(-_width*0.5,_width*0.5,
                        -_height*0.5,_height*0.5,
                        -_deep*0.5,_deep*0.5,
                        1,1,1,
                        true,true,true,
                        8);
    
    
    //  Add walls (un comment one pair if you like to shape the container)
    //
    //voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
    //con.add_wall(cyl);
    
    //voro::wall_sphere sph(0, 0, 0, min(_width*0.5, _height*0.5) );
    //con.add_wall(sph);
    
    //voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
    //con.add_wall(cone);
    
    vector<ofVec3f> vertices = AppManager::getInstance().getSeedsManager()->getSeedsVertices();
    
    //  Add the cell seed to the container
    for (int i=0; i<vertices.size(); i++) {
        addCellSeed(con, vertices[i], i, true);
    }
    
    vector<ofVboMesh> wireframesMesh = getCellsFromContainer(con,0.0,true);
    if(m_jitter || m_orbit || m_magnifying){
        
        for(int i = 0; i < wireframesMesh.size(); i++){
            for(int j = 0; j < wireframesMesh[i].getNumVertices(); j++){
                ofVec3f vertex = wireframesMesh[i].getVertex(j);
                if(m_orbit){
                    this->setOrbit(vertex,wireframesMesh[i].getCentroid());
                }
                if(m_jitter){
                    this->setJitter(vertex,i*j);
                }
                if(m_magnifying){
                    this->setMagnifying(vertex);
                }
                
                wireframesMesh[i].setVertex(j,vertex);
            }
        }

        
    }
    
    m_voronoiVisual->setCellMeshes(getCellsFromContainer(con,0.0));
    m_voronoiVisual->setCellMeshWireframes(wireframesMesh);
    m_voronoiVisual->setCellRadius(getCellsRadius(con));
    m_voronoiVisual->setCellCentroids(getCellsCentroids(con));
}

void VoronoiManager::setMagnifying(ofVec3f& vertex)
{
    ofVec3f mouse(ofGetMouseX() - ofGetWidth()*0.5, ofGetHeight()*0.5 - ofGetMouseY(),0);
    float distanceToMouse = mouse.distance(vertex);
    float displacement = ofMap(distanceToMouse,0,250,200,0,true);
    ofVec3f direction = vertex - mouse;
    direction.normalize();
    
    vertex += displacement*direction;
    
}

void VoronoiManager::setJitter(ofVec3f& vertex, int index)
{
    // A typical design pattern for using Perlin noise uses a couple parameters:
    // ofSignedNoise(time*timeScale+timeOffset)*displacementScale
    //     ofSignedNoise(time) gives us noise values that change smoothly over time
    //     ofSignedNoise(time*timeScale) allows us to control the smoothness of our noise (smaller timeScale, smoother values)
    //     ofSignedNoise(time+timeOffset) allows us to use the same Perlin noise function to control multiple things and have them look as if they are moving independently
    //     ofSignedNoise(time)*displacementScale allows us to change the bounds of the noise from [-1, 1] to whatever we want
    // Combine all of those parameters together, and you've got some nice control over your noise
 
    
    float time = ofGetElapsedTimef();
    float timeScale=0.9;
    float displacementScale=40.75;
    //ofVec3f timeOffsets = ofVec3f(ofRandom(0,100000),ofRandom(0,100000),ofRandom(0,100000));
    ofVec3f timeOffsets = ofVec3f(index);
    
    //vertex.x+=(ofSignedNoise(time*timeScale+timeOffsets.x))*displacementScale;
    //vertex.y+=(ofSignedNoise(time*timeScale+timeOffsets.y))*displacementScale;
    vertex.z+=(ofSignedNoise(time*timeScale))*displacementScale;
}

void VoronoiManager::setOrbit(ofVec3f& vertex, const ofVec3f& meshCentroid)
{
    ofVec3f orbitVector;
    
    float distance= vertex.distance(meshCentroid);
    float angle = atan2(vertex.y - meshCentroid.y,vertex.x - meshCentroid.x);
    float elapsedTime=ofGetElapsedTimef() - m_startOrbitTime;
    
    //Lets adjust the speed of the orbits such that things that are closer to
    //the center rotate faster than things that are more distant
    float speed=ofMap(distance,0,200,1,0.25,true);
    
    float rotatedAngle = elapsedTime*speed+angle;
    vertex.x=distance*cos(rotatedAngle)+meshCentroid.x;
    vertex.y=distance*sin(rotatedAngle)+meshCentroid.y;
    
}




