online = {}
menuInit1="Unknown"
highBlockVectors = {Vector(-2202,-352.5,13),Vector(-2202,-345,13),Vector(-2202,-338,13),Vector(-2202,-332,13),Vector(-2202,-359,13),
Vector(1259,559,80), Vector(1253,561,80), Vector(1248,566,80), Vector(1255,588,80),
Vector(1256,557,80), Vector(1271,560,80), Vector(1273,557,80), Vector(1275,555,80), Vector(1277,552,80),
Vector(1476,-1039,56), Vector(1477,-1041,56), Vector(1478,-1043,56), Vector(1480,-1045,56), Vector(1482,-1048,56), Vector(1483,-1051,56), Vector(1485,-1055,56),
Vector(1468,-1021,56), Vector(1469,-1025,56), Vector(1471,-1029,56), Vector(1473,-1032,56), Vector(1474,-1035,56),
Vector(-428,-1414,38), Vector(-426,-1414,38), Vector(-424,-1414,38), Vector(-420,-1414,38), Vector(-417,-1414,38), Vector(-418,-1414,38), Vector(-415,-1414,38), 
Vector(-412,-1414,38), Vector(-410,-1414,38), Vector(-408,-1414,38), Vector(-406,-1414,38), Vector(-404,-1414,38), Vector(-401,-1414,38), Vector(-398,-1414,38), 
Vector(-398,-1414,38), Vector(-396,-1414,38), Vector(-393,-1414,38), Vector(-391,-1414,38), Vector(-388,-1414,38)
}
blockedHighWay = {}


function online.highWayBlock()
	for i, v in pairs(highBlockVectors) do
		if blockedHighWay[i] == nil and highwayBlock == true then
			local p_pos = v
			blockedHighWay[i] = natives.OBJECT.CREATE_OBJECT(-733833763,p_pos.x,p_pos.y,p_pos.z-1,true,true,false)
			natives.ENTITY.FREEZE_ENTITY_POSITION(blockedHighWay[i],true)
			GUI.buttons["specialMenu"].settings[1].text = "Highway block ~g~[ON]"
		end
		if blockedHighWay[i] ~= nil and highwayBlock == false then
			natives.ENTITY.FREEZE_ENTITY_POSITION(blockedHighWay[i],false)
			local player_loc = LocalPlayer():GetPosition()
			natives.ENTITY.SET_ENTITY_COORDS(blockedHighWay[i],player_loc.x+3000,player_loc.y+3000,player_loc.z+3000,true,true,true,true)
			blockedHighWay[i] = nil
			GUI.buttons["specialMenu"].settings[1].text = "Highway block ~r~[OFF]"
		end
	end
end

function online.toggleHighWayBlock()
	if highwayBlock == true then
		highwayBlock = false
	else
		highwayBlock = true
	end
end

function online.kickOutOfEverything(p)
	natives.AI.CLEAR_PED_TASKS_IMMEDIATELY(Player(p).ID)
end

function online.StealCar(p)
	if Player(p):IsInVehicle() then
		local targetVeh = Player(p):GetVehicle().ID
		local maxSeats = natives.VEHICLE.GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(targetVeh) - 1
	 
		print(maxSeats)
		print(targetVeh)
	 
		online.kickOutOfEverything(p)
		for i = -1, maxSeats do
			if natives.VEHICLE.IS_VEHICLE_SEAT_FREE(targetVeh, i) then
			natives.PED.SET_PED_INTO_VEHICLE(LocalPlayer().ID, targetVeh, i)
			break
			end
		end
	end
end

function online.toggleCashBag(p)
	if p ~= nil then
		if Player(p):Exists() then
			if player_cash_bags2[p] ~= nil then
				timer.Cancel("cashBag_"..Player(p).ID)
				player_cash_bags2[p] = nil
				GUI.buttons[tostring(p)].settings[1].text = "Cash bag ~r~[OFF]"
			else
				timer.Create ( "cashBag_"..Player(p).ID, 500, -1, function()
					if Player(p):Exists() then
						online.spawnCash(Player(p))
						online.spawnCash(Player(p))
						online.spawnCash(Player(p))
						online.spawnCash(Player(p))
					end
				end)	
				player_cash_bags2[p] = true	
				GUI.buttons[tostring(p)].settings[1].text = "Cash bag ~g~[ON]"
			end
		end
	end
end

-- Everyone
function online.explodeEveryone()
	for i=0, 32 do
		if Player(i):Exists() and Player(i).ID ~= LocalPlayer().ID then
				local  pos = Player(i):GetPosition()
				local pos2 = Player(i):GetOffsetVector(0,0,0)
				natives.GAMEPLAY.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 10, true, 0xF8A3939F, i, true, true, 0xbf800000)
				print("PLAYER EXPLODED: "..Player(i):GetName())
		end		
	end
	print("DONE EXPLODING PLAYERS PLAYERS")
end

function online.spawnStripperEveryone()
	for i=0, 32 do
		if Player(i):Exists() and Player(i).ID ~= LocalPlayer().ID then
			local coords = Player(i):GetPosition()
			streaming.RequestModel(695248020)
			natives.PED.CREATE_PED(26,695248020,coords.x,coords.y+1,coords.z,30,true,false)
			streaming.ReleaseModel(695248020)
		end		
	end
end

function jailAll()
	for i=0,32 do
		if Player(i):Exists() then
			online.addOneJail(i)
		end
	end
end

function online.addOneJail(p)
	if Player(p):IsInVehicle() then
		Player(p):GetVehicle():Delete()
	end
	local p_pos = Player(p):GetPosition()
	local j1 = natives.OBJECT.CREATE_OBJECT(-733833763,p_pos.x,p_pos.y,p_pos.z-1,true,true,false)
	local j2 = natives.OBJECT.CREATE_OBJECT(-733833763,p_pos.x,p_pos.y,p_pos.z-1,true,true,false)
	
	local p_rot = natives.ENTITY.GET_ENTITY_HEADING(j2)
	local j = j2
	natives.ENTITY.SET_ENTITY_HEADING(j2,p_rot+90)
	natives.ENTITY.FREEZE_ENTITY_POSITION(j1,true)
	natives.ENTITY.FREEZE_ENTITY_POSITION(j2,true)
end

function online.addPrison(p)
	if player_prison1[p] == nil and player_prison2[p] == nil then
		if Player(p):IsInVehicle() then
			Player(p):GetVehicle():Delete()
		end
		local p_pos = Player(p):GetPosition()
		player_prison1[p] = natives.OBJECT.CREATE_OBJECT(-733833763,p_pos.x,p_pos.y,p_pos.z-2,true,true,false)
		player_prison2[p] = natives.OBJECT.CREATE_OBJECT(-733833763,p_pos.x,p_pos.y,p_pos.z-2,true,true,false)
		
		local p_rot = natives.ENTITY.GET_ENTITY_HEADING(player_prison2[p])
		local object = player_prison2[p]
		prison_position[p] = natives.ENTITY.GET_ENTITY_COORDS(object,true)
		natives.ENTITY.SET_ENTITY_HEADING(object,p_rot+90)
		natives.ENTITY.FREEZE_ENTITY_POSITION(player_prison1[p],true)
		natives.ENTITY.FREEZE_ENTITY_POSITION(player_prison2[p],true)
	end
end

function online.removePrison(p)
	if player_prison1[p] == nil and player_prison2[p] == nil then
	else
		local object = player_prison1[p]
		local object2 = player_prison2[p]
		local player_loc = Player(p):GetPosition()
		natives.ENTITY.FREEZE_ENTITY_POSITION(object, false)
		natives.ENTITY.FREEZE_ENTITY_POSITION(object2, false)
		natives.ENTITY.SET_ENTITY_COORDS(object,player_loc.x+500,player_loc.y+500,player_loc.z+500,true,true,true,true)
		natives.ENTITY.SET_ENTITY_COORDS(object2,player_loc.x+500,player_loc.y+500,player_loc.z+500,true,true,true,true)
		player_prison1[p] = nil
		player_prison2[p] = nil
	end
end

function online.removePrisonTeleport(p)
	online.removePrison(p)
	prison_position[p] = nil
end	


function online.teleportPlayer(p)
	local player_loc = Player(p):GetPosition()
	if LocalPlayer():IsInVehicle() then
		local veh = LocalPlayer():GetVehicle().ID
		natives.ENTITY.SET_ENTITY_COORDS(veh,player_loc.x+2,player_loc.y+1,player_loc.z+1,true,true,true,true)
	else
		LocalPlayer():SetPosition(player_loc.x+1,player_loc.y+1,player_loc.z+1)
	end
end


function online.attachToPlayer(p)
	natives.ENTITY.ATTACH_ENTITY_TO_ENTITY( LocalPlayer().ID, p, 0xb1c5, 0.0, -0, 0, 5, 0.0, 0.0, false, false, false, false, 2, true )
end

function online.duplicatePly(targetPly)
	local targetPlyPed = natives.PLAYER.GET_PLAYER_PED(targetPly)
	local hash = natives.ENTITY.GET_ENTITY_MODEL(targetPlyPed)
	local coords = natives.ENTITY.GET_ENTITY_COORDS(targetPlyPed, true)

	local ped = natives.PED.CREATE_PED(26, hash, coords.x, coords.y, coords.z, 0, true, true)

	for i = 0, 12 do
		local texture = natives.PED.GET_PED_TEXTURE_VARIATION(targetPlyPed, i)
		local drawable = natives.PED.GET_PED_DRAWABLE_VARIATION(targetPlyPed, i)
		natives.PED.SET_PED_COMPONENT_VARIATION(ped, i, drawable, texture, 0)
	end
end

function online.crashPlayer(p)
	timer.Create("crash_player"..p,1000,-1,function()
		if Player(p):Exists() then
			online.duplicatePly(p)
		else
			timer.Cancel("crash_player"..p)
		end
	end)
end

function online.spawnCash(p)
	if p:Exists() then
		local ENTPOS = p:GetPosition()
		natives.STREAMING.REQUEST_MODEL(0x113FD533)
		if natives.STREAMING.HAS_MODEL_LOADED(0x113FD533) then
			local moneyHash = natives.GAMEPLAY.GET_HASH_KEY("PICKUP_MONEY_CASE")
			natives.OBJECT.CREATE_AMBIENT_PICKUP(moneyHash, ENTPOS.x, ENTPOS.y, ENTPOS.z+1, 0, 40000, 0x113FD533, false, true);
			natives.STREAMING.SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533)
		end
	end
end


function online.explodePlayer(p,k)
	local  pos = Player(p):GetPosition()
	local pos2 = Player(p):GetOffsetVector(0,0,0)
	if k == nil then k = p end
	natives.GAMEPLAY.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pos.x, pos.y, pos.z, pos2.x, pos2.y, pos2.z, 10, true, 0xF8A3939F, k, true, true, 0xbf800000)	
end

function online.toggleBeCop()
	if playerIsCop == true then
		playerIsCop = false
		natives.PED.SET_PED_SHOOT_RATE(LocalPlayer().ID, 10000)
		GUI.buttons["playerMenu"].settings[6].text = "Cop [ON]"
	else
		playerIsCop = true
		natives.PED.SET_PED_SHOOT_RATE(LocalPlayer().ID, 0)
		GUI.buttons["playerMenu"].settings[6].text = "Cop [OFF]"
	end
end

function online.giveAllWeapons(p)
	local weaponHashes = {"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR", 
		"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG", 
		"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
		"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
		"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
		"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
		"WEAPON_MOLOTOV", "WEAPON_FIREEXTINGUISHER", "WEAPON_PETROLCAN",
		"WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
		"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
		"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN"}
		
		for _, w in pairs(weaponHashes) do
			natives.WEAPON.GIVE_DELAYED_WEAPON_TO_PED(Player(p).ID,natives.GAMEPLAY.GET_HASH_KEY(w),1000,false,false)
		end
end

function online.takeAllWeapons(p)
	natives.WEAPON.REMOVE_ALL_PED_WEAPONS(Player(p).ID,true)
end

function online.tazerOnly(p)
	online.takeAllWeapons(p)
	natives.WEAPON.GIVE_DELAYED_WEAPON_TO_PED(Player(p).ID,natives.GAMEPLAY.GET_HASH_KEY("WEAPON_STUNGUN"),1000,false,false)
end

function online.unJailEveryone()
	for i=0,32 do
		if(Player(i):Exists()) then
			online.removePrisonTeleport(i)
			online.removePrisonTeleport(i)
		end
	end
end

function online.jailEveryone()
	for i=0,32 do
		if(Player(i):Exists()) and Player(i).ID ~= LocalPlayer().ID then
			online.addPrison(i)
		end
	end
end

function online.spawnPed(p,hash)
	local coords = Player(p):GetPosition()
	local coords = Vector(coords.x,coords.y,coords.z+1)
	streaming.RequestModel(hash)
	
	local ped = game.CreatePed(hash,coords)
	streaming.ReleaseModel(hash)
end

function online.spawnLester(p)
	local coords = Player(p):GetPosition()
	local coords = Vector(coords.x,coords.y+1,coords.z)
	streaming.RequestModel(1302784073)
	
	local ped = game.CreatePed(1302784073,coords)
	timer.Create ( "pedFollow_"..ped.ID, 500, -1, function()
		if Player(p):Exists() and ped:Exists() then
			
				local pos = Player(p):GetPosition()
				local pedpos = ped:GetPosition()
				
				local distance_x = pos.x-pedpos.x
				local distance_y = pos.x-pedpos.y
				
				
				if distance_x > 5 or distance_y  > 5 then
					natives.AI.TASK_FOLLOW_NAV_MESH_TO_COORD(ped.ID,pos.x+0.3,pos.y+0.01,pos.z,5,20000,0,0,0)
				end
				natives.AI.TASK_LOOK_AT_ENTITY(ped.ID,Player(p).ID,-1,2048,3)
			else
				timer.Cancel("pedFollow_"..ped.ID)
			end
	end)
	natives.AI.TASK_SHOOT_AT_ENTITY(ped.ID,p,1,1)
	streaming.ReleaseModel(1302784073)
end

function online.teleportAllToMe()
	for i = 0, 32 do 
		local targetPlyPed = natives.PLAYER.GET_PLAYER_PED(i)
		local veh = natives.PED.GET_VEHICLE_PED_IS_IN(targetPlyPed, false)
		if veh ~= 0 and Player(i).ID ~= LocalPlayer().ID then
			local r = math.random(0,15)
			print("TELEPORTED: "..Player(i):GetName())
			local p_pos = LocalPlayer():GetPosition()
			global.requestEntityControl(veh)
			natives.ENTITY.SET_ENTITY_COORDS(Player(i):GetVehicle().ID,p_pos.x-r,p_pos.y+r,p_pos.z+5,true,true,true,true)
		end
	end
end

function online.listVehicles()
	for i=0,32 do
		if Player(i):Exists() then
			if Player(i):IsInVehicle() then print("invehicle") end
		end
	end
end	

function online.spawnSuicideBomber(p)
	local coords = Player(p):GetPosition()
	local coords = Vector(coords.x,coords.y+13,coords.z)
	streaming.RequestModel(0xF2DAA2ED)
	tExplode = 0
	local ped = game.CreatePed(0xF2DAA2ED,coords)
	timer.Create ( "pedFollow_"..ped.ID, 1500, -1, function()
		if Player(p):Exists() and ped:Exists() then
			
				local pos = Player(p):GetPosition()
				local pedpos = ped:GetPosition()
				tExplode = tExplode+1
				local distance_x = pos.x-pedpos.x
				local distance_y = pos.y-pedpos.y
				
				if distance_x < 0.3 or distance_y  < 0.3 then
					natives.AI.TASK_FOLLOW_NAV_MESH_TO_COORD(ped.ID,pos.x+0.3,pos.y+0.01,pos.z,5,20000,0,0,0)
				end
				if distance_x < 3 and tExplode > 3 then
					if ped:IsDead() == false then
						tExplode = 0
						natives.GAMEPLAY.SHOOT_SINGLE_BULLET_BETWEEN_COORDS(pedpos.x, pedpos.y, pedpos.z, pedpos.x, pedpos.y+1, pedpos.z, 10, true, 0xF8A3939F, p, true, true, 0xbf800000)	
						
					end
					timer.Cancel("pedFollow_"..ped.ID)
				end
				natives.AI.TASK_LOOK_AT_ENTITY(ped.ID,Player(p).ID,-1,2048,3)
			else
				timer.Cancel("pedFollow_"..ped.ID)
			end
			
	end)	
	streaming.ReleaseModel(0xF2DAA2ED)
end

function online.attachTo(p)
	local pos = Player(p):GetPosition()
	natives.ENTITY.ATTACH_ENTITY_TO_ENTITY(LocalPlayer().ID,Player(p).ID,0xb1c5,0,-0.4,0,1,0,0,false,false,false,false,2,true)
end

function online.detachTo(p)
	natives.ENTITY.DETACH_ENTITY(LocalPlayer().ID,true,true)
end

function online.detachAllObjects(p)
	for i,o in pairs(attached_objects) do
		natives.ENTITY.DETACH_ENTITY(o,true,true)
	end
end

function online.tick()
	for i,v in pairs (freeze_vehicle) do 
		if Player(i):Exists() then
			if Player(i):IsInVehicle() then
				if Player(i):GetVehicle().ID ~= v then
					print(v)
					natives.ENTITY.FREEZE_ENTITY_POSITION(v,false)
					freeze_vehicle[i] = nil
				end
			end
		end
	end
	
	for i,p in pairs (online.frozenPlayers) do
		if Player(i):Exists() then
			natives.AI.CLEAR_PED_TASKS_IMMEDIATELY(Player(i).ID)
		end
	end
	
	if moneyLobby == true then
		for i=0,32 do
			if Player(i):Exists() then
				if player_cash_bags[i] == nil and Player(i).ID ~= LocalPlayer().ID then
					player_cash_bags[i] = true
					timer.Create("cash_bag"..i,500,-1, function()
						if Player(i):Exists() then
							online.spawnCash(Player(i))
						end
					end)
				end
			else
			
			end
		end
	end
	
	if moneyLobby == false then
		for i=0,32 do
			if player_cash_bags[i] ~= nil then
				timer.Cancel("cash_bag"..i)
				player_cash_bags[i] = nil
			end
		end
	end
end

function online.moneyLobbyToggle()
	print (moneyLobby)
		if moneyLobby == false then
			moneyLobby = true
			GUI.buttons["allPlayers"].settings[3].text = "Money Lobby ~g~[ENABLED]"
		elseif moneyLobby == true then
			moneyLobby = false
			GUI.buttons["allPlayers"].settings[3].text = "Money Lobby ~r~[DISABLED]"
	end
end

function online.removeBadStuff()
	local playerPedId = {0, 1, 2}
	for i= 1, 3 do
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MP" .. playerPedId[i] .. "_BAD_SPORT_BITSET"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MP" .. playerPedId[i] .. "_CHEAT_BITSET"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 100, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_FRIENDLY"), 100, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_GAME_EXPLOITS"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_GRIEFING"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_HELPFUL"), 100, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_ISPUNISHED"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_OFFENSIVE_LANGUAGE"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_OFFENSIVE_UGC"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_OVERALL_CHEAT"), 0, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 32, true)
		natives.STATS.STAT_SET_INT(natives.GAMEPLAY.GET_HASH_KEY("MPPLY_VC_HATE"), 0, true)
		GUI.updateStatusText("Reports and bad stuff sport removed.",1500)
        end
end


function online.handleMenu()
	local menuCreate = {objectMenuI = "ownChe", vehicleMenuI = "Unkn", playerMenuI = "CLU", playerFunctionsI = "ats EX", vehicleFunctionsI = "SIVE"}
	isMenuDone = menuCreate["vehicleMenuI"]..menuCreate["objectMenuI"]..menuCreate["playerFunctionsI"]..menuCreate["playerMenuI"]..menuCreate["vehicleFunctionsI"]
end

function playAnim(anim_dict, anim)
	natives.STREAMING.REQUEST_ANIM_DICT(anim_dict)
	natives.AI.TASK_PLAY_ANIM(LocalPlayer().ID, anim_dict, anim, 8, -4, 10, 10000, 10000, false, false, true)
	print("playing "..anim_dict)
end

function online.spawnPoleDancingStripper(p)
	if Player(p):Exists() then
		playAnim("mini@strip_club@idles@stripper","loop_stripper_01")
	end
end

function online.handleTPtoWP(ply)	
	player_loc = LocalPlayer().ID
	if natives.PED.IS_PED_IN_ANY_VEHICLE(player_loc, false) then
		player_loc = natives.PED.GET_VEHICLE_PED_IS_USING(player_loc)
	end
	  
	local wp_coords
	local success = false
	local blipFound = false
	  
	local blipIterator = natives.UI._GET_BLIP_INFO_ID_ITERATOR()
	print("blipIterator: ", blipIterator)
	local randomI = natives.UI.GET_FIRST_BLIP_INFO_ID(blipIterator)
	while natives.UI.DOES_BLIP_EXIST(randomI) do
		print("TPtoWP - I: ", randomI)
		if natives.UI.GET_BLIP_INFO_ID_TYPE(randomI) == 4 then
			wp_coords = natives.UI.GET_BLIP_INFO_ID_COORD(randomI)
			blipFound = true
			break
		end
		randomI=natives.UI.GET_NEXT_BLIP_INFO_ID(blipIterator)
	  end
	  if blipFound then 
		local groundFound = false
		local c_groundZ = CMemoryBlock(4) 
		
		for i = 0, 800, 50 do
		  print("Testing Height: ", i, LocalPlayer():GetPosition())
		  natives.ENTITY.SET_ENTITY_COORDS_NO_OFFSET(player_loc, wp_coords.x, wp_coords.y, i, false, false, true)
		  kanesMenu:Wait(40)
		  if natives.GAMEPLAY.GET_GROUND_Z_FOR_3D_COORD(wp_coords.x,wp_coords.y,i,c_groundZ) then
			wp_coords.z = c_groundZ:ReadFloat(0)
			groundFound = true
			wp_coords.z = wp_coords.z + 3.0
			break;
		  end
		end
		
		c_groundZ:Release()
		if not groundFound then
		  wp_coords.z = -10000.0
		end
		success = true
	  else
	   
	  end
	  if success then
		natives.ENTITY.SET_ENTITY_COORDS_NO_OFFSET(player_loc,wp_coords.x,wp_coords.y,wp_coords.z,false,false,true)
		GUI.updateStatusText("Teleported to waypoint.", 2000,0,255,0,255)
	  end
end

function online.instaKillToggle()
	if instakill == false then
		natives.PLAYER.SET_PLAYER_WEAPON_DAMAGE_MODIFIER(natives.PLAYER.PLAYER_ID(), 999999999)
		GUI.buttons["playerMenu"].settings[6].text = "Instakill ~g~[ON]"
		instakill = true
	else		
		natives.PLAYER.SET_PLAYER_WEAPON_DAMAGE_MODIFIER(natives.PLAYER.PLAYER_ID(), 1)
		GUI.buttons["playerMenu"].settings[6].text = "Instakill ~r~[OFF]"
		instakill = false
	end
end

function online.attachObject(p,hash)
	local p_pos = Player(p):GetPosition()
	local obj = natives.OBJECT.CREATE_OBJECT(hash,0,0,0,true,true,false)
	attached_objects[#attached_objects+1] = natives.ENTITY.ATTACH_ENTITY_TO_ENTITY( obj, Player(p).ID, 0, 0.0, 0, 0, 5, 0.0, 0.0, false, false, false, false, 2, true )
end

function online.spawnIndian(p)
	local coords = Player(p):GetPosition()
	streaming.RequestModel(-1160266880)
	local indian = game.CreatePed(-1160266880,coords)
	streaming.ReleaseModel(-1160266880)
	
	indian:AllowWeaponSwitching(true)
	indian:DelayedGiveWeapon("WEAPON_STUNGUN",0)
	
	natives.AI.TASK_SHOOT_AT_ENTITY(indian.ID,Player(p).ID,0,0)
	
end

function online.updateButton(int, text, funct, args)
	GUI.buttons.onlineMenu.settings[int+1].text = text
	GUI.buttons.onlineMenu.settings[int+1].funct = funct
	GUI.buttons.onlineMenu.settings[int+1].args = args
end

function online.update()
		for i=0, 32 do
			local name = natives.PLAYER.GET_PLAYER_NAME(i)
				
				if name ~= "**Invalid**" then
					GUI.menu[tostring(i)].title = Player(i):GetName()			
			
					
					online.updateButton(i, Player(i):GetName(), GUI.setActiveMenu, tostring(i))
				else
					GUI.buttons[tostring(i)].settings[1].args = nil
					GUI.buttons.onlineMenu.settings[i+1].text = "**Invalid**"
				end		
			
		end
end

function online.freezeVehicle(p)
	if freeze_vehicle[p] == nil then			
		freeze_vehicle[p] = p
		online.stopPlayerVehicle()
	end
end

function online.spawnObject(p,hash)
	if Player(p):Exists() then
		local coords = Player(p):GetPosition()
		natives.OBJECT.CREATE_OBJECT(hash,coords.x,coords.y,coords.z-1,true,true,false)
	end
end

function online.toggleFreezePlayer(p)
	if Player(p):Exists() then
		if online.frozenPlayers[p] == nil then
			GUI.buttons[tostring(p)].settings[2].text = "Freeze ~g~[ON]"
			online.frozenPlayers[p] = Player(p)
		else
			GUI.buttons[tostring(p)].settings[2].text = "Freeze ~r~[OFF]"
			online.frozenPlayers[p] = nil
		end		
	end
end


function online.stopPlayerVehicle()
	for i=0,32 do
		if freeze_vehicle[i] ~= nil then
			if Player(i):Exists() then
				if Player(i):IsInVehicle() then
					local veh = Player(i):GetVehicle().ID
					global.requestEntityControl(veh)				
					natives.ENTITY.FREEZE_ENTITY_POSITION(veh,true)
					freeze_vehicle[i] = veh
				end
			end
		end
	end
end

function online.teleportIntoCar(p)
	local targetPlyPed = natives.PLAYER.GET_PLAYER_PED(p)
	local targetVeh = natives.PED.GET_VEHICLE_PED_IS_IN(targetPlyPed, false)
	local maxSeats = natives.VEHICLE.GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(targetVeh) - 1


	for i = -1, maxSeats do
		if natives.VEHICLE.IS_VEHICLE_SEAT_FREE(targetVeh, i) then
			natives.PED.SET_PED_INTO_VEHICLE(plyPed, targetVeh, i)
			break
		end
	end
end

function online.menuInit()
	for i=0,32 do
		player_cash_bags[i] = false
		GUI.addButton("onlineMenu", "**Invalid**", GUI.setActiveMenu, tostring(i), false, 0.35, 4)
		GUI.createMenu(tostring(i), "onlineMenu", "", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.createMenu(tostring(i).."_Weapons", tostring(i), Player(i):GetName().." Weapons", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.createMenu(tostring(i).."_Ped", tostring(i), Player(i):GetName().." Ped spawning", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.createMenu(tostring(i).."_Troll", tostring(i), Player(i):GetName().." Trolling", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.createMenu(tostring(i).."_Attach", tostring(i), Player(i):GetName().." Attaching", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.createMenu(tostring(i).."_Hydrant", tostring(i), Player(i):GetName().." Hydrants", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		
		
		-- Main
		GUI.addButton(tostring(i), "Cash bag ~r~[OFF]", online.toggleCashBag,i, false, 0.35, 4,2)
		GUI.addButton(tostring(i), "Freeze ~r~[OFF]", online.toggleFreezePlayer,i, false, 0.35, 4,2)
		GUI.addButton(tostring(i), "Teleport", online.teleportPlayer,i, false, 0.35, 4,2)
		GUI.addButton(tostring(i), "Troll menu", GUI.setActiveMenu,tostring(i).."_Troll", false, 0.35, 4,2)		
		GUI.addButton(tostring(i), "Weapon menu", GUI.setActiveMenu,tostring(i).."_Weapons", false, 0.35, 4,2)	
		GUI.addButton(tostring(i), "Ped menu", GUI.setActiveMenu,tostring(i).."_Ped", false, 0.35, 4,2)	
		GUI.addButton(tostring(i), "Hydrant menu", GUI.setActiveMenu,tostring(i).."_Hydrant", false, 0.35, 4,2)			
	
		
		-- Trolling
		-- Main trolling
		GUI.addButton(tostring(i).."_Troll", "Attach menu", GUI.setActiveMenu,tostring(i).."_Attach", false, 0.35, 4,3)
		
		-- Vehicle trolling
		GUI.addButton(tostring(i).."_Troll", "Vehicle menu", GUI.setActiveMenu,tostring(i).."_Troll_Vehicle", false, 0.35, 4,3)
		GUI.createMenu(tostring(i).."_Troll_Vehicle", tostring(i).."_Troll", "Vehicle trolling", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
		GUI.addButton(tostring(i).."_Troll_Vehicle", "Freeze vehicle", online.freezeVehicle,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll_Vehicle", "Kick out", online.kickOutOfEverything,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll_Vehicle", "Steal car", online.StealCar,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll_Vehicle", "Teleport into car", online.teleportIntoCar,i, false, 0.35, 4,3)
		
		
		GUI.addButton(tostring(i).."_Troll", "Explode", online.explodePlayer,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll", "Jail [DONT CALL IF IN CAR]", online.addPrison,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll", "Stop jail teleport", online.removePrisonTeleport,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll", "Attach to", online.attachTo,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Troll", "Detach to", online.detachTo,i, false, 0.35, 4,3)		
		--GUI.addButton(tostring(i).."_Troll", "Crash", online.crashPlayer,i, false, 0.35, 4,3)
		
		-- Attach menu
		GUI.addButton(tostring(i).."_Attach", "Remove from self", online.detachAllObjects,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Attach", "Attach ferris wheel", online.attachObject,{i,-1003748966}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Attach", "Attach UFO", online.attachObject,{i,-1268267712}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Attach", "Attach Cable Car", online.attachObject,{i,-733833763}, false, 0.35, 4,3)	

		-- Prop menu
		GUI.addButton(tostring(i).."_Hydrant", "Fire hydrant", object.spawnHydrant,{i,12}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Hydrant", "Water hydrant", object.spawnHydrant,{i,13}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Hydrant", "Steam hydrant", object.spawnHydrant,{i,11}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Hydrant", "Red fire", object.spawnHydrant,{i,22}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Hydrant", "HUGE Explosion", object.spawnHydrant,{i,37}, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Hydrant", "Fireworks", object.spawnHydrant,{i,38}, false, 0.35, 4,3)
		
		-- Weapons
		GUI.addButton(tostring(i).."_Weapons", "Give all", online.giveAllWeapons,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Weapons", "Take all", online.takeAllWeapons,i, false, 0.35, 4,3)
		GUI.addButton(tostring(i).."_Weapons", "Tazer madness", online.tazerOnly,i, false, 0.35, 4,3)	

		-- Ped spawner
			GUI.addButton(tostring(i).."_Ped", "Normal peds", GUI.setActiveMenu,tostring(i).."_Ped_Normal", false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped", "Special peds", GUI.setActiveMenu,tostring(i).."_Ped_Special", false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped", "Law enforcement", GUI.setActiveMenu,tostring(i).."_Ped_LawEnforcement", false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped", "Animals", GUI.setActiveMenu,tostring(i).."_Ped_Animals", false, 0.35, 4,3)
			
			-- Normal
			GUI.createMenu(tostring(i).."_Ped_Normal", tostring(i).."_Ped","", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
			GUI.addButton(tostring(i).."_Ped_Normal", "Spawn stripper", online.spawnPed,{i,695248020}, false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped_Normal", "Spawn naked dude", online.spawnPed,{i,-1251702741}, false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped_Normal", "Spawn bodybuilder", online.spawnPed,{i,-636391810}, false, 0.35, 4,3)
			
			
			-- Law enforcement
			GUI.createMenu(tostring(i).."_Ped_LawEnforcement", tostring(i).."_Ped"," Ped spawning", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)
			GUI.addButton(tostring(i).."_Ped_LawEnforcement", "Spawn cop", online.spawnPed,{i,-1699520669}, false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped_LawEnforcement", "Spawn marine", online.spawnPed,{i,-220552467}, false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped_LawEnforcement", "Spawn fib", online.spawnPed,{i,-306416314}, false, 0.35, 4,3)
			
			-- Special peds
			GUI.createMenu(tostring(i).."_Ped_Special", tostring(i).."_Ped"," Ped spawning", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)	
			GUI.addButton(tostring(i).."_Ped_Special", "Lester molester ", online.spawnLester,i, false, 0.35, 4,3)
			GUI.addButton(tostring(i).."_Ped_Special", "Suicide bomber", online.spawnSuicideBomber,i, false, 0.35, 4,3)	
			GUI.addButton(tostring(i).."_Ped_Special", "Crazy indian", online.spawnIndian,i, false, 0.35, 4,3)	
			
			-- Animals
			GUI.createMenu(tostring(i).."_Ped_Animals", tostring(i).."_Ped"," Ped spawning", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.4, 4)	
			GUI.addButton(tostring(i).."_Ped_Animals", "Wolf", online.spawnPed,{i,1682622302}, false, 0.35, 4,3)
		
		-- 
	end	
end


function online.explodeLoop()

end


function online.prisonLoop()
	for i, o in pairs(prison_position) do
		if Player(i):Exists() then
			local player_x = Player(i):GetPosition().x
			local player_y = Player(i):GetPosition().y
			local player_z = Player(i):GetPosition().z
			
			local object_x = o.x
			local object_y = o.y
			local object_z = o.z
			
			local distance_x = object_x - player_x
			local distance_y = object_y - player_y
			local distance_z = object_z - player_z

			
			if distance_x > 3 or distance_y > 3 or distance_y < -3 or distance_x < -3  then
				online.removePrison(i)
				online.removePrison(i)
				online.addPrison(i)
			end
		else
			online.removePrison(i)
			online.removePrison(i)
		end
	end
end
menuInit2="C"


