/*
 * option.cpp
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#include <numeric>
#include <cmath>
#include "option.h"

BarrierOption::BarrierOption(const unique_ptr<Payoff> &payoff_, const double T_,
		const double r_) :
		payoff(payoff_), T(T_), r(r_) {
}

BarrierOptionDownOut::BarrierOptionDownOut(const unique_ptr<Payoff> &payoff_,
		const double T_, const double r_) :
		BarrierOption(payoff_, T_, r_) {
}

// Arithmetic mean pay-off price
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
		BarrierOption(payoff_, T_, r_) {
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

