#pragma once
#include "Reel.h"

class State
{
public:
    const std::string STATEID;
    virtual void enter(Reel*) = 0;      // Вход в состояние
    virtual void exit() = 0;            // Выход из состояния
    virtual std::string getId() = 0;
    virtual ~State() = default;
};

class WaitingState : public State {
    Reel* reel = nullptr;
public:
    const std::string STATEID = "WAIT";
    void enter(Reel* const) override;
    void exit() override;
    std::string getId();
};

class SpinningState :public State {
    Reel* reel = nullptr;
public:
    const std::string STATEID = "SPIN";
    void enter(Reel* const) override;
    void exit() override;
    void spin( std::vector<float>&);  //Вызов функции вращения у барабана, вектор
    std::string getId();
};

class ResultState :public State {
    Reel* reel = nullptr;
public:
    const std::string STATEID = "RESULT";
    bool correction(float corrspeed);
    void enter(Reel* const) override;
    void exit() override;
    std::string getId();
};