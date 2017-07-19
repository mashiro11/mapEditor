#ifndef MAPCOMPONENTS_H
#define MAPCOMPONENTS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <windows.h> //for sleep
#include "rapidxml.hpp"

#include <sstream>

#include "MapObject.h"
#include "Grid.h"
#include "GameMap.h"

#define MAP_LENGHT  200
#define MAP_HEIGHT  12

#ifndef GRID_W_H
#define GRID_W_H 32
#endif // GRID_W_H

using std::vector;
using std::cout;
using std::endl;
using std::ofstream;
using std::cin;
using std::map;
using std::string;
using std::ostringstream;
using std::to_string;
using std::ifstream;
using namespace rapidxml;
/*
namespace patch{
    template <typename T> string to_string(const T& n){
        ostringstream stm;
        stm << n;
        return stm.str();
    }
}*/
class MapObject;
class MapComponents
{
    public:
        //MapComponents();
        virtual ~MapComponents();
        static void AddMapObject(MapObject* mapObj);
        static MapObject* GetObject(int i);
        static void ConfigImages(int tileDim);
        static unsigned int GetMapObjNum();
        static void LoadComponents();
        static void SetGridSize(int w, int h);
        static void Show(int dt = 0);
        static void LoadMapMatrix();
        static void PrintMapMatrix();
        static void MapToXML(string nomeArq);
        static int currentLevel;
        static void XMLHeader();
        static void XMLFooter();
        static string MapToString(const vector<vector<int>*> &matrix, int level, int time, int bgColor = 0x5C94FC , string irEsquerda = "false");
        static void SaveMap(const vector<vector<int>*> &matrix, int level, int time, int bgColor = 0x5C94FC, string irEsquerda = "false");
        static void RewindMap(vector<vector<int>*> &matrix);
        static void ClearMap();
        static void ReadXML();

    private:

        static map<int, string> newMapsOutput;
        static vector<MapObject*> mapObjects;
        static Grid gridMap;
        static Grid gridMenu;
        static GameMap gmap;
        static vector<GameMap*> gmaps;
        static vector<vector<int>*> gameMap;
        static int origin;
        static xml_document<> doc;

};

#endif // MAPCOMPONENTS_H
