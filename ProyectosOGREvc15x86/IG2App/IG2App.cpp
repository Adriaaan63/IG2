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
        laberinto->ajustarCamara(mCamNode);
        laberinto->createSky(mSM);
        cinematica->setVisibleCinematica(false);
        mLightNode1->setVisible(false);
        mSM->setShadowTechnique(Ogre::ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);
        createInfoPlayer();
    }
    
  return true;
}
void IG2App::createInfoPlayer() {
    mTrayMgr->destroyWidget("InfoCinematica");
    mTrayMgr->destroyWidget("InfoPlayerCine");
    InfoTitle = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoLabel", "Game Info", 200);

   InfoPlayer = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoPlayer", "Info", 200, 120);
   InfoPlayer->appendText("Puntos:" + to_string(0));
   InfoPlayer->appendText("Vidas:" + to_string(laberinto->getHeroe()->getVidas()));

   laberinto->getHeroe()->setInfoText(InfoPlayer);
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
    InfoCinematica = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "InfoCinematica", "Insert coin(s) to start", 300);

    InfoPlayerCine = mTrayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "InfoPlayerCine", "Game Info here!", 300, 120);
    InfoPlayerCine->appendText("Waiting for the player...\n");
    InfoPlayerCine->appendText("1 player mode" );

    cinematica->getHeroe()->setInfoText(InfoPlayerCine);
    //------------------------------------------------------------------------
    // Creating the light
   //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    
    Light* light = laberinto->getLightHeroe();
    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->setPosition(laberinto->getHeroe()->getPosition().x, 1000, laberinto->getHeroe()->getPosition().z);
    mLightNode->setDirection(Ogre::Vector3(0, -1, 0));
    mLightNode->attachObject(light);
    laberinto->getHeroe()->setLight(mLightNode);

   
    addInputListener(cinematica->getHeroe());
    addInputListener(cinematica->getVillanos());
    addInputListener(laberinto->getHeroe());
    for (size_t i = 0; i < laberinto->getVillanos().size(); i++)
    {
        addInputListener(laberinto->getVillanos()[i]);
    }
}

void IG2App::frameRendered(const Ogre::FrameEvent& evt) {
        static float time = 0.0f;
        time += evt.timeSinceLastFrame;

        float cycle = fmod(time, 15.0f) / 15.0f;

        float zoomFactor = 0.3f + 0.7f * sin(cycle * 2.0f * M_PI);
        float lightIntensity = 0.3f + 0.7f * cos(cycle * 2.0f * M_PI);

        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName("practica2/spaceSkyZoomLightShader");
        Ogre::Technique* technique = material->getTechnique(0);
        Ogre::Pass* pass = technique->getPass(0);
        pass->getVertexProgramParameters()->setNamedConstant("zoomFactor", zoomFactor);
        pass->getFragmentProgramParameters()->setNamedConstant("intLuzAmb", lightIntensity);
}



