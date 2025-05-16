// This file is a prototype.

#include "units.hh"

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


auto main() -> int
{
	return 0;
}
