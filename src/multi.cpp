#include <chrono>
#include "multi.hpp"

/**
 * Konstruktor klasy Simulator
 * @param simulatables - tablica wskaźników na obiekty które mają być symulowane
 * @param dt - krok czasowy symulacji
 * @return obiekt klasy Simulator
 */
Simulator::Simulator(std::vector<Renderable*> simulatables, double dt):
simulatables_(simulatables), dt_(dt){}

/**
 * Wątek w którym trwa symulacja
 */
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
