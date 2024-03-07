#include <iostream>
#include <sstream>
#include <iomanip>

#include "Players.h"
#include "MiniMax.h"
#include "Common.h"
#include "Constants.h"

Players *Players::getInstance(Session &ses)
{
    return new Players(constants::playerParamater, ses);
}

Players::~Players()
{
    destroyTexture();
}

void Players::tick()
{
    int outputX, outputY;
    SDL_GetMouseState(&outputX, &outputY);

    if (gameBoard.isPlayer())
    {
        if (updatingLabels && lastTile->inPlace() && constants::visualizeMinimax && !gameBoard.isGameOver())
        {
            miniMax(); // Update minimax for player
            updatingLabels = false;
        }
        if (outputX)
            mouseX = outputX;
        setX(mouseX - 50);
    }
    else if ((boardEmpty || lastTile->inPlace()) && !gameBoard.isGameOver())
    {
        placeMarker();
        updatingLabels = true;
    }
}

void Players::draw() const
{
    // Handle the address to temporary object
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
}

void Players::mouseDown(const SDL_Event &)
{
    if (!gameBoard.isPlayer() || (!boardEmpty && !lastTile->inPlace()) || gameBoard.isGameOver())
        return;
    placeMarker();
    updatingLabels = true;
}

void Players::destroyTexture()
{
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
}

SDL_Texture *Players::getTexture() const
{
    if (gameBoard.getTurn() == common::Turn::firstPlayer)
        return texture1;
    else
        return texture2;
}

Players::Players(common::SetupParameter parameter, Session &ses) : Component(0, -50, 100, 100), ses(ses), gameBoard(parameter)
{
    texture1 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/green_tile.png").c_str());
    texture2 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/red_tile.png").c_str());
    if (constants::visualizeMinimax)
    {
        miniMax();
        for (int i = 0; i < constants::sizeX; i++)
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << minimaxVector[i];
            Label *currentLabel = Label::getInstance(125 + i * 100, 700, 50, 50, ss.str());
            ses.add(currentLabel);
            labelVector.push_back(currentLabel);
        }
    }
}

bool Players::placeMarker()
{
    int col;
    common::Turn turn = gameBoard.getTurn();
    if (gameBoard.isPlayer())
        col = getClosestCol();
    else
        col = miniMax();
    if (col >= 0 && col < constants::sizeX)
    {
        int row = gameBoard.placeMarker(col);
        if (row != -1)
        {
            lastTile = Tile::getInstance(col, row, mouseX - 50, turn);
            ses.add(lastTile);
            boardEmpty = false;

            return true;
        }
    }
    return false;
}

int Players::miniMax()
{
    common::Turn turn = gameBoard.getTurn();
    std::vector<std::vector<int>> matrix = gameBoard.getMatrixCopy();
    MoveScore minimax = MiniMax::minimaxAll(matrix, constants::searchDepth, (turn == common::Turn::firstPlayer));
    minimaxVector = minimax.evaluationVector;
    if (constants::visualizeMinimax)
    {
        if (constants::outputStdOut)
        {
            for (double d : minimaxVector)
                std::cout << d << ", ";
            std::cout << std::endl;
        }
        updateLabels();
    }
    return minimax.move;
}

int Players::getClosestCol() const
{
    return (mouseX - 100) / 100;
}

void Players::updateLabels()
{
    if (labelVector.empty())
    {
        return;
    }
    for (int i = 0; i < constants::sizeX; i++)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << minimaxVector[i];
        labelVector[i]->setText(ss.str());
    }
}