#include "MenuObject.h"

MenuObject::MenuObject()
{
    width_frame=0;
    height_frame=0;
}

MenuObject::~MenuObject()
{

}

bool MenuObject::IsInside(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		bool inside = true;
		if(x < rect_.x)
		{
			inside = false;
		}
		else if(x > rect_.x + width_frame)
		{
			inside = false;
		}
		else if(y < rect_.y)
		{
			inside = false;
		}
		else if(y > rect_.y + height_frame)
		{
			inside = false;
		}
		return inside;
	}
}

void MenuObject::HandlePlayButton(SDL_Event event, SDL_Renderer* screen, bool &InMenu)
{
    if(IsInside(event))
	{
	    LoadImg("Image/Player/Play.png", screen);
		if(event.type == SDL_MOUSEBUTTONDOWN)
		{
		    InMenu = !InMenu;
		}
	}
}

void MenuObject::HandleExitButton(SDL_Event event, SDL_Renderer* screen, bool &play, bool &InMenu)
{
	if(IsInside(event))
	{
	    LoadImg("Image/Player/Quit.png", screen);
		if(event.type==SDL_MOUSEBUTTONDOWN)
		{
		    play = !play;
		    InMenu = true;
		}
	}
}


