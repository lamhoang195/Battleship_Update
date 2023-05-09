#ifndef BOSS_BULLET_H
#define BOSS_BULLET_H

#include "BaseObject.h"
#include "CommonFunction.h"
#include <vector>
#include <bits/stdc++.h>

#define WIDTH_BOSS 19
#define HEIGHT_BOSS 19

class BossBullet : public BaseObject
{
public:
	BossBullet();
	~BossBullet();

	void set_x_speed(const double& xSpeed) {x_speed = xSpeed;}
    void set_y_speed(const double& ySpeed) {y_speed = ySpeed;}

	void set_is_move(const bool &isMove) {is_move_ = isMove;}
	bool get_is_move() const {return is_move_;};

    void set_angle(const double& angle_) {angle=angle_;}
    void set_angle_random();

    void set_pos(const double& xPos, const double& yPos)
    {
        x_pos=xPos;
        y_pos=yPos;
    }
    int get_posX(){return x_pos;}

    void HandleMove(const int &x_border,const int &y_border);

private:
	double x_pos;
    double y_pos;

    double x_speed;//tốc độ đạn
    double y_speed;

    double angle;

    bool is_move_;
};


#endif // BOSS_BULLET_H



