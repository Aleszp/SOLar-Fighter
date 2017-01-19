#ifndef _MULTI_HPP_
#define _MULTI_HPP_

#include <thread>
#include <vector>
#include "renderable.hpp"

/**
 *	Klasa odpowiedzialna za prowadzenie symulacji w osobnym wątku (TBA). 
 */
class Simulator
{
	private:
		std::vector<Renderable*> simulatables_;
		std::vector<Renderable*> buffer_;
		double dt_;
	public:
		Simulator(std::vector<Renderable*> simulatables, double dt);
		void operator()();

		/**
		 * Aktualizuje bufor do zwracania do wątku renderującego
		 */ 
		inline void update_buffer(){buffer_=simulatables_;}
		
		/**
		 * Zwraca bufor dla wątku renderującego
		 * @return kopia bufora
		 */ 
		inline std::vector<Renderable*> get_buffer(){return buffer_;}
};

#endif
