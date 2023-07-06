#include "ImpTimer.h"
#include "CommonFunction.h"

ImpTimer::ImpTimer()		//Init the data
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::Start()		//Start to run program
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

void ImpTimer::Stop()		//Stop to run program
{
	is_paused_ = false;
	is_started_ = false;
}

void ImpTimer::Pause()		//Pause program
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}
}

void ImpTimer::Unpaused()	//Free the pause
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}

int ImpTimer::get_ticks()	//Take time (miliseconds)
{
	if (is_started_ == true)
	{
		if (is_paused_ == true)
		{
			return paused_tick_;
		}
		else
		{
			return SDL_GetTicks() - start_tick_;
		}
	}

	return 0;
}

bool ImpTimer::is_started()	//Check if it is started
{
	return is_started_;
}

bool ImpTimer::is_paused()	//Check if it is paused
{
	return is_paused_;
}