#include "Random.h"

int Random::reseed()
{
	seed=seed*multiplier+add_on;
	return seed;

}
Random::Random(bool pseudo)
{
	if(pseudo)seed=1;
	else seed=time(NULL)%INT_MAX;
	multiplier=2743;
	add_on=5923;
}
double Random::random_real()
{
	double max=INT_MAX+1.0;
	double temp=reseed();
	if(temp<0) temp=temp+max;
	return temp/max;
}
int Random::random_integer(int low,int high)
{
	if(low>high) return random_integer(high,low);
	else return ((int)((high-low+1)*random_real()))+low;


}
Random::~Random(void)
{
}
