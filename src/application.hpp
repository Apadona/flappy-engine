#pragma once

#include <string>

class Application
{
    public:        
        virtual bool Init() = 0;

        virtual void OnCreate() = 0;
        virtual bool OnUpdate( float dt ) = 0;
        virtual void OnClose() = 0;

        virtual void UpdateScreen() const = 0;// HACK. will change later.
};
