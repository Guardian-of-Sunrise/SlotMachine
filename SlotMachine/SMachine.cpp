#include "SMachine.h"
#include "iostream"


const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 900;


SMachine::SMachine(std::vector<std::string> fileNames,int wheelsCount)

{
    reel = std::make_unique<Reel>(fileNames, wheelsCount);
    currentState = std::make_unique<WaitingState>();
    currentState.get()->enter(reel.get());
    curentSpeed.resize(maxSpeed.size());

}



void SMachine::launch() {

    srand(static_cast<unsigned int>(time(0)));

    // ������������� ����
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Slot Machine");
    window.setFramerateLimit(60);


    /*
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("res\\Smback.png")) {
         // ������ �������� �����
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        float(window.getSize().x) / backgroundTexture.getSize().x,
        float(window.getSize().y) / backgroundTexture.getSize().y
    );
    backgroundSprite.setPosition(0, 0);
    */



    // ������
    sf::Font font;
    if (!font.loadFromFile("res\\Arial.ttf")) {
        throw std::runtime_error("�� ������� ��������� ����� arial.ttf");
    }

    sf::Text spinButton("SPIN", font, 30);
    spinButton.setPosition(920, 0);
    spinButton.setFillColor(sf::Color::White);

    sf::Text stopButton("STOP", font, 30);
    stopButton.setPosition(920, 100);
    stopButton.setFillColor(sf::Color::White);

    sf::Text score;
    score.setFont(font);
    score.setString("Score 0");
    score.setFillColor(sf::Color::Red);
    score.setPosition(920, 200);


    // ������� ����
    sf::Clock clock;
    bool ISSPINING = false;
    bool STOPPING = false;
    float positionOffset = 0.0f;




    while (window.isOpen()) {
        // ��������� �������
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            //��������� ������� ������
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // �������� ������� �� ������ "SPIN"
                if (spinButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    //��������� ������ � ��������� ��������
                    if (currentState->getId() == "WAIT") {
                        currentState->exit();
                        currentState.reset(new SpinningState());
                        currentState->enter(reel.get());
                        ISSPINING = true;
                        clock.restart();
                    }
                }

                // �������� ������� �� ������ "STOP"
                if (stopButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    //������ ������ � ��������� ��������� � ���� �� �������� ���������
                    if (currentState->getId() == "SPIN" &&!STOPPING) {
                        ISSPINING = false;
                        STOPPING = true;
                        stopSpeed = curentSpeed;
                        clock.restart();
                    }
                }
            }
        }
        //��������� �������� �� ������������ �������� � �������� � ������� (spinTime + accelerationTime) �������
        if (currentState.get()->getId() == "SPIN" && ISSPINING) {
            float time = clock.getElapsedTime().asSeconds();
            rotate(time);
            if (clock.getElapsedTime().asSeconds() > spinTime + accelerationTime) {
                ISSPINING = false;
                STOPPING = true;
                stopSpeed = curentSpeed;
                clock.restart();
            }
        }
        //��������� ��������
        if (STOPPING == true) {
            float time = clock.getElapsedTime().asSeconds();
            rotate(-1*time);
            if (clock.getElapsedTime().asSeconds() > stopTime) {
                STOPPING = false;
                currentState->exit();
                currentState.reset(new ResultState());
                currentState->enter(reel.get());
                clock.restart();
            }
        }
        //"�������" ������� ���� � ����� ����������
        if (currentState.get()->getId() == "RESULT") {
            if (dynamic_cast<ResultState*>(currentState.get())->correction(5.f)) {
                currentState->exit();
                calcRezult(score);
                currentState.reset(new WaitingState());
                currentState->enter(reel.get());
                clock.restart();
            }
        }

        // ������� ����
        window.clear(sf::Color::Black);
        /*
        window.draw(backgroundSprite);
        */

        // ��������� ���������
        for (auto wheel : (reel.get())->get()) {
            for (auto i = wheel.begin(); i != --wheel.end(); i++) {
                sf::Sprite sprite = *i;
                window.draw(sprite);
            }
        }

      
     
        window.draw(score);
        // ��������� ������
        window.draw(spinButton);
        window.draw(stopButton);

        // ����������� ����������
        window.display();
    }
}

void SMachine::rotate(float time) {
    if (time > 0) {
        int j = 0;
        //�������� ��������. ������������ �������� (maxSpeed) ����������� �� ����� ������� (accelerationTime)
        for (auto& i : curentSpeed) {
            if (time <= maxSpeed[j]) {
                i = time*maxSpeed[j]/accelerationTime;
            }
            else {
                //��� ���������� ���� �������� �������� �� ��� ���������.
                i = maxSpeed[j];
            }
            j++;
        }
    }
    //���������� ��������
    else {
        int j = 0;
        for (auto& i : curentSpeed) {
            if ( (i + time) >= 0 ) {
                i = stopSpeed[j] + time* stopSpeed[j]/stopTime;
            }
            else {
                i = 0;
            }
            j++;
        }
    }
    dynamic_cast<SpinningState*>(currentState.get())->spin(curentSpeed);   
}

SMachine::~SMachine() {


}

void SMachine::setIconHeight(int height) {
    this->reel->setIconHeight(height);
}

void SMachine::setIconWidth(int width) {
    this->reel->setIconWidth(width);
}

void SMachine::setStartPos(int x, int y) {
    this->reel->setStartPos(x, y);
}


int SMachine::calcRezult(sf::Text& scorelabel) {
    
    std::string rezult;
    auto wheelIndexes = reel->getCurState();

    if (scoreCalc) {//���������� ���������������� ���������� ��������
        score += scoreCalc(wheelIndexes);
    }
    else {//������� ����������, ��� ����� 100 ����� �� ����� ����� ���������� ��������
        int first = wheelIndexes[0][0];
        int second = wheelIndexes[0][1];
        int third = wheelIndexes[0][2];
            for (auto i = 1; i < wheelIndexes.size();i++) {
                if(wheelIndexes[i][0] != first){
                    first = -1;
                }
                if (wheelIndexes[i][1] != second) {
                    second = -1;
                }
                if (wheelIndexes[i][2] != third) {
                    third = -1;
                }
        }
            if (first != -1) {
                score += 100;
            }
            if (second != -1) {
                score += 100;
            }
            if (third != -1) {
                score += 100;
            }
    }
    scorelabel.setString("Score "+std::to_string(score));

    return 0;
};



void SMachine::setScoreCalc(int (*scoreCalc)(std::vector<std::vector<int>>)) {
    this->scoreCalc = scoreCalc;
}