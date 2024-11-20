#include "IG2App.h"

using namespace Ogre;
using namespace std;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt){
        
    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE){
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_s) {
        laberinto->setVisibleLaberinto(true);
        cinematica->setVisibleCinematica(false);
        mLightNode1->setVisible(false);
        mSM->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
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

    mCamNode->setPosition(0, 0, 1000); //posicion de la camara
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);//punto donde mira la camara
    
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);
    
    
   
    //------------------------------------------------------------------------
        // Creating the laberinto
        // The laberinto is created by loading from a file
    string nombreArchivo = "../stage1.txt";
    laberinto = new Laberinto(nombreArchivo, mSM, mSM->getRootSceneNode(), mCamNode);
    laberinto->setVisibleLaberinto(false);
    //------------------------------------------------------------------------
     //Creating the cinematic
    cinematica = new Cinematica(mSM, mSM->getRootSceneNode(), mCamNode);
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(1, 1, 1);

    mLightNode1 = mSM->getRootSceneNode()->createChildSceneNode("nLuz1");
    //mLightNode = mCamNode->createChildSceneNode("nLuz");
    mLightNode1->attachObject(luz);
    mLightNode1->setDirection(Ogre::Vector3(0, -1,0));
    // Creating the light
   

   //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    
    Light* light = laberinto->getLightHeroe();
    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->setPosition(laberinto->getHeroe()->getPosition().x, 1000, laberinto->getHeroe()->getPosition().z);
    mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
    mLightNode->attachObject(light);
    laberinto->getHeroe()->setLight(mLightNode);

   InfoTitle = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoLabel", "Game Info", 200);
    
   InfoPlayer = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoPlayer", "Info", 200, 120);
   InfoPlayer->appendText("Puntos:" + to_string(0));
   InfoPlayer->appendText("Vidas:" + to_string(laberinto->getHeroe()->getVidas()));

    laberinto->getHeroe()->setInfoText(InfoPlayer);
   
    addInputListener(cinematica->getHeroe());
    addInputListener(laberinto->getHeroe());
    for (size_t i = 0; i < laberinto->getVillanos().size(); i++)
    {
        addInputListener(laberinto->getVillanos()[i]);
    }
}


