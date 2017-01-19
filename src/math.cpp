#include <cmath>
#include "math.hpp"

/**
 * Przelicza kąt w radianach na jego odpowiednik w zakresie <-pi;pi> nadpisując jego wartość w wskaźniku
 * @param wskaźnik na kąt do przeliczenia
 */ 
void overflow(double* deg)
{
	while(std::abs(*deg)>PI)
	{
		*deg-=PI2*copysign(1,*deg);
	}
}

/**
 * Przelicza kąt w radianach na jego odpowiednik w zakresie <-pi;pi>
 * @param kąt do przeliczenia
 * @return przeliczony kąt
 */ 
double overflow(double deg)
{
	while(std::abs(deg)>PI)
	{
		deg-=PI2*copysign(1,deg);
	}
	return deg;
}

/**
 * Przelicza kąt w radianach na jego odpowiednik w zakresie <-pi/2;pi/2> z wpływem na drugi kąt
 * @param kąt do przeliczenia
 * @param kąt który ma zostać obrócony o pi w razie przekroczenia zakresu przez przeliczany kąt
 */ 
void overflow2(double *deg1, double *deg2)
{
	while(std::abs(*deg1)>PI05)
	{
		*deg1-=(-PI05*copysign(1,*deg1)+*deg1);
		*deg2-=PI*copysign(1,*deg2);
	}
}
