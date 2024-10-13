#pragma once
#include "Bloque.h"
#include "Hueco.h"
#include "Muro.h"
#include <iostream>
#include <fstream> 
#include <vector>

using namespace std;

class Laberinto
{
private:
    int filas;
    int columnas;
    std::vector<std::vector<Bloque*>> bloques;
    Bloque* suelo;
    Vector3 posHeroe;
public:
    Laberinto(const std::string& nombreArchivo, SceneManager* sceneManager, SceneNode* parentNode, SceneNode* camNode)
    {
        cargarDesdeFichero(nombreArchivo, sceneManager, parentNode);
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

        archivo >> filas >> columnas;
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
                    bloques[j][i] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager,"cube.mesh", false);
                }
                else if (linea[j] == 'o')
                {
                    //Hueco perlas
                    bloques[j][i] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true);
                    bloques[j][i]->setScale(Vector3(0.1, 0.1, 0.1));
                }
                else if (linea[j] == 'h') {
                    bloques[j][i] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true);
                    bloques[j][i]->setScale(Vector3(0.1, 0.1, 0.1));
                    posHeroe = pos;
                }
                
            }
        }
        /*suelo = new Bloque(Vector3(filas *100 / 2, -50.0, columnas * 100 / 2), parentNode->createChildSceneNode(), sceneManager, "cube.mesh", false);
        suelo->setScale(Vector3(-filas, 0.0, columnas));*/
        archivo.close();
    }

    Vector3 getPosHeroe() const { 
        return posHeroe;
    };

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
        return bloques[x][z]->esTraspasable();
    }

    Bloque* getBloque(Vector3 posBloque) const {
        int x = posBloque.x / TILE_WIDTH;
        int z = posBloque.z / TILE_HEIGHT;
        return bloques[x][z];
    }

    int getFilas() {
        return filas;
    }

    int getColumnas() {
        return columnas;
    }
};

