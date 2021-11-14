/*
 * heston_path_generator.h
 *
 *  Created on: 13 Nov 2021
 *      Author: sergeynasekin
 */

#ifndef HESTON_PATH_GENERATOR_H_
#define HESTON_PATH_GENERATOR_H_

#pragma once

#include <cmath>
#include <vector>
#include <random>
#include "option.h"

class HestonPathGenerator {
private:
	const unique_ptr<BarrierOption> &boption;
	double kappa; // mean reversion rate
	double theta; // long-run vola
	double v_0; // initial vola
	double sigma; // vol of vol
	double rho; // correlation of spot and vola
	unsigned int n_steps; // number of simulation steps
	vector<double> vol_draws; // standard normal (correlated) draws for vola
	vector<double> spot_draws; // standard normal (correlated) draws for spot

public:
	HestonPathGenerator(const unique_ptr<BarrierOption> &boption_,
			double kappa_, double theta_, double v_0_, double sigma_,
			double rho_, unsigned n_steps_);
	virtual ~HestonPathGenerator() {
	}

	void calc_spot_path(vector<double> &spot_path);

private:
	void generate_correlated_std_normal_draws(
			std::vector<double> &std_normals_1,
			std::vector<double> &std_normals_2);

	void calc_vol_path(vector<double> &vol_path);
};

#endif /* HESTON_PATH_GENERATOR_H_ */
