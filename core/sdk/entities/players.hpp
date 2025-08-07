#ifndef PLAYERS_HPP
#define PLAYERS_HPP

namespace aactor
{
	class c_item {
	private:
	public:

		uemath::fvector		m_item_base;

		e_fort_item_type	m_item_type;
		e_fort_item_tier	m_item_tier;

		float               m_distance;

		std::string			m_name;
	};

	class c_actor {
	private:
	public:

		uemath::fvector		m_actor_base;
		uemath::fvector     m_actor_head;
		bool is_target;

		uemath::bounds_t    m_bounds;

		//sdk::u_skeletal_mesh_component*		m_mesh;
		//sdk::a_fort_player_pawn_athena*		m_actor;
		//sdk::a_fort_player_state_athena*	m_state;

		std::string			m_username;
		std::uint32_t       m_index;
		std::uintptr_t		m_player_state;

		float               m_distance;
		bool				m_is_bot;
		bool				m_is_visible;
		bool				m_is_knocked;
		bool				m_is_dying;

	};

	class c_list {
	private:
	public:

		ALWAYS_INLINE c_list( ) = default;
		ALWAYS_INLINE c_list(
			std::uint32_t index,
			uintptr_t actor,
			std::uint32_t size,
			uintptr_t player_state)
			: m_index( index ), m_actor( actor ), m_actor_size( size ), m_player_state( player_state ) {}


		std::uint32_t					     m_index;
		std::uint32_t					     m_actor_size;
		uintptr_t							 m_actor;
		uintptr_t							 m_player_state;

		//sdk::a_fort_player_state_athena*	 m_state;
		//sdk::a_game_state_base*				 m_game_state;

		//friend bool operator == ( const c_list& a, const c_list& b ) { return bool( a.m_actor == b.m_actor ); }
	};
}

#endif // !gaurd