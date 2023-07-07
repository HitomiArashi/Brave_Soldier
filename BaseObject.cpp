#include "BaseObject.h"

/**
Information initialization of the object
*/
BaseObject::BaseObject()
{
	p_object_ = NULL;

	rect_.x = 0; //Reset the x pos
	rect_.y = 0; //Reset the y pos
	rect_.w = 0; //Reset the width
	rect_.h = 0; //Reeset the height
}

/**
Destroy the object to save data
*/
BaseObject::~BaseObject()
{
	Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	//Free "trash" memory
	Free();
	
	SDL_Texture* new_texture = NULL; //Reset the object image

	SDL_Surface* load_surface = IMG_Load(path.c_str()); //Upload the object image
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B)); //Remove the image background
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface); //Convert the image to the texture

		if (new_texture != NULL)
		{
			rect_.w = load_surface->w; //Set the width of the object
			rect_.h = load_surface->h; //Set the height of the object
		}

		SDL_FreeSurface(load_surface); //Remove the load_surface as the info has been moved
	}

	p_object_ = new_texture; //Take the index of the texture of the object

	return p_object_ != NULL;
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip /* = NULL */)
{
	SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w, rect_.h }; //Position and size of the image

	SDL_RenderCopy(des, p_object_, clip, &renderquad); //Show the object on the screen
}

void BaseObject::Free()
{
	if (p_object_ != NULL)
	{
		SDL_DestroyTexture(p_object_); //Free the memory about the texture
		p_object_ = NULL; //Reset all the index of the object
		rect_.w = 0;
		rect_.h = 0;
	}
}