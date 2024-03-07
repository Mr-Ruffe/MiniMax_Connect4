#include "Label.h"
#include "System.h"
#include <iostream>

Label *Label::getInstance(int x, int y, int w, int h, const std::string &txt)
{
    return new Label(x, y, w, h, txt);
}

void Label::draw() const
{
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
}

std::string Label::getText() const
{
    return text;
}

void Label::setText(std::string newText)
{
    SDL_Color color = {255, 255, 255};
    text = newText;
    SDL_DestroyTexture(texture);
    double value = std::stod(text);
    if (value > 0.99)
        color = {0, 255, 0};
    else if (value < -0.99)
        color = {255, 0, 0};

    SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(),
                                             text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
}

Label::~Label()
{
    SDL_DestroyTexture(texture);
}

Label::Label(int x, int y, int w, int h, const std::string &txt) : Component(x, y, w, h), text(txt)
{
    SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {255, 255, 255});
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
}
