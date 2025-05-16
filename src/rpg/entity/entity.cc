#include "rpg/entity/entity.hh"

namespace rpg
{

entity::entity(double max_health, uint16_t level)
	: max_health_(max_health)
	, health_(max_health)
	, level_(level)
{
}

auto entity::interact_with(entity &entity)
{
	entity.when_interacted_with(*this);
}

auto entity::heal(double amount) -> void
{
	health_ = std::clamp(health_ + amount, 0.0, max_health_);
	when_healed(amount);
}

auto entity::hurt(double amount) -> void
{
	health_ = std::clamp(health_ - amount,
			     -std::numeric_limits<double>::infinity(),
			     max_health_);
	when_hurt(amount);
}

auto use_item_on(entity &other, item &item);

auto use_item_on(math::point2d &position, item &item);

auto entity::get_health() const -> double
{
	return health_;
}

auto entity::is_alive() const -> double
{
	return health_ >= 0.0;
}

auto entity::is_dead() const -> double
{
	return !is_alive();
}

}
