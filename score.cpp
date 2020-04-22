#include "score.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
    mScoreText.setFont(mFont);
    mScoreText.setString(std::to_string(0));
    mScoreText.setColor(sf::Color::Yellow);
    mScoreText.move(650,50);
    mScoreText.setCharacterSize(48);
    mGameOverText.setFont(mFont);
    mGameOverText.setColor(sf::Color::Red);
    mGameOverText.move(650,100);
    mGameOverText.setCharacterSize(48);
   // Vaš kod dolazi ovdje
}

void Score::addNoLinesCompleted(int n)
{
    mScore += n*mScorePerLine;
}

void Score::setGameOver()
{
    mGameOverText.setString("Game Over");
    mScoreText.setColor(sf::Color::Red);
}

void Score::update()
{
    mScoreText.setString(std::to_string(mScore));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mScoreText,states);
    target.draw(mGameOverText);
}
