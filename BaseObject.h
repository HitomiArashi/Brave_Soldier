#pragma once
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
protected:
	SDL_Texture* p_object_; //Take object image
	SDL_Rect     rect_;     //Take object image size

public:
	BaseObject();
	~BaseObject();

	/**
	Set the size of the object
	*/
	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}

	/**
	Get the size of the object
	*/
	SDL_Rect GetRect() const {
		return rect_;
	}

	/**
	Get the object
	*/
	SDL_Texture* GetObject() {
		return p_object_;
	}

	/**
	Show the object on the screen, also check if it is loaded successfully
	*/
	bool LoadImg(std::string path, SDL_Renderer* screen);

	/**
	Load the image on the background
	*/
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	/**
	Free all the memory saved
	*/
	void Free();
};

#endif // !BASE_OBJECT_H_
