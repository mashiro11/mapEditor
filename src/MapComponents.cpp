#include "MapComponents.h"

vector<MapObject*> MapComponents::mapObjects;
vector<vector<int>*> MapComponents::gameMap;
Grid MapComponents::gridMenu;
Grid MapComponents::gridMap;
int MapComponents::origin = 0;

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

void MapComponents::LoadComponents(){
    int i = 0;
    LoadMapMatrix();
    AddMapObject(new MapObject("img/block1.png", i, 0, 21)); i += 32;
    AddMapObject(new MapObject("img/brick1.png", i, 0, 2)); i += 32;
    AddMapObject(new MapObject("img/bush-left1.png", i, 0, 8)); i += 32;
    AddMapObject(new MapObject("img/bush-mid1.png", i, 0, 9)); i += 32;
    AddMapObject(new MapObject("img/bush-right1.png", i, 0, 10)); i += 32;
    AddMapObject(new MapObject("img/cloud-bottom-left1.png", i, 0, 14)); i += 32;
    AddMapObject(new MapObject("img/cloud-bottom-mid1.png", i, 0, 15)); i += 32;
    AddMapObject(new MapObject("img/cloud-bottom-right1.png", i, 0, 16)); i += 32;
    AddMapObject(new MapObject("img/cloud-left1.png", i, 0, 11)); i += 32;
    AddMapObject(new MapObject("img/cloud-mid1.png", i, 0, 12)); i += 32;
    AddMapObject(new MapObject("img/cloud-right1.png", i, 0, 13)); i += 32;
    AddMapObject(new MapObject("img/coin.png", i, 0, 29)); i += 32;
    AddMapObject(new MapObject("img/coinbounce.png", i, 0, 30)); i += 32;
    AddMapObject(new MapObject("img/coinbox1.png", i, 0, 3)); i += 32;
    AddMapObject(new MapObject("img/emptycoinbox1.png", i, 0, 25)); i += 32;
    AddMapObject(new MapObject("img/flag.png", i, 0, 26)); i += 32;
    AddMapObject(new MapObject("img/goomba1.png", i, 0, 50)); i += 32;
    AddMapObject(new MapObject("img/grass1.png", i, 0, 22)); i += 32;
    AddMapObject(new MapObject("img/hill-left1.png", i, 0, 4)); i += 32;
    AddMapObject(new MapObject("img/hill-mid1.png", i, 0, 5)); i += 32;
    AddMapObject(new MapObject("img/hill-right1.png", i, 0, 6)); i += 32;
    AddMapObject(new MapObject("img/hill-top1.png", i, 0, 7)); i += 32;
    AddMapObject(new MapObject("img/koopatroopa1.png", i, 0, 51)); i += 32;
    AddMapObject(new MapObject("img/pipe-bottom-left1.png", i, 0, 19)); i += 32;
    AddMapObject(new MapObject("img/pipe-bottom-right1.png", i, 0, 20)); i += 32;
    AddMapObject(new MapObject("img/pipe-top-left1.png", i, 0, 17)); i += 32;
    AddMapObject(new MapObject("img/pipe-top-right1.png", i, 0, 18)); i += 32;
    AddMapObject(new MapObject("img/pole1.png", i, 0, 23)); i += 32;
    AddMapObject(new MapObject("img/poletop.png", i, 0, 27)); i += 32;
    AddMapObject(new MapObject("img/rock1.png", i, 0, 1)); i += 32;
    //AddMapObject(new MapObject("img/sky1.png", i, 0, 0));
    for(int i = 0; i < MAP_LENGHT; i++){
        MapObject* tmp = new MapObject("img/rock1.png", i*32, (MAP_HEIGHT+2)*32, 1);
        tmp->SetType("copy");
        AddMapObject(tmp);
        gameMap[MAP_HEIGHT-1]->at(i) = 1;
    }
    gridMenu.SetGridColor(0xff, 0, 0);
    gridMenu.SetDimensions(32, 32, 0, 0, WINDOW_WIDTH, 32*3);
}

void MapComponents::SetGridSize(int w, int h){
    //gridMap.SetDimensions(w, h);
    gridMap.SetDimensions(w, h, 0, 32*3, WINDOW_WIDTH, WINDOW_HEIGHT - 32*3);
}

void MapComponents::Show(int dt){
    if(InputHandler::GetKey() == SDLK_LEFT) origin += dt;
    if(InputHandler::GetKey() == SDLK_RIGHT) origin -= dt;

    gridMap.Update(dt);
    gridMap.Render();
    gridMenu.Update();
    gridMenu.Render();
    for(unsigned int i = 0; i < mapObjects.size(); i++){
        mapObjects[i]->Update(dt);
        mapObjects[i]->Render();
        int ypos;
        ypos = mapObjects[i]->GetY() - 32*3;
        if(mapObjects[i]->GetStatus() == "delete"){
             if(ypos > 0)gameMap[ ypos/32 ]->at( (mapObjects[i]->GetX()+origin)/32 ) = 0;
             mapObjects.erase(mapObjects.begin() + i);
        }else if(mapObjects[i]->GetStatus() == "selected"){
            if(ypos > 0)gameMap[ ypos/32 ]->at( (mapObjects[i]->GetX()+origin)/32 ) = 0;
        }else if(mapObjects[i]->GetStatus() == "placed"){
            if(ypos > 0)gameMap[ ypos/32 ]->at( (mapObjects[i]->GetX()+origin)/32 ) = mapObjects[i]->GetCode();
        }
    }
    if(InputHandler::GetKey() == SDLK_p){
        PrintMapMatrix();
    }
    if(InputHandler::GetKey() == SDLK_RETURN){
        string nomeArq;
        cout << "Nomeie a saida: ";
        cin >> nomeArq;
        MapToXML(nomeArq);
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

ofstream& operator<<(ofstream& out, const vector<vector<int>*> &matrix){
    /*
            Por enquanto, faz o xml na força bruta.
    */
    out << "<?xml version='1.0'?>" << endl;
    out << "<levelData>" << endl;
    out << "<sounds>" << endl;
    out << "<sound name='music-1' res='01-main-theme-overworld.wav'></sound>" << endl;
    out << "<sound name='smallJumpSound' res='smb_jump-small.wav'></sound>" << endl;
    out << "<sound name='mariodie' res='smb_mariodie.wav'></sound>" << endl;
    out << "<sound name='goalsound' res='smb_world_clear.wav'></sound>" << endl;
    out << "<sound name='stomp' res='smb_stomp.wav'></sound>" << endl;
    out << "<sound name='coin' res='smb_coin.wav'></sound>" << endl;
    out << "<sound name='bump' res='smb_bump.wav'></sound>" << endl;
    out << "<sound name='flagpole' res='smb_flagpole.wav'></sound>" << endl;
    out << "<sound name='pause' res='smb_pause.wav'></sound>" << endl;
    out << "<sound name='warning' res='smb_warning.wav'></sound>" << endl;
    out << "<sound name='gameover' res='smb_gameover.wav'></sound>" << endl;
    out << "</sounds>" << endl;
    out << "<tiles width='64' height='64'>" << endl;
    out << "<tile id='0' background='true' />" << endl;
    out << "<tile id='1' entity='rock' res='rock1' frames='1' static='true' />" << endl;
    out << "<tile id='2' entity='brick' res='brick1' frames='1' static='true'  />" << endl;
    out << "<tile id='3' entity='coinbox' res='coinbox1' frames='3' static='true'   />" << endl;
    out << "<tile id='4' res='hill-left1' />" << endl;
    out << "<tile id='5' res='hill-mid1' />" << endl;
    out << "<tile id='6' res='hill-right1' />" << endl;
    out << "<tile id='7' res='hill-top1' />" << endl;
    out << "<tile id='8' res='bush-left1' />" << endl;
    out << "<tile id='9' res='bush-mid1' />" << endl;
    out << "<tile id='10' res='bush-right1' />" << endl;
    out << "<tile id='11' res='cloud-left1' />" << endl;
    out << "<tile id='12' res='cloud-mid1' />" << endl;
    out << "<tile id='13' res='cloud-right1' />" << endl;
    out << "<tile id='14' res='cloud-bottom-left1' />" << endl;
    out << "<tile id='15' res='cloud-bottom-mid1' />" << endl;
    out << "<tile id='16' res='cloud-bottom-right1' />" << endl;
    out << "<tile id='17' entity='pipetopleft' res='pipe-top-left1' frames='1' static='true' />" << endl;
    out << "<tile id='18' entity='pipetopright' res='pipe-top-right1' frames='1' static='true' />" << endl;
    out << "<tile id='19' entity='pipeleft' res='pipe-bottom-left1' frames='1' static='true' />" << endl;
    out << "<tile id='20' entity='piperight' res='pipe-bottom-right1' frames='1' static='true' />" << endl;
    out << "<tile id='21' entity='block' res='block1' frames='1' static='true' />" << endl;
    out << "<tile id='22' res='grass1' />" << endl;
    out << "<tile id='23' entity='flagpole' res='pole1' frames='2' static='true' />" << endl;
    out << "<tile id='24' entity='goal' res='block1' frames='1' static='true'  />" << endl;
    out << "<tile id='25' entity='emptycoinbox' res='emptycoinbox1' frames='1' static='true'  />" << endl;
    out << "<tile id='26' entity='flag' res='flag' frames='1' static='true' />" << endl;
    out << "<tile id='27' entity='poletop' res='poletop' frames='1' static='true' />" << endl;
    out << "<tile id='28' entity='smallcastle' res='castle1' frames='1' static='true' />" << endl;
    out << "<tile id='29' entity='coin' res='coin' frames='2' />" << endl;
    out << "<tile id='30' entity='coinbounce' res='coinbounce' frames='6' />" << endl;
    out << "<tile id='50' entity='goomba' res='goomba1' frames='3' />" << endl;
    out << "<tile id='51' entity='koopatroopa' res='koopatroopa1' frames='2'/>" << endl;
    out << "</tiles>" << endl;

    out << "<levels>" << endl;
    out << "<level id='1'>" << endl;
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
    ofstream mapFile;
    mapFile.open(nomeArq);
    mapFile << gameMap;

    mapFile.close();
}

