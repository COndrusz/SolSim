#pragma once
#include <utility>
#include <cmath>
#include "Logger.h"


class Planet
{
private:
	float radius;
	float mass;
	std::pair<double, double> position;
	std::pair<double, double> velocity;

	
public:
	Planet(double x, double y, double v_x, double v_y, float radius, float mass);
	Planet();

	void update_position(float delta_t, std::pair<double, double> positions[], float masses[]);
	std::pair<double, double> get_position();
	float get_mass();
private:
	double distance_to(std::pair<double, double> pos);
	void updateVelocity(std::pair<double, double> delta_v);
	
	std::pair<double, double> calculateGravitationalForce(std::pair<double, double> n_position, float mass);

};

