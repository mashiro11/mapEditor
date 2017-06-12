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
    Window::Start();

    MapComponents::LoadComponents();
    MapComponents::ConfigImages(TILEDIM);
    MapComponents::SetGridSize(MapComponents::GetObject(0)->GetWidth(), MapComponents::GetObject(0)->GetHeight());
    while(!SDL_QuitRequested()){
        Window::Clear();
        InputHandler::Update();
        MapComponents::Show();
        Window::Render();
    }
    Window::Finish();
    return 0;
}
