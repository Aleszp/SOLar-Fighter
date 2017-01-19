#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "simple_object.hpp"
#include "camera.hpp"

class Object: public SimpleObject
{
	private:
		double size_x_;	//długość boku prostopadłościanu w którym się mieści w osi x
		double size_y_;	//długość boku prostopadłościanu w którym się mieści w osi y
		double size_z_;	//długość boku prostopadłościanu w którym się mieści w osi z
	public:
		Object(double x, double y, double z, double yaw, double pitch, double roll, double size_x, double size_y, double size_z);
		virtual ~Object(){}
		virtual bool is_visible(const Camera* camera);
		virtual void render(const Camera* camera);
};
#endif
