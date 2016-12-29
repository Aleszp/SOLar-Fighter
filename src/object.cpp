#include "object.hpp"

Object::Object(double x, double y, double z, double yaw=0.0,double pitch=0.0,double roll=0.0, double size_x=0.0, double size_y=0.0, double size_z=0.0)
:SimpleObject(x, y, z, yaw, pitch, roll), size_x_(size_x),size_y_(size_y),size_z_(size_z){}

bool Object::is_visible(const Camera* camera) //double fov_x, double fov_y, double render_dist
{
	double dist=calculate_distance(camera, (SimpleObject*)this);	//policz odległość
	if(dist>camera->render_dist_)											//jeśli jest poza zasięgiem rysowania
		return false;												//to nie jest widoczne
	//if(dist	
	return true;
}

void Object::render(const Camera* camera)
{
	
}
