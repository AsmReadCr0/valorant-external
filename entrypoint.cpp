#pragma once
#include "core/inc.hpp"

auto main( ) -> std::int32_t //-> to dll (rwx)
{
	auto status = g_utils->attach_console( );
	if ( !status ) { return 0; }

	status = vm->attach_vm( L"VALORANT-Win64-Shipping.exe" );
	if ( !status ) { return 0; }

	status = g_render->setup( L"VALORANT-Win64-Shipping.exe" );
	if ( !status ) { return 0; }

	std::jthread( [ & ] ( ) -> void { g_entity->tick( ); } ).detach( );
	std::jthread( [ & ] ( ) -> void { g_render->tick( ); } ).detach( );
	//std::jthread( [ & ] ( ) -> void { aimbot.get( )->tick( ); } ).detach( );

	return std::cin.get( ) != EOF;
}