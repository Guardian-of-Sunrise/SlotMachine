#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include "SMachine.h"
#include "unordered_map"
#include <iostream>
#include <string>



int calculateScore(const std::vector<std::vector<int>> reels) {
    // Таблица выплат
    std::unordered_map<int, int> scoreTable = {
        {0, 100},// A
        {1, 80},// B
        {2, 60},// C
        {3, 40},// D
        {4, 20}// E
    };

    // Линии для проверки (3 горизонтальные и 2 диагональные)
    std::vector<std::vector<std::pair<int, int>>> lines = {
        {{0, 2}, {1, 2}, {2, 2}},//Верхняя линия
        {{0, 1}, {1, 1}, {2, 1}},//Средняя линия
        {{0, 0}, {1, 0}, {2, 0}},//Нижняя линия
        {{0, 2}, {1, 1}, {2, 0}},//Диагональ слева направо
        {{2, 2}, {1, 1}, {0, 0}} //Диагональ справа налево
    };

    int totalScore = 0;

    // Проверка каждой линии
    for (const auto& line : lines) {
        int a = reels[line[0].first][line[0].second];
        int b = reels[line[1].first][line[1].second];
        int c = reels[line[2].first][line[2].second];

        if (a == b && b == c) {//Три одинаковых символа
            totalScore += scoreTable[a];
        }
        else if (a == b || b == c || a == c) {//Два одинаковых символа
            int commonSymbol = (a == b) ? a : ((b == c) ? b : a);
            totalScore += scoreTable[commonSymbol] / 10;//10% от основного выигрыша
        }
    }
    return totalScore;
}




int main() {

    std::vector<std::string> fileNames = {"res\\seven.png","res\\watermelon.png","res\\lemon.png", "res\\cherries.png","res\\plum.png" };
    SMachine sm(fileNames,3);
    sm.setIconHeight(300);
    sm.setIconWidth(300);
    sm.setScoreCalc(calculateScore);
    sm.launch();

    return 0;
}