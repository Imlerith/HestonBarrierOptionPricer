/*
 * heston_path_generator.cpp
 *
 *  Created on: 13 Nov 2021
 *      Author: sergeynasekin
 */

#include "heston_path_generator.h"

HestonPathGenerator::HestonPathGenerator(const unique_ptr<Option> &boption_,
		double kappa_, double theta_, double v_0_, double sigma_, double rho_,
		unsigned int n_steps_) :
		boption(boption_), kappa(kappa_), theta(theta_), v_0(v_0_), sigma(
				sigma_), rho(rho_), n_steps(n_steps_), vol_draws(
				vector<double>(n_steps, 0.0)), spot_draws(
				vector<double>(n_steps, 0.0)) {
	generate_correlated_std_normal_draws(vol_draws, spot_draws);
}

vector<double> HestonPathGenerator::get_spot_draws() const {
	return spot_draws;
}

void HestonPathGenerator::generate_correlated_std_normal_draws(
		std::vector<double> &std_normals_1,
		std::vector<double> &std_normals_2) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> dist(0, 1);

	std::vector<double>::iterator i1;
	std::vector<double>::iterator i2;

	for (i1 = std_normals_1.begin(), i2 = std_normals_2.begin();
			i1 < std_normals_1.end() && i2 < std_normals_2.end(); ++i1, ++i2) {
		double x = dist(gen);
		double y = rho * x + sqrt(1 - pow(2, rho)) * dist(gen);
		*i1 = x;
		*i2 = y;
	}
}

void HestonPathGenerator::calc_vol_path(vector<double> &vol_path_) {
	size_t path_size = vol_draws.size();
	const double dt = boption->get_T() / static_cast<double>(path_size);

	for (int i = 1; i < path_size; i++) {
		double v_max = std::max(vol_path_[i - 1], 0.0);
		vol_path_[i] = vol_path_[i - 1] + kappa * (theta - v_max) * dt
				+ sigma * sqrt(v_max * dt) * vol_draws[i - 1];
	}

}

void HestonPathGenerator::calc_spot_path(vector<double> &spot_path) {
	// first generate the vola path
	std::vector<double> vol_path(spot_path.size(), v_0);
	calc_vol_path(vol_path);

	// then generate the spot path
	size_t path_size = spot_draws.size();
	const double dt = boption->get_T() / static_cast<double>(path_size);

	for (int i = 1; i < path_size; i++) {
		double v_max = std::max(vol_path[i - 1], 0.0);
		spot_path[i] = spot_path[i - 1]
				* exp(
						(boption->get_r() - 0.5 * v_max) * dt
								+ sqrt(v_max * dt) * spot_draws[i - 1]);
	}

}

