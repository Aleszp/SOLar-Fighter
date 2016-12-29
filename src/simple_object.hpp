#ifndef _SIMPLE_OBJECT_HPP_
#define _SIMPLE_OBJECT_HPP_
#include "renderable.hpp"
#include <stdio.h>

class Object;			//niezbędne dla przyjaźni
class Star;

class SimpleObject: public Renderable	//prosty obiekt - punkt w przestrzeni kartezjańskiej - trzy współrzędne xyz i kąty w trzech osiach
{
	private:
		double x_;		//współrzędna x
		double y_;		//współrzędna y
		double z_;		//współrzędna z
		double yaw_;	//obrót w osi z - obrót "lewo/prawo"
		double pitch_;	//obrót w osi y - obrót "przód/tył"
		double roll_; 	//obrót w osi x - pochylenie w "lewo/prawo"
	public:
		SimpleObject(double x, double y, double z, double yaw, double pitch, double roll);
		SimpleObject(Object* object);
		virtual ~SimpleObject(){}
		virtual void render(const Camera* camera){};
		virtual bool is_visible(const Camera* camera){return false;}
		virtual void rotate_yaw(double Dyaw);
		virtual void rotate_pitch(double Dpitch);
		virtual void rotate_roll(double Droll);
		
	friend double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);
	friend Star;
};

double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);


#endif