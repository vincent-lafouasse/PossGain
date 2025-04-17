#pragma once

#include <array>
#include <cstddef>

// a 1 pole low pass filter that smoothes step functions
// of the form y[n] = beta * y[n - 1] + (1 - beta) * x[n]
// where ln(beta) = - cutoff_pulsation * sampling_period
//
template <typename FloatType, std::size_t N>
class Smoothed {
public:
	Smoothed();

	void setSampleRate(float sampleRate);

	void setTarget(FloatType target, std::size_t channel);
	void setTarget(FloatType target);

	FloatType get(std::size_t channel);
	FloatType get();

private:
	std::array<FloatType, N> memory;
	std::array<FloatType, N> targets;

	float sampleRate = 44100;
};
