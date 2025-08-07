#pragma once 
#include "../../inc.hpp"


float radar_width  = g_vars->radar.width;
float radar_height = g_vars->radar.height;
float radar_size   = g_vars->radar.size;

auto c_radar::draw_radar() -> void
{
	if (g_vars->radar.moveable)
	{
		uemath::fvector2d mouse_position = g_interface->get_cursor();
		bool left_mouse_down = (GetAsyncKeyState(VK_LBUTTON) & 0x8000);


		bool is_hovered = g_interface->is_hovered(uemath::fvector2d(radar_width, radar_height), uemath::fvector2d(radar_size, radar_size));

		if (is_hovered && left_mouse_down) {
			radar_width = mouse_position.x - radar_size / 2;
			radar_height = mouse_position.y - radar_size / 2;
		}
	}

	uemath::fvector2d center = uemath::fvector2d(radar_width + radar_size / 2, radar_height + radar_size / 2);

	framework->filled_rect(radar_width, radar_height, radar_size, radar_size, uemath::flinearcolor(150, 45, 45, 45), false, 0, 0);
	framework->rect(radar_width, radar_height, radar_size, radar_size, uemath::flinearcolor(255, 25, 25, 25), false, 0, 0);
	framework->line(center.x, radar_height, center.x, radar_height + radar_size, uemath::flinearcolor(255, 25, 25, 25));
	framework->line(radar_width, center.y, radar_width + radar_size, center.y, uemath::flinearcolor(255, 25, 25, 25));

	if (g_vars->radar.line)
	{
		framework->filled_rect(radar_width, radar_height, radar_size, 3, uemath::flinearcolor(255, 235, 52, 52), false, 0, 0);
	}
}

auto c_radar::range_to(float* x, float* y, float range) -> void
{
	if (abs((*x)) > range || abs((*y)) > range)
	{
		if ((*y) > (*x))
		{
			if ((*y) > -(*x))
			{
				(*x) = range * (*x) / (*y);
				(*y) = range;
			}
			else
			{
				(*y) = -range * (*y) / (*x);
				(*x) = -range;
			}
		}
		else
		{
			if ((*y) > -(*x))
			{
				(*y) = range * (*y) / (*x);
				(*x) = range;
			}
			else
			{
				(*x) = -range * (*x) / (*y);
				(*y) = -range;
			}
		}
	}
}


auto c_radar::calculate_radar_point(uemath::fvector camera_location, uemath::fvector origin) -> uemath::fvector2d
{
	auto dx = origin.x - camera_location.x;
	auto dy = origin.y - camera_location.y;

	auto x = dy * -1;
	x *= -1;
	auto y = dx * -1;


	float calcualted_range = 35.f * 1000;

	this->range_to(&x, &y, calcualted_range);

	int rad_x = (int)radar_width;
	int rad_y = (int)radar_height;

	float r_siz_x = radar_size;
	float r_siz_y = radar_size;

	int x_max = (int)r_siz_x + rad_x - 5;
	int y_max = (int)r_siz_y + rad_y - 5;

	auto return_value = uemath::fvector2d();

	return_value.x = rad_x + ((int)r_siz_x / 2 + int(x / calcualted_range * r_siz_x));
	return_value.y = rad_y + ((int)r_siz_y / 2 + int(y / calcualted_range * r_siz_y));

	if (return_value.x > x_max)
		return_value.x = x_max;

	if (return_value.x < rad_x)
		return_value.x = rad_x;

	if (return_value.y > y_max)
		return_value.y = y_max;

	if (return_value.y < rad_y)
		return_value.y = rad_y;

	return return_value;
}

auto c_radar::add_radar(uemath::fvector origin, uemath::flinearcolor color, std::string distance) -> void
{
	auto projected = this->calculate_radar_point(engine->location, origin);

	framework->text(distance.c_str(), projected.x, projected.y + 3, uemath::flinearcolor(255, 255, 255, 255), 13, false, 1, true);

	framework->circle(projected.x, projected.y, 4, color, 50, true);
}