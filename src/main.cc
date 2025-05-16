// This file is a prototype.

#include "units.hh"
#include <algorithm>
#include <cstdint>
#include <vector>

// Only exposes literals
// Does not cause any identifiers to breach their namespaces
using namespace units::literals;

struct cartesian2d {
	explicit constexpr
	cartesian2d(units::length::meter_t x_component,
		    units::length::meter_t y_component) noexcept
		: x_(x_component),
		  y_(y_component)
	{
	}

	[[nodiscard]] constexpr auto x() const noexcept
		-> units::length::meter_t
	{
		return x_;
	}

	[[nodiscard]] constexpr auto y() const noexcept
		-> units::length::meter_t
	{
		return y_;
	}

	// This is on purpose.
	// I operate under encapsulation forbidding the use of protected fields
    private:
	units::length::meter_t x_;
	units::length::meter_t y_;
};

struct vector2d : public cartesian2d {
	explicit constexpr vector2d(units::length::meter_t x_component,
				    units::length::meter_t y_component) noexcept
		: cartesian2d(x_component, y_component)
	{
	}

	[[nodiscard]] constexpr auto square_magnitude() const noexcept
		-> units::area::square_meter_t
	{
		return units::math::pow<2>(x()) + units::math::pow<2>(y());
	}

	[[nodiscard]] constexpr auto magnitude() const noexcept
		-> units::length::meter_t
	{
		return units::math::sqrt(square_magnitude());
	}
};


auto main() -> int
{
	return 0;
}
