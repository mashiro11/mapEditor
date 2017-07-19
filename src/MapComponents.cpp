#include "MapComponents.h"

vector<MapObject*> MapComponents::mapObjects;
GameMap MapComponents::gmap(1, MAP_HEIGHT, MAP_LENGHT);
vector<vector<int>*> MapComponents::gameMap;
Grid MapComponents::gridMenu;
Grid MapComponents::gridMap;
int MapComponents::origin = 0;
int MapComponents::currentLevel = 1;
map<int, string> MapComponents::newMapsOutput;
xml_document<> MapComponents::doc;

MapComponents::~MapComponents()
{
    //dtor
}


void MapComponents::AddMapObject(MapObject* mapObj){
    mapObjects.push_back(mapObj);
}

MapObject* MapComponents::GetObject(int i){
    return mapObjects[i];
}

void MapComponents::ConfigImages(int tileDim){
    for(unsigned int i = 0; i < mapObjects.size(); i++){
        int w = mapObjects[i]->GetWidth();
        if(w > tileDim){
            mapObjects[i]->Clip(tileDim, mapObjects[i]->GetHeight());
        }
        mapObjects[i]->Resize(50);
        if(mapObjects[i]->GetHeight()>tileDim/2){
            mapObjects[i]->Resize(100, 50);
        }
    }

}

unsigned int MapComponents::GetMapObjNum(){
    return mapObjects.size();
}

void MapComponents::SetGridSize(int w, int h){
    //gridMap.SetDimensions(w, h);
    gridMap.SetDimensions(w, h, 0, GRID_W_H*3, WINDOW_WIDTH, WINDOW_HEIGHT - GRID_W_H*3);
}

void MapComponents::Show(int dt){
    if(InputHandler::GetKey() == SDLK_RIGHT) origin += dt;
    if(InputHandler::GetKey() == SDLK_LEFT) origin -= dt;

    gridMap.Update(dt);
    gridMap.Render();

    gridMenu.Update();
    gridMenu.Render();

    for(unsigned int i = 0; i < mapObjects.size(); i++){
        mapObjects[i]->Update(dt);
        mapObjects[i]->Render();

        int ypos;
        ypos = mapObjects[i]->GetY() - GRID_W_H*3;
        if(mapObjects[i]->GetStatus() == "delete"){
             if(ypos > 0){
                    gameMap[ ypos/GRID_W_H ]->at( (mapObjects[i]->GetX()+origin)/GRID_W_H ) = 0;
                    gmap.SetValue(ypos/GRID_W_H, (mapObjects[i]->GetX()+origin)/GRID_W_H, 0);
             }
             mapObjects.erase(mapObjects.begin() + i);
        }else if(mapObjects[i]->GetStatus() == "selected"){
            if(ypos > 0){
                    gameMap[ ypos/GRID_W_H ]->at( (mapObjects[i]->GetX()+origin)/GRID_W_H ) = 0;
                    gmap.SetValue(ypos/GRID_W_H, (mapObjects[i]->GetX()+origin)/GRID_W_H, 0);
            }
        }else if(mapObjects[i]->GetStatus() == "placed"){
            if(ypos > 0){
                    gameMap[ ypos/GRID_W_H ]->at( (mapObjects[i]->GetX()+origin)/GRID_W_H ) = mapObjects[i]->GetCode();
                    gmap.SetValue(ypos/GRID_W_H, (mapObjects[i]->GetX()+origin)/GRID_W_H, mapObjects[i]->GetCode());
            }
        }
    }
    if(InputHandler::GetKey() == SDLK_p){
        //PrintMapMatrix();
        cout << "Numero do mapa: ";
        int num;
        cin >> num;
        cout << "Tempo da fase: ";
        int time;
        cin >> time;
        cout << "Permitido ir para esquerda? s/n: ";
        string irEsquerda;
        cin >> irEsquerda;
        (irEsquerda == "s")? irEsquerda = "true": irEsquerda = "false";
        cout << "Backgorund color? 1(preto)/2(azul)/3(insira hexa da cor): ";
        int bgColor;
        cin >> bgColor;
        switch(bgColor){
        case 1:
            bgColor = 0x000000;
            break;
        case 2:
            bgColor = 0x5C94FC;
            break;
        }
        SaveMap(gameMap, num, time, bgColor, irEsquerda);

        //cout << newMapsOutput[num];
        currentLevel++;
        RewindMap(gameMap);
        ClearMap();
    }
    if(InputHandler::GetKey() == SDLK_RETURN){
        cout << "Numero do mapa: ";
        int num;
        cin >> num;
        cout << "Tempo da fase: ";
        int time;
        cin >> time;
        cout << "Permitido ir para esquerda? s/n: ";
        string irEsquerda;
        cin >> irEsquerda;
        (irEsquerda == "s")? irEsquerda = "true": irEsquerda = "false";
        cout << "Backgorund color? 1(preto)/2(azul)/3(insira hexa da cor): ";
        int bgColor;
        cin >> bgColor;
        switch(bgColor){
        case 1:
            bgColor = 0x000000;
            break;
        case 2:
            bgColor = 0x5C94FC;
            break;
        }
        SaveMap(gameMap, num, time, bgColor, irEsquerda);
        string nomeArq("leveldata.xml");
        cout << "Saida salva em: leveldata.xml";
        //cout << "Nomeie a saida: ";
        //cin >> nomeArq;
        MapToXML(nomeArq);
    }if(InputHandler::GetKey() == SDLK_r){
        //ReadXML();
        ClearMap();
        gmap.SetFromXML("leveldata.xml", 1);
        cout << gmap.GetRows() << endl;
        cout << gmap.GetCols() << endl;
        for(unsigned int i = 0; i < gmap.GetRows(); i++ ){
            for(unsigned int j = 0; j < gmap.GetCols(); j++){
                for(unsigned int k = 0; k < mapObjects.size(); k++){
                    if(mapObjects[k]->GetCode() == gmap.GetValue(i, j)){
                        cout << "(" << i << "," << j << "): " << gmap.GetValue(i, j) << endl;
                        AddMapObject(mapObjects[k]->CreateCopy("placed", i, j));
                        break;
                    }
                }
            }
        }
    }
}

void MapComponents::LoadMapMatrix(){
    for(int i = 0; i < MAP_HEIGHT; i++){
        gameMap.push_back(new vector<int>);
        for(int j = 0; j < MAP_LENGHT; j++){
            gameMap[i]->push_back(0);
        }
    }
}

void MapComponents::PrintMapMatrix(){
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_LENGHT; j++){
            cout << gameMap[i]->at(j);
        }
        cout << endl;
    }
}

void MapComponents::SaveMap(const vector<vector<int>*> &matrix, int i, int time, int bgColor, string irEsquerda){
    newMapsOutput[i] = MapToString(gameMap, i, time, bgColor, irEsquerda);
}

void MapComponents::ClearMap(){
    for(unsigned int i = mapObjects.size()-1; i > 30 + MAP_LENGHT ;i--){
        mapObjects.erase(mapObjects.begin()+i);
    }
}

void MapComponents::XMLFooter(){
    unsigned int i = newMapsOutput.size();

    string temp = "</levels>\n";
    temp += "</levelData>\n";
    newMapsOutput[i] = temp;
}

string MapComponents::MapToString(const vector<vector<int>*> &matrix, int level, int time, int bgColor, string irEsquerda){
    string temp = "<level id='" + to_string(level) + "'>\n";
    temp += "<player startrow='10' startcol='4' facing='right'/>\n";

    temp += "<tilemap rows='" + to_string(matrix.size()) +
            "' cols='" + to_string(matrix[0]->size()) +
            "' bgcolor='" + to_string(bgColor) +
            "' time='"  + to_string(time) +
            "' goLeft='" + irEsquerda + "'>\n";
    temp += "<rows>\n";
    for(unsigned int i = 0; i < matrix.size(); i++){
        temp += "<row>";
        for(unsigned int j = 0; j < matrix[i]->size(); j++){
            temp += to_string(matrix[i]->at(j)) +( (j == matrix[i]->size()-1)?"":"," );
        }
        temp += "</row>\n";
    }
    temp += "</rows>\n";
    temp += "</tilemap>\n";

    temp += "</level>\n";
    return temp;
}

ofstream& operator<<(ofstream& out, const vector<vector<int>*> &matrix){

    //out << "<levels>" << endl;
    out << "<level id='" << MapComponents::currentLevel << "'>" << endl;
    out << "<player startrow='10' startcol='4' facing='right' />" << endl;

    out << "<tilemap rows='" << matrix.size() << "' cols='" << matrix[0]->size() << "' bgcolor='5C94FC'>"<< endl;
    out << "    <rows>";
    for(unsigned int i = 0; i < matrix.size(); i++){
        out << "        <row>";
        for(unsigned int j = 0; j < matrix[i]->size(); j++){
            out << matrix[i]->at(j) <<( (j == matrix[i]->size()-1)?"":"," );
        }
        out << "</row>";
    }
    out << endl;
    out << "    </rows>" << endl;
    out << "</tilemap>" << endl;

    out << "</level>" << endl;
    out << "</levels>" << endl;
    out << "</levelData>" << endl;

    return out;
}

void MapComponents::MapToXML(string nomeArq){
    XMLFooter();
    ofstream mapFile;
    mapFile.open(nomeArq);
    for(map<int, string>::iterator it = newMapsOutput.begin(); it != newMapsOutput.end(); it++){
        mapFile << it->second;
    }
    mapFile.close();
}

void MapComponents::RewindMap(vector<vector<int>*> &matrix){
    for(unsigned int i = 0; i < matrix.size() - 1; i++){
        for(unsigned int j = 0; j < matrix[i]->size(); j++){
            matrix[i]->at(j) = 0;
        }
    }
    for(unsigned int j = 0; j < matrix[matrix.size() - 1]->size(); j++){
            matrix[matrix.size() - 1]->at(j) = 1;
    }
    //Por causa de uma gambiarra no codigo do jogo do mario
    gameMap[MAP_HEIGHT - 2]->at(0) = 30;
    gameMap[MAP_HEIGHT - 1]->at(0) = 25;
}

void MapComponents::ReadXML(){
    //Converter para o formato do parser de xml
        ifstream enterMap;
        enterMap.open("leveldata.xml", std::ifstream::in);
        string aux, aux2;
        while(!enterMap.eof()){
            getline(enterMap, aux2);
            aux += aux2;
        }
        char *c =(char*)malloc(sizeof(char)*aux.size());
        strcpy(c, aux.c_str());
        //FIM

        doc.parse<0>(c);
        free(c);
        enterMap.close();
}

void MapComponents::XMLHeader(){
    newMapsOutput[0] = "<?xml version='1.0'?>\n";
    newMapsOutput[0] += "<levelData>\n";
    newMapsOutput[0] += "<sounds>\n";
    newMapsOutput[0] += "<sound name='music-1' res='01-main-theme-overworld.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='smallJumpSound' res='smb_jump-small.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='mariodie' res='smb_mariodie.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='goalsound' res='smb_world_clear.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='stomp' res='smb_stomp.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='coin' res='smb_coin.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='bump' res='smb_bump.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='flagpole' res='smb_flagpole.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='pause' res='smb_pause.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='warning' res='smb_warning.wav'></sound>\n";
    newMapsOutput[0] += "<sound name='gameover' res='smb_gameover.wav'></sound>\n";
    newMapsOutput[0] += "</sounds>\n";
    newMapsOutput[0] += "<tiles width='64' height='64'>\n";
    newMapsOutput[0] += "<tile id='0' background='true' />\n";
    newMapsOutput[0] += "<tile id='1' entity='rock' res='rock1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='2' entity='brick' res='brick1' frames='1' static='true'  />\n";
    newMapsOutput[0] += "<tile id='3' entity='coinbox' res='coinbox1' frames='3' static='true'   />\n";
    newMapsOutput[0] += "<tile id='4' res='hill-left1' />\n";
    newMapsOutput[0] += "<tile id='5' res='hill-mid1' />\n";
    newMapsOutput[0] += "<tile id='6' res='hill-right1' />\n";
    newMapsOutput[0] += "<tile id='7' res='hill-top1' />\n";
    newMapsOutput[0] += "<tile id='8' res='bush-left1' />\n";
    newMapsOutput[0] += "<tile id='9' res='bush-mid1' />\n";
    newMapsOutput[0] += "<tile id='10' res='bush-right1' />\n";
    newMapsOutput[0] += "<tile id='11' res='cloud-left1' />\n";
    newMapsOutput[0] += "<tile id='12' res='cloud-mid1' />\n";
    newMapsOutput[0] += "<tile id='13' res='cloud-right1' />\n";
    newMapsOutput[0] += "<tile id='14' res='cloud-bottom-left1' />\n";
    newMapsOutput[0] += "<tile id='15' res='cloud-bottom-mid1' />\n";
    newMapsOutput[0] += "<tile id='16' res='cloud-bottom-right1' />\n";
    newMapsOutput[0] += "<tile id='17' entity='pipetopleft' res='pipe-top-left1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='18' entity='pipetopright' res='pipe-top-right1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='19' entity='pipeleft' res='pipe-bottom-left1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='20' entity='piperight' res='pipe-bottom-right1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='21' entity='block' res='block1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='22' res='grass1' />\n";
    newMapsOutput[0] += "<tile id='23' entity='flagpole' res='pole1' frames='2' static='true' />\n";
    newMapsOutput[0] += "<tile id='24' entity='goal' res='block1' frames='1' static='true'  />\n";
    newMapsOutput[0] += "<tile id='25' entity='emptycoinbox' res='emptycoinbox1' frames='1' static='true'  />\n";
    newMapsOutput[0] += "<tile id='26' entity='flag' res='flag' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='27' entity='poletop' res='poletop' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='28' entity='smallcastle' res='castle1' frames='1' static='true' />\n";
    newMapsOutput[0] += "<tile id='29' entity='coin' res='coin' frames='2' />\n";
    newMapsOutput[0] += "<tile id='30' entity='coinbounce' res='coinbounce' frames='6' />\n";
    newMapsOutput[0] += "<tile id='50' entity='goomba' res='goomba1' frames='3' />\n";
    newMapsOutput[0] += "<tile id='51' entity='koopatroopa' res='koopatroopa1' frames='2'/>\n";
    newMapsOutput[0] += "</tiles>\n";
    newMapsOutput[0] += "<levels>\n";
}

void MapComponents::LoadComponents(){
    int i = 0;
    LoadMapMatrix();
    AddMapObject(new MapObject("img/block1.png", i, 0, 21)); i += GRID_W_H;
    AddMapObject(new MapObject("img/brick1.png", i, 0, 2)); i += GRID_W_H;
    AddMapObject(new MapObject("img/bush-left1.png", i, 0, 8)); i += GRID_W_H;
    AddMapObject(new MapObject("img/bush-mid1.png", i, 0, 9)); i += GRID_W_H;
    AddMapObject(new MapObject("img/bush-right1.png", i, 0, 10)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-bottom-left1.png", i, 0, 14)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-bottom-mid1.png", i, 0, 15)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-bottom-right1.png", i, 0, 16)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-left1.png", i, 0, 11)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-mid1.png", i, 0, 12)); i += GRID_W_H;
    AddMapObject(new MapObject("img/cloud-right1.png", i, 0, 13)); i += GRID_W_H;
    AddMapObject(new MapObject("img/coin.png", i, 0, 29)); i += GRID_W_H;
    AddMapObject(new MapObject("img/coinbounce.png", i, 0, 30)); i += GRID_W_H;
    AddMapObject(new MapObject("img/coinbox1.png", i, 0, 3)); i += GRID_W_H;
    AddMapObject(new MapObject("img/emptycoinbox1.png", i, 0, 25)); i += GRID_W_H;
    AddMapObject(new MapObject("img/flag.png", i, 0, 26)); i += GRID_W_H;
    AddMapObject(new MapObject("img/goomba1.png", i, 0, 50)); i += GRID_W_H;
    AddMapObject(new MapObject("img/grass1.png", i, 0, 22)); i += GRID_W_H;
    AddMapObject(new MapObject("img/hill-left1.png", i, 0, 4)); i += GRID_W_H;
    AddMapObject(new MapObject("img/hill-mid1.png", i, 0, 5)); i += GRID_W_H;
    AddMapObject(new MapObject("img/hill-right1.png", i, 0, 6)); i += GRID_W_H;
    AddMapObject(new MapObject("img/hill-top1.png", i, 0, 7)); i += GRID_W_H;
    AddMapObject(new MapObject("img/koopatroopa1.png", i, 0, 51)); i += GRID_W_H;
    AddMapObject(new MapObject("img/pipe-bottom-left1.png", i, 0, 19)); i += GRID_W_H;
    AddMapObject(new MapObject("img/pipe-bottom-right1.png", i, 0, 20)); i += GRID_W_H;
    AddMapObject(new MapObject("img/pipe-top-left1.png", i, 0, 17)); i += GRID_W_H;
    AddMapObject(new MapObject("img/pipe-top-right1.png", i, 0, 18)); i += GRID_W_H;
    AddMapObject(new MapObject("img/pole1.png", i, 0, 23)); i += GRID_W_H;
    AddMapObject(new MapObject("img/poletop.png", i, 0, 27)); i += GRID_W_H;
    AddMapObject(new MapObject("img/rock1.png", i, 0, 1)); i += GRID_W_H;
    AddMapObject(new MapObject("img/block1.png", i, 0, 24)); i += GRID_W_H;

    XMLHeader();
    //preenche previamente todo o chão
    for(int i = 0; i < MAP_LENGHT; i++){
        MapObject* tmp = new MapObject("img/rock1.png", i*GRID_W_H, (MAP_HEIGHT+2)*GRID_W_H, 1);
        tmp->SetType("copy");
        AddMapObject(tmp);
        gameMap[MAP_HEIGHT-1]->at(i) = 1;
    }
    //Por causa de uma gambiarra no codigo do jogo do mario
    gameMap[MAP_HEIGHT - 2]->at(0) = 25;
    gameMap[MAP_HEIGHT - 1]->at(0) = 30;

    gridMenu.SetGridColor(0xff, 0, 0);
    gridMenu.SetDimensions(GRID_W_H, GRID_W_H, 0, 0, WINDOW_WIDTH, GRID_W_H*3);
}
