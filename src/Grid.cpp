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
    for(int i = 0; i < w / dw +1; i++){             //( x1 , y1 ) ( x2 , y2 )
        SDL_RenderDrawLine(Window::GetRenderer(), i*dw + x, y, i*dh + x, h + y);
    }
    for(int i = 0; i < h / dh +1; i++){          //( x1 , y1 ) ( x2 , y2 )
        SDL_RenderDrawLine(Window::GetRenderer(), x, i*dw + y, w + x, i*dh + y);
    }
}

void Grid::Update(int dt){
    if(InputHandler::GetKey() == SDLK_LEFT){
            x -= dt;
            if(x < 0) x += 32;
    }
    if(InputHandler::GetKey() == SDLK_RIGHT){
            x += dt;
            if(x > 32) x -= 32;
    }


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

void Grid::SetDimensions(int dw, int dh, int x, int y, int w, int h){
    this->dw = dw;//lateral do quadrado
    this->dh = dh;//altura do quadrado
    this->x = x;//comecando em x
    this->y = y;//comecando em y
    this->w = w;//tamanho da linha
    this->h = h;//tamanho da linha

}

void Grid::SetGridColor(int r, int g, int b, int a){
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}
