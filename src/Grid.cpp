#include "Grid.h"
Grid::Grid(){
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = SDL_ALPHA_OPAQUE;
}

Grid::Grid(int w, int h): gridShow(true)
{
    this->w = w;
    this->h = h;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = SDL_ALPHA_OPAQUE;
}

Grid::~Grid()
{
    //dtor
}

void Grid::Render(){
    SDL_SetRenderDrawColor(Window::GetRenderer(), color.r, color.g, color.b, color.a);
    for(int i = 0; i < WINDOW_WIDTH / w + 1; i++){
        SDL_RenderDrawLine(Window::GetRenderer(), i*w, 0, i*h, WINDOW_HEIGHT);
        SDL_RenderDrawLine(Window::GetRenderer(), 0, i*w, WINDOW_WIDTH, i*h);
    }
}

void Grid::Update(){
    if(InputHandler::GetKey() == SDLK_1){
        if(gridShow){
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.a = SDL_ALPHA_OPAQUE;
        }else{
            color.r = 255;
            color.g = 255;
            color.b = 255;
            color.a = SDL_ALPHA_OPAQUE;
        }
        gridShow = !gridShow;
    }
}

void Grid::SetSize(int w, int h){
    this->w = w;
    this->h = h;
}

void Grid::SetGridColor(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}
