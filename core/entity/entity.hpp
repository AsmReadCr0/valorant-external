#ifndef ENTITY_HPP
#define ENTITY_HPP

namespace entity
{

	class c_entity
	{
		std::mutex	m_mutex { };
		//std::vector<aactor::c_list>  m_list_cache{ };

		std::vector<aactor::c_list>  m_list_cache { };
		//std::vector<fortnite::c_item>   m_loots{ };

	public:

		uintptr_t persistent_level;
		uintptr_t camera_manager;
		uintptr_t game_state;
		int local_unique_id;
		uemath::fvector relative_location;


		ALWAYS_INLINE ~c_entity( ) = default;

		ALWAYS_INLINE c_entity( ) 
			: m_list_cache( { } )
		{
			g_vars->load( ); this->m_list_cache.resize( 110 ); 
			/*this->m_list_cache.reserve( 110 );*/ 
			/* this->m_loots.reserve( 300 );*/ 
		}

		//ALWAYS_INLINE std::uint32_t size() { return fortnite::m_actors.size(); }
		//ALWAYS_INLINE std::uint32_t loot_size() { return m_loot.size(); }
		ALWAYS_INLINE void reset( ) { /*fortnite::m_players.clear( ); */ /* this->m_loots.clear( );*/ }

		ALWAYS_INLINE void get_world(  );
		ALWAYS_INLINE void get_actors(  );

		void tick( ) noexcept;
		//void loop( const std::function< void( aactor::c_list )>& fn ) const;
		void loop( const std::function< void( aactor::c_list )>& val) const;

		//std::vector<std::unique_ptr< aactor::c_list>>  m_list { };
		std::vector<aactor::c_list>  m_list { };
		//std::vector<fortnite::c_item>  m_loot{ };

		 // temp

 	};

} inline const auto g_entity = std::make_unique<entity::c_entity>( );

#endif // ENTITY_HPP

/*
namespace fortnite {
	class c_list {
	public:
		// Assuming types for actor, index, and state are ActorType*, int, and StateType* respectively
		c_list(ActorType* actor, int index, StateType* state)
			: m_actor(actor), m_index(index), m_state(state) {}
		// Existing members and methods...
	};
}

*/