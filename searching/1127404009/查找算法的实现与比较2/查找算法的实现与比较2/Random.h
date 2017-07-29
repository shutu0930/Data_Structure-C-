const int max_int = INT_MAX;

class Random{
public:
	Random(bool pseudo=true);
    int random_integer(int low,int high);
	double random_real();
private:
	int reseed();
	int seed,multiplier,add_on;
};


int Random::reseed()
{
	seed=seed*multiplier+add_on;
	return seed;
}

Random::Random(bool pseudo)
{
	if(pseudo)seed=1;
	else seed=time(NULL)%max_int;
	multiplier=2743;
	add_on=5923;
}

int Random::random_integer(int low,int high)
{
	if(low>high)return random_integer(high,low);
	else return ((int)((high-low+1)*random_real()))+low;
}
double Random::random_real()
{
	double max=max_int+1.0;
	double temp=reseed();
	if(temp<0)temp=temp+max;
	return temp/max;
}