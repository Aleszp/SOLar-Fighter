#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

class Camera;

class Renderable
{
	public:
		Renderable(){}
		virtual ~Renderable(){}
		virtual bool is_visible(const Camera* camera)=0;
		virtual void render(const Camera* camera)=0;
		virtual void update(double dt)=0;
};

#endif
