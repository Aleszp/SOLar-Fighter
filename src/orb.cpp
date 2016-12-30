#include "orb.hpp"

Orb::Orb(double m, double r=0, double alfa=0, double z=0, double yaw=0, double pitch=0, double roll=0, double vr=0, double valfa=0, double vz=0, double vyaw=0, double vpitch=0, double vroll=0)
:m_(m), r_(r), alfa_(alfa), z_(z), yaw_(yaw), pitch_(pitch), roll_(roll), vr_(vr), valfa_(valfa), vz_(vz), vyaw_(vyaw), vpitch_(vpitch), vroll_(vroll){}

Orb::Orb(const Orb &src)
:m_(src.m_), r_(src.r_), alfa_(src.alfa_), z_(src.z_), yaw_(src.yaw_), pitch_(src.pitch_), roll_(src.roll_), vr_(src.vr_), valfa_(src.valfa_), vz_(src.vz_), vyaw_(src.vyaw_), vpitch_(src.vpitch_), vroll_(src.vroll_){}


void Orb::update(double dt)
{
	r_+=vr_*dt;
	alfa_+=valfa_*dt;
	z_+=vz_*dt;
	
	//yaw_+=vyaw_*dt;
	//pitch_+=pitch_*dt;
	//roll_+=roll_*dt;
}

bool Orb::is_visible(const Camera* camera)
{
	return false;
}

void Orb::render(const Camera* camera)
{
	
}
