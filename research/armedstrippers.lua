local armedstrippers = {}
armedstrippers.peds = {}
armedstrippers.howMany = 130
armedstrippers.numberspawned = 0
armedstrippers.GUI = Libs["GUI"]
armedstrippers.GUIOpened = false
function armedstrippers.unload()
	for k,guard in pairs(armedstrippers.peds) do
		if( guard ~= nil) then
			PED.DELETE_PED(guard)
			armedstrippers.peds[k] = nil
		end
	end
end
function armedstrippers.deleteAll()
	for i = 0, armedstrippers.numberspawned, 1 do
	PED.DELETE_PED(armedstrippers.peds[i])
	end
end
function armedstrippers.TeleportTo(player)
	local ped =PLAYER.GET_PLAYER_PED(player)
	local playerPed = PLAYER.PLAYER_PED_ID()
	local pedPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0, 35.0, 0.0)
	ENTITY.SET_ENTITY_COORDS(playerPed,pedPosition.x,pedPosition.y,pedPosition.z,true,true,true,true)
	
end
function armedstrippers.init()
	
	for  i = 0 ,PLAYER.GET_NUMBER_OF_PLAYERS() ,1 do
		

	end
end
function armedstrippers.tick()
	if(get_key_pressed(Keys.F9))then
		armedstrippers.spawnBodyGuards()
		armedstrippers.spawnBodyGuards2()
		armedstrippers.spawnBodyGuards3()
		armedstrippers.spawnBodyGuards4()
		armedstrippers.spawnBodyGuards5()
		armedstrippers.spawnBodyGuards6()
		armedstrippers.spawnBodyGuards7()
		armedstrippers.spawnBodyGuards8()
		armedstrippers.spawnBodyGuards9()
		armedstrippers.spawnBodyGuards10()
		armedstrippers.spawnBodyGuards11()
		armedstrippers.TeleportTo(player)
		
	end
	if(get_key_pressed(Keys.F10))then
	armedstrippers.deleteAll()
	end
	armedstrippers.GUI.tick()
end
function armedstrippers.spawnBodyGuards()

	local strippergunID = GAMEPLAY.GET_HASH_KEY("a_m_m_tranvest_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)
	STREAMING.REQUEST_MODEL(strippergunID)

	while(not STREAMING.HAS_MODEL_LOADED(strippergunID)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
--		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
--		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID)
end
function armedstrippers.spawnBodyGuards2()

	local strippergunID2 = GAMEPLAY.GET_HASH_KEY("a_m_m_tranvest_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)
	STREAMING.REQUEST_MODEL(strippergunID2)
	
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID2)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID2,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
--		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
--		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID2)
end
function armedstrippers.spawnBodyGuards3()

	local strippergunID3 = GAMEPLAY.GET_HASH_KEY("s_f_y_hooker_03")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)


	STREAMING.REQUEST_MODEL(strippergunID3)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID3)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID3,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
	--	WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID3)
end

function armedstrippers.spawnBodyGuards4()
	local strippergunID4 = GAMEPLAY.GET_HASH_KEY("s_f_y_hooker_02")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID4)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID4)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID4,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
	--	WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID4)
end
function armedstrippers.spawnBodyGuards5()
	local strippergunID5 = GAMEPLAY.GET_HASH_KEY("s_f_y_hooker_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID5)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID5)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID5,playerPosition.x, playerPosition.y, playerPosition.z + 5,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID5)
end
function armedstrippers.spawnBodyGuards6()
	local strippergunID6 = GAMEPLAY.GET_HASH_KEY("a_c_rhesus")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID6)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID6)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID6,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID6)
end
function armedstrippers.spawnBodyGuards7()
	local strippergunID7 = GAMEPLAY.GET_HASH_KEY("a_f_y_topless_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID7)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID7)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID7,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID7)
end
function armedstrippers.spawnBodyGuards8()
	local strippergunID8 = GAMEPLAY.GET_HASH_KEY("a_m_y_breakdance_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID8)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID8)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID8,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID8)
end
function armedstrippers.spawnBodyGuards9()
	local strippergunID9 = GAMEPLAY.GET_HASH_KEY("a_f_m_fatcult_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID9)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID9)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID9,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned - 3
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID9)
end
function armedstrippers.spawnBodyGuards10()
	local strippergunID10 = GAMEPLAY.GET_HASH_KEY("a_f_y_topless_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID10)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID10)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID10,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID4strippergunID10)
end
function armedstrippers.spawnBodyGuards11()
	local strippergunID11 = GAMEPLAY.GET_HASH_KEY("a_f_y_topless_01")
	local playerPed = PLAYER.PLAYER_PED_ID()
	local player = PLAYER.GET_PLAYER_PED(playerPed)
	local playerID = PLAYER.PLAYER_ID()
	local playerExists = ENTITY.DOES_ENTITY_EXIST(playerPed)
	local playerPosition = ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0.0, 15.0, 0.0)
	local playerGroup = PED.GET_PED_GROUP_INDEX(playerPed)

	STREAMING.REQUEST_MODEL(strippergunID11)
	while(not STREAMING.HAS_MODEL_LOADED(strippergunID11)) do
			wait(50)
	end

	armedstrippers.peds[armedstrippers.numberspawned] = PED.CREATE_PED( 130,strippergunID11,playerPosition.x, playerPosition.y, playerPosition.z + 10,1,false,true)
		PED.SET_PED_CAN_SWITCH_WEAPON(armedstrippers.peds[armedstrippers.numberspawned],true)
		WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_RAILGUN"), 1000, true)
		--WEAPON.GIVE_DELAYED_WEAPON_TO_PED(armedstrippers.peds[armedstrippers.numberspawned], GAMEPLAY.GET_HASH_KEY("WEAPON_PISTOL"), 1000, false)
		PED.SET_PED_AS_GROUP_MEMBER(armedstrippers.peds[armedstrippers.numberspawned], playerGroup)
		armedstrippers.numberspawned = armedstrippers.numberspawned + 1
	STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(strippergunID11)
end
return armedstrippers