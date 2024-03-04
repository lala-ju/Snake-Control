#include "CustomController.h"

DirectionType CustomController::NextDirection(const Game& game, size_t id) {
    const auto& snake = game.Snakes().at(id);
    if(game.Snakes().size() == 1){
        _dirSymbol = AngleToSymbol(snake.Direction()) ;
        if(FrontWallDistance(snake.Head(), _dirSymbol, game.FieldWidth(), game.FieldHeight())>5){
            _nextDirection == DirectionType::kForward ;
        }
        else{
            _nextDirection == DirectionType::kLeft ;
        }
    }
    else{
        _dirSymbol = AngleToSymbol(snake.Direction()) ;
        if(GetCollisionDistance(snake.Head(), _dirSymbol, game, id) > 5){
            _nextDirection == DirectionType::kForward ;
        }
        else{
            _nextDirection == DirectionType::kLeft ;
        }
    }
    return _nextDirection ;
}

CustomController::DirectionSymbol CustomController::AngleToSymbol(float angle) {
    // if angle is not a multiple of 90
    if (int(angle) % 90 != 0) {
        return DirectionSymbol::NONE;
    }
    // can be converted into 4 directions
    int dir = abs(angle / 90);
    dir %= 4;
    return static_cast<DirectionSymbol>(dir);
}

float CustomController::GetCollisionDistance(Position snakePos, DirectionSymbol dirSymbol, const Game& game, size_t id) {
    float distance = FrontWallDistance(snakePos, dirSymbol, game.FieldWidth(), game.FieldHeight());
    // check front collision distance with other snakes
    for (auto it = game.Snakes().begin(); it != game.Snakes().end(); ++it) {
        const size_t anotherID = it->first;
        const Snake& anotherSnake = it->second;
        if (anotherID == id) continue;

        float d = GetFrontCollisionDistance(snakePos, Game::kSnakeRadius, dirSymbol, anotherSnake.Head(), Game::kSnakeRadius);
        
        if (d > 0) {
            if (distance < 0)    distance = d;
            else {
                distance = std::min(distance, d);
            }
        }

        for (const Position& pos : anotherSnake.Body()) {
            float d_body = GetFrontCollisionDistance(snakePos, Game::kSnakeRadius, dirSymbol, pos, Game::kSnakeRadius);
            if (d_body > 0) {
                if (distance < 0)    distance = d_body;
                else {
                    distance = std::min(distance, d_body);
                }
            }
            
        }
        
    }
    return distance;
}


float CustomController::GetFrontCollisionDistance(Position snakePos, float snakeRadius, DirectionSymbol dirSymbol, Position target, float targetRadius) {
    float distanceX = abs(snakePos.x - target.x) - snakeRadius - targetRadius;
    float distanceY = abs(snakePos.y - target.y) - snakeRadius - targetRadius;
    
    // if direction is Left/Right
    if (dirSymbol == DirectionSymbol::LEFT || dirSymbol == DirectionSymbol::RIGHT) {
        if (distanceY > 0) { // if will not hit target y, return -1
            return -1;
        }
        return distanceX;
    }

    // if direction is Up/Down
    if (dirSymbol == DirectionSymbol::UP || dirSymbol == DirectionSymbol::DOWN) {
        if (distanceX > 0) { // if will not hit target x, return -1
            return -1;
        }
        
        return distanceY;
    }

    return -1;
}

float CustomController::FrontWallDistance(Position snakeHead, DirectionSymbol dirSymbol, float rightWall, float downWall) {
    Position frontFieldCollisionPos{ 0, 0 };
    if (dirSymbol == DirectionSymbol::LEFT) {
        frontFieldCollisionPos.x = 0;
        frontFieldCollisionPos.y = snakeHead.y;
    }
    else if (dirSymbol == DirectionSymbol::RIGHT) {
        frontFieldCollisionPos.x = rightWall;
        frontFieldCollisionPos.y = snakeHead.y;
    }
    else if (dirSymbol == DirectionSymbol::UP) {
        frontFieldCollisionPos.x = snakeHead.x;
        frontFieldCollisionPos.y = 0;
    }
    else if (dirSymbol == DirectionSymbol::DOWN) {
        frontFieldCollisionPos.x = snakeHead.x;
        frontFieldCollisionPos.y = downWall;
    }
    
    return GetFrontCollisionDistance(snakeHead, Game::kSnakeRadius, dirSymbol, frontFieldCollisionPos, 0);
}
