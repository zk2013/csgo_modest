#include "csgo.hpp"

namespace menu
{
	/// Helper functions
	float get_curtime()
	{
		return ctx::csgo.globals->curtime;
	}

	float get_frametime()
	{
		return ctx::csgo.globals->frametime;
	}

	void text( const math::vec2_t& pos, const col_t& col, std::string_view text )
	{
		render::text( render::fonts::m_menu, pos, col, 0, text );
	}

	math::vec2_t text_size( std::string_view text )
	{
		return render::text_size( render::fonts::m_menu, text );
	}

	void clip( const math::vec2_t& pos, const math::vec2_t& size, bool override_clip = false )
	{
		return render::clip( pos, size, override_clip );
	}

	void init()
	{
		/// Set up helper functions
		gui::setup_helper(
			get_curtime,
			get_frametime,
			render::rect_filled,
			render::rect,
			text,
			text_size,
			render::reset_clip,
			clip
		);

		/// Set up buttons
		gui::set_toggle_key( VK_INSERT );
		gui::set_hold_key( VK_MENU );

		/// Set up name
		gui::set_name( "csgo_modest" );

		/// Now actually do the controls
		if ( auto tab1 = gui::add_tab( "tab 1" ) )
		{
			tab1->add( std::make_shared<gui::controls::c_checkbox>( "Checkbox 1", &ctx::config.bhop ) );
			tab1->add( std::make_shared<gui::controls::c_separator>( "A section" ) );
			{
				tab1->add( std::make_shared<gui::controls::c_checkbox>( "Checkbox 2", &ctx::config.health_esp ) );
				tab1->add( std::make_shared<gui::controls::c_checkbox>( "Checkbox 3", &ctx::config.name_esp ) );
			}

			tab1->add( std::make_shared<gui::controls::c_separator>( "Another section" ) );
			{
				tab1->add( std::make_shared<gui::controls::c_combo>( "Combobox", &ctx::config.health_style, std::vector<std::string_view>{ "Type 1", "Type 2", "Type 3", "Largest Item" } ) );
				tab1->add( std::make_shared<gui::controls::c_slider>( "Slider", &ctx::config.some_float, -100.f, 100.f ) );
			}
		}

		if ( auto tab2 = gui::add_tab( "tab 2" ) )
		{

		}

		if ( auto tab3 = gui::add_tab( "tab 3" ) )
		{

		}
	}

	void render()
	{
		gui::set_pos( render::get_screen_size() * 0.5f );
		gui::set_size( { 200, 14 } );

		gui::setup_style();

		ctx::csgo.surface->m_bClippingEnabled() = true;

		gui::render();

		ctx::csgo.surface->m_bClippingEnabled() = false;
	}
}