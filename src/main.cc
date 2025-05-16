// This file is a prototype.

#include "units.hh"
#include <algorithm>

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
	displaced_by(vector2d const &displacement_vector) const noexcept
		-> point2d
	{
		return point2d{ x() + displacement_vector.x(),
				y() + displacement_vector.y() };
	}
};

namespace constants
{
constexpr point2d origin = point2d(0.0_m, 0.0_m);
}

struct entity {
	explicit constexpr entity(point2d const &position)
		: position_(position)
	{
	}

	explicit constexpr entity()
		: entity(constants::origin)
	{
	}

	[[nodiscard]] constexpr auto
	distance_to(entity const &other) const noexcept
		-> units::length::meter_t
	{
		return position_.distance_to(other.position_);
	}

	constexpr auto displace_by(vector2d const &displacement_vector) noexcept
		-> void
	{
		this->position_ = position_.displaced_by(displacement_vector);
	}

	[[nodiscard]] constexpr auto position() const noexcept -> point2d
	{
		return position_;
	}

    private:
	point2d position_;
};

struct living_entity : virtual public entity {
	explicit living_entity(double max_health) noexcept
		: max_health_(max_health),
		  health_(max_health),
		  level_(1)
	{
	}

	[[nodiscard]] auto is_dead() const noexcept -> bool
	{
		return health_ <= 0.0;
	}

	[[nodiscard]] auto is_alive() const noexcept -> bool
	{
		return !is_dead();
	}

	auto heal(double amount) noexcept -> void
	{
		health_ = std::clamp(health_ + amount, 0.0, max_health_);
	}

	auto hurt(double amount) noexcept -> void
	{
		health_ = std::clamp(health_ - amount,
				     -std::numeric_limits<double>::infinity(),
				     max_health_);
	}

	virtual auto on_hurt(living_entity &other, double amount) noexcept
		-> void = 0;

    private:
	double max_health_;
	double health_;
	int level_;
};

struct tool {
	[[nodiscard]] virtual constexpr auto
	can_use_on(living_entity const &user,
		   living_entity const &target) const noexcept -> bool = 0;

	[[nodiscard]] virtual constexpr auto
	can_use_on(living_entity const &user,
		   point2d const &target) const noexcept -> bool = 0;

	virtual constexpr auto use(living_entity &user,
				   living_entity &target) noexcept -> void = 0;

	virtual constexpr auto use(living_entity &user,
				   point2d &position) noexcept -> void = 0;
};

auto main() -> int
{
	return 0;
}
