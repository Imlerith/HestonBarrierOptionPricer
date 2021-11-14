/*
 * option.h
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#ifndef OPTION_H_
#define OPTION_H_

#pragma once

#include <vector>
#include "payoff.h"

class BarrierOption {
protected:
	const unique_ptr<Payoff> &payoff;
	const double T;
	const double r;

public:
	BarrierOption(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~BarrierOption() {
	}

	// pure virtual payoff operator
	virtual double payoff_price(const vector<double> &spot_prices) const = 0;

public:
	double get_T() const {
		return T;
	}
	int get_r() const {
		return r;
	}
};

class BarrierOptionDownOut: public BarrierOption {
public:
	BarrierOptionDownOut(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~BarrierOptionDownOut() {
	}

	// override the pure virtual operator
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

class BarrierOptionUpOut: public BarrierOption {
public:
	BarrierOptionUpOut(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~BarrierOptionUpOut() {
	}

	// override the pure virtual operator
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

#endif /* OPTION_H_ */
