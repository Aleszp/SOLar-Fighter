#ifndef _STAR_HPP_
#define _STAR_HPP_

#include <cstdint>
#include "renderable.hpp"

class simple_object;

/**
 * Klasa odpowiedzialna za gwiazdy w tle
 */ 
class Star: public Renderable
{
	protected:
		double alfa_;
		double beta_;
		uint_fast8_t r_;
		uint_fast8_t g_;
		uint_fast8_t b_;
	public:
		Star(double alfa=0, double beta=0);
		Star(double alfa, double beta, uint_fast8_t r,uint_fast8_t g_,uint_fast8_t b_);
		virtual ~Star(){}
		virtual void update(double dt){}
		virtual bool is_visible(const Camera* camera);
		virtual void render(const Camera* camera);
};

#endif
