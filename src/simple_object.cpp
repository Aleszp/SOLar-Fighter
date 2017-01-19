#include <cmath>

#include "simple_object.hpp"
#include "object.hpp"
#include "math.hpp"

/**
 * Konstruktor klasy SimpleObject
 * @param x - położenie w osi x
 * @param y - położenie w osi y
 * @param z - położenie w osi z
 * @param yaw - obrót w osi z
 * @param pitch - obrót w osi xy
 * @param roll - obrót wokół własnej osi
 * @return obiekt typu SimpleObject
 */ 
SimpleObject::SimpleObject(double x, double y, double z, double yaw=0.0,double pitch=0.0,double roll=0.0)
: x_(x),y_(y),z_(z),yaw_(yaw),pitch_(pitch),roll_(roll) {}

/**
 * Konstruktor kopiujący klasy SimpleObject z klasy Object
 * @param object - referencja na obiekt z którego są kopiowane fane
 * @return obiekt typu SimpleObject
 */
SimpleObject::SimpleObject(const Object* object)
: x_(object->get_x()), y_(object->get_y()), z_(object->get_z()),yaw_(object->get_yaw()),pitch_(object->get_pitch()),roll_(object->get_roll()){}

/**
 * Obraca w osi z o zadany kąt i przelicza go na wartość z zakresu <-pi;pi>
 * @param Dyaw - wartość przesunięcia  
 */
void SimpleObject::rotate_yaw(double Dyaw)
{
	yaw_+=Dyaw;
	if(Dyaw>0)
		if(yaw_>PI)
			yaw_-=PI2;
	if(Dyaw<0)
		if(yaw_<-PI)
			yaw_+=PI2;
	//fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

/**
 * Obraca w osi xy o zadany kąt i przelicza go na wartość z zakresu <-pi/2;pi/2> uwzględniając wpływ na obrót w pozostałych dwóch osiach
 * @param Dpitch - wartość przesunięcia  
 */
void SimpleObject::rotate_pitch(double Dpitch)
{
	pitch_+=Dpitch;
	if(Dpitch>0)
		if(pitch_>PI05)
		{
			pitch_=PI-pitch_;
			rotate_roll(PI);
			rotate_yaw(PI);
		}
	if(Dpitch<0)
		if(pitch_<-PI05)
		{
			pitch_=-PI-pitch_;
			rotate_roll(PI);
			rotate_yaw(PI);
		}
	//fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

/**
 * Obraca w osi obiektu o zadany kąt i przelicza go na wartość z zakresu <-pi;pi>
 * @param Droll - wartość przesunięcia  
 */
void SimpleObject::rotate_roll(double Droll)
{
	roll_+=Droll;
	if(Droll>0)
		if(roll_>PI)
			roll_-=PI2;
	if(Droll<0)
		if(roll_<-PI)
			roll_+=PI2;
	//fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

/**
 * Oblicza odległość między dwoma obiektami
 * @param o1 - wskaźnik na pierwszy obiekt
 * @param o2 - wskaźnik na drugi obiekt
 * @return odległość w kilometrach
 */
double calculate_distance(const SimpleObject* o1,const SimpleObject* o2)
{
	double x=o1->x_-o2->x_;
	double y=o1->y_-o2->y_;
	double z=o1->z_-o2->z_;
	return sqrt(x*x+y*y+z*z);
}
