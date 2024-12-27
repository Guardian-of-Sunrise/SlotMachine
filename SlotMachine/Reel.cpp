#include "Reel.h"

    Reel::Reel(std::vector<std::string> fileNames,int wheelsCount) {

        this->wheelsCount = wheelsCount;
        textures = loadTextures(fileNames);
        textureSizeX = float(textures[0].getSize().x);
        textureSizeY = float(textures[0].getSize().y);
        int iconWidth = textureSizeX;
        int iconHeight = textureSizeY;

        wheelIndexes.resize(wheelsCount);

        // ���������� ���������
        for (int i = 0; i < wheelsCount; i++) {
            std::list<sf::Sprite> wheel;
            for (int j = 0; j < 4; ++j) {
                int rng = (rand() % textures.size());
                int distX = startPosX;
                int distY = startPosY;
                wheelIndexes[i].push_back(rng); 
                if (j > 0) {
                    distX = interval;
                }
                sf::Sprite sprite(textures[rng]);
                sprite.setPosition(float(i * iconWidth + interval),float(startPosY + (2 - j) * iconHeight)); // ������������ �������� �� ��������
                sprite.setScale(iconWidth/textureSizeX,iconHeight / textureSizeY);
                wheel.push_back(sprite);
            }
            wheels.push_back(wheel);
        }
        for (auto& i : wheelIndexes) {
            i.push_back(-1);
        }
    }
    //������� ��������, ������������ ��� ������� ����, ��� � �����
    void Reel::spin(std::vector<float>& speed) {
        //�������� ��������� �� ��������� speed ��� ������ ������
        int k = 0;
        for (auto& wheel : wheels) {//��������
            for (auto& sprite : wheel) {
                sprite.move(0, speed[k]);
            }
            //���������  �������, ����� ������ ������ ���������� �� ����� �������, � ������ ����������� ��� ���� ������ (5 �������),
            //����� � ������ �������� � ��� �������� ��� �� 4 ������� �� �������� ��� 3 ������
            if ((*wheel.begin()).getPosition().y >= 2*iconHeight && wheel.size() < 5) {
                int rng = rand() % textures.size();
                sf::Sprite sprite(textures[rng]);
                wheelIndexes[k][4] = rng;//���������� 5 ������������ ���������
                sprite.setPosition((*wheel.begin()).getPosition().x, (*(--wheel.end())).getPosition().y-iconWidth);
                sprite.setScale(iconWidth / textureSizeX, iconHeight / textureSizeY);
                wheel.push_back(sprite);
            }
            //��� ������ ������ ��������� ����������, �� ���������
            if ((*wheel.begin()).getPosition().y >= 3*iconHeight) {
                for (int t = 0; t < wheelIndexes[k].size()-1; t++) {//�������� ������ 
                    wheelIndexes[k][t] = wheelIndexes[k][t+1];
                }
                wheelIndexes[k][wheelIndexes[k].size() - 1] = -1;
                wheel.pop_front();
                (*(--wheel.end())).setPosition((*wheel.begin()).getPosition().x, (*wheel.begin()).getPosition().y - 3 * iconHeight);
            }
            k++;
        }
    }
    //������� ������������ ���������
    bool Reel::correction(float speed) {
        //������� k ��� ���������� ���������. ���� ��� �������� ���������, ������� ��������� true
        int k = 0;
        int t = 0;
        for (auto& wheel : wheels) {

            int pos = (*wheel.begin()).getPosition().y; //������� �������� ���� � ������� ����� �������


            //���� ������� �������� ���� � ������� ����� ������� ���� �������� ����� ��� ���������� ������� �� ������ ���������� �����
            if (pos <= 2 * iconHeight+ iconHeight/2 && pos != 2 * iconHeight) {
                if (pos - speed <= 2 * iconHeight) {//��������� ������������� ����� �������� ������ ��� ���������� ��������� �� ����������� ���������
                    for (auto& sprite : wheel) {
                        sprite.move(0, 2 * iconHeight - pos);
                    }
                }
                else {
                    for (auto& sprite : wheel) {
                        sprite.move(0, -1 * speed);
                    }
                }
            }
            else {
                //����� ������ ���������� ����, � ������ ������ ���������
                if (pos > 2 * iconHeight + iconHeight / 2 && pos != 3*iconHeight) {
                    if (pos + speed >= 3 * iconHeight) {//����������� ������������� ��� ��� ������� ������
                        for (auto& sprite : wheel) {
                            sprite.move(0, 3 * iconHeight - pos);
                        }
                        wheel.pop_front();
                        for (int l = 0; l < wheelIndexes[t].size() - 1;l++) {
                            wheelIndexes[t][l] = wheelIndexes[t][l+1];
                        }
                        wheelIndexes[t][wheelIndexes[t].size() - 1] = -1;
                    }
                    else {
                        for (auto& sprite : wheel) {
                            sprite.move(0, speed);
                        }
                    }
                }
                else {
                    k++;
                }
            }
            t++;
        }
        if (k == wheels.size()) {
            return true;
        }
        else {
            return false;
        }

    }

    const std::vector<std::list<sf::Sprite>>& Reel::get() {
        return wheels;
    }

    std::vector<sf::Texture> Reel::loadTextures(const std::vector<std::string>& fileNames) {
        std::vector<sf::Texture> textures;
        for (const auto& fileName : fileNames) {
            sf::Texture texture;
            if (!texture.loadFromFile(fileName)) {
                throw std::runtime_error("�� ������� ��������� " + fileName);
            }
            textures.push_back(texture);
        }
        return textures;
    }

    void Reel::setIconWidth(int width) {
        this->iconWidth = width;
        int i = 0;
        int j = 0;
        for (auto& wheel : wheels) {
            for (auto& sprite : wheel) {
                sprite.setScale(iconWidth / textureSizeX, iconHeight / textureSizeY);
                sprite.setPosition(float(i * iconWidth + interval), float(startPosY + (2 - j) * iconHeight));
                j++;
            }
            j = 0;
            i++;
        }
    }
    
    void Reel::setIconHeight(int height) {
        this->iconHeight = height;
        int i = 0;
        int j = 0;
        for (auto& wheel : wheels) {
            for (auto& sprite : wheel) {
                sprite.setScale(iconWidth / textureSizeX, iconHeight / textureSizeY);
                sprite.setPosition(float(i * iconWidth + interval), float(startPosY + (2 - j) * iconHeight));
                j++;
            }
            j = 0;
            i++;
        }
    }

    void Reel::setIconInterval(int interval) {
        this->interval = interval;
        int i = 0;
        int j = 0;
        for (auto& wheel : wheels) {
            for (auto& sprite : wheel) {
                sprite.setPosition(float(i * iconWidth + interval), float(startPosY + (2 - j) * iconHeight));
                j++;
            }
            j = 0;
            i++;
        }
    }

    std::vector<std::vector<int>> Reel::getCurState() {
        return wheelIndexes;
    }

    void Reel::setStartPos(int x, int y) {
        this->startPosX = x;
        this->startPosY = y;
        int i = 0;
        int j = 0;
        for (auto& wheel : wheels) {
            for (auto& sprite : wheel) {
                sprite.setPosition(float(i * iconWidth + interval), float(startPosY + (2 - j) * iconHeight));
                j++;
            }
            j = 0;
            i++;
        }
    }