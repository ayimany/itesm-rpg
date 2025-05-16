#pragma once

#include "rpg/math/cartesian2d.hh"

namespace rpg
{

struct entity;

struct item {
	[[nodiscard]] virtual constexpr auto can_be_used() const -> bool;

	[[nodiscard]] virtual constexpr auto
	can_be_used_on(entity const &user, entity const &target) const
		-> bool = 0;

	[[nodiscard]] virtual constexpr auto
	can_be_used_on(entity const &user, math::point2d const &target) const
		-> bool = 0;

	virtual constexpr auto when_used(entity &user, entity &target)
		-> void = 0;

	virtual constexpr auto when_used(entity &user, math::point2d &position)
		-> void = 0;
};

struct breakable_item : virtual public item {
	explicit breakable_item(double durability) noexcept;

	auto can_be_used() const noexcept -> bool override;

    private:
	double durability_;
};

struct single_use_item : virtual public item {
	explicit single_use_item();

	auto can_be_used() const noexcept -> bool override;

    private:
	bool has_been_used_;
};

}
