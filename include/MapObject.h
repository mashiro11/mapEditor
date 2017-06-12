#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <iostream>

#include <string>
#include <iostream>

#include "Sprite.h"
#include "InputHandler.h"
#include "MapComponents.h"

using std::string;

class MapObject
{
    public:
        MapObject(string path, int x = 0, int y = 0, int code = 0);
        virtual ~MapObject();
        void Render();
        void Update();
        int GetWidth();
        int GetHeight();
        int GetX();
        int GetY();
        bool MouseInside();
        void Resize(int percentx = 100, int percenty = 100);
        void Clip(int w, int h);
        void SetGrab(bool grab);
        void SetType(string type);
        void SetStatus(string status);
        string GetStatus();

        int GetCode();


    protected:

    private:
        Sprite sp;
        bool grab;
        int x;
        int y;
        string path;
        string type;
        string status;
        int code;
};

#endif // MAPOBJECT_H
