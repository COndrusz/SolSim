#include "Planet.h"

Planet::Planet(double x, double y, double v_x, double v_y, float radius, float mass) : radius{radius}, mass{mass}
{
	this->position.first = x;
	this->position.second = y;

	this->velocity.first = v_x;
	this->velocity.second = v_y;
}

Planet::Planet()
{
	this->position.first = 0;
	this->position.second = 0;

	this->velocity.first = 0;
	this->velocity.second = 0;

	this->radius = 500;
	this->mass = 1e11;
}

void Planet::update_position(float delta_t, std::pair<double, double> positions[], float masses[])
{
	int num_masses = sizeof(masses)/8; // sizeof(masses[0]);
	int num_positions = sizeof(positions)/ 8; // sizeof(positions[0]);
	Logger::error("Num Masses %i", num_masses);
	Logger::error("Num Positions %i", num_positions);

    if (num_positions != num_masses)
    {
        Logger::error("Different number of positions and masses when calculating gravitational forces");
    }

	for (int i = 0; i < num_masses; i++)
	{
		std::pair<double, double> d_v = calculateGravitationalForce(positions[i], masses[i]);
		d_v.first *= delta_t;
		d_v.second *= delta_t;
		updateVelocity(d_v);

	}

	this->position.first += velocity.first * delta_t;
	this->position.second += velocity.second * delta_t;
}

std::pair<double, double> Planet::get_position()
{
	return this->position;
}

float Planet::get_mass()
{
	return this->mass;
}

void Planet::updateVelocity(std::pair<double, double> delta_v)
{
	this->velocity.first += delta_v.first;
	this->velocity.second += delta_v.second;
}

std::pair<double, double> Planet::calculateGravitationalForce(std::pair<double, double> n_position, float mass)
{
	float G = 6.6743e-11;

	double xdiff = this->position.first - n_position.first;
	double ydiff = this->position.second - n_position.second;
	double r = std::sqrt(xdiff * xdiff + ydiff * ydiff);
	double theta = atan2(ydiff, xdiff);
	double a = G * mass / (r * r);
	

	return std::pair<double, double>(a * cos(theta), a * sin(theta));
}



