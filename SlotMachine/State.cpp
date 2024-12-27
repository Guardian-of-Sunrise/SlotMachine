#include "State.h"


void WaitingState::enter(Reel* reel) {
	this->reel = reel;
}

void WaitingState::exit() {
	reel = nullptr;
}

std::string WaitingState::getId() {
	return this->STATEID;
}

void SpinningState::spin( std::vector<float>& speed) {
		reel->spin(speed);
}

void SpinningState::enter(Reel* reel) {
	this->reel = reel;
}

void SpinningState::exit() {
	reel = nullptr;
}

std::string SpinningState::getId() {
	return this->STATEID;
}


void ResultState::enter(Reel* reel) {
	this->reel = reel;
}

void ResultState::exit() {
	reel = nullptr;
}

std::string ResultState::getId() {
	return this->STATEID;
}

bool ResultState::correction(float corrspeed) {
	return reel->correction(corrspeed);
}