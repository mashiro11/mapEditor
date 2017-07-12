#include <iostream>
#include <vector>
#include <memory>

#include "Window.h"
#include "Grid.h"
#include "MapObject.h"
#include "Resources.h"
#include "MapComponents.h"

using std::cout;
using std::endl;
using std::vector;
using std::unique_ptr;

#define TILEDIM     64

int main(int argc, char** argv){
    /*
        Mensagens:
    */
    cout << "Para pegar um tile: clique no tile" << endl;
    cout << "Para soltar o tile: s" << endl;
    cout << "Para salvar um mapa especifico: p" << endl;
    cout << "Para terminar e exportar o mapa: enter" << endl;
    Window::Start();

    MapComponents::LoadComponents();
    MapComponents::ConfigImages(TILEDIM);
    MapComponents::SetGridSize(MapComponents::GetObject(0)->GetWidth(), MapComponents::GetObject(0)->GetHeight());
    int speed = 1;
    while(!SDL_QuitRequested() && !(InputHandler::GetKey() == SDLK_ESCAPE) ){
        Window::Clear();
        InputHandler::Update();
        if(InputHandler::GetKey() == SDLK_UP){
                speed += 1;
                if(speed > 10) speed = 10;
                cout << "movingspeed = " << speed << endl;
        }
        if(InputHandler::GetKey() == SDLK_DOWN){
                speed -= 1;
                if(speed < 1) speed = 1;
                cout << "movingspeed = " << speed << endl;
        }
        MapComponents::Show(GRID_W_H*speed);
        Window::Render();
    }
    Window::Finish();
    return 0;
}
