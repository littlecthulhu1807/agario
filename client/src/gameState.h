#ifndef GAMESTATE_H
#define GAMESTATE_H


#include <cstdint>
#include <mutex>

namespace agario{

struct GameState{

float x {350.0f};
float y {250.0f};
uint32_t playerId{1};

std::mutex mtx;

};



}


#endif