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

class Option {
protected:
	const unique_ptr<Payoff> &payoff;
	const double T;
	const double r;

public:
	Option(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~Option() {
	}

	// pure virtual payoff function
	virtual double payoff_price(const vector<double> &spot_prices) const = 0;

public:
	double get_T() const {
		return T;
	}

	int get_r() const {
		return r;
	}
};

class AsianOptionArithmetic: public Option {
public:
	AsianOptionArithmetic(const unique_ptr<Payoff>& payoff_, const double T_,
			const double r_);
	virtual ~AsianOptionArithmetic() {
	}

	// Override the pure virtual function to produce arithmetic Asian Options
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

class AsianOptionGeometric: public Option {
public:
	AsianOptionGeometric(const unique_ptr<Payoff>& payoff_, const double T_,
			const double r_);
	virtual ~AsianOptionGeometric() {
	}

	// Override the pure virtual function to produce geometric Asian Options
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

class BarrierOptionDownOut: public Option {
public:
	BarrierOptionDownOut(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~BarrierOptionDownOut() {
	}

	// override the pure virtual payoff function
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

class BarrierOptionUpOut: public Option {
public:
	BarrierOptionUpOut(const unique_ptr<Payoff> &payoff_, const double T_,
			const double r_);
	virtual ~BarrierOptionUpOut() {
	}

	// override the pure virtual payoff function
	virtual double payoff_price(const vector<double> &spot_prices) const;
};

#endif /* OPTION_H_ */
