#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include "score.h"

class Game{
	public:
            Game();
	    void run();
	private:
            sf::RenderWindow mWindow;
            Board mBoard;
            Score mScore;
            bool  mMove = true;
            bool  mRot = true;
            bool mJump = true;
            bool  mUpKeyPressed = false;
            bool  mLeftKeyPressed = false;
            bool  mRightKeyPressed = false;
            bool  mSpaceKeyPressed = false;

	    void processEvents();
            void update();
            void render();
};




