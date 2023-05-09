#ifndef BOSS_OBJECT_H
#define BOSS_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "TextObject.h"
#include "BossBullet.h"
#include "PlayerObject.h"
#include <vector>

class BossObject : public BaseObject
{
public:
    BossObject();
    ~BossObject();

    void set_y_pos(const double &yPos) {y_pos = yPos;}//tạo vị trí boss bắt đầu chạy
    void set_x_pos(const double &xPos) {x_pos = xPos;}
    double get_y_pos() const {return y_pos;}
    double set_x_pos() const {return x_pos;}
    void set_y_limit(const double &yLimit) {y_limit = yLimit;}//vị trí dừng lại

    bool canspawnbullet();//set đến vị trí thì bắn đạn
    void GenerateBullet(SDL_Renderer* screen);//khởi tạo đạn

    void set_x_speed(const float &xSpeed) {x_speed = xSpeed;}//tốc độ boss
    void set_y_speed(const float &ySpeed) {y_speed = ySpeed;}

    void MoveThreat();

    void rotate_angle();//đạn quay tròn
    void set_angle_rotate_speed(const double& angleSpeed) {angle_rotate_speed = angleSpeed;}//tốc độ quay
    void set_angle(const double& angle_) {angle = angle_;}//set đạn tròn

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des,const SDL_Rect* clip);

    void got_hit(const int damage) {health -= damage;}//boss mất máu
    void set_health(const int &life) {health = life;}//máu boss
    int get_health() const {return health;}

    void set_boss_bullet_list(std::vector <BossBullet*> boss_bullet_list)
    {
        p_boss_bullet_list_ = boss_bullet_list;
    }

    std::vector <BossBullet*> get_boss_bullet_list() const {return p_boss_bullet_list_;}

    void set_stats();//ảnh, tốc độ
    void MakeBullet(SDL_Renderer* des, const int& x_limit, const int& y_limit);//bắn đạn

private:
    double x_pos;
    double y_pos;
    double x_speed;
    double y_speed;

    double angle;
    double angle_rotate_speed;

    int width_frame;
    int height_frame;

    int y_limit;
    int x_limit;
    int health;

    int delay_shoot_time;

    bool reverse;
    unsigned long long CurrentTime;
    unsigned long long LastTime;

    std::vector <BossBullet*> p_boss_bullet_list_;
};

#endif // BOSS_OBJECT_H



