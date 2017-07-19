#include "GameMap.h"

GameMap::GameMap(int id, int rows, int cols, int time, int bgcolor, bool goLeft)
{
    this->id = id;
    this->rows = rows;
    this->cols = cols;
    this->time = time;
    this->bgcolor = bgcolor;
    this->goLeft = goLeft;
    for(int i = 0; i < this->rows; i++){
        gameMap.push_back(new vector<int>);
        for(int j = 0; j < this->cols; j++){
            gameMap[i]->push_back(0);
        }
    }
}

GameMap::~GameMap()
{
    //dtor
}

void GameMap::SetValue(int row, int col, int value){
    gameMap[row]->at(col) = value;
}

int GameMap::GetValue(int row, int col){
    return gameMap[row]->at(col);
}

void GameMap::PrintMap(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << gameMap[i]->at(j);
        }
        cout << endl;
    }
}

void GameMap::SetFromXML(string xmlDoc, int id){
    this->id = id;
    string aux, aux2;
    bool found = false;

    //abre o arquivo
    ifstream enterMap;
    enterMap.open(xmlDoc, std::ifstream::in);

    //pega a primeira linha
    getline(enterMap, aux2);
    aux += aux2;

    //pega as outras linhas
    while(!enterMap.eof()){
        getline(enterMap, aux2);
        if(!found){
            if(aux2 != "<level id='"+to_string(id)+"'>") continue;
            else{
                aux += aux2;
                found = true;
            }
        }else{
            aux += aux2;
            if(aux2 == "</level>") break;
        }
    }
    enterMap.close();

    char *c =(char*)malloc(sizeof(char)*aux.size());
    strcpy(c, aux.c_str());
    //FIM

    doc.parse<0>(c);
    free(c);

    xml_node<>* tilemap = doc.first_node();    //node == <level></level>
    tilemap = tilemap->first_node();              //node == <player/>
    tilemap = tilemap->next_sibling();            //node == <tilemap></tilemap>

    ReadAttributes(tilemap);
    ReadRows(tilemap->first_node()->first_node());
}

void GameMap::ReadAttributes(xml_node<>* tilemap){
    xml_attribute<>* tilemapAtt = tilemap->first_attribute();

    this->rows = atoi(tilemapAtt->value());
    tilemapAtt = tilemapAtt->next_attribute();

    this->cols = atoi(tilemapAtt->value());
    tilemapAtt = tilemapAtt->next_attribute();

    this->bgcolor = atoi(tilemapAtt->value());
    tilemapAtt = tilemapAtt->next_attribute();

    this->time = atoi(tilemapAtt->value());
    tilemapAtt = tilemapAtt->next_attribute();

    string goL(tilemapAtt->value());
    if(goL == "true") this->goLeft = true;
    else this->goLeft = false;
}

void GameMap::ReadRows(xml_node<>* row){
    gameMap.resize( this->rows ); //resize do numero de linhas
    for(unsigned int i = 0; i < gameMap.size(); i++){
        gameMap[i]->resize( this->cols ); //resize do numero de colunas
        stringstream ssAux;
        ssAux << row->first_node()->value();
        for(unsigned int j = 0, k = 0; j < gameMap[i]->size(); j++, k+=2){
            ssAux >> gameMap[i]->at(j);
            if(ssAux.peek() == ',') ssAux.ignore();
        }
        row = row->next_sibling();
    }
}

unsigned int GameMap::GetRows(){
    return rows;
}

unsigned int GameMap::GetCols(){
    return cols;
}
