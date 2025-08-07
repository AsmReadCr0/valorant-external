#pragma once 
#include "../../inc.hpp"

auto uengine::c_engine::in_screen(
	uemath::fvector bone ) -> bool {

	if ( bone.x > 0 && bone.x < this->m_width && bone.y > 0 && bone.y < this->m_height ) {
		return true;
	}
	else {
		return false;
	}
}

auto uengine::c_engine::is_shot(
	uemath::fvector lur, uemath::fvector wl ) -> bool {

	if ( lur.x >= wl.x - 20 && lur.x <= wl.x + 20 && lur.y >= wl.y - 20 && lur.y <= wl.y + 20 && lur.z >= wl.z - 30 && lur.z <= wl.z + 30 )
		return true;
	else
		return false;

}

auto uengine::c_engine::get_cross_distance(
	float x1,
	float y1,
	float x2,
	float y2 ) -> float {

	return sqrtf( powf( ( x2 - x1 ), 2 ) + powf( ( y2 - y1 ), 2 ) );
}

auto uengine::ftransform::to_matrix( ) -> uengine::c_matrix {

	uengine::c_matrix matrix = {};

	auto x2 = this->rotation.x * 2;
	auto y2 = this->rotation.y * 2;
	auto z2 = this->rotation.z * 2;

	auto xx2 = this->rotation.x * x2;
	auto yy2 = this->rotation.y * y2;
	auto zz2 = this->rotation.z * z2;

	auto yz2 = this->rotation.y * z2;
	auto wx2 = this->rotation.w * x2;

	auto xy2 = this->rotation.x * y2;
	auto wz2 = this->rotation.w * z2;

	auto xz2 = this->rotation.x * z2;
	auto wy2 = this->rotation.w * y2;

	matrix.x_plane.x = ( 1.0 - ( yy2 + zz2 ) ) * this->scale.x;
	matrix.x_plane.y = ( xy2 + wz2 ) * this->scale.x;
	matrix.x_plane.z = ( xz2 - wy2 ) * this->scale.x;

	matrix.y_plane.x = ( xy2 - wz2 ) * this->scale.y;
	matrix.y_plane.y = ( 1.0 - ( xx2 + zz2 ) ) * this->scale.y;
	matrix.y_plane.z = ( yz2 + wx2 ) * this->scale.y;

	matrix.z_plane.x = ( xz2 + wy2 ) * this->scale.z;
	matrix.z_plane.y = ( yz2 - wx2 ) * this->scale.z;
	matrix.z_plane.z = ( 1.0 - ( xx2 + yy2 ) ) * this->scale.z;

	matrix.w_plane.x = this->translation.x;
	matrix.w_plane.y = this->translation.y;
	matrix.w_plane.z = this->translation.z;

	matrix.w_plane.w = 1.0;

	return matrix;
}

auto uengine::c_matrix::to_rotation_matrix(
	uemath::frotator& rotation ) -> uengine::c_matrix
{
	uengine::c_matrix matrix = {};

	auto rad_pitch = ( rotation.pitch * std::numbers::pi / 180.f );
	auto rad_yaw = ( rotation.yaw * std::numbers::pi / 180.f );
	auto rad_roll = ( rotation.roll * std::numbers::pi / 180.f );

	auto sin_pitch = sin( rad_pitch );
	auto cos_pitch = cos( rad_pitch );

	auto sin_yaw = sin( rad_yaw );
	auto cos_yaw = cos( rad_yaw );

	auto sin_roll = sin( rad_roll );
	auto cos_roll = cos( rad_roll );

	matrix.x_plane.x = cos_pitch * cos_yaw;
	matrix.x_plane.y = cos_pitch * sin_yaw;
	matrix.x_plane.z = sin_pitch;
	matrix.x_plane.w = 0.f;

	matrix.y_plane.x = sin_roll * sin_pitch * cos_yaw - cos_roll * sin_yaw;
	matrix.y_plane.y = sin_roll * sin_pitch * sin_yaw + cos_roll * cos_yaw;
	matrix.y_plane.z = -sin_roll * cos_pitch;
	matrix.y_plane.w = 0.f;

	matrix.z_plane.x = -( cos_roll * sin_pitch * cos_yaw + sin_roll * sin_yaw );
	matrix.z_plane.y = cos_yaw * sin_roll - cos_roll * sin_pitch * sin_yaw;
	matrix.z_plane.z = cos_roll * cos_pitch;
	matrix.z_plane.w = 0.f;

	matrix.w_plane.w = 1.f;

	return matrix;
}

auto uengine::c_matrix::to_multiplication(
	uengine::c_matrix m_matrix ) -> uengine::c_matrix {

	uengine::c_matrix matrix{};

	matrix.w_plane.x = (
		this->w_plane.x * m_matrix.x_plane.x +
		this->w_plane.y * m_matrix.y_plane.x +
		this->w_plane.z * m_matrix.z_plane.x +
		this->w_plane.w * m_matrix.w_plane.x
		);

	matrix.w_plane.y = (
		this->w_plane.x * m_matrix.x_plane.y +
		this->w_plane.y * m_matrix.y_plane.y +
		this->w_plane.z * m_matrix.z_plane.y +
		this->w_plane.w * m_matrix.w_plane.y
		);

	matrix.w_plane.z = (
		this->w_plane.x * m_matrix.x_plane.z +
		this->w_plane.y * m_matrix.y_plane.z +
		this->w_plane.z * m_matrix.z_plane.z +
		this->w_plane.w * m_matrix.w_plane.z
		);

	matrix.w_plane.w = (
		this->w_plane.x * m_matrix.x_plane.w +
		this->w_plane.y * m_matrix.y_plane.w +
		this->w_plane.z * m_matrix.z_plane.w +
		this->w_plane.w * m_matrix.w_plane.w
		);

	return matrix;
}

//auto uengine::c_engine::get_bone(
//	sdk::u_skeletal_mesh_component* mesh,
//	std::uint32_t bone_index, 
//	ftransform* bone_transform )  -> uemath::fvector {
//
//	//auto bone_array = m_vm.get( )->read<uintptr_t>( std::uintptr_t( mesh ) + 0x608 + ( mesh->is_cached( ) * 0x10 ) );
//
//	//std::vector<uefi_interface::read_args> read_args { };
//	//read_args.push_back( { bone_array.get_address( ) + ( sizeof( uengine::ftransform ) * bone_index ), &bone, sizeof( uengine::ftransform ) } );
//	//read_args.push_back( { std::uintptr_t( mesh ) + 0x1c0, &ctw, sizeof( uengine::ftransform ) } );
//
//	//m_vm.get( )->batch_read( read_args, sizeof( uefi_interface::read_args ) * read_args.size( ) );
//	//read_args.clear( );
//
//	auto bone_array = mesh->bone_array( );
//	if ( !bone_array.is_valid( ) ) {
//		bone_array = mesh->bone_array_cache( );
//	}
//
//	auto bone = bone_array.get( bone_index );
//
//	auto matrix = bone.to_matrix( ).to_multiplication(
//		mesh->component_to_world( ).to_matrix( )
//	);
//
//	return uemath::fvector(
//		matrix.w_plane.x,
//		matrix.w_plane.y,
//		matrix.w_plane.z
//	);
//
//}

//auto uengine::c_engine::update_matrix( ) -> void {
//
//	auto projection = vm->read<uengine::c_matrix>( std::uintptr_t( g_entity->view_state ) + 0x900 );
//
//	// Pitch (X), Yaw (Y), and Roll (Z).
//	this->rotation.pitch = to_deg( std::asin( projection.z_plane.w ) );
//	this->rotation.yaw = to_deg( std::atan2( projection.y_plane.w, projection.x_plane.w ) );
//	this->rotation.roll = 0.0;
//
//	this->location.x = projection.m[3][0];
//	this->location.y = projection.m[3][1];
//	this->location.z = projection.m[3][2];
//
//	auto fov = atanf( 1 / vm->read<float>( std::uintptr_t( g_entity->view_state ) + 0x700 ) ) * 2;
//	this->field_of_view = to_deg( fov );
//}

D3DXMATRIX matrix_rotation(uemath::fvector rot, uemath::fvector origin)
{
	// if ur seeing this carter im sorry

	#define M_PI (double)3.1415926535

	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}


auto uengine::c_engine::get_axes(uemath::fvector& world_location) -> uemath::fvector
{
	auto matrix = matrix_rotation(this->rotation, uemath::fvector(0, 0, 0));

	auto axis_x = uemath::fvector(matrix.m[0][0], matrix.m[0][1], matrix.m[0][2]);
	auto axis_y = uemath::fvector(matrix.m[1][0], matrix.m[1][1], matrix.m[1][2]);
	auto axis_z = uemath::fvector(matrix.m[2][0], matrix.m[2][1], matrix.m[2][2]);

	auto delta = (world_location - this->location);

	auto transform = uemath::fvector(
		delta.vector_scalar(axis_y),
		delta.vector_scalar(axis_z),
		delta.vector_scalar(axis_x)
	);

	transform.z = (transform.z < 1.f) ? 1.f : transform.z;

	return transform;
}


struct FMinimalViewInfo {
	uemath::fvector Location;
	uemath::fvector Rotation;
	float FOV;
};

auto uengine::c_engine::world_to_screen(
	uemath::fvector& world_location ) -> uemath::fvector
{
	auto ViewInfo = vm->read<FMinimalViewInfo>(g_entity->camera_manager + 0x1f80 + 0x10);

	this->location = ViewInfo.Location;
	this->rotation = ViewInfo.Rotation;
	this->field_of_view = ViewInfo.FOV;

	auto axis = this->get_axes(
		world_location
	);

	auto fov_radians = this->field_of_view * std::numbers::pi / 360.f;

	return uemath::fvector(
		this->m_width_2 + axis.x * ( this->m_width_2 / tanf( fov_radians ) ) / axis.z,
		this->m_height_2 - axis.y * ( this->m_width_2 / tanf( fov_radians ) ) / axis.z,
		0.0f
	);
}

auto uengine::c_engine::world_to_screen(
	uemath::fvector& world_location,
	uemath::fvector point_location ) -> uemath::fvector
{
	auto screen_pos = this->world_to_screen( world_location );
	return uemath::fvector( fabs( screen_pos.x - point_location.x ), fabs( screen_pos.x - point_location.y ), screen_pos.z );
}

bool IsInArea(uemath::fvector2d Coordinate, uemath::fvector2d Start, uemath::fvector2d End)
{
	if (Coordinate.x > Start.x && Coordinate.y > Start.y)
	{
		if (Coordinate.x < End.x && Coordinate.y < End.y)
		{
			return true;
		}
	}

	return false;
}

//auto uengine::c_engine::radar_world_to_screen(
//	uemath::fvector WorldLocation, 
//	uemath::fvector2d* ScreenLocation, 
//	bool IgnoreBehind = false) -> bool
//{
//	auto Matrix = this->to_rotation_matrix(this->rotation);
//
//	auto XAxis = uemath::fvector(Matrix.x_plane.x, Matrix.x_plane.y, Matrix.x_plane.z);
//	auto YAxis = uemath::fvector(Matrix.y_plane.x, Matrix.y_plane.y, Matrix.y_plane.z);
//	auto ZAxis = uemath::fvector(Matrix.z_plane.x, Matrix.z_plane.y, Matrix.z_plane.z);
//
//	auto DeltaCoordinates = WorldLocation - this->location;
//
//	auto Transform = uemath::fvector(DeltaCoordinates.dot(YAxis), DeltaCoordinates.dot(ZAxis), DeltaCoordinates.dot(XAxis));
//	if (Transform.z < 0.01)
//	{
//		if (IgnoreBehind)
//		{
//			Transform.z = 0.01;
//		}
//		else
//		{
//			return false;
//		}
//	}
//
//	ScreenLocation->x = this->m_width_2 + Transform.x * (this->m_width_2 / tan(this->field_of_view * 3.14159265358979323846 / 360)) / Transform.z;
//	ScreenLocation->y = this->m_height_2 - Transform.y * (this->m_width_2 / tan(this->field_of_view * 3.14159265358979323846 / 360)) / Transform.z;
//
//	return IgnoreBehind ? true : IsInArea(*ScreenLocation, uemath::fvector2d(10, 10), uemath::fvector2d((this->m_width_2 * 2) - 10, (this->m_height_2 * 2) - 10));
//}

auto uengine::c_engine::player_dimensions( bool in_lobby, uemath::bounds_t* out_bounds ) -> bool
{
	/*const auto get_bounds = [ & ]( float expand = 0.f ) -> bool
		{

			auto bounds = uemath::bounds_t{ flt_max, flt_min, flt_max, flt_min };

			for ( auto& bone : this->bone_array )
			{
				auto bone_pos = m_engine.get( )->get_bone( mesh, bone.index );

				if ( !in_lobby ) {

					switch ( bone.index )
					{
					case e_bones::HumanHead:
					{
						bone_pos.z += 15;
						break;
					}

					case e_bones::HumanLCalf:
					{
						bone_pos.z -= 8.5;
						break;
					}

					case e_bones::HumanRCalf:
					{
						bone_pos.z -= 8.5;
						break;
					}

					case e_bones::HumanRPalm:
					{
						bone_pos.x -= 10.5;
						break;
					}

					case e_bones::HumanLPalm:
					{
						bone_pos.x += 11;
						break;
					}

					default:
						break;
					}

				}

				bone.screen = this->world_to_screen( bone_pos );
				if ( !this->in_screen( bone.screen ) )
					continue;

				if ( bone.screen.x < bounds.left )
					bounds.left = bone.screen.x;
				else if ( bone.screen.x > bounds.right )
					bounds.right = bone.screen.x;
				if ( bone.screen.y < bounds.top )
					bounds.top = bone.screen.y;
				else if ( bone.screen.y > bounds.bottom )
					bounds.bottom = bone.screen.y;

				bone.on_screen = true;

			}

			if ( bounds.left == flt_max )
				return false;
			if ( bounds.right == flt_min )
				return false;
			if ( bounds.top == flt_max )
				return false;
			if ( bounds.bottom == flt_min )
				return false;

			bounds.left += in_lobby ? -60 : -expand;
			bounds.right += in_lobby ? 60 : expand;
			bounds.top += in_lobby ? -100.f : -expand;
			bounds.bottom += in_lobby ? 50.f : expand;

			*out_bounds = bounds;
			return true;
		};

	if ( get_bounds( 7.f ) )
		return true;*/

	return false;

}