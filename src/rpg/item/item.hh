#pragma once

#include "rpg/math/cartesian2d.hh"

namespace rpg
{

struct entity;

struct item {
	[[nodiscard]] virtual constexpr auto
	can_be_used_on(entity const &user, entity const &target) const noexcept
		-> bool = 0;

	[[nodiscard]] virtual constexpr auto
	can_be_used_on(entity const &user,
		       math::point2d const &target) const noexcept -> bool = 0;

	virtual constexpr auto use(entity &user, entity &target) noexcept
		-> void = 0;

	virtual constexpr auto use(entity &user,
				   math::point2d &position) noexcept
		-> void = 0;
};

}
