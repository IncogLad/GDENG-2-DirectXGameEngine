#include "Renderer.h"

Renderer* Renderer::getInstance()
{
    return nullptr;
}

void Renderer::initialize()
{
    sharedInstance = new Renderer();
    

}

void Renderer::destroy()
{
}
