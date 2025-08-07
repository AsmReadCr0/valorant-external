#ifndef RADAR_HPP
#define RADAR_HPP

class c_radar
{
private:

public:

	void draw_radar();
	void range_to(float* x, float* y, float range);
	uemath::fvector2d calculate_radar_point(uemath::fvector camera_location, uemath::fvector origin);
	void add_radar(uemath::fvector camera_location, uemath::flinearcolor color, std::string distance);
};

inline const auto radar = std::make_unique<c_radar>();

#endif