#include "../../include/map/layer.h"


Layer::Layer() :
    objects(),
    parallax(1.0f)
{

}

Layer::Layer(float _parallax) :
    objects(),
    parallax(_parallax)
{

}

void Layer::Draw(GLint* renderUniform) const
{
    for (auto obj : objects) {
        obj->Draw(renderUniform);
    }
}

void Layer::addObject(Sprite* sprite)
{
    objects.push_back(sprite);
}

void Layer::update(float dt)
{
    
}

void Layer::setParallax(float p)
{
    parallax = p;
}

float Layer::getParallax() const
{
    return parallax;
}