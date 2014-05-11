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
#include "cJobManager.h"
#include "cBrothel.h"
#include "cClinic.h"
#include "cCustomers.h"
#include "cRng.h"
#include "cInventory.h"
#include "sConfig.h"
#include "cRival.h"
#include <sstream>
#include "CLog.h"
#include "cTrainable.h"
#include "cTariff.h"
#include "cGold.h"
#include "cGangs.h"
#include "cMessageBox.h"
#include "libintl.h"

extern cRng g_Dice;
extern CLog g_LogFile;
extern cCustomers g_Customers;
extern cInventory g_InvManager;
extern cBrothelManager g_Brothels;
extern cClinicManager g_Clinic;
extern cGangManager g_Gangs;
extern cMessageQue g_MessageQue;

bool cJobManager::WorkHealing(sGirl* girl, sBrothel* brothel, int DayNight, string& summary)
{
	string message = "";
	int tex = g_Dice%4;

	bool hasDoctor = false;
	if(g_Clinic.GetNumGirlsOnJob(brothel->m_id, JOB_DOCTOR, true) >= 1 || g_Clinic.GetNumGirlsOnJob(brothel->m_id, JOB_DOCTOR, false) >= 1)
		hasDoctor = true;

	if (!hasDoctor)
	{
		string message = girl->m_Realname + gettext(" does nothing. You don't have any Doctor (require 1)");
		if(DayNight == 0)
			message += gettext("day");
		else
			message += gettext("night");
		message += gettext(" Shift.");

		girl->m_Events.AddMessage(message, IMGTYPE_PROFILE, EVENT_WARNING);
		return true;
	}

	if (g_Girls.HasTrait(girl, "Construct"))
	{
		string message = girl->m_Realname + gettext(" should go to the repair shop.");
		if(DayNight == 0)
		girl->m_Events.AddMessage(message, IMGTYPE_PROFILE, EVENT_WARNING);
		return true;
	}

	// not for patient
	g_Girls.UnequipCombat(girl);

	message += gettext("She does nothing while the doctor takes care of her.");

	if (g_Girls.HasTrait(girl, "Construct"))
	{
		g_Girls.UpdateStat(girl, STAT_HEALTH, 200); //constructs heal 10% so 200 becomes 20 actual healing
		g_Girls.UpdateStat(girl, STAT_MANA, 20);
	}
	else if (g_Clinic.GetNumGirlsOnJob(0, JOB_NURSE, false) >= 1 && g_Girls.HasTrait(girl, "Half-Construct"))
	{
		g_Girls.UpdateStat(girl, STAT_HEALTH, 30);
		g_Girls.UpdateStat(girl, STAT_MANA, 30);
	}
	if (g_Clinic.GetNumGirlsOnJob(0, JOB_NURSE, false) >= 1)
	{
		g_Girls.UpdateStat(girl, STAT_HEALTH, 40);
		g_Girls.UpdateStat(girl, STAT_MANA, 40);
	}
	else 
	{
		g_Girls.UpdateStat(girl, STAT_HEALTH, 20);
		g_Girls.UpdateStat(girl, STAT_MANA, 20);
	}
	girl->m_Events.AddMessage(message, IMGTYPE_PROFILE, DayNight);

	return false;
}
