// This file is a prototype.

#include <algorithm>

#include "cartesian2d.hh"

namespace rpg
{

struct entity {
	explicit constexpr entity(math::point2d const &position)
		: position_(position)
	{
	}

	explicit constexpr entity()
		: entity(math::constants::origin)
	{
	}

	[[nodiscard]] constexpr auto
	distance_to(entity const &other) const noexcept
		-> units::length::meter_t
	{
		return position_.distance_to(other.position_);
	}

	constexpr auto
	displace_by(math::vector2d const &displacement_vector) noexcept -> void
	{
		this->position_ = position_.displaced_by(displacement_vector);
	}

	[[nodiscard]] constexpr auto position() const noexcept -> math::point2d
	{
		return position_;
	}

    private:
	math::point2d position_;
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
		   math::point2d const &target) const noexcept -> bool = 0;

	virtual constexpr auto use(living_entity &user,
				   living_entity &target) noexcept -> void = 0;

	virtual constexpr auto use(living_entity &user,
				   math::point2d &position) noexcept
		-> void = 0;
};

}

auto main() -> int
{
	return 0;
}
