#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

using draw_flag = enum
{
	null,
	exe,
	end_frame
};

using request = enum {
	m_endframe,
	m_rectangle,
	m_reloadbar,
	m_fill_rect,
	m_line,
	m_circle,
	m_text,
	m_boundingbox,
	m_boundingcorner,
	m_icon
};

typedef enum font_weight {
	m_filler,
	m_normal,
	m_medium,
	m_bold
};

typedef enum icon_holder {
	m_logo_icon,
	m_eye_icon,
	m_crosshair_icon,
	m_box_icon,
	m_sparkle_icon,
	m_pallet_icon,
	m_gear_icon,
	m_logo_first,
	m_logo_second
};

using vec2 = struct {
	float x, y;
};

using rect_t = struct {
	float x, y, height, width;
};

using rectangle_t = struct {

	rect_t object;
	uemath::flinearcolor color;
	vec2 radius;
	bool rounded;

};

using bounding_t = struct {
	float left, right, top, bottom;
	uemath::flinearcolor color;
	bool rounded;
};

using line_t = struct {
	vec2 point1, point2;
	uemath::flinearcolor color;
	float stroke;
};

using icon_t = struct {
	vec2 point;
	uemath::flinearcolor color;
	float fontSize;
	int icon;
};

using circle_t = struct {
	vec2 point;
	float radius;
	uemath::flinearcolor color;
	float stroke;
	bool filled;
};

using reload_t = struct {
	rect_t object;
	uemath::flinearcolor color;
	float time_total;
};

using text_t = struct {
	std::uint32_t text_length;
	std::string input1;
	std::string input2;
	vec2 point;
	uemath::flinearcolor color;
	float fontSize;
	bool center;
	bool menu;
	int weight;
};

using invoke_data = struct {

	request code;

	text_t text;
	line_t line;
	circle_t circle;
	rectangle_t rectangle;
	reload_t reload;
};

using draw_array = struct {

	draw_flag flag;
	std::uint32_t count; 
	invoke_data data[ 0 ]; // [ 1 ];
};

class c_framework {

public:

	//c_framework( ) {

	//	auto buffer = malloc( 0xF4240 );
	//	if ( !buffer ) {
	//		std::printf( " [buffer] -> invalid.\n" );
	//	}

	//	ZeroMemory( buffer, 0xF4240 );
	//	object = reinterpret_cast< draw_array* >( buffer );

	//};

	explicit c_framework( ) { };

	// test
	void initializer( );

	[[nodiscard]] uemath::flinearcolor get_color( std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a = 255 );

	[[nodiscard]] bool send_cmd( draw_array* data, request code );

	void end_scene( );
	void begin_scene( );
	void release( );

	void icon( int icon, float x, float y, uemath::flinearcolor color, float fontSize );
	void bounding_box( float left, float right, float top, float bottom, uemath::flinearcolor color );
	void bounding_corner( const uemath::fvector& position, const uemath::fvector& size, uemath::flinearcolor color );
	void text( const std::string& input, float x, float y, uemath::flinearcolor color, float fontSize, bool center, int weight = 1, bool menu = false );
	void rect( float x, float y, float width, float height, uemath::flinearcolor color, bool rounded = false, float _x = 0, float _y = 0 );
	void reload_bar(float x, float y, float width, float height, float time_total, uemath::flinearcolor color);
	void filled_rect( float x, float y, float width, float height, uemath::flinearcolor color, bool rounded = false, float _x = 0, float _y = 0 );
	void line( float x1, float y1, float x2, float y2, uemath::flinearcolor color, float stroke = 1.0f );
	void circle( float x, float y, float radius, uemath::flinearcolor color, float stroke, bool filled = false );

	void crosshair( );
	void fov( );
	void index_color(int team_index, uemath::flinearcolor& name_index);

	draw_array* object = nullptr;
	std::uint32_t index = 0;

}; inline auto framework = std::make_unique<c_framework>( );

#endif