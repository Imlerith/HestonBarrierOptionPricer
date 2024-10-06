/*
 * option.cpp
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#include <numeric>
#include <cmath>
#include "option.h"

Option::Option(const unique_ptr<Payoff> &payoff_, const double T_,
		const double r_) :
		payoff(payoff_), T(T_), r(r_) {
}

AsianOptionArithmetic::AsianOptionArithmetic(const unique_ptr<Payoff> &payoff_,
		const double T_, const double r_) :
		Option(payoff_, T_, r_) {

}

AsianOptionGeometric::AsianOptionGeometric(const unique_ptr<Payoff> &payoff_,
		const double T_, const double r_) :
		Option(payoff_, T_, r_) {

}

BarrierOptionDownOut::BarrierOptionDownOut(const unique_ptr<Payoff> &payoff_,
		const double T_, const double r_) :
		Option(payoff_, T_, r_) {
}

double AsianOptionArithmetic::payoff_price(
		const vector<double> &spot_prices) const {
	unsigned num_times = spot_prices.size();
	double sum = std::accumulate(spot_prices.begin(), spot_prices.end(), 0);
	double arith_mean = sum / static_cast<double>(num_times);
	std::function<bool(const double&)> cond_dummy = [&](const double &x) {
		return true;
	};
	return (*payoff.get())(arith_mean, cond_dummy);
}

double AsianOptionGeometric::payoff_price(
		const vector<double> &spot_prices) const {
	unsigned num_times = spot_prices.size();
	double log_sum = 0.0;
	for (int i = 0; i < spot_prices.size(); i++) {
		log_sum += log(spot_prices[i]);
	}
	double geom_mean = exp(log_sum / static_cast<double>(num_times));
	std::function<bool(const double&)> cond_dummy = [&](const double &x) {
		return true;
	};
	return (*payoff.get())(geom_mean, cond_dummy);
}

double BarrierOptionDownOut::payoff_price(
		const vector<double> &spot_prices) const {
	auto min_spot_price = std::min_element(spot_prices.begin(),
			spot_prices.end());
	std::function<bool(const double&)> cond_down_out = [&](const double &x) {
		return (*min_spot_price > x) ? true : false;
	};
	return (*payoff.get())(spot_prices.back(), cond_down_out);
}

BarrierOptionUpOut::BarrierOptionUpOut(const unique_ptr<Payoff> &payoff_,
		const double T_, const double r_) :
		Option(payoff_, T_, r_) {
}

double BarrierOptionUpOut::payoff_price(
		const vector<double> &spot_prices) const {
	auto max_spot_price = std::max_element(spot_prices.begin(),
			spot_prices.end());
	std::function<bool(const double&)> cond_up_out = [&](const double &x) {
		return (*max_spot_price < x) ? true : false;
	};
	return (*payoff.get())(spot_prices.back(), cond_up_out);
}

