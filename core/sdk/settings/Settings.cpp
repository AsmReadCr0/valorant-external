#pragma once
#include "../../inc.hpp"

auto settings::c_vars::load( ) -> void
{
	this->aim.enabled       = true;
	this->aim.target_bone   = 110;
	this->aim.fov_c			= 550.f;
	this->aim.aim_keycode   = 0x02;
	this->aim.smooth		= 3.4f;

	this->aim.prediction = true;

	this->aim.ignore_invisible = true;
	this->aim.ignore_knocked = true;
	this->aim.ignore_team = true;

	this->weapon_config.smg.enabled = true;
	this->weapon_config.smg.weapon_fov = this->aim.fov_c;
	this->weapon_config.smg.prediction = true;

	this->weapon_config.ars.enabled = true;
	this->weapon_config.ars.weapon_fov = this->aim.fov_c;
	this->weapon_config.ars.prediction = true;

	this->weapon_config.shotgun.enabled = true;
	this->weapon_config.shotgun.weapon_fov = this->aim.fov_c;

	this->weapon_config.pistol.enabled = true;
	this->weapon_config.pistol.weapon_fov = this->aim.fov_c;
	this->weapon_config.pistol.prediction = true;

	this->weapon_config.snipers.enabled = true;
	this->weapon_config.snipers.weapon_fov = this->aim.fov_c;
	this->weapon_config.snipers.prediction = true;

	this->visuals.esp		= true;
	this->visuals.bounding_corner	= true;
	this->visuals.bounding_3d		= false;
	this->visuals.distance	= true;
	this->visuals.snapline	= true;
	this->visuals.username  = true;
	this->visuals.weapon    = true;
	this->visuals.reloading = true;
	this->visuals.team_index = true;
	this->visuals.index_w_username = false;
	this->visuals.index_colors = true;
	this->visuals.ignore_team = false;
	this->visuals.ignore_dbno = false;

	this->radar.enabled     = true;
	this->radar.height      = 200;
	this->radar.width       = 200;
	this->radar.size		= 250;
	this->radar.line		= true;
	this->radar.moveable	= false;


	this->misc.fov			= false;
	this->misc.menu			= false;
	this->misc.trigger_bot  = false;
	this->misc.crosshair	= true;
	this->misc.debug		= false;

	this->misc.custom_delay = 50;
	this->misc.maximum_distance = 450.f;
	this->misc.has_clicked;
	this->misc.tb_begin;
	this->misc.tb_end;
	this->misc.tb_time_since;

	this->color.bot = uemath::flinearcolor(255, 0, 195, 255);
	this->color.crosshair = uemath::flinearcolor(255, 255, 255, 255);
	this->color.fov = uemath::flinearcolor(255, 255, 255, 255);
	this->color.is_dbno = uemath::flinearcolor(255, 217, 255, 0);
	this->color.team = uemath::flinearcolor(255, 0, 255, 4);
	this->color.visible = uemath::flinearcolor(255, 255, 0, 0);
	this->color.invisible = uemath::flinearcolor(255, 74, 0, 0);

}

auto settings::c_vars::save( ) -> void
{

}

auto settings::c_vars::reset( ) -> void
{

}