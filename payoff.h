/*
 * payoff.h
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#ifndef PAYOFF_H_
#define PAYOFF_H_

#pragma once

#include <algorithm>
#include <functional>

using namespace std;

class Payoff {
public:
	Payoff();
	virtual ~Payoff() {
	}

	virtual double operator()(const double &S,
			function<bool(const double&)> &cond) const = 0;
};

class PayoffCall: public Payoff {
private:
	double K;
	double B;

public:
	PayoffCall(const double &K_, const double &B_);
	virtual ~PayoffCall() {
	}

	virtual double operator()(const double &S,
			function<bool(const double&)> &cond) const;
};

class PayoffPut: public Payoff {
private:
	double K;
	double B;
	function<bool(const double&)> cond;

public:
	PayoffPut(const double &K_, const double &B_);
	virtual ~PayoffPut() {
	}

	virtual double operator()(const double &S,
			function<bool(const double&)> &cond) const;
};

#endif /* PAYOFF_H_ */
