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
        // Creating the laberinto
        // The laberinto is created by loading from a file
    string nombreArchivo = "../stage1.txt";
    laberinto = new Laberinto(nombreArchivo, mSM, mSM->getRootSceneNode(), mCamNode);
    //------------------------------------------------------------------------
   // Creating the light
    mSM->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

   //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    Light* luzFoco = mSM->createLight("Luz Foco");
    luzFoco->setType(Ogre::Light::LT_SPOTLIGHT);
    luzFoco->setDiffuseColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));
    luzFoco->setCastShadows(true);
   /* luzFoco->setDirection(Ogre::Vector3(1, -1, 0));*/
    luzFoco->setSpotlightInnerAngle(Ogre::Degree(90.0f));
    luzFoco->setSpotlightOuterAngle(Ogre::Degree(90.0f));
    luzFoco->setSpotlightFalloff(5.0f);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->setPosition(laberinto->getHeroe()->getPosition().x, 1000, laberinto->getHeroe()->getPosition().z);
    mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
    mLightNode->attachObject(luzFoco);
    laberinto->getHeroe()->setLight(mLightNode);

   InfoTitle = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoLabel", "Game Info", 200);
    
   InfoPlayer = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoPlayer", "Info", 200, 120);
   InfoPlayer->appendText("Puntos:" + to_string(0));
   InfoPlayer->appendText("Vidas:" + to_string(laberinto->getHeroe()->getVidas()));

    /*InfoTextBox = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoBox", "Game Info", 200, 50);*/
   /* InfoTextBox->setTextAlignment(Ogre::TextAreaOverlayElement::Right);
    InfoPuntos = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoLabel", "Puntos: 0", 200);
    InfoVidas = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "Info", "Vidas: 3", 200);*/
    laberinto->getHeroe()->setInfoText(InfoPlayer);
   
    addInputListener(laberinto->getHeroe());
    for (size_t i = 0; i < laberinto->getVillanos().size(); i++)
    {
        addInputListener(laberinto->getVillanos()[i]);
    }
   /* SceneNode* villanoNode = mSM->getRootSceneNode()->createChildSceneNode("Villano1");
    Villano* villanoPrueba = new Villano(Vector3(0, 500, 0), villanoNode, mSM, laberinto);
    addInputListener(villanoPrueba);*/
}


