/*
 * path_generator.h
 *
 *  Created on: 11 Nov 2021
 *      Author: sergeynasekin
 */

#ifndef PATH_GENERATOR_H_
#define PATH_GENERATOR_H_

#pragma once

#include <vector>
#include <cmath>
#include <random>

using namespace std;

double gaussian_box_muller() {
	double x = 0.0;
	double y = 0.0;
	double euclid_sq = 0.0;

	do {
		x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
		euclid_sq = x * x + y * y;
	} while (euclid_sq >= 1.0);

	return x * sqrt(-2 * log(euclid_sq) / euclid_sq);

}

void calc_path_spot_prices(std::vector<double> &spot_prices, const double &r,
		const double &v, const double &T) {

	double dt = T / static_cast<double>(spot_prices.size());
	double drift = exp(dt * (r - 0.5 * v * v));
	double vol = sqrt(v * v * dt);

	for (int i = 1; i < spot_prices.size(); i++) {
		double gauss_bm = gaussian_box_muller();
		spot_prices[i] = spot_prices[i - 1] * drift * exp(vol * gauss_bm);
	}
}

void generate_correlated_std_normal_draws(std::vector<double> &std_normals_1,
		std::vector<double> &std_normals_2) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(0, 1);
	double rho = -0.5;

	std::vector<double>::iterator i1;
	std::vector<double>::iterator i2;

	for (i1 = std_normals_1.begin(), i2 = std_normals_2.begin();
			i1 < std_normals_1.end() && i1 < std_normals_2.end(); ++i1, ++i2) {
		double x = dist(gen);
		double y = rho * x + sqrt(1 - pow(2, rho)) * dist(gen);
		*i1 = x;
		*i2 = y;
	}
}

#endif /* PATH_GENERATOR_H_ */
