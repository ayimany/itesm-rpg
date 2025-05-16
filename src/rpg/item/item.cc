#include "rpg/item/item.hh"

namespace rpg
{
breakable_item::breakable_item(double durability) noexcept
	: durability_(durability)
{
}

auto breakable_item::can_be_used() const noexcept -> bool
{
	return durability_ >= 0.0;
}

single_use_item::single_use_item()
	: has_been_used_(false)
{
}

auto single_use_item::can_be_used() const noexcept -> bool
{
	return !has_been_used_;
}

}
