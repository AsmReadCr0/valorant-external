#pragma once 
#include "../../inc.hpp"


//uemath::fvector bone_matrix(int index, uintptr_t mesh)
//{
//	auto bone_array = vm->read<uintptr_t>(mesh + 0x5D8);
//	if (!bone_array) { 
//		bone_array = vm->read<uintptr_t>(mesh + (0x5D8 + 10));
//	}
//
//	auto bone = vm->read<uengine::ftransform>(bone_array + (0x30 * index));
//
//	auto c2w = vm->read<uengine::ftransform>(mesh + 0x250);
//
//	auto matrix = bone.to_matrix().to_multiplication(
//		c2w.to_matrix()
//	);
//
//	return uemath::fvector(
//		matrix.w_plane.x,
//		matrix.w_plane.y,
//		matrix.w_plane.z
//	);
//}

int position = 5;

void draw_healthbar(float x, float y, float width, float height, int thickness, int health)
{
	float healthBarX = x - (thickness + 3);
	float healthBarY = y;

	float textX = healthBarX;
	float textY = y + height - ((height / 100) * health) - 7;

	framework->filled_rect(healthBarX, healthBarY, thickness, height, uemath::flinearcolor(255, 255 - health, 55 + health * 2, 75), false, 0, 0);

	framework->filled_rect(healthBarX, healthBarY, thickness, height - ((height / 100) * health), uemath::flinearcolor(150, 0, 0, 0), false, 0, 0);
	framework->rect(healthBarX - 1, healthBarY - 1, thickness + 1, height + 1, uemath::flinearcolor(255, 0, 0, 0), 0.5f);

	if (health <= 10) {
		position = 2.4;
	}
	else {
		position = 4.5;
	};

	if (health != 100)
		framework->text(std::to_string(health), textX - position, textY, uemath::flinearcolor(255, 255, 255, 255), 7, false, false);

}

void print_actor_info(const uintptr_t player, const std::uint32_t size, const std::string& hello, std::unordered_set<uintptr_t>& show_actors, int& print_count) {
	// Check if the actor has been shown before
	if (show_actors.find(player) == show_actors.end()) {
		// Increment the print count
		print_count++;

		// Print actor information with count
		printf("%s | size -> %i | actor -> %llu | actors counted: %d\n", hello.c_str(), size, player, print_count);

		// Add the actor to the set of shown actors
		show_actors.insert(player);
	}
}

int print_count;
std::unordered_set<uintptr_t> start_of_loop;

std::unordered_set<uintptr_t> damage_handlerr;
int print_count1;

auto c_visual::render( ) -> void
{
	//radar.get()->draw_radar();


	auto val = [&](aactor::c_list const entity) {
		const auto player = static_cast<aactor::c_list const>(entity);

		print_actor_info(player.m_actor, player.m_actor_size, "start_of_loop", start_of_loop, print_count);

		if (vm->read<bool>(player.m_actor + 0x101)) // dormant check chat?
		{
			//auto unique_id = vm->read<int>(player.m_actor + 0x38);
			//if (unique_id != 18743553) return;

			auto damage_handler = vm->read<uintptr_t>(player.m_actor + 0x9E8);
			if (!damage_handler) return;

			//print_actor_info(player.m_actor, player.m_actor_size, "inside loop", damage_handlerr, print_count1);

			auto health = vm->read<float>(damage_handler + 0x1B0);
			//if (health <= 0) return;

			//auto team_component = vm->read<uintptr_t>(player.m_player_state + 0x610);
			//std::cout << "team_component -> " << team_component << std::endl;
			//auto team_id = vm->read<int>(team_component + 0xF8);
			//std::cout << "team_id -> " << team_id << std::endl;

			/*auto mesh = vm->read<uintptr_t>(player.m_actor + 0x418);
			//if (!mesh) return;

			auto bone_count = vm->read<int>(mesh + 0x5E0);
			bool is_bot = bone_count == 103;

			uemath::fvector head_bone = bone_matrix(8, mesh);
			uemath::fvector head_screen = world_to_screen(head_bone);

			uemath::fvector root_bone = bone_matrix(0, mesh);
			uemath::fvector root_screen = world_to_screen(root_bone);*/
			

			auto root_component = vm->read<uintptr_t>(player.m_actor + 0x238);

			auto relative_location = vm->read<uemath::fvector>(root_component + 0x164);

			uemath::fvector root_bone = { relative_location.x , relative_location.y , relative_location.z - 50.f };
			uemath::fvector head_bone = { relative_location.x , relative_location.y , relative_location.z + 100.f };

			uemath::fvector root_screen = engine->world_to_screen(root_bone);
			uemath::fvector head_screen = engine->world_to_screen(head_bone);


			auto distance = engine->location.distance_to(relative_location);

			print_actor_info(player.m_actor, player.m_actor_size, "damage_handler", damage_handlerr, print_count1);

			uemath::flinearcolor text_color = uemath::flinearcolor(255, 255, 255, 255);
			if (health <= 0) { 
				text_color = uemath::flinearcolor(255, 255, 0, 0); 
			}

			std::string distance_string = std::format("{:.0f}m", distance);
			if (health <= 0) {
				distance_string = std::format("dead entity | {:.0f}m", distance);
			}
			framework->text(distance_string, root_screen.x, root_screen.y, text_color, 20, false);
		
			if (health <= 0)
				return;

			// Rectangle Box
			float box_height = abs(head_screen.y - root_screen.y);
			float box_width = box_height * 0.50f;

			framework->rect(
				head_screen.x - (box_width / 2),
				head_screen.y, box_width, box_height,
				uemath::flinearcolor(255, 0, 0, 0),
				2
			);		

			// Health Bar
			float health_height = abs(abs(head_screen.y) - abs(root_screen.y));
			float health_width = box_height / 2.f;
			float health_middle = root_screen.x - (box_width / 2.f);


			draw_healthbar(health_middle, head_screen.y, health_width, box_height, 2, health);

		}

	};
	g_entity->loop(val);

	//for (int idx = 0; idx < actor_size; idx++)
	//{
	//	auto actor = vm->read<uintptr_t>(actor_array + (idx * 0x8));
	//	if (!actor) continue;

	//	auto mesh = vm->read<uintptr_t>(actor + 0x418);
	//	if (!mesh) continue;

	//	auto player_state = vm->read<uintptr_t>(actor + 0x3d8);
	//	
	///*	auto team_component = vm->read<uintptr_t>(actor + 0x610);
	//	auto team_id = vm->read<int>(team_component + 0xF8);
	//	std::cout << "team id -> " << team_id << std::endl;*/

	//	auto damage_handler = vm->read<uintptr_t>(actor + 0x9E8);
	//	if (!damage_handler) continue;

	//	auto health = vm->read<float>(damage_handler + 0x1B0);
	//	if (health <= 0) continue;

	//	auto bone_array = vm->read<uintptr_t>(mesh + 0x5D8);
	//	if (!bone_array) continue;

	//	auto bone_count = vm->read<int>(mesh + 0x5E0);
	//	if (!bone_count) continue;

	//	view_info();
	//	
	//	if (vm->read<bool>(actor + 0x100)) // dormant check chat?
	//	{
	//		uemath::fvector head_bone = bone_matrix(8, mesh, bone_array);
	//		head_bone = ProjectWorldToScreen(head_bone);
	//		//printf("health -> %f | bone_count -> %i | head_bone -> %f , %f ,%f \n", health , bone_count, head_bone.x, head_bone.y, head_bone.z);

	//		std::string formattedString = std::format("health: {:.2f}", health);
	//		framework->text(formattedString, head_bone.x, head_bone.y, uemath::flinearcolor(255, 255, 255, 255), 20, false);
	//	}
	//}
}
