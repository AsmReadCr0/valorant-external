#pragma once 
#include "../inc.hpp"

auto timer_stop = std::chrono::high_resolution_clock::now( );



auto entity::c_entity::tick( ) noexcept -> void
{

	for ( ;; ) {
		
		//constexpr auto update_time = 50;
		//constexpr auto update_time = 15;
		constexpr auto update_time = 100;

		auto timer_start = std::chrono::high_resolution_clock::now( );
		auto count = std::chrono::duration_cast< std::chrono::milliseconds >(
			timer_start - timer_stop
		).count( );

		if ( count > update_time )
		{
			std::unique_lock<std::mutex> lock( this->m_mutex );
			{
				this->get_world( );

				this->get_actors( );
			}
			lock.unlock( );
			timer_stop = std::move( timer_start );
		}
		else {

			std::this_thread::sleep_for(
				std::chrono::milliseconds(
					update_time - count
				) );
		}

	}
}

auto entity::c_entity::get_world( ) -> void
{
	auto u_world = vm->read_kernel_virtual<uintptr_t>(vm->m_guarded + 0x60);
	u_world = vm->validate_pointer(u_world);

	auto game_instance = vm->read_guarded<uintptr_t>(u_world + 0x1A0);

	this->persistent_level = vm->read_kernel_virtual<uintptr_t>(u_world + 0x38);
	this->persistent_level = vm->validate_pointer(persistent_level);

	this->game_state = vm->read_kernel_virtual<uintptr_t>(u_world + 0x140);
	this->game_state = vm->validate_pointer(game_state);

	auto local_players = vm->read_kernel_virtual<uintptr_t>(game_instance + 0x40);
	local_players = vm->validate_pointer(local_players);

	auto local_player = vm->read<uintptr_t>(local_players);
	local_player = vm->validate_pointer(local_player);

	auto player_controller = vm->read<uintptr_t>(local_player + 0x38);
	player_controller = vm->validate_pointer(player_controller);

	auto local_controller = vm->read<uintptr_t>(local_player + 0x38);
	local_controller = vm->validate_pointer(local_controller);
	
	this->camera_manager = vm->read<uintptr_t>(player_controller + 0x460); // using kernel virtual doesnt make it minus in comp games 
	this->camera_manager = vm->validate_pointer(camera_manager);
	
	if (g_vars->misc.debug)
	{
		print_info("u_world -> % I64d \n", u_world);
		print_info("game_instance -> % I64d \n", game_instance);
		print_info("persistent_level -> % I64d \n", persistent_level);
		print_info("game_state -> % I64d \n", game_state);
		print_info("local_players -> % I64d \n", local_players);
		print_info("local_player -> % I64d \n", local_player);
		print_info("player_controller -> % I64d \n", player_controller);
	}

}

auto entity::c_entity::get_actors(  ) -> void 
{
	const auto actor_array = vm->read<sdk::tarray<uintptr_t>>(game_state + 0x3d0).get_itter(); // struct TArray<struct APlayerState*> PlayerArray; // 0x3d0(0x10)
	
	auto actor_size = (actor_array.size());

	if (actor_size > 13)
		return;

	for (auto index = 0ul; index < actor_size; ++index) {

		auto player_state = actor_array[index];
		if (!player_state) continue;

		static uintptr_t maxValidPointer = 0; // Initialize with a default value

		auto actor = vm->read_guarded_2<uintptr_t>(player_state + 0x978);  // struct AShooterCharacter* SpawnedCharacter; // 0x978(0x08)


		//print_info("size -> %i | actor -> % I64d \n", actor_size,  actor );

		std::uint32_t actor_size = actor_array.size();

		const auto is_same = [&](const aactor::c_list& list)
			{
					return actor == list.m_actor;
			};

		const auto it = std::find_if(m_list_cache.begin(), m_list_cache.end(), is_same);
		if (it == m_list_cache.end()) {
				m_list_cache.emplace_back(aactor::c_list{ index, actor, actor_size, player_state });
		}
	}

	this->m_list.swap(m_list_cache);

	if (!this->m_list_cache.empty())
		this->m_list_cache.clear();
}


void entity::c_entity::loop( const std::function< void( aactor::c_list )>& val) const {

	for ( const auto& it : this->m_list ) {

		// checks here
		
		val( it );
	}

}