#pragma once 
#include "../../core/inc.hpp"

auto c_framework::get_color( std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a ) -> uemath::flinearcolor {

	return uemath::flinearcolor { 
		static_cast< std::int8_t >( a ),
		static_cast< std::int8_t >( r ),
		static_cast< std::int8_t >( g ),
		static_cast< std::int8_t >( b )
	};

}

auto c_framework::crosshair( ) -> void
{
	this->line(
		engine->m_width_2 - 5,
		engine->m_height_2,
		engine->m_width_2 + 5,
		engine->m_height_2,
		this->get_color( 255, 255, 255, 255 )
	);

	this->line(
		engine->m_width_2,
		engine->m_height_2 - 5,
		engine->m_width_2,
		engine->m_height_2 + 5,
		this->get_color( 255, 255, 255, 255 )
	);
}

auto c_framework::fov( ) -> void
{
	this->circle(
		engine->m_width_2, engine->m_height_2,
		g_vars->aim.fov_c,
		this->get_color( 255, 255, 255, 255 ),
		1.f
	);
}

auto c_framework::index_color(int team_index, uemath::flinearcolor& name_index) -> void
{
	switch (team_index) {
	case 1:   name_index = uemath::flinearcolor(255, 0, 0, 0);    break; // Red
	case 2:   name_index = uemath::flinearcolor(255, 0, 0, 85);   break; // Dark Red
	case 3:   name_index = uemath::flinearcolor(255, 0, 0, 170);  break; // Maroon
	case 4:   name_index = uemath::flinearcolor(255, 0, 0, 255);  break; // Deep Maroon
	case 5:   name_index = uemath::flinearcolor(255, 0, 85, 0);   break; // Dark Green
	case 6:   name_index = uemath::flinearcolor(255, 0, 85, 85);  break; // Forest Green
	case 7:   name_index = uemath::flinearcolor(255, 0, 85, 170); break; // Dark Cyan
	case 8:   name_index = uemath::flinearcolor(255, 0, 85, 255); break; // Teal
	case 9:   name_index = uemath::flinearcolor(255, 0, 170, 0);  break; // Green
	case 10:  name_index = uemath::flinearcolor(255, 0, 170, 85); break; // Light Teal
	case 11:  name_index = uemath::flinearcolor(255, 0, 170, 170); break; // Aqua
	case 12:  name_index = uemath::flinearcolor(255, 0, 170, 255); break; // Sky Blue
	case 13:  name_index = uemath::flinearcolor(255, 0, 255, 0);  break; // Lime Green
	case 14:  name_index = uemath::flinearcolor(255, 0, 255, 85); break; // Spring Green
	case 15:  name_index = uemath::flinearcolor(255, 0, 255, 170); break; // Turquoise
	case 16:  name_index = uemath::flinearcolor(255, 0, 255, 255); break; // Cyan
	case 17:  name_index = uemath::flinearcolor(255, 85, 0, 0);   break; // Dark Maroon
	case 18:  name_index = uemath::flinearcolor(255, 85, 0, 85);  break; // Brown
	case 19:  name_index = uemath::flinearcolor(255, 85, 0, 170); break; // Deep Pink
	case 20:  name_index = uemath::flinearcolor(255, 85, 0, 255); break; // Fuchsia
	case 21:  name_index = uemath::flinearcolor(255, 85, 85, 0);   break; // Olive
	case 22:  name_index = uemath::flinearcolor(255, 85, 85, 85);  break; // Dark Olive
	case 23:  name_index = uemath::flinearcolor(255, 85, 85, 170); break; // Olive Drab
	case 24:  name_index = uemath::flinearcolor(255, 85, 85, 255); break; // Light Purple
	case 25:  name_index = uemath::flinearcolor(255, 85, 170, 0);  break; // Goldenrod
	case 26:  name_index = uemath::flinearcolor(255, 85, 170, 85); break; // Tan
	case 27:  name_index = uemath::flinearcolor(255, 85, 170, 170); break; // Peach
	case 28:  name_index = uemath::flinearcolor(255, 85, 170, 255); break; // Salmon
	case 29:  name_index = uemath::flinearcolor(255, 85, 255, 0);  break; // Chartreuse
	case 30:  name_index = uemath::flinearcolor(255, 85, 255, 85); break; // Light Chartreuse
	case 31:  name_index = uemath::flinearcolor(255, 85, 255, 170); break; // Spring Chartreuse
	case 32:  name_index = uemath::flinearcolor(255, 85, 255, 255); break; // Light Cyan
	case 33:  name_index = uemath::flinearcolor(255, 170, 0, 0);   break; // Dark Pink
	case 34:  name_index = uemath::flinearcolor(255, 170, 0, 85);  break; // Rosy Brown
	case 35:  name_index = uemath::flinearcolor(255, 170, 0, 170); break; // Purple
	case 36:  name_index = uemath::flinearcolor(255, 170, 0, 255); break; // Light Purple
	case 37:  name_index = uemath::flinearcolor(255, 170, 85, 0);  break; // Dark Khaki
	case 38:  name_index = uemath::flinearcolor(255, 170, 85, 85); break; // Khaki
	case 39:  name_index = uemath::flinearcolor(255, 170, 85, 170); break; // Light Salmon
	case 40:  name_index = uemath::flinearcolor(255, 170, 85, 255); break; // Light Pink
	case 41:  name_index = uemath::flinearcolor(255, 170, 170, 0);  break; // Yellow
	case 42:  name_index = uemath::flinearcolor(255, 170, 170, 85); break; // Light Yellow
	case 43:  name_index = uemath::flinearcolor(255, 170, 170, 170); break; // Light Grey
	case 44:  name_index = uemath::flinearcolor(255, 170, 170, 255); break; // White Smoke
	case 45:  name_index = uemath::flinearcolor(255, 170, 255, 0);  break; // Beige
	case 46:  name_index = uemath::flinearcolor(255, 170, 255, 85); break; // Light Beige
	case 47:  name_index = uemath::flinearcolor(255, 170, 255, 170); break; // Seashell
	case 48:  name_index = uemath::flinearcolor(255, 170, 255, 255); break; // Snow
	case 49:  name_index = uemath::flinearcolor(255, 255, 0, 0);   break; // Red
	case 50:  name_index = uemath::flinearcolor(255, 255, 0, 85);  break; // Light Red
	case 51:  name_index = uemath::flinearcolor(255, 255, 0, 170); break; // Pink
	case 52:  name_index = uemath::flinearcolor(255, 255, 0, 255); break; // Light Pink
	case 53:  name_index = uemath::flinearcolor(255, 255, 85, 0);  break; // Dark Orange
	case 54:  name_index = uemath::flinearcolor(255, 255, 85, 85); break; // Orange
	case 55:  name_index = uemath::flinearcolor(255, 255, 85, 170); break; // Light Orange
	case 56:  name_index = uemath::flinearcolor(255, 255, 85, 255); break; // Peach
	case 57:  name_index = uemath::flinearcolor(255, 255, 170, 0);  break; // Dark Yellow
	case 58:  name_index = uemath::flinearcolor(255, 255, 170, 85); break; // Gold
	case 59:  name_index = uemath::flinearcolor(255, 255, 170, 170); break; // Light Gold
	case 60:  name_index = uemath::flinearcolor(255, 255, 170, 255); break; // Lemon
	case 61:  name_index = uemath::flinearcolor(255, 255, 255, 0);  break; // Yellow
	case 62:  name_index = uemath::flinearcolor(255, 255, 255, 85); break; // Light Yellow
	case 63:  name_index = uemath::flinearcolor(255, 255, 255, 170); break; // Cream
	case 64:  name_index = uemath::flinearcolor(255, 255, 255, 255); break; // White
	case 65:  name_index = uemath::flinearcolor(255, 0, 0, 0);    break; // Red
	case 66:  name_index = uemath::flinearcolor(255, 0, 0, 85);   break; // Dark Red
	case 67:  name_index = uemath::flinearcolor(255, 0, 0, 170);  break; // Maroon
	case 68:  name_index = uemath::flinearcolor(255, 0, 0, 255);  break; // Deep Maroon
	case 69:  name_index = uemath::flinearcolor(255, 0, 85, 0);   break; // Dark Green
	case 70:  name_index = uemath::flinearcolor(255, 0, 85, 85);  break; // Forest Green
	case 71:  name_index = uemath::flinearcolor(255, 0, 85, 170); break; // Dark Cyan
	case 72:  name_index = uemath::flinearcolor(255, 0, 85, 255); break; // Teal
	case 73:  name_index = uemath::flinearcolor(255, 0, 170, 0);  break; // Green
	case 74:  name_index = uemath::flinearcolor(255, 0, 170, 85); break; // Light Teal
	case 75:  name_index = uemath::flinearcolor(255, 0, 170, 170); break; // Aqua
	case 76:  name_index = uemath::flinearcolor(255, 0, 170, 255); break; // Sky Blue
	case 77:  name_index = uemath::flinearcolor(255, 0, 255, 0);  break; // Lime Green
	case 78:  name_index = uemath::flinearcolor(255, 0, 255, 85); break; // Spring Green
	case 79:  name_index = uemath::flinearcolor(255, 0, 255, 170); break; // Turquoise
	case 80:  name_index = uemath::flinearcolor(255, 0, 255, 255); break; // Cyan
	case 81:  name_index = uemath::flinearcolor(255, 85, 0, 0);   break; // Dark Maroon
	case 82:  name_index = uemath::flinearcolor(255, 85, 0, 85);  break; // Brown
	case 83:  name_index = uemath::flinearcolor(255, 85, 0, 170); break; // Deep Pink
	case 84:  name_index = uemath::flinearcolor(255, 85, 0, 255); break; // Fuchsia
	case 85:  name_index = uemath::flinearcolor(255, 85, 85, 0);   break; // Olive
	case 86:  name_index = uemath::flinearcolor(255, 85, 85, 85);  break; // Dark Olive
	case 87:  name_index = uemath::flinearcolor(255, 85, 85, 170); break; // Olive Drab
	case 88:  name_index = uemath::flinearcolor(255, 85, 85, 255); break; // Light Purple
	case 89:  name_index = uemath::flinearcolor(255, 85, 170, 0);  break; // Goldenrod
	case 90:  name_index = uemath::flinearcolor(255, 85, 170, 85); break; // Tan
	case 91:  name_index = uemath::flinearcolor(255, 85, 170, 170); break; // Peach
	case 92:  name_index = uemath::flinearcolor(255, 85, 170, 255); break; // Salmon
	case 93:  name_index = uemath::flinearcolor(255, 85, 255, 0);  break; // Chartreuse
	case 94:  name_index = uemath::flinearcolor(255, 85, 255, 85); break; // Light Chartreuse
	case 95:  name_index = uemath::flinearcolor(255, 85, 255, 170); break; // Spring Chartreuse
	case 96:  name_index = uemath::flinearcolor(255, 85, 255, 255); break; // Light Cyan
	case 97:  name_index = uemath::flinearcolor(255, 170, 0, 0);   break; // Dark Pink
	case 98:  name_index = uemath::flinearcolor(255, 170, 0, 85);  break; // Rosy Brown
	case 99:  name_index = uemath::flinearcolor(255, 170, 0, 170); break; // Purple
	case 100: name_index = uemath::flinearcolor(255, 170, 0, 255); break; // Light Purple
	}
}


void c_framework::icon(
	int icon,
	float x,
	float y,
	uemath::flinearcolor color,
	float fontSize ) {

	//auto object = icon_t { vec2{ x,y }, color, fontSize, icon };
	//auto object_id = request::m_icon;

	//ipc.get( )->insert_object(
	//	&object_id,
	//	sizeof( std::uint8_t )
	//);

	//ipc.get( )->insert_object(

	//	&object,
	//	sizeof( icon_t )
	//);
}


void c_framework::bounding_box( float left,float right,float top,float bottom,uemath::flinearcolor color ) {

	//auto object = bounding_t { left,right,top,bottom,color };
	//auto object_id = request::m_boundingbox;

	//ipc.get( )->insert_object(
	//	&object_id,
	//	sizeof( std::uint8_t )
	//);

	//ipc.get( )->insert_object(

	//	&object,
	//	sizeof( bounding_t )
	//);

}

void c_framework::text(
	const std::string& input,
	float x,
	float y,
	uemath::flinearcolor color,
	float fontSize,
	bool center,
	int weight,
	bool menu) {

	this->index++;
	invoke_data args{ };

	args.code = request::m_text;

	size_t halfSize = input.length() / 2;
	std::string input1 = input.substr(0, halfSize);
	std::string input2 = input.substr(halfSize);

	args.text.text_length = input1.length();
	args.text.input1 = std::move(input1);
	args.text.input2 = std::move(input2);

	args.text.point.x = x;
	args.text.point.y = y;

	args.text.color = color;
	args.text.fontSize = fontSize;

	std::memcpy(&object->data[this->index - 1], &args, sizeof(args));
}

/* ignore above */

void c_framework::line( float x1, float y1, float x2, float y2, uemath::flinearcolor color, float stroke ) {

	this->index++;
	invoke_data args { };

	args.code = request::m_line;

	args.line.point1.x = x1;
	args.line.point1.y = y1;

	args.line.point2.x = x2;
	args.line.point2.y = y2;

	args.line.color = color;
	args.line.stroke = stroke;

	std::memcpy( &object->data[ this->index - 1 ], &args, sizeof( args ) );

}

void c_framework::bounding_corner( const uemath::fvector& position, const uemath::fvector& size, uemath::flinearcolor color ) {

	//auto object = bounding_t { left,right,top,bottom,color };
	//auto object_id = request::m_boundingcorner;

	//ipc.get( )->insert_object(
	//	&object_id,
	//	sizeof( std::uint8_t )
	//);

	//ipc.get( )->insert_object(

	//	&object,
	//	sizeof( bounding_t )
	//);

	this->index++;
	invoke_data args { };

	args.code = request::m_boundingcorner;

	args.rectangle.object.x = position.x;
	args.rectangle.object.y = position.y;

	args.rectangle.object.width = size.x;
	args.rectangle.object.height = size.y;

	args.rectangle.color = color;

	std::memcpy( &object->data[ this->index - 1 ], &args, sizeof( args ) );
}

void c_framework::rect(
	float x,
	float y,
	float width,
	float height,
	uemath::flinearcolor color,
	bool rounded,
	float _x,
	float _y ) {

	this->index++;
	invoke_data args { };

	args.code = request::m_rectangle;

	args.rectangle.object.x = x;
	args.rectangle.object.y = y;

	args.rectangle.object.width = width;
	args.rectangle.object.height = height;

	args.rectangle.color = color;

	std::memcpy( &object->data[ this->index - 1 ], &args, sizeof( args ) );

}

void c_framework::reload_bar(
	float x,
	float y,
	float width,
	float height,
	float time_total,
	uemath::flinearcolor color ) {

	this->index++;
	invoke_data args{ };

	args.code = request::m_reloadbar;

	args.reload.object.x = x;
	args.reload.object.y = y;

	args.reload.object.width = width;
	args.reload.object.height = height;

	args.reload.color = color;

	args.reload.time_total = time_total;

	std::memcpy(&object->data[this->index - 1], &args, sizeof(args));

}

void c_framework::filled_rect(
	float x,
	float y,
	float width,
	float height,
	uemath::flinearcolor color,
	bool rounded,
	float _x,
	float _y ) {

	this->index++;
	invoke_data args { };

	args.code = request::m_fill_rect;

	args.rectangle.object.x = x;
	args.rectangle.object.y = y;

	args.rectangle.object.width = width;
	args.rectangle.object.height = height;

	args.rectangle.color = color;


	std::memcpy( &object->data[ this->index - 1 ], &args, sizeof( args ) );

}

void c_framework::circle( float x, float y, float radius, uemath::flinearcolor color, float stroke, bool filled ) {

	this->index++;
	invoke_data args { };

	args.code = request::m_circle;

	args.circle.point.x = x;
	args.circle.point.y = y;

	args.circle.radius = radius;
	args.circle.stroke = stroke;
	args.circle.color  = color;
	args.circle.filled = filled;


	std::memcpy( &object->data[ this->index - 1 ], &args, sizeof( args ) );

}

bool c_framework::send_cmd( draw_array* data, request code )
{
	if ( !data )
		return false;

	return true;
}

auto c_framework::release( ) -> void {

	std::printf( " released.\n" );
	if ( object ) {
		free( object );
		object = nullptr;
	}
	return;
}

constexpr auto allocate = true;

auto c_framework::initializer( ) -> void
{
	if ( !ipc ) {
		std::printf( " [ipc] -> invalid.\n" );
		std::cin.get( );
	}

	if ( allocate ) {
		
		print_info( hash_str( "ipc allocated.\n" ) );
		auto buffer = malloc( 0xF4240 );
		if ( !buffer ) {
			std::printf( " [buffer] -> invalid.\n" );
			std::cin.get( );
		}

		ZeroMemory( buffer, 0xF4240 );

		this->object = reinterpret_cast< draw_array* >( buffer );
	}
	else
	{
		print_info( hash_str( "ipc aligned.\n" ) );
		this->object = reinterpret_cast< draw_array* >( ipc->buffer );
		ZeroMemory( this->object, sizeof( draw_array ) );
	}

	print_info( hash_str( "ipc->buffer: 0x%p\n" ), ipc->buffer );
	print_info( hash_str( "this->object: 0x%p\n" ), this->object );
}

auto c_framework::begin_scene( ) -> void {

	this->index = 0;
	object->count = std::move( this->index );

	//ipc->offset = offsetof( draw_array, flag );
	//object->flag = draw_flag::exe;

	//ipc->insert_object( 
	//	&object->flag, 
	//	sizeof( draw_flag ) 
	//);

}

auto c_framework::end_scene( ) -> void {

	object->count = std::move( this->index );

	if ( allocate ) {
		ipc->copy( object, 0xF4240 );
	}
	else {

		ipc->offset = offsetof( draw_array, count );

		ipc->insert_object(
			&object->count,
			sizeof( std::uint32_t )
		);

		// fix 
		Sleep( 1 );

	}

	//if ( allocate ) {
	//	this->release( );
	//}

	object->count = this->index = 0;

	//ipc->offset = offsetof( draw_array, flag );
	//object->flag = draw_flag::end_frame;

	//ipc->insert_object(
	//	&object->flag,
	//	sizeof( draw_flag )
	//);
}