/*
 * payoff.cpp
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#include "payoff.h"

Payoff::Payoff() {
}

PayoffCall::PayoffCall(const double &K_, const double &B_) {
	K = K_;
	B = B_;
}

double PayoffCall::operator ()(const double &S,
		function<bool(const double&)> &cond) const {
	if (cond(B) == true) {
		return max(S - K, 0.0);
	} else {
		return 0.0;
	}
}

PayoffPut::PayoffPut(const double &K_, const double &B_) {
	K = K_;
	B = B_;
}

double PayoffPut::operator ()(const double &S,
		function<bool(const double&)> &cond) const {
	if (cond(B) == true) {
		return max(K - S, 0.0);
	} else {
		return 0.0;
	}
}

