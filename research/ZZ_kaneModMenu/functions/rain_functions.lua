rain = {}
local plyPed = LocalPlayer().ID
local ply = LocalPlayer().ID


function rain.changeRainSpawn(rainType)
	if raintype ~= "" then
		rainToSpawn = rainType
		rainSpawnIsOn = true
		GUI.updateStatusText("The sky begins to open...", 1000)
	else
	    rainToSpawn = rainType
		rainSpawnIsOn = false
		GUI.updateStatusText("The sky begins to clear...", 1000)
	end
end

function rain.clear()
	rainToSpawn = ""
	rainSpawnIsOn = false
	GUI.updateStatusText("The sky begins to clear...", 1000)
end

function rain.rainSpawnTick()
	if(rainToSpawn == "whales") then
		models = {"a_c_humpback"}
	end

	if(rainToSpawn == "cows") then
		models = {"a_c_cow"}
	end

	if(rainToSpawn == "clowns") then
		models = {"s_m_y_clown_01"}
	end

	if(rainToSpawn == "pantos") then
		models = {"panto"}
	end

	if(rainToSpawn == "missiles") then
		models = {"WEAPON_VEHICLE_ROCKET", "WEAPON_FIREWORK"}
	end

	if(rainToSpawn == "ufos") then
		models = {"p_spinning_anus_s"}
	end
	
	if(rainToSpawn == "cashbags") then
	
	end

	if rainToSpawn ~= "" and models ~= nil then
		local randModel = models[math.random(#models)]
		local hash = natives.GAMEPLAY.GET_HASH_KEY(randModel)
		local plyCoords = natives.ENTITY.GET_ENTITY_COORDS(plyPed, true)
		local rand = {}
		rand.x = math.random(-100, 100)
		rand.y = math.random(-100, 100)
		rand.z = math.random(15, 50)
		local spawn = natives.ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(plyPed, rand.x, rand.y, rand.z)


		if(rainToSpawn == "missiles") then
			natives.GAMEPLAY.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(spawn.x, spawn.y, spawn.z, spawn.x, spawn.y, spawn.z - 100, 250, true, hash, ply, true, false, 10000.0)
		end


		if rainToSpawn == "cows" or rainToSpawn == "whales" or rainToSpawn == "clowns" then
			if(streaming.HasModelLoaded(hash)) then
				local ped = natives.PED.CREATE_PED(26, hash, spawn.x, spawn.y, spawn.z, 0, true, false)

				natives.PED.SET_PED_CAN_RAGDOLL(ped, true)
				natives.ENTITY.FREEZE_ENTITY_POSITION(ped, false)
				natives.PED.SET_PED_RAGDOLL_FORCE_FALL(ped)
				natives.PED.SET_PED_TO_RAGDOLL(ped, 5000, 5000, 0, true, true, true) 

				local pedDWORD = CMemoryBlock(4)
				pedDWORD:WriteDWORD32(0, ped)
				natives.ENTITY.SET_PED_AS_NO_LONGER_NEEDED(pedDWORD)
				pedDWORD:Release()
			else
				natives.STREAMING.REQUEST_MODEL(hash)
			end
		end
		
		if rainToSpawn == "cashbags" then
			natives.STREAMING.REQUEST_MODEL(0x113FD533)
			if natives.STREAMING.HAS_MODEL_LOADED(0x113FD533) then
				local moneyHash = natives.GAMEPLAY.GET_HASH_KEY("PICKUP_MONEY_CASE")
				natives.OBJECT.CREATE_AMBIENT_PICKUP(moneyHash, spawn.x, spawn.y, spawn.z+1, 0, 40000, 0x113FD533, false, true);
				natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533)
			end
		end


		if rainToSpawn == "pantos" then
			if(streaming.HasModelLoaded(hash)) then
				local veh = natives.VEHICLE.CREATE_VEHICLE(hash, spawn.x, spawn.y, spawn.z, 0, true, true)

				if math.random(1,2) == 2 then
					local rot = natives.ENTITY.GET_ENTITY_ROTATION(veh, 0)
					natives.ENTITY.SET_ENTITY_ROTATION(veh, rot.x, rot.y - 180, rot.z, 0, false)
				end
				
				local vehDWORD = CMemoryBlock(4)
				vehDWORD:WriteDWORD32(0, veh)
				natives.ENTITY.SET_VEHICLE_AS_NO_LONGER_NEEDED(vehDWORD)
				vehDWORD:Release()
			else
				natives.STREAMING.REQUEST_MODEL(hash)
			end
		end
	end
end

function rain.changeSpawnRate(num)
	if(rainSpawnRate + num < 50) then
		GUI.updateStatusText("Maximum spawn rate acheived (50ms)", 1000)
	else
		rainSpawnRate = rainSpawnRate + num
		GUI.updateStatusText("Spawn rate: " .. tostring(rainSpawnRate) .. "(ms)", 1000)
	end
end

function rain.tick()
	if rainSpawnIsOn then
		--this is basically a delay. by using this instead of using main:Wait(), it won't cause the whole script to pause
		if(nextSpawnTime == nil) then
			if rainSpawnRate == nil then rainSpawnRate = 100 end
			nextSpawnTime = natives.GAMEPLAY.GET_GAME_TIMER() + rainSpawnRate
		end

		if(nextSpawnTime < natives.GAMEPLAY.GET_GAME_TIMER()) then
			nextSpawnTime = nil
			rain.rainSpawnTick()
		end
	end
end