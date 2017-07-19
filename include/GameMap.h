#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>

#include "rapidxml.hpp"
//#include "rapidxml_print.hpp"
//#include "rapidxml_utils.hpp"
//#include "rapidxml_iterators.hpp"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::ifstream;
using std::stringstream;
using rapidxml::xml_document;
using namespace rapidxml;

class GameMap
{
    public:
        GameMap(int id, int rows, int cols, int time = 300, int bgcolor = 0, bool goLeft = false);
        virtual ~GameMap();
        void SetValue(int row, int col, int value);
        int GetValue(int row, int col);
        void SetPlayer(int startRow, int startCol, string facing);
        void PrintMap();
        void SetFromXML(string xmlDoc, int id);
        unsigned int GetRows();
        unsigned int GetCols();

    protected:

    private:
        int id;
        int startRow;
        int startCol;
        string facing;
        int rows;
        int cols;
        int bgcolor;
        int time;
        bool goLeft;
        vector<vector<int>*> gameMap;
        xml_document<> doc;
        void ReadAttributes(xml_node<>* tilemap);
        void ReadRows(xml_node<>* row);
};

#endif // GAMEMAP_H
