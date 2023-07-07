#include"MainObject.h"

MainObject::MainObject() //Init the data
{
	frame_ = 0;

	x_pos_ = 0;
	y_pos_ = 0;

	x_val_ = 0;
	y_val_ = 0;

	width_frame_ = 0;
	height_frame_ = 0;

	status_ = WALK_RIGHT;

	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.jump_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;

	on_ground_ = false;

	map_x_ = 0;
	map_y_ = 0;

	comeback_time = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen) //Upload the object image
{
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true) //Success
	{
		width_frame_ = rect_.w / FRAMES;
		height_frame_ = rect_.h;
	}

	return ret;
}

void MainObject::SetMapXY(const int map_x, const int map_y) //Set screen start pos
{
	map_x_ = map_x;
	map_y_ = map_y;
}

void MainObject::SetClips() //Set clip for object animation
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < FRAMES; i++)
		{
			frame_clip_[i].x = width_frame_ * i;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}

	}
}

void MainObject::Show(SDL_Renderer* des) //Show object on the screen
{
	UpdateImagePlayer(des);

	if (input_type_.left_ == 1 || input_type_.right_ == 1) //Moving = Show next frame
	{
		frame_++;
	}
	else //Not moving
	{
		frame_ = 0;
	}

	if (frame_ >= 7) //Out of range of frame = Reset
	{
		frame_ = 1;
	}

	if (comeback_time == 0)
	{
		rect_.x = x_pos_ - map_x_; //Current pos of object
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip_[frame_]; //Set the pos for the current frame

		SDL_Rect renderQuad = { rect_.x, rect_.y, width_frame_, height_frame_ }; //Not sure wat it is used for

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad); //Show the frame one the screen
	}

}

void MainObject::HandleInputAction(SDL_Event even, SDL_Renderer* screen) //Handle action from mouse and keyboard
{
	//Moving
	if (even.type == SDL_KEYDOWN)
	{
		switch (even.key.keysym.sym)
		{
		case SDLK_RIGHT: //Right arrow
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			UpdateImagePlayer(screen);
			break;
		case SDLK_d: //Key "D"
			status_ = WALK_RIGHT;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
			UpdateImagePlayer(screen);
			break;
		case SDLK_LEFT: //Left arrow
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
			break;
		case SDLK_a: //Key "A"
			status_ = WALK_LEFT;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
			break;
		default:
			break;
		}
	}
	//Stop moving
	else if (even.type == SDL_KEYUP)
	{
		switch (even.key.keysym.sym)
		{
		case SDLK_RIGHT: //Right arrow
			input_type_.right_ = 0;
			break;
		case SDLK_d: //Key "D"
			input_type_.right_ = 0;
			break;
		case SDLK_LEFT: //Left arrow
			input_type_.left_ = 0;
			break;
		case SDLK_a: //Key "A"
			input_type_.left_ = 0;
			break;
		default:
			break;
		}
	}

	if (even.type == SDL_KEYDOWN) //Jump
	{
		if (even.key.keysym.sym == SDLK_SPACE) //Right mouse button
		{
			input_type_.jump_ = 1;
		}
	}
}

void MainObject::DoPlayer(Map& map_data) //Set speed for player and screen
{
	if (comeback_time == 0) //Still alive
	{
		x_val_ = 0;
		y_val_ += GRAVITY; //Increase dropping speed

		if (y_val_ >= MAX_SPEED)
		{
			y_val_ = MAX_SPEED; //Reach max dropping speed
		}

		if (input_type_.left_ == 1)
		{
			x_val_ -= MOVING_SPEED; //Moving backward
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += MOVING_SPEED; //Moving forward
		}

		if (input_type_.jump_ == 1) //Jumping
		{
			if (on_ground_ == true)
			{
				y_val_ = -JUMP_VAL;
			}
			on_ground_ = false;
			input_type_.jump_ = 0;
		}

		CheckColMap(map_data); //Check collision
		CenterEntityOnMap(map_data); //Scroll the map when object at middle
	}
	else //Fall into chasm
	{
		on_ground_ = false;
		comeback_time--;
		if (comeback_time == 0)
		{
			//Go back a little
			if (x_pos_ > 192)
			{
				x_pos_ -= 192; //Tile map
			}
			else
			{
				x_pos_ = 0;
			}
			//Respawn in the sky and stop moving
			y_pos_ = 0;
			x_val_ = 0;
			y_val_ = 0;
		}
	}
}

void MainObject::CheckColMap(Map& map_data) //Check the collision between object and map
{
	int x1 = 0, x2 = 0; //Pos for corner of the part of screen to show
	int y1 = 0, y2 = 0;

	//Check horizontal
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;
	
	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) //Still in range
	{
		if (x_val_ > 0) //Moving to right direct
		{
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) //Collided
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
		}
		else if (x_val_ < 0) // Moving to left direct
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) //Collid
			{
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
		}
	}

	//Check vertical
	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) //Still in range
	{
		if (y_val_ > 0) //Go down (fall)
		{
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) //Collid
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) //Go up (jump)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE) //Collid
			{
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
				on_ground_ = false;
			}
		}
	}

	//Able to move
	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) //Out of range
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_) //Fall into chasm
	{
		comeback_time = 60;
	}
}

//Keep the object in the middle of the screen
void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2); //Update the x-pos to start
	if (map_data.start_x_ < 0) //Begin of file
	{
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) //End of file
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2); //Update the y-pos to start
	if (map_data.start_y_ < 0) //Top of file
	{
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) //Bottom of file
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground_ == true) //Moving
	{
		if (status_ == WALK_LEFT) //Left direct
		{
			LoadImg("Resources//img//player_left.png", des);
		}
		else if (status_ == WALK_RIGHT) //Right direct
		{
			LoadImg("Resources//img//player_right.png", des);
		}
	}
	else //Jumping
	{
		if (status_ == WALK_LEFT) //Left direct
		{
			LoadImg("Resources//img//jum_left.png", des);
		}
		else if (status_ == WALK_RIGHT) //Right direct
		{
			LoadImg("Resources//img//jum_right.png", des);
		}
	}
}