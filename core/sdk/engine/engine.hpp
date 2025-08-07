#pragma once 
namespace uengine {

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    using enough_float_t = std::conditional_t< sizeof( _value_t ) <= sizeof( float ), float, float >;

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_pi = static_cast< _ret_t >( std::numbers::pi );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_pi2 = static_cast< _ret_t >( k_pi< float > *2.0 );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_rad_pi = static_cast< _ret_t >( 180.0 / k_pi< float > );

    template < typename _ret_t >
        requires std::is_floating_point_v< _ret_t >
    inline constexpr auto k_deg_pi = static_cast< _ret_t >( k_pi< float > / 180.0 );

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    ALWAYS_INLINE constexpr auto to_deg( const _value_t rad )
    {
        using ret_t = enough_float_t< _value_t >;

        return static_cast< ret_t >( rad * k_rad_pi< ret_t > );
    }

    template < typename _value_t >
        requires std::is_arithmetic_v< _value_t >
    ALWAYS_INLINE constexpr auto to_rad( const _value_t deg )
    {
        using ret_t = enough_float_t< _value_t >;

        return static_cast< ret_t >( deg * k_deg_pi< ret_t > );
    }

    struct bone_t {
        uemath::fvector screen;
        int index;
        bool on_screen;
    };

    struct f_plane : uemath::fvector {

        f_plane( ) : w( 0 ) { }
        f_plane( float w ) : w( w ) { }

        uemath::fvector to_vector( ) {
            uemath::fvector value;
            value.x = this->x;
            value.y = this->y;
            value.z = this->z;
            return value;
        }

        float w;
    };

    //template < typename type_t >
    //concept arithmetic = std::is_arithmetic_v< type_t >;

    //template< arithmetic t, std::size_t r, std::size_t c > 
    class c_matrix {
    public:

        float m[ 4 ][ 4 ];
        f_plane x_plane, y_plane, z_plane, w_plane;

        c_matrix( ) : x_plane( ), y_plane( ), z_plane( ), w_plane( ) { }
        c_matrix( f_plane x_plane, f_plane y_plane, f_plane z_plane, f_plane w_plane )
            : x_plane( x_plane ), y_plane( y_plane ), z_plane( z_plane ), w_plane( w_plane ) { }

        c_matrix to_multiplication( c_matrix m_matrix );
        c_matrix to_rotation_matrix( uemath::frotator& rotation );
    };

    //using matrix4x4_t = c_matrix< float, 4, 4 >;

	struct FQuat {
		float x; // 0x00(0x08)
		float y; // 0x08(0x08)
		float z; // 0x10(0x08)
		float w; // 0x18(0x08)
	};

    //class ftransform {
    //public:
    struct ftransform {
        //f_plane rotation,translation;
        //uemath::fvector scale;
        //float unknown;

        //ftransform( ) : rotation( ), translation( ), scale( ), unknown( ) { }
        //ftransform( f_plane rotation, f_plane translation, uemath::fvector scale, float unknown )
        //    : rotation( rotation ), translation( translation ), scale( scale ), unknown( unknown ) { }

        //f_plane rotation;
        FQuat rotation;
        uemath::fvector translation;
        char pad[ 0x4 ]; // 0x38(0x08)
        uemath::fvector scale;
        char pad1[ 0x4 ]; // 0x58(0x08)

        ftransform( ) : rotation( ) , translation( 0.f, 0.f, 0.f ), scale( 0.f, 0.f, 0.f ), pad( ), pad1( ) { }

        ftransform( const FQuat& rot, const uemath::fvector& translation, const uemath::fvector& scale )
        {
            this->rotation = rot;
            this->translation = translation;

            this->pad[ 0x4 ] = 0;
            this->scale = scale;
            this->pad1[ 0x4 ] = 0;
        }

        [[nodiscard]] c_matrix to_matrix( );

    };

    class c_tick_listener
    {
    public:

    };

    class c_engine : public c_matrix {

        std::vector<uengine::ftransform> v_bone;

    public:
        void update_matrix( );
        bool in_screen( uemath::fvector bone );
        float get_cross_distance( float x1,float y1,float x2,float y2 );
        bool is_shot( uemath::fvector lur,uemath::fvector wl );

        uemath::fvector get_axes( uemath::fvector& world_location );
        uemath::fvector world_to_screen( uemath::fvector& world_location );
        uemath::fvector world_to_screen( uemath::fvector& world_location, uemath::fvector point_location ); 
        bool radar_world_to_screen(uemath::fvector WorldLocation, uemath::fvector2d* ScreenLocation, bool IgnoreBehind);

        //uemath::fvector get_bone( sdk::u_skeletal_mesh_component* mesh, std::uint32_t bone_index, ftransform* bone_transform = nullptr );
        bool player_dimensions( bool in_lobby, uemath::bounds_t* out_bounds );

        uemath::fvector rotation { };
        uemath::fvector location { };
        float field_of_view = 0;

        //sdk::a_fort_player_state_athena* local_player_state;
        //sdk::a_fort_player_pawn_athena* local_player_pawn;
        //sdk::a_player_controller* local_player_controller;
        //sdk::a_player_controller* player_controller;

        //sdk::a_fort_player_pawn_athena* target_player_pawn;


        int m_width { };
        int m_height { };

        int m_width_2 { };
        int m_height_2 { };
    };

} inline auto engine = std::make_unique<uengine::c_engine>( );