#pragma once
#include "State.h"
#include "Reel.h"
#include <memory>

class SMachine
{
private:
    std::unique_ptr<Reel> reel;//�������
    std::unique_ptr<State> currentState;//���������
    std::vector<float> maxSpeed{ 18.f,30.f,38.f };//������������ �������� ����������� �������
    std::vector<float> curentSpeed;//������� ��������
    float accelerationTime = 5;//����� ���������
    float spinTime = 5;//����� ��������
    float stopTime = 5;//����� ���������
    int score = 0;//����
    int (*scoreCalc)(std::vector<std::vector<int>>) = nullptr;//������� �������� �����
    void rotate(float increment);//�-� ��������
    std::vector<float> stopSpeed;//����� ��� ����������� ������� �������� ����
    
 
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

