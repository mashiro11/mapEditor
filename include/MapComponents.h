#ifndef MAPCOMPONENTS_H
#define MAPCOMPONENTS_H

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>

//  Correct to_string bug
#include <sstream>

#include "MapObject.h"
#include "Grid.h"

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

namespace patch{
    template <typename T> string to_string(const T& n){
        ostringstream stm;
        stm << n;
        return stm.str();
    }
}
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
        static string MapToString(const vector<vector<int>*> &matrix, int level, int time, string irEsquerda);
        static void SaveMap(const vector<vector<int>*> &matrix, int level, int time, string irEsquerda);
        static void RewindMap(vector<vector<int>*> &matrix);
        static void ClearMap();

    private:

        static map<int, string> newMapsOutput;
        static vector<MapObject*> mapObjects;
        static Grid gridMap;
        static Grid gridMenu;
        static vector<vector<int>*> gameMap;
        static int origin;

};

#endif // MAPCOMPONENTS_H
