#pragma once
#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

class ImpTimer
{
private:
	int start_tick_;	//When is started
	int paused_tick_;	//When is paused

	bool is_paused_;	//Check if it is paused
	bool is_started_;	//Check if it is paused
public:
	ImpTimer();
	~ImpTimer();

	void Start();
	void Stop();
	void Pause();
	void Unpaused();

	int get_ticks();

	bool is_started();
	bool is_paused();
};

#endif // !IMP_TIMER_H_
