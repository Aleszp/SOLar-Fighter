#ifndef _MULTI_HPP_
#define _MULTI_HPP_

#include <thread>
#include <vector>
#include "renderable.hpp"

class Simulator
{
	private:
		std::vector<Renderable*> simulatables_;
		std::vector<Renderable*> buffer_;
		double dt_;
	public:
		Simulator(std::vector<Renderable*> simulatables, double dt);
		void operator()();

		inline void update_buffer(){buffer_=simulatables_;}
		inline std::vector<Renderable*> get_buffer(){return buffer_;}
};

#endif
