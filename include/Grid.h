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
        void Update(int dt = 0);
        void SetDimensions(int dw, int dh, int x = 0, int y = 0, int w = WINDOW_WIDTH, int h = WINDOW_HEIGHT);
        void SetGridColor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);
    protected:

    private:
        bool gridShow;
        int dw;
        int dh;
        int x;
        int y;
        int w;
        int h;
        SDL_Color color;
};

#endif // GRID_H
