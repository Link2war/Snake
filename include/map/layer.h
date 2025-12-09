#pragma once

#include <BBOP/Graphics.h>


class Layer : public BbopDrawable
{
private :
    std::vector<Sprite*> objects;
    float parallax;

public :
    Layer();
    Layer(float _parallax);
    virtual ~Layer() = default;

    virtual void Draw(GLint* renderUniform) const override;

    void addObject(Sprite* sprite);

    void update(float dt);

    void setParallax(float p);
    float getParallax() const;
};