/*
 * payoff.cpp
 *
 *  Created on: 10 Nov 2021
 *      Author: sergeynasekin
 */

#include "payoff.h"

Payoff::Payoff(const double &K_) {
	K = K_;
}

PayoffAsianCall::PayoffAsianCall(const double &K_) :
		Payoff(K_) {
	K = K_;
}

PayoffAsianPut::PayoffAsianPut(const double &K_) :
		Payoff(K_) {
	K = K_;

}

PayoffBarrierCall::PayoffBarrierCall(const double &K_, const double &B_) :
		Payoff(K_) {
	B = B_;
}

PayoffBarrierPut::PayoffBarrierPut(const double &K_, const double &B_) :
		Payoff(K_) {
	B = B_;
}

double PayoffAsianCall::operator ()(const double &S_T,
		function<bool(const double&)> &cond) const {
	return max(S_T - K, 0.0);
}

double PayoffAsianPut::operator ()(const double &S_T,
		function<bool(const double&)> &cond) const {
	return max(K - S_T, 0.0);
}

double PayoffBarrierCall::operator ()(const double &S_T,
		function<bool(const double&)> &cond) const {
	if (cond(B) == true) {
		return max(S_T - K, 0.0);
	} else {
		return 0.0;
	}
}

double PayoffBarrierPut::operator ()(const double &S_T,
		function<bool(const double&)> &cond) const {
	if (cond(B) == true) {
		return max(K - S_T, 0.0);
	} else {
		return 0.0;
	}
}

