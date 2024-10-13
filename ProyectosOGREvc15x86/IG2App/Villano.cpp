#include "Villano.h"
void Villano::createVillano() {

}
void Villano::frameRendered(const Ogre::FrameEvent& evt) {
    if (mNode == nullptr || lab == nullptr) {
        return;
    }
    //calcular la nueva direccion que minimice la distancia con el heroe
    giro();
}