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
public:
    Laberinto(const std::string& nombreArchivo, SceneManager* sceneManager, SceneNode* parentNode)
    {
        cargarDesdeFichero(nombreArchivo, sceneManager, parentNode);
    }

    void cargarDesdeFichero(const std::string& nombreArchivo, SceneManager* sceneManager, SceneNode* parentNode)
    {
        std::ifstream archivo(nombreArchivo);

        if (!archivo)
        {
            std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
            return;
        }

        archivo >> filas >> columnas;
        archivo.ignore();  // Ignorar el resto de la l�nea

        bloques.resize(filas, std::vector<Bloque*>(columnas, nullptr));

        for (int i = 0; i < filas; ++i)
        {
            std::string linea;
            std::getline(archivo, linea);

            for (int j = 0; j < columnas; ++j)
            {
                Vector3 pos(100 * i, 0, 100 * j);

                if (linea[j] == 'x')
                {
                    bloques[i][j] = new Muro(pos, parentNode->createChildSceneNode(), sceneManager);
                }
                else if (linea[j] == 'o')
                {
                    bloques[i][j] = new Hueco(pos, parentNode->createChildSceneNode(), sceneManager);
                }
            }
        }
        archivo.close();
    }

};

