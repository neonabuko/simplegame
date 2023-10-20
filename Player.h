//
// Created by neo on 10/20/23.
//

#ifndef SIMPLEGAME_PLAYER_H
#define SIMPLEGAME_PLAYER_H


class Player {

private:
    float position_X;
    float position_Y;

public:
    Player(float position_X, float position_Y);

    void moveLeft(float speed);
    void moveRight(float speed);
    void moveUp(float speed);
    void moveDown(float speed);
};


#endif //SIMPLEGAME_PLAYER_H
