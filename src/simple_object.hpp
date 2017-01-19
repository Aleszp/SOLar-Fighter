#ifndef _SIMPLE_OBJECT_HPP_
#define _SIMPLE_OBJECT_HPP_
#include "renderable.hpp"


class Object;			//niezbędne dla przyjaźni


/**
 * Klasa abstrakcyjna po której dziedziczą klasy Object i Camera
 */ 
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
		SimpleObject(const Object* object);
		virtual ~SimpleObject(){}
		
		virtual bool is_visible(const Camera* camera){return false;}
		virtual void render(const Camera* camera){};
		virtual void update(double dt)=0;
		
		virtual void rotate_yaw(double Dyaw);
		virtual void rotate_pitch(double Dpitch);
		virtual void rotate_roll(double Droll);
		
		/**
		 * zwraca wartość składowej x
		 * @return składowa x
		 */ 
		inline double get_x() const {return x_;}
		/**
		 * zwraca wartość składowej y
		 * @return składowa y
		 */
		inline double get_y() const {return y_;}
		/**
		 * zwraca wartość składowej z
		 * @return składowa z
		 */
		inline double get_z() const {return z_;}
		
		/**
		 * Przesuwa w osi x
		 * @param dx - wartość przesunięcia
		 */
		inline void move_x(double dx) {x_+=dx;}
		/**
		 * Przesuwa w osi y
		 * @param dy - wartość przesunięcia
		 */
		inline void move_y(double dy) {y_+=dy;}
		/**
		 * Przesuwa w osi z
		 * @param dx=z - wartość przesunięcia
		 */
		inline void move_z(double dz) {z_+=dz;}
		
		/**
		 * Zwraca kąt obrotu w osi z
		 * @param wartość kąta w radianach <-pi;pi>
		 */
		inline double get_yaw()  const {return yaw_;}
		/**
		 * Zwraca kąt obrotu w osi xy
		 * @param wartość kąta w radianach <-pi/2;pi/2>
		 */
		inline double get_pitch()const {return pitch_;}
		/**
		 * Zwraca kąt obrotu wokół własnej osi
		 * @param wartość kąta w radianach <-pi;pi>
		 */
		inline double get_roll() const {return roll_;}
		
	friend double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);
};

double calculate_distance(const SimpleObject* o1,const SimpleObject* o2);


#endif
