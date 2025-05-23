#pragma once

#include "rpg/lib/units.hh"

namespace rpg::math
{

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

    protected:
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

struct grid2d : public cartesian2d {
	[[nodiscard]] constexpr auto get_width() const noexcept -> double;
};

struct point2d : public cartesian2d {
	explicit constexpr point2d(units::length::meter_t x_component,
				   units::length::meter_t y_component) noexcept
		: cartesian2d(x_component, y_component)
	{
	}

	[[nodiscard]] constexpr auto
	draw_vector_towards(point2d const &other) const noexcept -> vector2d
	{
		return vector2d{ other.x() - x(), other.y() - y() };
	}

	[[nodiscard]] constexpr auto
	squared_distance_to(point2d const &other) const noexcept
		-> units::area::square_meter_t
	{
		return draw_vector_towards(other).square_magnitude();
	}

	[[nodiscard]] constexpr auto
	distance_to(point2d const &other) const noexcept
		-> units::length::meter_t
	{
		return units::math::sqrt(squared_distance_to(other));
	}

	[[nodiscard]] constexpr auto
	translated_by(vector2d const &displacement_vector) const noexcept
		-> point2d
	{
		return point2d{ x() + displacement_vector.x(),
				y() + displacement_vector.y() };
	}
};

struct locatable2d {
	explicit constexpr locatable2d(point2d const &position)
		: position_(position)
	{
	}

	[[nodiscard]] constexpr auto
	distance_to(locatable2d const &other) const noexcept
		-> units::length::meter_t
	{
		return position_.distance_to(other.position_);
	}

	constexpr auto
	translate_by(math::vector2d const &displacement_vector) noexcept -> void
	{
		this->position_ = position_.translated_by(displacement_vector);
	}

	[[nodiscard]] constexpr auto position() const noexcept -> point2d
	{
		return position_;
	}

    protected:
	point2d position_;
};

namespace constants
{
constexpr point2d origin = point2d(0.0_m, 0.0_m);
}

}
