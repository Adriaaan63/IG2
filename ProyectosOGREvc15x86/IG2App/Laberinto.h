#pragma once
#include "Bloque.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include "Villano.h"
#include "IG2ApplicationContext.h"
#include "Heroe.h"
using namespace std;

class Laberinto
{
private:
    int filas;
    int columnas;
    std::vector<std::vector<Bloque*>> bloques;
    Heroe* heroe;
    std::vector<Villano*> villanos;
    string materialSuelo;
    string materialPerla;
    string materialMuro;
public:
    Laberinto(const std::string& nombreArchivo, SceneManager* sceneManager, SceneNode* parentNode, SceneNode* camNode)
    {
        cargarDesdeFichero(nombreArchivo, sceneManager, parentNode);
        createFloor(sceneManager);
        ajustarCamara(camNode);
    }
    ~Laberinto(){}
    void cargarDesdeFichero(const std::string& nombreArchivo, SceneManager* sceneManager, SceneNode* parentNode)
    {
        std::ifstream archivo(nombreArchivo);

        if (!archivo)
        {
            std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
            return;
        }

        archivo >> filas >> columnas >> materialSuelo >> materialMuro >> materialPerla;
        archivo.ignore();  

        bloques.resize(filas, std::vector<Bloque*>(columnas, nullptr));

        for (int i = 0; i < filas; ++i)
        {
            std::string linea;
            std::getline(archivo, linea);

            for (int j = 0; j < columnas; ++j)
            {
                Vector3 pos(TILE_WIDTH * j, 0, TILE_WIDTH * i);

                if (linea[j] == 'x')
                {
                    //Muros
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager,"cube.mesh", false, materialMuro);
                }
                else if (linea[j] == 'o')
                {
                    //Hueco perlas
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true, materialPerla);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
                }
                else if (linea[j] == 'h') {
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true, materialPerla);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
                    heroe = new Heroe(pos, parentNode->createChildSceneNode(), sceneManager, "Sinbad.mesh", this);
                    heroe->setScale(Vector3(10.0, 10.0, 10.0));
                }
                else if (linea[j] == 'v') {
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true, materialPerla);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
                    villanos.push_back(new Villano(pos, parentNode->createChildSceneNode(), sceneManager, "ogrehead.mesh", this));
                    
                }
                else if (linea[j] == 'V') {
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true, materialPerla);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
                    villanos.push_back(new Villano(pos, parentNode->createChildSceneNode(), sceneManager, this));

                }
                
            }
        }
       
        archivo.close();
        
    }

    Heroe* getHeroe() const { 
        return heroe;
    };
    std::vector<Villano*> getVillanos()const { return villanos; };
    void ajustarCamara(SceneNode* camNode) {
        float alturaCamara = max(filas, columnas) *100;  
        float centroX = (filas - 1) * 100 / 2.0f; 
        float centroZ = (columnas - 1) * 100 / 2.0f; 

        camNode->setPosition(centroX, alturaCamara, centroZ / 0.35f);
        
        camNode->lookAt(Vector3(centroX, 0, centroZ), Node::TS_WORLD);
    }

    bool esTrapasable(Vector3 posBloque) {
        int x = posBloque.x / TILE_WIDTH;
        int z = posBloque.z / TILE_HEIGHT;
        return bloques[z][x]->esTraspasable();
    }

    Bloque* getBloque(Vector3 posBloque) const {
        int x = posBloque.x / TILE_WIDTH;
        int z = posBloque.z / TILE_HEIGHT;
        return bloques[z][x];
    }

    int getFilas() {
        return filas;
    }

    int getColumnas() {
        return columnas;
    }
    std::vector<Vector3> getDireccionesTraspasables(Vector3 posBloque) const {
        std::vector<Vector3> posiblesDirecciones;
        if (getBloque(Vector3(posBloque.x - TILE_WIDTH, 0, posBloque.z))->esTraspasable()) {
            posiblesDirecciones.push_back(Vector3(-1, 0, 0));
        }
        if (getBloque(Vector3(posBloque.x + TILE_WIDTH, 0, posBloque.z))->esTraspasable()) {
            posiblesDirecciones.push_back(Vector3(1, 0, 0));
        }
        if (getBloque(Vector3(posBloque.x, 0, posBloque.z - TILE_HEIGHT))->esTraspasable()) {
            posiblesDirecciones.push_back(Vector3(0, 0, -1));
        }
        if (getBloque(Vector3(posBloque.x, 0, posBloque.z + TILE_HEIGHT))->esTraspasable()) {
            posiblesDirecciones.push_back(Vector3(0, 0, 1));
        }
        return posiblesDirecciones;
    }
    void createFloor(SceneManager* sceneManager);
};

