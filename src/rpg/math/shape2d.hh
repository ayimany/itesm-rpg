#pragma once

#include "rpg/math/cartesian2d.hh"

namespace rpg::math
{
struct shape2d : public locatable2d {
	explicit constexpr shape2d(point2d const &position)
		: locatable2d(position)
	{
	}

	[[nodiscard]] constexpr virtual auto
	contains(point2d const &point) const noexcept -> bool = 0;
};

struct circle : public shape2d {
	explicit constexpr circle(point2d const &center,
				  units::length::meter_t radius)
		: shape2d(center)
		, radius_(radius)
	{
	}

	[[nodiscard]] constexpr auto
	contains(const point2d &point) const noexcept -> bool override
	{
		return position_.squared_distance_to(point) <=
		       units::math::pow<2>(radius_);
	}

	[[nodiscard]] constexpr auto radius() const noexcept
		-> units::length::meter_t
	{
		return radius_;
	}

    private:
	units::length::meter_t radius_;
};

struct rectangle : public shape2d {
	explicit constexpr rectangle(point2d const &center,
				     units::length::meter_t width,
				     units::length::meter_t height)
		: shape2d(center)
		, width_(width)
		, height_(height)
	{
	}

	auto contains(const point2d &point) const noexcept -> bool override
	{
		point2d top_right = top_right_corner();
		point2d bottom_left = top_left_corner();

		bool within_horizontal_bounds = (point.x() > bottom_left.x() &&
						 point.x() < top_right.x());

		bool within_vertical_bounds = (point.y() > bottom_left.y() &&
					       point.y() < top_right.y());

		return within_horizontal_bounds && within_vertical_bounds;
	}

	[[nodiscard]] constexpr auto top_right_corner() const noexcept
		-> point2d
	{
		return position_.translated_by(
			vector2d{ width_ / 2.0, height_ / 2.0 });
	}

	[[nodiscard]] constexpr auto top_left_corner() const noexcept -> point2d
	{
		return position_.translated_by(
			vector2d{ width_ / -2.0, height_ / 2.0 });
	}

	[[nodiscard]] constexpr auto bottom_left_corner() const noexcept
		-> point2d
	{
		return position_.translated_by(
			vector2d{ width_ / -2.0, height_ / -2.0 });
	}

	[[nodiscard]] constexpr auto bottom_right_corner() const noexcept
		-> point2d
	{
		return position_.translated_by(
			vector2d{ width_ / 2.0, height_ / -2.0 });
	}

	[[nodiscard]] constexpr auto width() const noexcept
		-> units::length::meter_t
	{
		return width_;
	}

	[[nodiscard]] constexpr auto height() const noexcept
		-> units::length::meter_t
	{
		return height_;
	}

    private:
	units::length::meter_t width_;
	units::length::meter_t height_;
};

}
