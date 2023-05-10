#ifndef MENU_OBJECT_H
#define MENU_OBJECT_H

#include "BaseObject.h"
#include "CommonFunction.h"

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


