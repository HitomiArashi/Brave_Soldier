#pragma once
#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include <vector>

#include "CommonFunction.h"
#include "BaseObject.h"
#include "BulletObject.h"

/**
 * @brief New data type: MainObject
 * 
 * @note Handle for main object/character
 */
class MainObject : public BaseObject
{
private:
	int money_cnt;

	std::vector <BulletObject*> p_bullet_list_;

	float x_val_;			//Moving speed
	float y_val_;

	float x_pos_;			//Current pos
	float y_pos_;

	bool on_ground_;		//Check if object is on ground

	int width_frame_;		//Size of the object
	int height_frame_;

	int map_x_;				//Pos of the screen to show
	int map_y_;

	SDL_Rect frame_clip_[8];//Frame of object animation

	Input input_type_;		//Input action

	int frame_;				//Which frame of animation

	int status_;			//Current status

	int comeback_time;		//Delay time when fall into chasm

public:
	MainObject();
	~MainObject();

	/**
	 * @brief Walking type of the object
	 * 
	 */
	enum WalkType
	{
		WALK_RIGHT = 0,
		WALK_LEFT = 1
	};

	/**
	 * @brief Set the bullet list object
	 * 
	 * @param bullet_list 
	 */
	void set_bullet_list(std::vector <BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list;
	}
	/**
	 * @brief Get the bullet list object
	 * 
	 * @return std::vector <BulletObject*> 
	 */
	std::vector <BulletObject*> get_bullet_list() const
	{
		return p_bullet_list_;
	}

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event even, SDL_Renderer* screen);
	void UpdateImagePlayer(SDL_Renderer* des);
	void SetClips();

	void DoPlayer(Map& map_data);
	void CheckColMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y);
	void CenterEntityOnMap(Map& map_data);

	void HandleBullet(SDL_Renderer* des);

	void Increase_Money();
};

#endif
