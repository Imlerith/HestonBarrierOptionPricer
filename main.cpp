//============================================================================
// Name        : HestonOptionPricer.cpp
// Author      : SN
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include "payoff.h"
#include "option.h"
#include "heston_path_generator.h"

int main() {
	unsigned num_sims = 10000; // number of simulated asset paths
	unsigned n_steps = 100;     // number of steps in each asset path

	double S = 100.0; // stock spot price
	double K = 90.0; // strike price
	double B = 90.0; // barrier price

	double T = 1.00; // maturity
	double r = 0.08; // risk-free rate

	double kappa = 6.21;   // vola mean reversion rate
	double theta = 0.019;  // long-run average volatility
	double sigma = 0.2;	   // vol of vol parameter
	double rho = -0.7;     // correlation of spot and vola
	double v_0 = 0.010201; // initial vola

	std::vector<double> spot_prices_b(n_steps, S); // vector of spot prices
	std::vector<double> spot_prices_a(n_steps, S); // vector of spot prices

	// create a unique pointer to a barrier call payoff object
	const auto &payoff_barrier_call = std::unique_ptr<Payoff>(
			new PayoffBarrierCall(K, B));

	// create a unique pointer to an Asian call payoff object
	const auto &payoff_asian_call = std::unique_ptr<Payoff>(
			new PayoffAsianCall(K));

	// create a unique pointer to a barrier down-and-out option object
	const auto &down_out_option = std::unique_ptr<Option>(
			new BarrierOptionDownOut(payoff_barrier_call, T, r));

	// create a unique pointer to an arithmetic Asian option object
	const auto &arithmetic_option = std::unique_ptr<Option>(
			new AsianOptionArithmetic(payoff_asian_call, T, r));

	// create Heston paths' generator objects
	HestonPathGenerator barrier_heston_generator = HestonPathGenerator(down_out_option, kappa, theta,
			v_0, sigma, rho, n_steps);

	HestonPathGenerator arithmetic_heston_generator = HestonPathGenerator(arithmetic_option, kappa,
			theta, v_0, sigma, rho, n_steps);

	// get the sum of all payoffs
	double barrier_payoff_sum = 0.0;
	double asian_payoff_sum = 0.0;
	for (int i = 0; i < num_sims; i++) {
		// generate the spot path using Heston paths' generator object
		barrier_heston_generator.calc_spot_path(spot_prices_b);
		arithmetic_heston_generator.calc_spot_path(spot_prices_a);

		barrier_payoff_sum += down_out_option->payoff_price(spot_prices_b);
		asian_payoff_sum += arithmetic_option->payoff_price(spot_prices_a);
	}

	// discount the payoffs' sum
	double barrier_discount_payoff_avg = (barrier_payoff_sum
			/ static_cast<double>(num_sims)) * exp(-r * T);
	double asian_discount_payoff_avg = (asian_payoff_sum
			/ static_cast<double>(num_sims)) * exp(-r * T);

	// output parameters and the option price
	std::cout << "Number of paths: " << num_sims << std::endl;
	std::cout << "Number of steps: " << n_steps << std::endl;
	std::cout << "Spot:            " << S << std::endl;
	std::cout << "Strike:          " << K << std::endl;
	std::cout << "Barrier:         " << B << std::endl;
	std::cout << "Maturity:        " << T << std::endl;
	std::cout << "Risk-free rate:  " << r << std::endl;
	std::cout << "Kappa:           " << kappa << std::endl;
	std::cout << "Theta:           " << theta << std::endl;
	std::cout << "Vol of vol:      " << sigma << std::endl;
	std::cout << "Correlation:     " << rho << std::endl;
	cout << endl;
	std::cout << "Barrier option price:    " << barrier_discount_payoff_avg
			<< std::endl;
	std::cout << "Asian option price:    " << asian_discount_payoff_avg
			<< std::endl;

	return 0;
}
