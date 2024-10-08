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
        archivo.ignore();  // Ignorar el resto de la línea

        bloques.resize(filas, std::vector<Bloque*>(columnas, nullptr));

        for (int i = 0; i < filas; ++i)
        {
            std::string linea;
            std::getline(archivo, linea);

            for (int j = 0; j < columnas; ++j)
            {
                Vector3 pos(TILE_WIDTH * i, 0, TILE_WIDTH * j);

                if (linea[j] == 'x')
                {
                    //Muros
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager,"cube.mesh", false);
                }
                else if (linea[j] == 'o')
                {
                    //Hueco perlas
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
                }
                else if (linea[j] == 'h') {
                    bloques[i][j] = new Bloque(pos, parentNode->createChildSceneNode(), sceneManager, "sphere.mesh", true);
                    bloques[i][j]->setScale(Vector3(0.1, 0.1, 0.1));
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
        // Ajustamos la cámara para que vea todo el laberinto
        float alturaCamara = max(filas, columnas) *70;  // Ajustamos la altura dependiendo del tamaño del laberinto
        float centroX = (filas - 1) * 100 / 2.0f; // Centro del laberinto en X
        float centroZ = (columnas - 1) * 100 / 2.0f; // Centro del laberinto en Z

        // Colocamos la cámara en una posición elevada y centrada
        camNode->setPosition(centroX, alturaCamara, centroZ / 0.4f);

        // Hacemos que la cámara mire hacia el centro del laberinto
        camNode->lookAt(Vector3(centroX, 0, centroZ), Node::TS_WORLD);
    }
    bool esTrapasable(Vector3 posBloque) {
        int x = posBloque.x / TILE_WIDTH;
        int z = posBloque.z / TILE_HEIGHT;
        return bloques[x][z]->esTraspasable();
    }
};

