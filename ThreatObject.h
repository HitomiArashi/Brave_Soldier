#pragma once
#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"

/**
 * @brief Some static information of threat object
 * 
 */
enum Threat
{
	THREAT_FRAME_NUM = 10,
	THREAT_GRAVITY = 5,
	THREAT_MAX_SPEED = 20
};

/**
 * @brief New data type: ThreatsObject
 * 
 * @note Threaten to main object
 */
class ThreatsObject : public BaseObject
{
public:
	ThreatsObject();
	~ThreatsObject();
	/**
	 * @brief Set the x val object
	 * 
	 * @param x_val 
	 */
	void set_x_val(const float &x_val){x_val_ = x_val;}
	/**
	 * @brief Set the y val object
	 * 
	 * @param y_val 
	 */
	void set_y_val(const float &y_val){y_val_ = y_val;}

	/**
	 * @brief Set the x pos object
	 * 
	 * @param x_pos 
	 */
	void set_x_pos(const float &x_pos){x_pos_ = x_pos;}
	/**
	 * @brief Set the y pos object
	 * 
	 * @param y_pos 
	 */
	void set_y_pos(const float &y_pos){ y_pos_ = y_pos;}

	/**
	 * @brief Get the x pos object
	 * 
	 * @return float 
	 */
	float get_x_pos() const {return x_pos_;}
	/**
	 * @brief Get the y pos object
	 * 
	 * @return float 
	 */
	float get_y_pos() const {return y_pos_;}

	/**
	 * @brief Set the Map X Y object
	 * 
	 * @param map_x 
	 * @param map_y 
	 */
	void SetMapXY(const int& map_x, const int& map_y) {map_x_ = map_x; map_y_ = map_y;}

	/**
	 * @brief Get the width frame object
	 * 
	 * @return int 
	 */
	int get_width_frame() const {return width_frame_;}
	/**
	 * @brief Get the height frame object
	 * 
	 * @return int 
	 */
	int get_height_frame() const {return height_frame_;}

	void SetClip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);

	void DoPlayer(Map& gMap);
	void CheckColMap(Map& gMap);
private:
	int map_x_; //Pos on screen to show
	int map_y_;

	float x_pos_; //Current pos
	float y_pos_;

	float x_val_; //Moving speed
	float y_val_;

	bool on_ground_; //Check if object is on ground

	int come_back_time_; //Delay time when fall into chasm

	SDL_Rect frame_clip_[THREAT_FRAME_NUM]; //Frame of object animation

	int width_frame_; //Size of object frame
	int height_frame_;

	int frame_; //Current frame
};

#endif // !THREAT_OBJECT_H_
