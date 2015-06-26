#include "../stdafx.h"
#include "../natives.h"
#include "UIFunctions.h"
#include "PlayerFunctions.h"

void MoneyFountain(bool bMoneyFountainActive)
{
	if (bMoneyFountainActive)
	{
		try
		{
			static int iMoney = 0;
			iMoney++;
			if (!STREAMING::HAS_MODEL_LOADED(0x113FD533))
				STREAMING::REQUEST_MODEL(0x113FD533); //Manchester United: Nil Loadsamoney United: LOADS
			if (iMoney >= 2)
			{
				if (STREAMING::HAS_MODEL_LOADED(0x113FD533)) //Good evening and welcome to: Loads of Money.
				{
					Vector3 fountainPos; //Dereck B? On your bike!
					fountainPos.x = -519.349243f;
					fountainPos.y = -249.006134f;
					fountainPos.z = 36.277279f;
					static Hash PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"); //Right. Let's do up the house.
					int MONEY_DROP_AMOUNT = rand() % 25000 + 10000; // lets make it more random so r* wont recognize a pattern mch
					OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, fountainPos.x + (((rand() % 3000) - 1500) / 1000), fountainPos.y + (((rand() % 3000) - 1500) / 1000), fountainPos.z + (((rand() % 2000) - 1000) / 1000), 0, MONEY_DROP_AMOUNT, 0x113FD533, FALSE, TRUE); //WHOP YOUR WAD ON THE COUNTA
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533); //SHUT YOUR MOUTH!
				}
				iMoney = 0;
			}
		}
		catch (...){ Log::Error("Got too much money."); }
	}
}

void ATMFountain(Ped playerPed, bool bATMFountainActive)
{
	if (bATMFountainActive)
	{
		/*
		ATM model names:
		prop_fleeca_atm=506770882
		prop_atm_02=-1126237515
		prop_atm_03=-1364697528

		prop_atm_01

		just regular cash?
		PICKUP_MONEY_VARIABLE=-31919185
		*/
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
		Hash modelHashes[] = { 506770882, -1126237515, -1364697528 };

		for each (Hash modelHash in modelHashes)
		{
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(playerPosition.x, playerPosition.y, playerPosition.z, 3.0f, modelHash, TRUE, 0, 0);
			
			if (ENTITY::DOES_ENTITY_EXIST(obj))
			{
				Vector3 ATMPos = ENTITY::GET_ENTITY_COORDS(obj, true);
				{
					try
					{
						static int iMoney = 0;
						iMoney++;
						if (!STREAMING::HAS_MODEL_LOADED(-31919185))
							STREAMING::REQUEST_MODEL(-31919185); //Manchester United: Nil Loadsamoney United: LOADS
						if (iMoney >= 2)
						{
							if (STREAMING::HAS_MODEL_LOADED(-31919185)) //Good evening and welcome to: Loads of Money.
							{
								Vector3 fountainPos; //Dereck B? On your bike!
								fountainPos.x = -519.349243f;
								fountainPos.y = -249.006134f;
								fountainPos.z = 36.277279f;
								static Hash PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_VARIABLE"); //Right. Let's do up the house.
								int MONEY_DROP_AMOUNT = rand() % 1500 + 100; // lets make it more random so r* wont recognize a pattern mch
								OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, ATMPos.x, ATMPos.y, ATMPos.z, 0, MONEY_DROP_AMOUNT, -31919185, FALSE, TRUE); //WHOP YOUR WAD ON THE COUNTA
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(-31919185); //SHUT YOUR MOUTH!
							}
							iMoney = 0;
						}
					}
					catch (...){ Log::Error("Got too much money."); }
				}
			}
				
		}	
	}
}
