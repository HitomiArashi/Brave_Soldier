#include "ImpTimer.h"
#include "CommonFunction.h"

/**
 * @brief Construct a new Imp Timer:: Imp Timer object
 * 
 */
ImpTimer::ImpTimer()
{
	start_tick_ = 0;
	paused_tick_ = 0;
	is_paused_ = false;
	is_started_ = false;
}

/**
 * @brief Destroy the Imp Timer:: Imp Timer object
 * 
 */
ImpTimer::~ImpTimer()
{

}

/**
 * @brief Start to run program
 * 
 */
void ImpTimer::Start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}

/**
 * @brief Stop to run program
 * 
 */
void ImpTimer::Stop()
{
	is_paused_ = false;
	is_started_ = false;
}

/**
 * @brief Pause program
 * 
 */
void ImpTimer::Pause()
{
	if (is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks() - start_tick_;
	}
}

/**
 * @brief Free the pause
 * 
 */
void ImpTimer::Unpaused()
{
	if (is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks() - paused_tick_;
		paused_tick_ = 0;
	}
}

/**
 * @brief Take time (miliseconds)
 * 
 * @return int 
 */
int ImpTimer::get_ticks()
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

/**
 * @brief Check if it is started
 * 
 * @return true 
 * @return false 
 */
bool ImpTimer::is_started()
{
	return is_started_;
}

/**
 * @brief Check if it is paused
 * 
 * @return true 
 * @return false 
 */
bool ImpTimer::is_paused()
{
	return is_paused_;
}