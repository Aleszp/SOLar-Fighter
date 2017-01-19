#ifndef _SIMPLE_OBJECT_HPP_
#define _SIMPLE_OBJECT_HPP_
#include "renderable.hpp"


class Object;			//niezbędne dla przyjaźni

class SimpleObject: public Renderable	//prosty obiekt - punkt w przestrzeni kartezjańskiej - trzy współrzędne xyz i kąty w trzech osiach
{
	protected:
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
		
		virtual bool is_visible(const Camera* camera){return false;}
		virtual void render(const Camera* camera){};
		virtual void update(double dt)=0;
		
		virtual void rotate_yaw(double Dyaw);
		virtual void rotate_pitch(double Dpitch);
		virtual void rotate_roll(double Droll);
		
		inline double get_x() const {return x_;}
		inline double get_y() const {return y_;}
		inline double get_z() const {return z_;}
		
		inline void move_x(double dx) {x_+=dx;}
		inline void move_y(double dy) {y_+=dy;}
		inline void move_z(double dz) {z_+=dz;}
		
		inline double get_yaw()  const {return yaw_;}
		inline double get_pitch()const {return pitch_;}
		inline double get_roll() const {return roll_;}
		
	friend double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);
};

double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);


#endif
