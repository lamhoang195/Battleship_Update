#ifndef MENU_OBJECT_H
#define MENU_OBJECT_H

#include "BaseObject.h"
#include "CommonFunction.h"
#include "ThreatsObject.h"
#include "LaserObject.h"
#include "BossObject.h"
#include "PlayerObject.h"
#include "EnemyBullet.h"
#include "BossBullet.h"

class MenuObject: public BaseObject
{
    public:
    MenuObject();
    ~MenuObject();
    bool IsInside(SDL_Event event);//check vị trí button
    void HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &QuitMenu);
	void HandleExitButton(SDL_Event event, SDL_Renderer* screen, bool &play, bool &InMenu);

};

#endif // MENU_OBJECT_H


