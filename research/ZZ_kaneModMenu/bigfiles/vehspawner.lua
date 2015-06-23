vehSpawner = {}
plyPed = LocalPlayer().ID
vehList = {{"ADDER", "AIRBUS", "AIRTUG", "AKUMA", "ALPHA", "AMBULANCE", "ANNIHILATOR", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2",
"ASEA", "ASEA2", "ASTEROPE", "BAGGER", "BALETRAILER", "BALLER", "BALLER2", "BANSHEE", "BARRACKS", "BARRACKS2"},
{"BATI", "BATI2", "BENSON", "BFINJECTION", "BIFF", "BIFTA", "BISON", "BISON2", "BISON3", "BJXL",
"BLADE", "BLAZER", "BLAZER2", "BLAZER3", "BLIMP", "BLISTA", "BLISTA2", "BLISTA3", "BMX", "BOATTRAILER"},
{"BOBCATXL", "BODHI2", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BTYPE", "BUCCANEER", "BUFFALO", "BUFFALO2", "BUFFALO3",
"BULLDOZER", "BULLET", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "BUS", "BUZZARD", "BUZZARD2"},
{"CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CARBONRS", "CARGOBOB", "CARGOBOB2", "CARGOBOB3", "CARGOPLANE",
"CASCO", "CAVALCADE", "CAVALCADE2", "CHEETAH", "COACH", "COGCABRIO", "COMET2", "COQUETTE", "COQUETTE2", "CRUISER"},
{"CRUSADER", "CUBAN800", "CUTTER", "DAEMON", "DILETTANTE", "DILETTANTE2", "DINGHY", "DINGHY2", "DLOADER", "DOCKTUG",
"DODO", "DOMINATOR", "DOMINATOR2", "DOUBLE", "DUBSTA", "DUBSTA2", "DUBSTA3", "DUKES", "DUKES2", "DUMP"},
{"DUNE", "DUNE2", "DUSTER", "ELEGY2", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENDURO", "ENTITYXF", "EXEMPLAR",
"F620", "FAGGIO2", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FIXTER", "FLATBED"},
{"FORKLIFT", "FQ2", "FROGGER", "FROGGER2", "FUGITIVE", "FUROREGT", "FUSILADE", "FUTO", "GAUNTLET", "GAUNTLET2 ",
"GBURRITO", "GLENDALE", "GRAINTRAILER", "GRANGER", "GRESLEY", "GUARDIAN", "HABANERO", "HAKUCHOU", "HANDLER", "HAULER"},
{"HEXER", "HOTKNIFE", "HUNTLEY", "HYDRA ", "INFERNUS", "INGOT", "INNOVATION", "INSURGENT", "INSURGENT2", "INTRUDER",
"ISSI2", "JACKAL", "JB700", "JESTER", "JESTER2", "JET", "JETMAX", "JOURNEY", "KALAHARI", "KHAMELION"},
{"KURUMA", "KURUMA2", "LANDSTALKER", "LAZER", "LECTRO", "LGUARD", "LUXOR", "MAMMATUS", "MANANA", "MARQUIS",
"MARSHALL", "MASSACRO ", "MASSACRO2", "MAVERICK", "MESA", "MESA2", "MESA3", "MILJET", "MINIVAN", "MIXER"},
{"MIXER2", "MONROE", "MONSTER ", "MOWER", "MULE", "MULE2", "NEMESIS", "NINEF", "NINEF2", "ORACLE",
"ORACLE2", "PACKER", "PANTO", "PARADISE", "PATRIOT", "PBUS", "PCJ", "PENUMBRA", "PEYOTE", "PHANTOM"},
{"PHOENIX", "PICADOR", "PIGALLE", "POLICE", "POLICE2", "POLICE3", "POLICE4", "POLICEB", "POLICEOLD1", "POLICEOLD2",
"POLICET", "POLMAV", "PONY", "PONY2", "POUNDER", "PRAIRIE", "PRANGER", "PREDATOR", "PREMIER", "PRIMO"},
{"PROPTRAILER", "RADI", "RAKETRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RATLOADER", "RATLOADER2", "REBEL",
"REBEL2", "REGINA", "RENTALBUS", "RHAPSODY", "RHINO", "RIOT", "RIPLEY", "ROCOTO", "ROMERO", "RUBBLE"},
{"RUFFIAN", "RUINER", "RUMPO", "RUMPO2", "SABREGT", "SADLER", "SADLER2", "SANCHEZ", "SANCHEZ2", "SANDKING",
"SANDKING2", "SAVAGE", "SCHAFTER2", "SCHWARZER", "SCORCHER", "SCRAP", "SEASHARK", "SEASHARK2", "SEMINOLE", "SENTINEL"},
{"SENTINEL2", "SERRANO", "SHAMAL", "SHERIFF", "SHERIFF2", "SKYLIFT", "SLAMVAN", "SLAMVAN2", "SOVEREIGN", "SPEEDER",
"SPEEDO", "SPEEDO2", "SQUALO", "STALION", "STALION2", "STANIER", "STINGER", "STINGERGT", "STOCKADE", "STOCKADE3"},
{"STRATUM", "STRETCH", "STUNT", "SUBMERSIBLE", "SUBMERSIBLE2", "SULTAN", "SUNTRAP", "SUPERD", "SURANO", "SURFER",
"SURFER2", "SURGE", "TACO", "TAILGATER", "TANKER", "TAXI", "TECHNICAL", "THRUST", "TIPTRUCK", "TIPTRUCK2"},
{"TITAN", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2", "TR2", "TR3",
"TR4", "TRACTOR", "TRACTOR2", "TRACTOR3", "TRAILERLOGS", "TRAILERS", "TRAILERS2", "TRAILERS3", "TRAILERSMALL", "TRASH"},
{"TRFLAT", "TRIBIKE", "TRIBIKE2", "TRIBIKE3", "TROPIC", "TURISMOR", "TVTRAILER", "UTILLITRUCK", "UTILLITRUCK2", "UTILLITRUCK3",
"VACCA", "VADER", "VALKYRIE", "VELUM", "VELUM2 ", "VESTRA", "VIGERO", "VOLTIC", "VOODOO2", "WARRENER"},
{"WASHINGTON", "YOUGA", "ZENTORNO", "ZION", "ZION2", "ZTYPE"}}

function vehSpawner.spawnVeh(model)
	local hash = natives.GAMEPLAY.GET_HASH_KEY(model)
	--monster
	if hash == -441830889 then hash = 0xCD93A7DB end
	--gauntlet2
	if hash == 121423817 then hash = 0x14D22159 end
	--hydra
	if hash == 1735460305 then hash = 0x39D6E83F end
	--velum2
	if hash == -5899583 then hash = 0x403820E8 end

	if natives.STREAMING.IS_MODEL_VALID(hash) then
		local coords = natives.ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(plyPed, 0, 5, 2)
		local heading = natives.ENTITY.GET_ENTITY_HEADING(plyPed) + 90
		
		natives.STREAMING.REQUEST_MODEL(hash)
		
		-- Wait
		local tick = 0
		while not streaming.HasModelLoaded(hash) do
			tick = tick + 1

			if tick > 300 then
				tick = 0
				GUI.updateStatusText("Unable to load the model...", 1000)
				break
			end
			kanesMenu:Wait(5)
		end
		
		local veh = natives.VEHICLE.CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, heading, true, true)
		
		if spawnedVehs == nil then spawnedVehs = {} end
		
		if veh ~= 0 then
			table.insert(spawnedVehs, veh)
		end
		--if #spawnedVehs >= 15 then
		--	for _, v in pairs(spawnedVehs) do
		--		c_veh = CMemoryBlock(4)
		--		c_veh:WriteDWORD32(0, v)
		--		natives.ENTITY.SET_VEHICLE_AS_NO_LONGER_NEEDED(c_veh)
		--		c_veh:Release()
		--	end
		--end
	else
		print("Invalid model: ", model, hash)
	end
end


function vehSpawner.removeSpawnedVehs()
	if spawnedVehs ~= nil then
		for i,v in pairs(spawnedVehs) do
			if natives.PED.IS_PED_IN_VEHICLE(plyPed, v, false) == false then
				c_veh = CMemoryBlock(4)
				c_veh:WriteDWORD32(0, v)
				--natives.ENTITY.SET_VEHICLE_AS_NO_LONGER_NEEDED(c_veh)
				natives.ENTITY.DELETE_ENTITY(c_veh)
				
				if natives.ENTITY.DOES_ENTITY_EXIST(v) then
					print("Set as no longer needed!")
					natives.ENTITY.SET_VEHICLE_AS_NO_LONGER_NEEDED(c_veh)
				elseif natives.ENTITY.DOES_ENTITY_EXIST(v) == false then
				    spawnedVehs[i] = nil
				end

				c_veh:Release()
				kanesMenu:Wait(0)
			end
		end
		print("Vehicles left", #spawnedVehs)
	else
	    print("No vehicles!")
	end
end

--i was feeling a bit lazy, so the numbers are all hard coded in.. if you changed the number of vehicles, you need to change them in here
function vehSpawner.tick()
	if string.match(GUI.activeMenu, "[A-Za-z]+") == "vehSpawnerMenu" then
		
		GUI.setActiveMenu("vehSpawnerMenu" .. vehSpawner.lastMenu)

		--remove the original back button temporarily
		GUI.navButtons.navBack = {["keys"] = {}}

		if IsKeyDown(KEY_NUMPAD0) then
			--override the original back button(s)
			GUI.setActiveMenu("vehicleSpawner")
		end


		if IsKeyDown(KEY_NUMPAD4) then
			vehSpawner.lastMenu = vehSpawner.lastMenu - 1
			
			if vehSpawner.lastMenu <= 0 then
				vehSpawner.lastMenu = 18
			end
		end


		if IsKeyDown(KEY_NUMPAD6) then
			vehSpawner.lastMenu = vehSpawner.lastMenu + 1

			if vehSpawner.lastMenu >= 19 then
				vehSpawner.lastMenu = 1
			end
		end
	else
	    GUI.navButtons.navBack = {["keys"] = {KEY_NUMPAD0}}
	end
end


function vehSpawner.init()
	vehSpawner.lastMenu = 1

	vehSpawner.quickSpawn = {
	"MARSHALL", 
	"ADDER"
	}

	GUI.createMenu("vehicleSpawner", "vehicleMenu", "Vehicle Spawner", 0.09, 0.1, 0.125, 0.0625, 0.0015, 0.48, 4)
	GUI.addButton("vehicleSpawner", "Full List", GUI.setActiveMenu, "vehSpawnerMenu1", false, 0.35, 0)
	GUI.addButton("vehicleSpawner", "Remove Vehicles", vehSpawner.removeSpawnedVehs, nil, false, 0.35, 0)

	for k, v in pairs(vehSpawner.quickSpawn) do
		if v == "" or v == nil then v = "Not Set" end
		GUI.addButton("vehicleSpawner", v, vehSpawner.spawnVeh, v, false, 0.35, 0)
	end
	
		--GUI.createMenu("quickSpawn" .. i,  "vehicleSpawner", "No Vehicle Set", 0.09, 0.1, 0.125, 0.0625, 0.0015, 0.48, 4)
		--GUI.addButton("quickSpawn" .. i, "Vehicle not set", nil, nil, false, 0.35, 0)
		--GUI.addButton("quickSpawn" .. i, "Edit Vehicle", nil, nil, false, 0.35, 0)


	for i, v in pairs(vehList) do
		--the last argument (true) is a new setting in the gui lib. if set to true (or nil so it won't break exisiting menus), it will remember the active button position.
		--if set to false, it will set it to 1
		GUI.createMenu("vehSpawnerMenu" .. i, prevMenu, "Car Spawner (" .. i .. "/18)", 0.21, 0.08, 0.125, 0.0300, 0.000, 0.4, 4, true)

		for _, model in pairs(v) do
			--vehSpawner.spawnVeh(model)
			GUI.addButton("vehSpawnerMenu" .. i, model, vehSpawner.spawnVeh, model, false, 0.35, 0)
		end
	end
end