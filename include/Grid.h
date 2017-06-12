#ifndef GRID_H
#define GRID_H
#include <SDL.h>
#include "Window.h"
#include "InputHandler.h"

class Grid
{
    public:
        Grid();
        Grid(int w, int h);
        virtual ~Grid();
        void Render();
        void Update();
        void SetSize(int w, int h);
        void SetGridColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);
    protected:

    private:
        bool gridShow;
        int w;
        int h;
        SDL_Color color;
};

#endif // GRID_H
