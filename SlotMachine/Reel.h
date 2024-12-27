#pragma once
#include "list"
#include "string"
#include <SFML/Graphics.hpp>


class Reel {
private:
    std::vector<std::list<sf::Sprite>> wheels;
    std::vector<sf::Texture> textures;
    std::vector<std::vector<int>> wheelIndexes;



    std::vector<sf::Texture> loadTextures(const std::vector<std::string>& fileNames);
    int iconWidth; //Ширина символа барабана
    int iconHeight; //Высота символа
    int interval = 0; //Итервал между символами
    int startPosX = 0; //Начальная х координата барабана
    int startPosY = 0; //Начальная y координата барабана
    int wheelsCount; //Колличество колёс барабана
    float textureSizeX;  //Размеры текстур
    float textureSizeY;

public:

    Reel(std::vector<std::string> fileNames,int wheelsCount);

    const std::vector<std::list<sf::Sprite>>& get();

    void spin(std::vector<float>&);

    bool correction(float time);

    void setIconWidth(int width);

    void setIconHeight(int height);

    void setIconInterval(int interval);

    void setStartPos(int x, int y);

    std::vector<std::vector<int>> getCurState();
};
