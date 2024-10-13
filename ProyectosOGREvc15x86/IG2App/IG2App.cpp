#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    
  return true;
}

void IG2App::shutdown(){
    
  mShaderGenerator->removeSceneManager(mSM);
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown(); 
}

void IG2App::setup(void){
    
    // do not forget to call the base first
    IG2ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);

    mSM->addRenderQueueListener(mOverlaySystem);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);
    
    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void){
    
    //------------------------------------------------------------------------
    // Creating the camera
    
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);
            
    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    //mCamNode->setPosition(0, 0, 1000); //posicion de la camara
    //mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);//punto donde mira la camara
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
    //------------------------------------------------------------------------
    // Creating the light
    
    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.5, 0.5, 0.5);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  
    //------------------------------------------------------------------------
        // Creating the laberinto
        // The laberinto is created by loading from a file
    string nombreArchivo = "../stage1.txt";
    laberinto = new Laberinto(nombreArchivo, mSM, mSM->getRootSceneNode(), mCamNode);

    //------------------------------------------------------------------------
    // Crear el plano que servirá de suelo
    Plane plane(Vector3::UNIT_Y, -50);  
    MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, laberinto->getFilas() * 100, laberinto->getColumnas() *  100, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
    Entity* entSuelo = mSM->createEntity("ground");
    SceneNode* nodeSuelo = mSM->getRootSceneNode()->createChildSceneNode();
    nodeSuelo->setPosition(laberinto->getColumnas() * 100 / 2, 0, laberinto->getFilas() * 100 / 2);
    nodeSuelo->attachObject(entSuelo);

    InfoTextBox = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoBox", "Game Info", 200, 50);
    InfoTextBox->setTextAlignment(Ogre::TextAreaOverlayElement::Right);
    InfoLabel = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoLabel", "Puntos: 0", 200);  
    Vector3 posHeroe = laberinto->getPosHeroe();
    heroe = new Heroe(posHeroe, mSM->getRootSceneNode()->createChildSceneNode(), mSM, "Sinbad.mesh", laberinto, InfoLabel);
    heroe->setScale(Vector3(10.0, 10.0, 10.0));
    addInputListener(heroe);
}


