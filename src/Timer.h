#pragma once

template<typename Function>
class Timer
{
public: 
	void setTimeOut(Function function, int delay);
	void setInterval(Function, int interval);
	void stop();
};