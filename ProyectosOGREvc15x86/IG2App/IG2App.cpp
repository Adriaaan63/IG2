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

    mCamNode->setPosition(0, 0, 1000); //posicion de la camara
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);//punto donde mira la camara
    
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
    mLightNode->setDirection(Ogre::Vector3(1, 1, -1));
    

    ////------------------------------------------------------------------------
    //// Creating Scene
    //Ogre::Entity* ent1 = mSM->createEntity("RomanBathLower.mesh");
    //mRomanNode = mSM->getRootSceneNode()->createChildSceneNode("nRoman");
    //mRomanNode->attachObject(ent1);
    //// Show bounding box
    //mRomanNode->showBoundingBox(true);

    //// Set position of Sinbad
    ////mRomanNode->setPosition(x, y, z);

    //// Set scale of Sinbad
    //mRomanNode->setScale(1, 1, 1);

    ////mRomanNode->yaw(Ogre::Degree(-45));
    ////mRomanNode->setVisible(false); 
    //
    //Ogre::Entity* ent2 = mSM->createEntity("RomanBathUpper.mesh");
    //mRoman1Node = mSM->getRootSceneNode()->createChildSceneNode("nRoman1");
    //mRoman1Node->attachObject(ent2);
    //// Show bounding box
    //mRoman1Node->showBoundingBox(true);

    //// Set position of Sinbad
    ////mRoman1Node->setPosition(x, y, z);

    //// Set scale of Sinbad
    //mRoman1Node->setScale(1, 1, 1);

    ////mRoman1Node->yaw(Ogre::Degree(-45));
    ////mRoman1Node->setVisible(false); 
    //
    ////------------------------------------------------------------------------
    //// Creating Sinbad

    //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    //mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    //mSinbadNode->attachObject(ent);

    //// Show bounding box
    //mSinbadNode->showBoundingBox(true);
    //
    //// Set position of Sinbad
    //mSinbadNode->setPosition(0.0, 15.0, 0.0);
    //
    //// Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);
    //
    ////mSinbadNode->yaw(Ogre::Degree(-45));
    ////mSinbadNode->setVisible(false);    

    //------------------------------------------------------------------------
    // Creating Muneco
    Ogre::Entity* cabeza = mSM->createEntity("sphere.mesh");
    mSnowManNode = mSM->getRootSceneNode()->createChildSceneNode("nCabeza");
    mSnowManNode->attachObject(cabeza);
    

    // Set position of Sinbad
    mSnowManNode->setPosition(0.0, 150, 0.0);
    

    // Set scale of Sinbad
    mSnowManNode->setScale(0.75, 0.75, 0.75);

   /* mSnowManNode->yaw(Ogre::Degree(-45));*/
    
    //mSnowManNode->setVisible(false);  

    Ogre::Entity* nariz = mSM->createEntity("sphere.mesh");
    mCabezaNode = mSnowManNode->createChildSceneNode("nNariz");;
    mCabezaNode->attachObject(nariz);
   

    // Set position of Sinbad
    mCabezaNode->setPosition(0.0, 10.0, 100.0);

    // Set scale of Sinbad
    mCabezaNode->setScale(0.15, 0.15, 0.15);

    //mCabezaNode->yaw(Ogre::Degree(-45));

    //mCabezaNode->setVisible(false); 

    Ogre::Entity* boca = mSM->createEntity("sphere.mesh");
    mCabezaNode = mSnowManNode->createChildSceneNode("nBoca");;
    mCabezaNode->attachObject(boca);
    

    // Set position of Sinbad
    mCabezaNode->setPosition(0.0, -20.0, 100.0);

    // Set scale of Sinbad
    mCabezaNode->setScale(0.25, 0.1, 0.1);

    //mCabezaNode->yaw(Ogre::Degree(-45));

    //mCabezaNode->setVisible(false);

    Ogre::Entity* ojo1 = mSM->createEntity("sphere.mesh");
    mCabezaNode = mSnowManNode->createChildSceneNode("nojo1");;
    mCabezaNode->attachObject(ojo1);
    

    // Set position of Sinbad
    mCabezaNode->setPosition(-40.0, 30.0, 100.0);

    // Set scale of Sinbad
    mCabezaNode->setScale(0.15, 0.15, 0.15);

    //mCabezaNode->yaw(Ogre::Degree(-45));

    //mCabezaNode->setVisible(false); 

    Ogre::Entity* ojo2 = mSM->createEntity("sphere.mesh");
    mCabezaNode = mSnowManNode->createChildSceneNode("nojo2");;
    mCabezaNode->attachObject(ojo2);
    

    // Set position of Sinbad
    mCabezaNode->setPosition(40.0, 30.0, 100.0);

    // Set scale of Sinbad
    mCabezaNode->setScale(0.15, 0.15, 0.15);

    //mCabezaNode->yaw(Ogre::Degree(-45));

    //mCabezaNode->setVisible(false); 

    //------------------------------------------------------------------------
    
    Ogre::Entity* cuerpo = mSM->createEntity("sphere.mesh");
    mSnowManNode = mSM->getRootSceneNode()->createChildSceneNode("nCuerpo");
    mSnowManNode->attachObject(cuerpo);
    

    // Set position of Sinbad
    /*mSnowManNode->setPosition(0.0, 15.0, 0.0);*/

    // Set scale of Sinbad
    mSnowManNode->setScale(1, 1, 1);

    //mSnowManNode->yaw(Ogre::Degree(-45));
    //mSnowManNode->setVisible(false); 
    
    Ogre::Entity* ombligo = mSM->createEntity("sphere.mesh");
    mCuerpoNode = mSnowManNode->createChildSceneNode("nOmbligo");;
    mCuerpoNode->attachObject(ombligo);


    // Set position of Sinbad
    mCuerpoNode->setPosition(0.0, 0.0, 100.0);

    // Set scale of Sinbad
    mCuerpoNode->setScale(0.15, 0.15, 0.15);

    //mCabezaNode->yaw(Ogre::Degree(-45));

    //mCabezaNode->setVisible(false);

    
}


