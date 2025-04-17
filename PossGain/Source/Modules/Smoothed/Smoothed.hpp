#pragma once

#include <array>
#include <cstddef>

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
