#include "board.h"
#include <iostream>

// Vaš kod dolazi ovdje

Board::Board()
{
    float length = mWidth/mCols;
    for (int i = 0; i < mRows; ++i){
        for (int j = 0; j < mCols; j++){
            mGridContent[i][j]=-1;
            mGrid.push_back(sf::RectangleShape(sf::Vector2f(length,length)) );
            mGrid.back().move(mLeftMargin + length * j,mTopMargin + length * i);
            mGrid.back().setOutlineThickness(2.f);
            mGrid.back().setOutlineColor(sf::Color::White);
            mGrid.back().setFillColor(sf::Color::Black);
        }
    }
    spawnPiece();
    mPiece.mClock.restart();
    //update(0,0,0);

}

void Board::update(bool mR, bool mL, bool mRot, bool mJump)
{

    if (mJump){
        while (movePiece(mPiece.mXposition,mPiece.mYposition+1)){

        }
    }
    if (mL){
        bool t = movePiece(mPiece.mXposition-1,mPiece.mYposition);
        (void) t;
    }
    if (mR){
        bool t = movePiece(mPiece.mXposition+1,mPiece.mYposition);
        (void) t;
    }
    if (mRot){
        bool t = rotatePiece();
        (void) t;
    }


    mNoLinesCompleted += clearLines();
    for (unsigned int i = 0; i < mRows; ++i){
        for (unsigned int j = 0; j < mCols; j++){
            if (mGridContent[i][j]==-1){
                mGrid[i*mCols + j].setFillColor(sf::Color::Black);
            }
            else {
                mGrid[i*mCols + j].setFillColor(mPiece.mColors[mGridContent[i][j]]);
            }
        }
    }
    if (mPiece.mClock.getElapsedTime().asSeconds()>mDt){
        bool t = movePiece(mPiece.mXposition,mPiece.mYposition+1);
        if (t) {
            mPiece.mClock.restart();
        }
        else {
            //removePiece();
            spawnPiece();
            mPiece.mClock.restart();
        }
    }
}

void Board::spawnPiece()
{
    int rnd = abs(mUniformDist(e)%mPiece.SIZE);
    //removePiece();
    mPiece.mType=Tetrimino::Types(rnd);
    if (checkSpace(3,0,0)){
        mPiece.mXposition = 3;
        mPiece.mYposition = 0;
        placePiece();
    }
    else {
        mGameOver = true;
    }
}

bool Board::isGameOver() const
{
    return mGameOver;
}

int Board::getNoLinesCompleted() const
{
    return mNoLinesCompleted;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mCols*mRows; ++i) {
        target.draw(mGrid[i], states);
    }
}

bool Board::checkSpace(int x, int y, bool rot)
{
    //std::cout << x <<  " " << y << std::endl;
    for (int i = 0;i < 4;++i) {
        for (int j = 0;j < 4;++j) {
            if ((mPiece.mDijelovi[mPiece.mType][
                    (mPiece.mRotacija + rot)%mPiece.N_ROTACIJA][i][j] != 0 and
                    ((y + i) >= mRows or
                     (x + j)>= mCols or
                    (x+j)<0))){
                return false;

            }
            if (((y + i) < mRows or (x + j) < mCols or (x+j) >=0)){
                if (mGridContent[y+i][x+j] != -1 and
                        mPiece.mDijelovi[mPiece.mType][
                                            (mPiece.mRotacija + rot)%mPiece.N_ROTACIJA][i][j] != 0)
                    return false;

            }
        }
    }
    return true;
}

void Board::placePiece()
{
    for (int i = 0;i < 4;++i) {
        if (i + mPiece.mYposition >= mRows)
            break;
        for (int j = 0;j < 4;++j) {
            if (j + mPiece.mXposition >= mCols)
                break;
            if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]){
                mGridContent[mPiece.mYposition + i][mPiece.mXposition + j] = mPiece.mType;
            }
        }
    }
}

void Board::removePiece()
{
    for (int i = 0;i < 4;++i) {
        if (i + mPiece.mYposition >= mRows)
            break;
        for (int j = 0;j < 4;++j) {
            if (j + mPiece.mXposition >= mCols)
                break;
            if (mPiece.mDijelovi[mPiece.mType][mPiece.mRotacija][i][j]){
                mGridContent[mPiece.mYposition + i][mPiece.mXposition + j] = -1;
            }
        }
    }
}

bool Board::movePiece(int x, int y)
{
    removePiece();
    if (checkSpace(x,y,0)){
        mPiece.mXposition = x;
        mPiece.mYposition = y;
        placePiece();
        return true;
    }
    placePiece();
    return false;
}

bool Board::rotatePiece()
{
    removePiece();
    if (checkSpace(mPiece.mXposition,mPiece.mYposition,1)){
        mPiece.mRotacija += 1;
        mPiece.mRotacija %= mPiece.N_ROTACIJA;
        placePiece();
        return true;
    }
    placePiece();
    return false;
}

bool Board::isLineFull(int y) const
{
    for (int i = 0; i < mCols; ++i) {
        if (mGridContent[y][i] == -1) return false;
    }
    return true;
}

int Board::clearLines()
{
    int cLines = 0;
    removePiece();
    for (int i = 1; i < mRows; ++i) {
        if (isLineFull(i)){
            for (int k = i; k > 0; --k){
                for (int j = 0; j < mCols; ++j) {
                    if (k == 0){
                        mGridContent[k][j] = -1;
                    }
                    else {
                        mGridContent[k][j] = mGridContent[k-1][j];
                        //mGridContent[i-1][j] = -1;
                    }
                }
            }
            ++cLines;
        }
    }
    placePiece();
    return cLines;
}
