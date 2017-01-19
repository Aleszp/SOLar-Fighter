#include <chrono>
#include "multi.hpp"

Simulator::Simulator(std::vector<Renderable*> simulatables, double dt):
simulatables_(simulatables), dt_(dt){}

void Simulator::operator()()
{
	//auto start = std::chrono::high_resolution_clock::now();
    //auto end = start + std::chrono::seconds(dt_);
   // do 
    {
        std::this_thread::yield();
    } 
    //while (std::chrono::high_resolution_clock::now() < end);
	for(std::vector<Renderable*>::const_iterator it = simulatables_.begin();it != simulatables_.end(); ++it)
		it[0]->update(dt_);
}
