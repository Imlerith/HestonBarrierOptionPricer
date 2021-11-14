//============================================================================
// Name        : BarrierOptionPricer.cpp
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
	unsigned num_sims = 100000; // number of simulated asset paths
	unsigned n_steps = 100;     // number of steps in each asset path

	double S = 100.0; // stock spot price
	double K = 90.0; // strike price
	double B = 70.0; // barrier price

	double T = 1.00; // maturity
	double r = 0.08; // risk-free rate

	double kappa = 6.21;   // vola mean reversion rate
	double theta = 0.019;  // long-run average volatility
	double sigma = 0.3;	   // vol of vol parameter
	double rho = -0.7;     // correlation of spot and vola
	double v_0 = 0.010201; // initial vola

	std::vector<double> spot_prices(n_steps, S); // vector of spot prices

	// create a unique pointer to a call payoff object
	const auto &payoff_call = std::unique_ptr<Payoff>(new PayoffCall(K, B));

	// create a unique pointer to a barrier down-and-out option object
	const auto &down_out_option = std::unique_ptr<BarrierOption>(
			new BarrierOptionDownOut(payoff_call, T, r));

	// create Heston paths' generator object
	HestonPathGenerator heston_generator(down_out_option, kappa, theta, v_0,
			sigma, rho, n_steps);

	// get the sum of all payoffs
	double payoff_sum = 0.0;
	for (int i = 0; i < num_sims; i++) {
		// generate the spot path using Heston paths' generator object
		heston_generator.calc_spot_path(spot_prices);
		payoff_sum += down_out_option->payoff_price(spot_prices);
	}

	// discount the payoffs' sum
	double discount_payoff_avg = (payoff_sum / static_cast<double>(num_sims))
			* exp(-r * T);

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
	std::cout << "Option price:    " << discount_payoff_avg << std::endl;

	return 0;
}
