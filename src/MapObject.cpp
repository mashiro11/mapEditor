#include "MapObject.h"

MapObject::MapObject(string path, int x, int y, int code): sp(path), grab(false)
{
    this->path = path;
    this->x = x;
    this->y = y;
    this->code = code;

    sp.SetX(x);
    sp.SetY(y);
    type = "menu";
    status = "working";
}

MapObject::~MapObject()
{
    //dtor
}

void MapObject::Render(){
    sp.Render();
}

int MapObject::GetWidth(){
    return sp.GetWidth();
}

int MapObject::GetHeight(){
    return sp.GetHeight();
}


bool MapObject::MouseInside(){
    if( x <= InputHandler::GetMouseX() && InputHandler::GetMouseX() <= x + sp.GetWidth() &&
        y <= InputHandler::GetMouseY() && InputHandler::GetMouseY() <= y + sp.GetHeight()){
            return true;
    }
    else return false;
}

void MapObject::Update(int dt){
    if(type == "copy"){//HARDCOOOOODED
        if(InputHandler::GetKey() == SDLK_RIGHT){
            x -= dt;
            sp.SetX(sp.GetX()-dt);
        }
        if(InputHandler::GetKey() == SDLK_LEFT){
            x += dt;
            sp.SetX(sp.GetX()+dt);
        }
        if(grab){
            x = InputHandler::GetMouseX()/GetWidth() * GetWidth();
            y = InputHandler::GetMouseY()/GetHeight() * GetHeight();
            sp.SetX(x);
            sp.SetY(y);
        }
        if(status == "selected"){
            status = "moving";
        }else if(status == "placed"){
            status = "working";
        }
        if(MouseInside() && InputHandler::GetKey() == SDLK_s){
            grab = !grab;
            if(status == "working"){
                status = "selected";
            }else if(status == "moving"){
                status = "placed";
            }
        }
        if(MouseInside() && InputHandler::GetKey() == SDLK_d){
            status = "delete";
        }
    }else if(type == "menu"){
        if(MouseInside() && InputHandler::GetMouseLBState() == MOUSE_LBUTTON_PRESSED){
            MapObject* temp = new MapObject(path, InputHandler::GetMouseX(), InputHandler::GetMouseY(), code);
            temp->SetGrab(true);
            temp->SetType("copy");
            temp->SetStatus("selected");
            if(this->code != 30){//codigo da moeda pulando
                if(temp->GetWidth() > 64){
                    temp->Clip(64,64);
                }
            }else{
                if(temp->GetWidth() > 64){
                    temp->Clip(64,64, 0, 64);
                }
            }
            temp->Resize(50);
            MapComponents::AddMapObject(temp);
        }
    }
}


void MapObject::Resize(int percentx, int percenty ){
    sp.Resize(percentx, percenty);
}

void MapObject::Clip(int w, int h, int x, int y){
    sp.Clip(w, h, x, y);
}

void MapObject::SetGrab(bool grab){
    this->grab = grab;
}

void MapObject::SetType(string type){
    this->type = type;
}

void MapObject::SetStatus(string status){
    this->status = status;
}

string MapObject::GetStatus(){
    return status;
}

int MapObject::GetX(){
    return x;
}


int MapObject::GetY(){
    return y;
}

int MapObject::GetCode(){
    return code;
}
