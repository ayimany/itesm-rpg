#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include "rpg/item/item.hh"

namespace rpg
{

struct entity {
	explicit entity(double max_health, uint16_t level);

	auto heal(double amount) -> void;

	virtual auto when_healed(double amount) -> void = 0;

	auto hurt(double amount) -> void;

	virtual auto when_hurt(double amount) -> void = 0;

	[[nodiscard]] auto get_health() const -> double;

	[[nodiscard]] auto is_alive() const -> double;

	[[nodiscard]] auto is_dead() const -> double;

	auto interact_with(entity &entity);

	auto interact_with(entity &other, item &item);

	auto interact_with(math::point2d &position, item &item);

	virtual auto when_interacted_with(entity &other) -> void = 0;

	virtual auto when_interacted_with(entity &other, item &item)
		-> void = 0;

    protected:
	double max_health_;
	double health_;
	uint16_t level_;
};

}
