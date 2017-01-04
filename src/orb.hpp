#ifndef _ORB_HPP_
#define _ORB_HPP_

#include "camera.hpp"

//Słońce, planety, księżyce, meteory, komety, planetoidy...
class Orb: public Renderable
{
	protected:
		double m_;		//masa
		double radius_; //promień kuli
		
		double r_;		//układ walcowy
		double alfa_;
		double z_;
	
		double yaw_;	//obrót w osi z - obrót "lewo/prawo"
		double pitch_;	//obrót w osi y - obrót "przód/tył"
		double roll_; 	//obrót w osi x - pochylenie w "lewo/prawo"
		
		//Prędkości
		double vr_;		//układ walcowy
		double valfa_;
		double vz_;
		
		double vyaw_;	//obrót w osi z - obrót "lewo/prawo"
		double vpitch_;	//obrót w osi y - obrót "przód/tył"
		double vroll_; 	//obrót w osi x - pochylenie w "lewo/prawo"
		
	public:
		Orb(double m, double radius_, double r=0, double alfa=0, double z=0, double yaw=0, double pitch=0, double roll=0, double vr=0, double valfa=0, double vz=0, double vyaw=0, double vpitch=0, double vroll=0);
		Orb(const Orb &src);
		virtual ~Orb(){}
		
		virtual void update(double dt);
		virtual bool is_visible(const Camera* camera);
		virtual void render(const Camera* camera);
		
};

#endif
