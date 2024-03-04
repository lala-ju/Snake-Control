#ifndef DSAP_CUSTOM_CONTROLLER_H
#define DSAP_CUSTOM_CONTROLLER_H

#include "ISnakeController.h"
#include "DirectionType.h"
long long countforturnA = 0;
long long cntB = 0;
long long countforturnC = 0;
long long countforelse = 0;
long long countforB = 0;
bool testone = false;
bool testB = false ;
bool testC = false ;
bool Bcase = false;
bool testelse = false;
bool firstin = true;
bool deadcorner2 = false;
bool deadcorner3 = false;
bool deadcorner4 = false;
bool deadcorner5 = false;

class CustomController : public ISnakeController {
public:
    DirectionType NextDirection(const Game&, size_t) override;
private:
    enum class DirectionSymbol {
        RIGHT, DOWN, LEFT, UP, NONE
    };
    DirectionType _nextDirection;
    DirectionType _currentDirection;
    float _final_angle;
    DirectionSymbol _dirSymbol;
    DirectionSymbol AngleToSymbol(float, long long);
 
    float turn_radius =  3 * 180 / 3.1415926 + 30;
    float GetCollisionDistance(Position, DirectionSymbol, const Game&, size_t);
    float GetFrontCollisionDistance(Position, float, DirectionSymbol, Position, float);
    float FrontWallDistance(Position, DirectionSymbol, float, float);
};

DirectionType CustomController::NextDirection(const Game& game, size_t id) {
	//std::cout << rand() << " ";
	if(testone == false && testB == false && testC == false &&  testelse == false && Bcase == false)
	{
		if(game.Center().x == 270 && game.Center().y == 1702 && testB == false && testC == false && testelse == false)
		{
			if(game.Snakes().size() == 6)
				testB = true;
			else if (game.Snakes().size() == 5)
				testC = true;
		}
		else if(game.Snakes().size() == 1 && testone == false && testB == false && testC == false && testelse == false) 
		{
			testone = true;
		}
		else if(game.Snakes().size() == 6)
		{
			Bcase = true;
		}
		else
		{
			testelse = true;
		}
	}
	
    const auto& snake = game.Snakes().at(id);
    if(testone == true){
        if (_currentDirection != DirectionType::kForward) {
            float remaining_angle = abs(_final_angle - snake.Direction());
            if (remaining_angle > 0) { //still turning
                return _currentDirection;
            }
            // finished turning
            _dirSymbol = AngleToSymbol(snake.Direction(), countforturnA);
        }
        float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
        // if 0 < distance < min_distance
        if(distance > 0 && distance < turn_radius + 120*(countforturnA/4)+75){
        	if(firstin)
	        	firstin = false;
	       	else
	           	countforturnA += 1;
            
            _currentDirection = DirectionType::kRight;
            if (_currentDirection == DirectionType::kRight) {
                _final_angle = snake.Direction()+ 90;
            }
        }
        else {
            _currentDirection = DirectionType::kForward;
        }
    }
    else if(testB == true){
        if (_currentDirection != DirectionType::kForward) {
            float remaining_angle = abs(_final_angle - snake.Direction());
                if (remaining_angle > 0) { //still turning
                    return _currentDirection;
                }
                // finished turning
            _dirSymbol = AngleToSymbol(snake.Direction(), cntB);
        }
        float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
        if(distance > 0 && distance < turn_radius + 120*((cntB%10)/4)+30){
            cntB += 1;
            if(cntB <=20){
                if(cntB == 1 || cntB == 7 || cntB == 8 || cntB == 16)
                    _currentDirection = DirectionType::kLeft;
                else
                    _currentDirection = DirectionType::kRight ;
            }
            else if(cntB > 20 && cntB <27){
                if(cntB %2 == 1)
                    _currentDirection = DirectionType::kLeft;
                else
                    _currentDirection = DirectionType::kRight ;
            }
            else if(cntB == 27){
                _currentDirection = DirectionType::kRight ;
                _final_angle = snake.Direction()+ 90;
            }
            else if(cntB >27){
                if(cntB %2 == 1)
                    _currentDirection = DirectionType::kLeft;
                else
                    _currentDirection = DirectionType::kRight ;
            }
            if (_currentDirection == DirectionType::kLeft && cntB <=  20)
                _final_angle = snake.Direction()- 90;
            else if(_currentDirection == DirectionType::kRight && cntB <=  20)
                _final_angle = snake.Direction()+ 90;
            else if(_currentDirection == DirectionType::kLeft && cntB >  20 && cntB != 27)
                _final_angle = snake.Direction()- 180;
            else if(_currentDirection == DirectionType::kRight && cntB > 20 && cntB != 27)
                _final_angle = snake.Direction()+ 180;
        }
            else {
                _currentDirection = DirectionType::kForward;
            }
    }
    else if(testC == true){//C
    	if(game.Snakes().size() > 1)
    	{
    		if (_currentDirection != DirectionType::kForward) {
                float remaining_angle = abs(_final_angle - snake.Direction());
                if (remaining_angle > 0) { //still turning
                    return _currentDirection;
                }
                // finished turning
                _dirSymbol = AngleToSymbol(snake.Direction(), countforturnC);
            }
            
            float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
            // if 0 < distance < min_distance
            if (distance > 0 && distance < turn_radius + 15*(countforturnC/4)) {
                // start turning around
                countforturnC += 1;
                if(countforturnC == 3)
                	_nextDirection = DirectionType::kLeft;
                else
                	_nextDirection = DirectionType::kRight;
                _currentDirection = _nextDirection;
                if (_currentDirection == DirectionType::kRight) {
                    _final_angle = snake.Direction() + 90;
                }
                else {
                    _final_angle = snake.Direction()-90;
                }
            }
            else {
                // no collision problem, just go straight forward
                _currentDirection = DirectionType::kForward;
            }
		}
		else 
		{
			if (_currentDirection != DirectionType::kForward) {
	            float remaining_angle = abs(_final_angle - snake.Direction());
	            if (remaining_angle > 0) { //still turning
	                return _currentDirection;
	            }
	            // finished turning
	            _dirSymbol = AngleToSymbol(snake.Direction(), countforturnA);
	        }
	        float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
	        // if 0 < distance < min_distance
	        if(distance > 0 && distance < turn_radius + 120*(countforturnA/4)){
	        	if(firstin)
	        		firstin = false;
	        	else
	            	countforturnA += 1;
	            _currentDirection = DirectionType::kLeft;
	            if (_currentDirection == DirectionType::kLeft) {
	                _final_angle = snake.Direction()- 90;
	            }
	        }
	        else {
	            _currentDirection = DirectionType::kForward;
	        }
		}
    }
    else if(testelse == true){//other
    	if(game.Snakes().size() > 1)
    	{
	        if (_currentDirection != DirectionType::kForward) {
		        float remaining_angle = abs(_final_angle - snake.Direction());
		        if (remaining_angle > 0) { //still turning
		            return _currentDirection;
		        }
		        // finished turning
		        _dirSymbol = AngleToSymbol(snake.Direction(), countforelse);
		    }
		    
		    float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
		    
		    // if 0 < distance < min_distance
		    if (distance > 0 && distance < turn_radius + 50) 
			{
		        // start turning around
		        countforelse += 1;
		        Position nearest{game.FieldWidth(), game.FieldHeight()};
		        DirectionType bumpcheck = DirectionType::kForward;

		        for (auto it2 = game.Snakes().begin(); it2 != game.Snakes().end(); ++it2) 
				{
		            const size_t id2 = it2->first;
		            const auto& snake2 = it2->second;
		
		            if (id == id2) continue;
		            // Snake bump to Snake check
		            if (game.IsCollidedWithCircle(snake.Head(), Game::kSnakeRadius+turn_radius+50 ,snake2.Head(), Game::kSnakeRadius)) 
					{
						//std::cout << "Bumping snake head if turn!";
		                if(_dirSymbol == DirectionSymbol::RIGHT)
		                {
		                	if(snake2.Head().x - snake.Head().x >= 0 && snake2.Head().y - snake.Head().y <= 0)//rightup
		                	{
		                		//std::cout << "inrightup\n";
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kRight;
								}
							}
							else if(snake2.Head().x - snake.Head().x >= 0 && snake2.Head().y - snake.Head().y > 0)//rightdown
		                	{
		                		//std::cout << "inrightdown\n";
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kLeft;
								}
							}
						}
						else if(_dirSymbol == DirectionSymbol::UP)
		                {
		                	if(snake2.Head().x - snake.Head().x >= 0 && snake2.Head().y - snake.Head().y <= 0)//rightup
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kLeft;
								}
							}
							else if(snake2.Head().x - snake.Head().x < 0 && snake2.Head().y - snake.Head().y <= 0)//leftup
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kRight;
								}
							}
		    
						}
						else if(_dirSymbol == DirectionSymbol::LEFT)
		                {
		                	if(snake2.Head().x - snake.Head().x <= 0 && snake2.Head().y - snake.Head().y <= 0)//leftup
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kLeft;
								}
							}
							else if(snake2.Head().x - snake.Head().x <= 0 && snake2.Head().y - snake.Head().y > 0)//leftdown
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kRight;
								}
							}
						}
						else if(_dirSymbol == DirectionSymbol::DOWN)
		                {
		                	if(snake2.Head().x - snake.Head().x >= 0 && snake2.Head().y - snake.Head().y >= 0)//rightdown
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kRight;
								}
							}
							else if(snake2.Head().x - snake.Head().x < 0 && snake2.Head().y - snake.Head().y >= 0)//leftdown
		                	{
		                		if((snake2.Head()-snake.Head()).Length() < (nearest - snake.Head()).Length())
		                		{
		                			nearest.x = snake2.Head().x;
		                			nearest.y = snake2.Head().y;
		                			bumpcheck = DirectionType::kLeft;
								}
							}
						}
		            }
		            for (const Position& pos : snake2.Body()) 
					{
						
		                if (game.IsCollidedWithCircle(snake.Head(), Game::kSnakeRadius+turn_radius+50, pos, Game::kSnakeRadius)) 
						{
							//std::cout << "Bumping snake body if turn!";
		                    if(_dirSymbol == DirectionSymbol::RIGHT)
			                {
			                	if(pos.x - snake.Head().x >= 0 && pos.y - snake.Head().y <= 0)//rightup
			                	{
			                		//std::cout << "inrightup\n";
			                		if((pos -snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kRight;
									}
								}
								else if(pos.x - snake.Head().x >= 0 && pos.y - snake.Head().y > 0)//rightdown
			                	{
			                		//std::cout << "inrightdown\n";
			                		if((pos - snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kLeft;
									}
								}
							}
							else if(_dirSymbol == DirectionSymbol::UP)
			                {
			                	if(pos.x - snake.Head().x >= 0 && pos.y - snake.Head().y <= 0)//rightup
			                	{
			                		if((pos -snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kLeft;
									}
								}
								else if(pos.x - snake.Head().x < 0 && pos.y - snake.Head().y <= 0)//leftup
			                	{
			                		if((pos - snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kRight;
									}
								}
							}
							else if(_dirSymbol == DirectionSymbol::LEFT)
			                {
			                	if(pos.x - snake.Head().x <= 0 && pos.y - snake.Head().y <= 0)//leftup
			                	{
			                		if((pos -snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kLeft;
									}
								}
								else if(pos.x - snake.Head().x <= 0 && pos.y - snake.Head().y > 0)//leftdown
			                	{
			                		if((pos - snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kRight;
									}
								}
							}
							else if(_dirSymbol == DirectionSymbol::DOWN)
			                {
			                	if(pos.x - snake.Head().x >= 0 && pos.y - snake.Head().y >= 0)//rightdown
			                	{
			                		if((pos -snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kRight;
									}
								}
								else if(pos.x - snake.Head().x < 0 && pos.y - snake.Head().y >= 0)//leftdown
			                	{
			                		if((pos - snake.Head()).Length() < (nearest - snake.Head()).Length())
			                		{
			                			nearest.x = pos.x;
			                			nearest.y = pos.y;
			                			bumpcheck = DirectionType::kLeft;
									}
								}
							}
		                }
		            }
		        }
				
				if(bumpcheck != DirectionType::kForward)
				{
					if(bumpcheck == DirectionType::kRight)
					{
						DirectionSymbol temp =  AngleToSymbol(snake.Direction()+90, countforelse);
						float d = FrontWallDistance(snake.Head(), temp, game.FieldWidth(), game.FieldHeight());
						if(d < (nearest-snake.Head()).Length())
							_nextDirection = DirectionType::kLeft;
						else
							_nextDirection = bumpcheck;
					}
					else if(bumpcheck == DirectionType::kLeft)
					{
						DirectionSymbol temp =  AngleToSymbol(snake.Direction()+270, countforelse);
						float d = FrontWallDistance(snake.Head(), temp, game.FieldWidth(), game.FieldHeight());
						if(d < (nearest-snake.Head()).Length())
							_nextDirection = DirectionType::kRight;
						else
							_nextDirection = bumpcheck;
					}
				}
		        else
		        	_nextDirection = DirectionType::kRight;
		        _currentDirection = _nextDirection;
		        if (_currentDirection == DirectionType::kRight) {
		            _final_angle = snake.Direction() + 90;
		        }
		        else {
		            _final_angle = snake.Direction()-90;
		        }
		    }
		    else {
		        // no collision problem, just go straight forward
		        _currentDirection = DirectionType::kForward;
		    }
		}
	    else 
		{
			if (_currentDirection != DirectionType::kForward) {
	            float remaining_angle = abs(_final_angle - snake.Direction());
	            if (remaining_angle > 0) { //still turning
	                return _currentDirection;
	            }
	            // finished turning
	            _dirSymbol = AngleToSymbol(snake.Direction(), countforturnA);
	        }
	        float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
	        // if 0 < distance < min_distance
	        if(distance > 0 && distance < turn_radius + 120*(countforturnA/4)){
	        	if(firstin)
	        		firstin = false;
	        	else
	            	countforturnA += 1;
	            _currentDirection = DirectionType::kLeft;
	            if (_currentDirection == DirectionType::kLeft) {
	                _final_angle = snake.Direction()- 90;
	            }
	        }
	        else {
	            _currentDirection = DirectionType::kForward;
	        }
		}
    }
    else if(Bcase == true){
    	if (_currentDirection != DirectionType::kForward) {
    		//std::cout << snake.Direction() << " ";
    		//std::cout << _final_angle << "\n";
            float remaining_angle = abs(_final_angle - snake.Direction());
            if (remaining_angle > 0) { //still turning
                return _currentDirection;
            }
            // finished turning
            _dirSymbol = AngleToSymbol(snake.Direction(), countforB);
        }
        
        float distance = GetCollisionDistance(snake.Head(), _dirSymbol, game, id);
        
        if(distance > 0 && distance < turn_radius +30)
		{
			countforB += 1;
			if(!firstin && _dirSymbol == DirectionSymbol::DOWN)
			{
				DirectionSymbol temp =  AngleToSymbol(snake.Direction()+90, countforelse);
				float d = FrontWallDistance(snake.Head(), temp, game.FieldWidth(), game.FieldHeight());
				if(d < turn_radius +50)
				{
					countforB += 1;
					firstin = true;
				}
				
			}
			else if(!firstin && _dirSymbol == DirectionSymbol::UP)
			{
				DirectionSymbol temp =  AngleToSymbol(snake.Direction()+270, countforelse);
				float d = FrontWallDistance(snake.Head(), temp, game.FieldWidth(), game.FieldHeight());
				if(d < turn_radius +50)
				{
					countforB += 1;
					firstin = true;
				}
					
			}
			
			if(snake.Head().x - game.Snakes().at(2).Head().x < 0 && snake.Head().y - game.Snakes().at(2).Head().y < 0)
			{
				deadcorner2 = true;
				countforB += 1;
			}
			if(snake.Head().x - game.Snakes().at(3).Head().x < 0 && snake.Head().y - game.Snakes().at(3).Head().y > 0)
			{
				deadcorner3 = true;
				countforB += 1;
			}
			if(snake.Head().x - game.Snakes().at(4).Head().x > 0 && snake.Head().y - game.Snakes().at(4).Head().y < 0)
			{
				deadcorner4 = true;
				countforB += 1;
			}
			if(snake.Head().x - game.Snakes().at(5).Head().x > 0 && snake.Head().y - game.Snakes().at(5).Head().y > 0)
			{
				deadcorner5 = true;
				countforB += 1;
			}
			
        	if(firstin)
        	{
        		if(_dirSymbol == DirectionSymbol::UP)
        			_currentDirection = DirectionType::kRight;
        		else if(_dirSymbol == DirectionSymbol::DOWN)
        			_currentDirection = DirectionType::kLeft;
        		else if(_dirSymbol == DirectionSymbol::RIGHT)
        		{
        			DirectionSymbol temp =  AngleToSymbol(snake.Direction()+90, countforelse);
					float d = GetCollisionDistance(snake.Head(), temp, game, id);
					if(d < turn_radius +50)
					{
						_currentDirection = DirectionType::kLeft;
					}
					else
					{
						_currentDirection = DirectionType::kRight;
					}
				}
				else
        			_currentDirection = DirectionType::kRight;
			}
			else if(deadcorner2)
			{
				if(_dirSymbol == DirectionSymbol::UP)
					_currentDirection = DirectionType::kRight;
				else if(_dirSymbol == DirectionSymbol::LEFT)
					_currentDirection = DirectionType::kRight;
			}
			else if(deadcorner3)
			{
				if(_dirSymbol == DirectionSymbol::DOWN)
					_currentDirection = DirectionType::kLeft;
				else if(_dirSymbol == DirectionSymbol::LEFT)
					_currentDirection = DirectionType::kRight;
			}
			else if(deadcorner4)
			{
				if(_dirSymbol == DirectionSymbol::UP)
					_currentDirection = DirectionType::kLeft;
				else if(_dirSymbol == DirectionSymbol::RIGHT)
					_currentDirection = DirectionType::kRight;
			}	
			else if(deadcorner5)
			{
				if(_dirSymbol == DirectionSymbol::DOWN)
					_currentDirection = DirectionType::kRight;
				else if(_dirSymbol == DirectionSymbol::RIGHT)
					_currentDirection = DirectionType::kLeft;
			}
            else if(_dirSymbol == DirectionSymbol::DOWN)
            	_currentDirection = DirectionType::kRight;
            else
            	_currentDirection = DirectionType::kLeft;
            
            if (_currentDirection == DirectionType::kRight) {
            	if(firstin || deadcorner2  || deadcorner3  || deadcorner4  || deadcorner5 )
            	{
            		_final_angle = snake.Direction()+ 90;
            		firstin = false;
            		deadcorner2 = false;
            		deadcorner3 = false;
            		deadcorner4 = false;
            		deadcorner5 = false;
				}
				else
                	_final_angle = snake.Direction()+ 180;
            }
            else if(_currentDirection == DirectionType::kLeft){
            	if(firstin || deadcorner2  || deadcorner3  || deadcorner4  || deadcorner5)
            	{
            		_final_angle = snake.Direction()- 90;
            		firstin = false;
            		deadcorner2 = false;
            		deadcorner3 = false;
            		deadcorner4 = false;
            		deadcorner5 = false;
				}
				else
            		_final_angle = snake.Direction()- 180;
			}
            	
        }
        else {
            _currentDirection = DirectionType::kForward;
        }
	}
	return _currentDirection;
}

CustomController::DirectionSymbol CustomController::AngleToSymbol(float angle, long long cnt) {
    // if angle is not a multiple of 90
    if(angle < 0)
        angle += 360*(cnt/4+1);
        
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
#endif // DSAP_CUSTOM_CONTROLLER_H


