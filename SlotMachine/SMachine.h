#pragma once
#include "State.h"
#include "Reel.h"
#include <memory>

class SMachine
{
private:
    std::unique_ptr<Reel> reel;//Барабан
    std::unique_ptr<State> currentState;//Состояние
    std::vector<float> maxSpeed{ 18.f,30.f,38.f };//Максимальная скорость развиваемая колёсами
    std::vector<float> curentSpeed;//Текущая скорость
    float accelerationTime = 5;//Время ускорения
    float spinTime = 5;//Время вращения
    float stopTime = 5;//Время остановки
    int score = 0;//Счёт
    int (*scoreCalc)(std::vector<std::vector<int>>) = nullptr;//функция подсчёта очков
    void rotate(float increment);//Ф-я вращения
    std::vector<float> stopSpeed;//Нужна для регистрации текущей скорости колёс
    
 
public:

    SMachine(std::vector<std::string> fileNames, int wheelsCount);
    void launch();

    void setIconHeight(int height);

    void setIconWidth(int width);

    void setStartPos(int x, int y);

    int calcRezult(sf::Text& scorelabel);

    void setScoreCalc(int (*scoreCalc)(std::vector<std::vector<int>>));

    ~SMachine();

};

