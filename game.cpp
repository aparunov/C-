#include "game.h"

Game::Game() : mWindow(sf::VideoMode(1000,1000), "Tetris")
{
    // Vaš kod dolazi ovdje (ako bude potrebe).   
}

void Game::run(){
    while(mWindow.isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch(event.type)
        {
        default:
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code==sf::Keyboard::Up){
                mUpKeyPressed = true;
            }
            if (event.key.code==sf::Keyboard::Left){
                mLeftKeyPressed = true;
            }
            if (event.key.code==sf::Keyboard::Right){
                mRightKeyPressed = true;
            }
            if (event.key.code==sf::Keyboard::Space){
                mSpaceKeyPressed = true;
            }
	    break;
        case sf::Event::KeyReleased:
            if (event.key.code==sf::Keyboard::Up){
                    mUpKeyPressed = false;
                    mRot = true;
            }
            if (event.key.code==sf::Keyboard::Left){
                    mLeftKeyPressed = false;
                    mMove = true;
            }
            if (event.key.code==sf::Keyboard::Right){
                    mRightKeyPressed = false;
                    mMove = true;
            }
            if (event.key.code==sf::Keyboard::Space){
                    mSpaceKeyPressed = false;
                    mJump = true;
            }
        break;
        case sf::Event::Resized:
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
            break;

        }
    }
}

void Game::update()
{
    // Updatiranje scene. Vaš kod dolazi ovdje
    if (!mBoard.isGameOver()){
        if (mMove and mRightKeyPressed){
            mBoard.update(1,0,0,0);
            mMove = false;
        }
        else if (mMove and mLeftKeyPressed){
            mBoard.update(0,1,0,0);
            mMove = false;
        }
        else if (mRot and mUpKeyPressed){
            mBoard.update(0,0,1,0);
            mRot = false;
        }
        else if (mJump and mSpaceKeyPressed){
            mBoard.update(0,0,0,1);
            mJump = false;
        }
        else {
            mBoard.update(0,0,0,0);
        }
        mScore.addNoLinesCompleted(mBoard.getNoLinesCompleted());
        mBoard.clearNoLinesCompleted();

    }
    else {
        mScore.setGameOver();
    }
    mScore.update();

}

void Game::render()
{
     mWindow.clear();


     mWindow.draw(mBoard);
     mWindow.draw(mScore);

     mWindow.display();
}
