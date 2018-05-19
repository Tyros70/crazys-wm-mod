/*
 * Copyright 2009, 2010, The Pink Petal Development Team.
 * The Pink Petal Devloment Team are defined as the game's coders 
 * who meet on http://pinkpetal.org     // old site: http://pinkpetal .co.cc
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "DirPath.h"
#include "cInterfaceWindow.h"
#include "InterfaceGlobals.h"

class cBuilding;

class cScreenFarm : public cInterfaceWindowXML 
{
private:
	int BuyBrothel;
	bool GetName;

	static	bool		ids_set;
	
	int buildinglabel_id;
	int background_id;
	int walk_id;			// Walk Around Town button

	int weeks_id;			// next week map button
	int	farmdetails_id;		// farm description text
	int girls_id;			// girl managment map button
	int staff_id;			// gang map button
	int setup_id;			// setup map button
	int dungeon_id;			// 
	int turns_id;			// turn summary map button

	int girlimage_id;		// Girl image
	int back_id;			// 

	int nextbrothel_id;		// next brothel button
	int prevbrothel_id;		// prev brothel button
	int	farm_id;			// farm's House map button

	bool m_first_walk;

	void set_ids();
	void check_brothel(int BrothelNum);
	void check_farm(int FarmNum);
public:
	cScreenFarm();
	~cScreenFarm();

	void init();
	void process();
	void check_events();
	void more_button();
	void release_button();
	void update_details();
	sGirl* get_selected_girl();
	void selection_change();
	bool check_keys();
	void do_walk();
	string walk_no_luck();

};