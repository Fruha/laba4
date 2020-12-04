#pragma once

namespace game 
{
	class Effect 
	{
	private:
		float timeLeft;
		float power;
	protected:
	public:
		enum Type { POISONING, WEAKNESS };
		
		Type type;

		Effect(Type t_type, float t_timeLeft, float t_power) :
			type(t_type),
			timeLeft(t_timeLeft),
			power(t_power)
		{};

		float getTimeLeft() { return timeLeft; };
		float getPower() { return power; };

		void setTimeLeft(float t_timeLeft) { timeLeft = t_timeLeft; };
		void setPower(float t_power) { power = t_power; };

	};
}