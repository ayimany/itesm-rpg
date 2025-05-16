#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include "rpg/item/item.hh"

namespace rpg
{

struct entity {
	explicit entity(double max_health, uint16_t level)
		: max_health_(max_health)
		, health_(max_health)
		, level_(level)
	{
	}

	auto interact_with(entity &entity)
	{
		entity.when_interacted_with(*this);
	}

	virtual auto when_interacted_with(entity &other) -> void = 0;

	auto heal(double amount) -> void
	{
		health_ = std::clamp(health_ + amount, 0.0, max_health_);
		when_healed(amount);
	}

	virtual auto when_healed(double amount) -> void = 0;

	auto hurt(double amount) -> void
	{
		health_ = std::clamp(health_ - amount,
				     -std::numeric_limits<double>::infinity(),
				     max_health_);
		when_hurt(amount);
	}

	virtual auto when_hurt(double amount) -> void = 0;

	auto use_item_on(entity &other, item &item);

	auto use_item_on(math::point2d &position, item &item);

	[[nodiscard]] auto get_health() const -> double
	{
		return health_;
	}

	[[nodiscard]] auto is_alive() const -> double
	{
		return health_ >= 0.0;
	}

	[[nodiscard]] auto is_dead() const -> double
	{
		return !is_alive();
	}

    protected:
	double max_health_;
	double health_;
	uint16_t level_;
};

}
