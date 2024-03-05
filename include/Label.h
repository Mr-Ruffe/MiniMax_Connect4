#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <iostream>
#include <string>

#include "Component.h"

/// Based on the Label class by @author jozef

/// @brief The label-object used for displaying text in the SDL-window.
class Label : public Component
{
public:
    /// @brief Acts as a constructor and restricts the user to create Label-objects in other ways.
	/// @param x The position of the object in x-direction.
	/// @param y The position of the object in y-direction.
	/// @param w The width of the object.
	/// @param h The height of the object.
    /// @param txt The initial text set for the label.
    /// @return A new Label-instance.
    static Label *getInstance(int x, int y, int w, int h, const std::string &txt)
    {
        return new Label(x, y, w, h, txt);
    }

    /// @brief Called every tick for updating the object in the renderer.
    void draw() const
    {
        const SDL_Rect &rect = getRect();
        SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
    }

    /// @brief Get:er for the text currently active for the label.
    /// @return The text in the label as a string.
    std::string getText() const
    {
        return text;
    }

    /// @brief Sets the text currently displayed in the label.
    /// @param newText The new text to be displayed in the label.
    void setText(std::string newText)
    {
        text = newText;
        SDL_DestroyTexture(texture);
        SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(),
                                                 text.c_str(), {0, 0, 0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
    
    /// @brief Destructor for the label object, destroying allocated data.
    ~Label()
    {
        SDL_DestroyTexture(texture);
    }

protected:
    /// @brief Protected constructor of the Label-object.
	/// @param x The position of the object in x-direction.
	/// @param y The position of the object in y-direction.
	/// @param w The width of the object.
	/// @param h The height of the object.
    /// @param txt The initial text set for the label.
    Label(int x, int y, int w, int h, const std::string &txt) : Component(x, y, w, h), text(txt)
    {
        SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(), text.c_str(), {0, 0, 0});
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

private:
    // The text displayed in the label.
    std::string text;

    // The texture used by the object.
    SDL_Texture *texture;
};

#endif