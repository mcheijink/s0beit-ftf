
kanesMenu = ScriptThread("kanesMenu")

-- Required
menuInit = {}
include("lib.lua")
include("functions/online_functions.lua")
include("functions/player_functions.lua")
include("functions/vehicle_functions.lua")
include("functions/bodyguard_functions.lua")
include("functions/object_functions.lua")
include("functions/global_functions.lua")
include("functions/misc_functions.lua")
include("functions/rain_functions.lua")

-- Big files
include("bigfiles/vehspawner.lua")
include("bigfiles/allanimations.lua")

locs = {}



function mainInit()
	----------- OPTIONS --------------
	SLPText = "I LOVE HACKING"  --- Set the scrolling license text text here.
	openKey = KEY_O ---- Set the key to whatever you want. Default is O
	personalVehicle = VEHICLE_ADDER ---- Set personal vehicle here, it spawns it when calling Personal Vehicle in vehicle tab.
	----------------------------------



	GUI.navButtons = {
						["menuOpen"]  = {["keys"] = {openKey}, ["menu"] = "mainMenu"},
						["menuClose"] = {["keys"] = {}},
						["navUp"] 	  = {["keys"] = {KEY_NUMPAD8}}, 
						["navDown"]   = {["keys"] = {KEY_NUMPAD2}}, 
						["select"] 	  = {["keys"] = {KEY_NUMPAD5}}, 
						["navBack"]   = {["keys"] = {KEY_NUMPAD0}}
					}

				

	GUI.createMenu("mainMenu", "", "~b~K~y~a~b~n~y~e'~b~s ~y~M~b~o~y~d ~b~M~y~e~b~n~y~u", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 7)
	-- Buttons
	GUI.addButton("mainMenu", "Player", GUI.setActiveMenu, "playerMenu", false, 0.5, 4,1)
	GUI.addButton("mainMenu", "Teleport", GUI.setActiveMenu, "teleportMenu", false, 0.5, 4,2)
	GUI.addButton("mainMenu", "Vehicle", GUI.setActiveMenu, "vehicleMenu", false, 0.5, 4,3)
	GUI.addButton("mainMenu", "Special", GUI.setActiveMenu, "specialMenu", false, 0.5, 4,5)
	GUI.addButton("mainMenu", "Objects", GUI.setActiveMenu, "objectMenu", false, 0.5, 4,4)
	GUI.addButton("mainMenu", "Bodyguards", GUI.setActiveMenu, "bodyguardMenu", false, 0.5, 4,4)
	GUI.addButton("mainMenu", "Misc", GUI.setActiveMenu, "miscMenu", false, 0.5, 4,4)
	GUI.addButton("mainMenu", "All Players", GUI.setActiveMenu, "allPlayers", false, 0.5, 4,4)
	GUI.addButton("mainMenu", "Online Players", GUI.setActiveMenu, "onlineMenu", false, 0.5, 4,5)

	


	GUI.createMenu("allPlayers", "mainMenu", "All players", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("allPlayers", "Explode", online.explodeEveryone, "", false, 0.5, 4,1)
	GUI.addButton("allPlayers", "Spawn stripper", online.spawnStripperEveryone, "", false, 0.5, 4,1)
	GUI.addButton("allPlayers", "Money Lobby ~r~[DISABLED]", online.moneyLobbyToggle, "", false, 0.5, 4,1)
	GUI.addButton("allPlayers", "Jail all", jailAll, "", false, 0.5, 4,1)
	GUI.addButton("allPlayers", "Teleport in vehicle to me", online.teleportAllToMe, "", false, 0.5, 4,1)
	--GUI.addButton("allPlayers", "Jail", online.jailEveryone, "", false, 0.5, 4,1)
	--GUI.addButton("allPlayers", "UnJail", online.unJailEveryone, "", false, 0.5, 4,1)

	
	
	GUI.createMenu("onlineMenu", "mainMenu", "Online players", 0.9, 0.02, 0.150, 0.0250, 0.000, 0.4, 4)

	GUI.createMenu("objectMenu", "mainMenu", "Object menu", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("objectMenu", "Object settings", GUI.setActiveMenu, "objectSettingsMenu", false, 0.5, 4,1)
	
	GUI.createMenu("objectSettingsMenu", "objectMenu", "Object menu", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("objectSettingsMenu", "Remove all", object.RemoveAll, "", false, 0.5, 4,1)
	
	

	GUI.createMenu("playerMenu", "mainMenu", "Player options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	
	
	GUI.createMenu("miscMenu", "mainMenu", "Misc options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("miscMenu", "Seatbelt ~r~[OFF]", misc.toggleSeatBelt, "", false, 0.5, 4,1)
	GUI.addButton("miscMenu", "Radio Disabled ~r~[OFF]", misc.toggleRadio, "", false, 0.5, 4,1)


	GUI.addButton("playerMenu", "God ~r~[OFF]", ply.toggleGod, "", false, 0.5, 4,1)
	GUI.addButton("playerMenu", "NoCops ~r~[OFF]", ply.toggleNoCops, "", false, 0.5, 4,2)
	GUI.addButton("playerMenu", "Unlimited Ammo ~r~[OFF]", ply.toggleUnlimitedAmmo, "", false, 0.5, 4,3)
	GUI.addButton("playerMenu", "No ragdoll ~r~[OFF]", ply.toggleNoRagdoll, "", false, 0.5, 4,4)
	GUI.addButton("playerMenu", "Visible ~r~[VISIBLE]", ply.toggleVisible, "", false, 0.5, 4,5)
	GUI.addButton("playerMenu", "Instakill ~r~[OFF]", online.instaKillToggle, "", false, 0.5, 4,5)
	GUI.addButton("playerMenu", "Remove badstuff",	online.removeBadStuff, "", false, 0.5, 4,5)
	GUI.addButton("playerMenu", "Animation menu",	GUI.setActiveMenu, "animMenu", false, 0.5, 4,5)
	
	-- Anim menu
	GUI.createMenu("animMenu", "playerMenu", "Animations", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("animMenu", "Take shit",	ply.playAnim, {"amb@medic@standing@tendtodead@base","base"}, false, 0.5, 4,5)
	GUI.addButton("animMenu", "My pee pee",	ply.playAnim, {"amb@code_human_in_car_idles@low@ps@idle_e","idle_n"}, false, 0.5, 4,5)
	GUI.addButton("animMenu", "Fucka you",	ply.playAnim, {"amb@code_human_in_car_mp_actions@finger@bodhi@rds@base","enter"}, false, 0.5, 4,5)


	GUI.createMenu("teleportMenu", "mainMenu", "Teleport", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("teleportMenu", "TP Waypoint", online.handleTPtoWP, LocalPlayer().ID, false, 0.5, 4,1)


	GUI.createMenu("vehicleMenu", "mainMenu", "Vehicle options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("vehicleMenu", "Vehicle God ~r~[OFF]", vehicle.toggleVehicleGod, "", false, 0.5, 4,1)
	GUI.addButton("vehicleMenu", "Boost Key ~r~[OFF]", vehicle.toggleBoostKey, "", false, 0.5, 4,2)
	GUI.addButton("vehicleMenu", "Fix Key ~r~[OFF]", vehicle.toggleFixKey, "", false, 0.5, 4,3)
	GUI.addButton("vehicleMenu", "Scrolling License ~r~[OFF]", vehicle.toggleLicensePlate, "", false, 0.5, 4,4)
	GUI.addButton("vehicleMenu", "Jump Key ~r~[OFF]", vehicle.toggleJumpKey, "", false, 0.5, 4,4)
	GUI.addButton("vehicleMenu", "Fix", vehicle.fixVehicle, "", false, 0.5, 4,5)
	GUI.addButton("vehicleMenu", "Upgrade Fully", vehicle.upgradePVehicle, nil,false, 0.5, 4,6)
	GUI.addButton("vehicleMenu", "Vehicle spawner", GUI.setActiveMenu, "vehicleSpawner",false, 0.5, 4,6)
	--GUI.addButton("vehicleMenu", "Personal Vehicle", vehicle.spawnVeh, VEHICLE_ADDER,false, 0.5, 4,6)

	GUI.createMenu("rainMenu", "specialMenu", "Rain menu", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	GUI.addButton("rainMenu", "Rain Missles", rain.changeRainSpawn, "missiles", false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Rain Whales", rain.changeRainSpawn, "whales", false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Rain Cows", rain.changeRainSpawn, "cows", false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Rain Clowns", rain.changeRainSpawn, "clowns", false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Rain Pantos", rain.changeRainSpawn, "pantos", false,0.5, 4,1)
	GUI.addButton("rainMenu", "Rain Cash", rain.changeRainSpawn, "cashbags", false,0.5, 4,1)
	GUI.addButton("rainMenu", "Clear", rain.clear, "", false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Decrease Rate", rain.changeSpawnRate, 5, false, 0.5, 4,1)
	GUI.addButton("rainMenu", "Increase Rate", rain.changeSpawnRate, -5, false, 0.5, 4,1)

	GUI.createMenu("specialMenu", "mainMenu", "Special options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
	--GUI.addButton("specialMenu", "Block highway ~r~[OFF]", online.toggleHighWayBlock, "", false, 0.5, 4,1)
	GUI.addButton("specialMenu", "Noclip ~r~[OFF]", ply.noclipToggle, nil, false, 0.5, 4,1)
	GUI.addButton("specialMenu", "Rain menu", GUI.setActiveMenu, "rainMenu", false, 0.5, 4,1)
end


-- Run
function kanesMenu:Run()
	player_cash_bags = {}
	player_cash_bags2 = {}
	freeze_vehicle = {}
	mainInit()
	online.menuInit()
	timer.Create ( "prison_loop", 5000, -1, function()
		online.prisonLoop()	
	end)
	-- Setting needed variables
	player_menus = {}
	godMode = false
	noCops = false
	unlimitedAmmo = false
	noRagdoll = false
	vehicleGod = false
	boostKey = false
	fixKey = false
	noClip = false
	instakill = false
	visible = true
	scrollingLicense = false
	moneyLobby = false
	jumpKey = false
	done = nil
	seatbelt = false
	donec = nil
	player_explode_loop = {}
	player_ufos = {}
	player_prison1 = {}
	player_prison2 = {}
	prison_position = {}
	online.handleMenu()
	player_spawnAsBodyguard = {}
	online.lesterMolesters = {}
	online.frozenPlayers = {}
	gameCrashPed = {}
	attached_objects = {}
	cashGun = true
	prevNumPlayers = 0
	rainSpawnRate = 100
	rainSpawnIsOn = false
	object.addObjects()
	handleCreateM()
	vehSpawner.init()
	---------------------------
	while self:IsRunning() do
		if IsKeyDown(KEY_F9) then
			print ("X:  "..LocalPlayer():GetPosition().x)
			print ("Y:  "..LocalPlayer():GetPosition().y)
			print ("Z:  "..LocalPlayer():GetPosition().z)
			print ("")
			locs[#locs+1] = 1
			print(#locs.."------------------------")
		end
		online.update()
		GUI.tick()
		ply.tick()
		vehicle.tick()
		misc.tick()
		vehSpawner.tick()
		online.highWayBlock()
		online.tick()
		rain.tick()
		animResearch.tick()
		self:Wait(0)
	end
end

-- OnError
function kanesMenu:OnError()
	print("kanesMenu Thread caused an error!")
	self:Reset()
end

-- Register
kanesMenu:Register()

-- Objects initizialed
