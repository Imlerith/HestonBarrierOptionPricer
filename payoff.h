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
protected:
	double K;

public:
	Payoff(const double &K_);

	virtual ~Payoff() {
	}

	virtual double operator()(const double &S_T,
			function<bool(const double&)> &cond) const = 0;
};

class PayoffAsianCall: public Payoff {
private:
	double K;

public:
	PayoffAsianCall(const double &K_);
	virtual ~PayoffAsianCall() {
	}

	virtual double operator()(const double &S_T,
			function<bool(const double&)> &cond) const;
};

class PayoffAsianPut: public Payoff {
private:
	double K;

public:
	PayoffAsianPut(const double &K_);
	virtual ~PayoffAsianPut() {
	}

	virtual double operator()(const double &S_T,
			function<bool(const double&)> &cond) const;
};

class PayoffBarrierCall: public Payoff {
private:
	double B;

public:
	PayoffBarrierCall(const double &K_, const double &B_);
	virtual ~PayoffBarrierCall() {
	}

	virtual double operator()(const double &S_T,
			function<bool(const double&)> &cond) const;
};

class PayoffBarrierPut: public Payoff {
private:
	double B;
	function<bool(const double&)> cond;

public:
	PayoffBarrierPut(const double &K_, const double &B_);
	virtual ~PayoffBarrierPut() {
	}

	virtual double operator()(const double &S_T,
			function<bool(const double&)> &cond) const;
};

#endif /* PAYOFF_H_ */
