#pragma once
namespace settings
{
	class c_instance
	{
	public:
		c_instance( ) {}
		c_instance( const std::uintptr_t& inst )
		{
			this->instance = inst;
		}
		~c_instance( ) {}

	protected:
		std::uintptr_t instance = 0;


	public: 
		operator std::uintptr_t( ) const 
		{ 
			return this->instance; 
		}
	};

	class c_vars : public c_instance
	{

	public: 

		using c_instance::c_instance;

		void load( );
		void save( );
		void reset( );

		struct {
			int aim_keycode;
			int target_bone;
			bool enabled;
			float fov_c; 
			bool prediction;
			float smooth;
			//float accuracy_rate;
			bool ignore_team;
			bool ignore_knocked;
			bool ignore_invisible;
		} aim;

		//struct {
		//	bool no_float_pump_cooldown;
		//	bool instant_weapon_animation;
		//	bool no_sprint_to_shoot_cooldown;
		//	bool first_person;
		//	bool no_recoil;
		//	bool no_spread;
		//} exploits;

		struct {
			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} smg;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} ars;

			struct {
				bool enabled;
				float weapon_fov;
			} shotgun;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} pistol;

			struct {
				bool enabled;
				bool prediction;
				float weapon_fov;
			} snipers;

		} weapon_config;
		
		struct {
			bool esp;
			
			bool bounding_box;
			bool bounding_corner;
			bool bounding_3d;
			bool username;
			bool distance;
			bool snapline;
			bool weapon;
			bool reloading;
			bool team_index;
			bool index_w_username;
			bool index_colors;
			//bool skeleton;
			//bool view_angle;
			
			bool ignore_team;
			bool ignore_dbno;

		} visuals;

		struct {
			uemath::flinearcolor bot;
			uemath::flinearcolor visible;
			uemath::flinearcolor invisible;
			uemath::flinearcolor is_dbno;
			uemath::flinearcolor crosshair;
			uemath::flinearcolor fov;
			uemath::flinearcolor team;
		} color;

		struct {
			bool enabled;
			float width;
			float height;
			float size;
			bool show_team;
			bool line;
			bool moveable;
		} radar;

		/*struct {
			bool weapons;
			bool items;
			bool vehicles;
			bool chests;
			bool ammo;

			bool smart_loot;
			bool priot_tier;
			bool prior_ammo;
			bool prior_health;
			bool prior_shield;
			
			float weapons_render_distance = 50.0f;
			float items_render_distance = 50.0f;
			float vehicles_render_distance = 150.0f;
			float chests_render_distance = 50.0f;
			float ammo_render_distance = 50.0f;
		} loot;*/

		struct {

			bool fov;
			bool fps;
			bool menu;
			bool trigger_bot;
			bool crosshair;

			bool debug;
			bool kill;

			float custom_delay;
			float maximum_distance;
			bool has_clicked;
			std::chrono::steady_clock::time_point tb_begin;
			std::chrono::steady_clock::time_point tb_end;
			int tb_time_since;

		} misc;

		struct {

		} keybind;
	};

} inline const auto g_vars= std::make_shared<settings::c_vars>( );