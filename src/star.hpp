#ifndef _STAR_HPP_
#define _STAR_HPP_

#include "renderable.hpp"

class simple_object;

class Star: public Renderable
{
	private:
		double alfa_;
		double beta_;
		int color_;
	public:
		Star(double alfa, double beta);
		Star(double alfa, double beta, int color);
		virtual ~Star(){}
		virtual bool is_visible(const Camera* camera);
		virtual void render(const Camera* camera);
};

#endif
