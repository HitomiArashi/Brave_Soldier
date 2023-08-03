#pragma once
#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunction.h"

/**
 * @brief New data type: BaseObject
 * 
 * @note Base for every object
 */
class BaseObject
{
protected:
	SDL_Texture* p_object_; //Take object image
	SDL_Rect     rect_;     //Take object image size

public:
	BaseObject();
	~BaseObject();

	/**
	 * @brief Set the Rect object
	 * 
	 * @param x 
	 * @param y 
	 */
	void SetRect(const int& x, const int& y) {
		rect_.x = x;
		rect_.y = y;
	}

	/**
	 * @brief Get the Rect object
	 * 
	 * @return SDL_Rect 
	 */
	SDL_Rect GetRect() const {
		return rect_;
	}

	/**
	 * @brief Get the Object object
	 * 
	 * @return SDL_Texture* 
	 */
	SDL_Texture* GetObject() {
		return p_object_;
	}

	bool LoadImg(std::string path, SDL_Renderer* screen);

	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void Free();
};

#endif // !BASE_OBJECT_H_
