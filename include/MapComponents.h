#ifndef MAPCOMPONENTS_H
#define MAPCOMPONENTS_H

#include <iostream>
#include <vector>
#include <fstream>

#include "MapObject.h"
#include "Grid.h"

#define MAP_LENGHT  200
#define MAP_HEIGHT  12

using std::vector;
using std::cout;
using std::endl;
using std::ofstream;

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
        static void Show();
        static void LoadMapMatrix();
        static void PrintMapMatrix();
        static void MapToXML();

    private:
        static vector<MapObject*> mapObjects;
        static Grid grid;
        static vector<vector<int>*> gameMap;

};

#endif // MAPCOMPONENTS_H
