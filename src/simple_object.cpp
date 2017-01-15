#include <cmath>

#include "simple_object.hpp"
#include "object.hpp"
#include "math.hpp"


SimpleObject::SimpleObject(double x, double y, double z, double yaw=0.0,double pitch=0.0,double roll=0.0)
: x_(x),y_(y),z_(z),yaw_(yaw),pitch_(pitch),roll_(roll) {}

SimpleObject::SimpleObject(Object* object)
: x_(object->x_), y_(object->y_), z_(object->z_){}

void SimpleObject::rotate_yaw(double Dyaw)
{
	yaw_+=Dyaw;
	if(Dyaw>0)
		if(yaw_>PI)
			yaw_-=PI2;
	if(Dyaw<0)
		if(yaw_<-PI)
			yaw_+=PI2;
	fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

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
	fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

void SimpleObject::rotate_roll(double Droll)
{
	roll_+=Droll;
	if(Droll>0)
		if(roll_>PI)
			roll_-=PI2;
	if(Droll<0)
		if(roll_<-PI)
			roll_+=PI2;
	fprintf(stderr, "YPR = (%lf,%lf,%lf)\n",rad2deg(yaw_),rad2deg(pitch_),rad2deg(roll_));
}

double calculate_distance(const SimpleObject* o1,const SimpleObject* o2)
{
	double x=o1->x_-o2->x_;
	double y=o1->y_-o2->y_;
	double z=o1->z_-o2->z_;
	return sqrt(x*x+y*y+z*z);
}
