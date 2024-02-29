#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <iostream>
#include <string>

#include "Component.h"

class Label : public Component
{
public:
    static Label *getInstance(int x, int y, int w, int h, const std::string &txt)
    {
        return new Label(x, y, w, h, txt);
    }
    void draw() const
    {
        const SDL_Rect &rect = getRect();
        SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
    }
    std::string getText() const
    {
        return text;
    }
    void setText(std::string newText)
    {
        text = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(),
                                                 text.c_str(), {0, 0, 0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
    ~Label()
    {
        SDL_DestroyTexture(texture);
    }
    void tick() {}

protected:
    Label(int x, int y, int w, int h, const std::string &txt) : Component(x, y, w, h), text(txt)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0, 0, 0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

private:
    std::string text;
    SDL_Texture *texture;
};

#endif