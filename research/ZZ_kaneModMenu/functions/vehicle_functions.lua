vehicle = {}

function vehicle.toggleVehicleGod()
	if vehicleGod == false then
		GUI.buttons["vehicleMenu"].settings[1].text = "Vehicle God ~g~[ON]"
		vehicleGod = true
	elseif vehicleGod == true then
		GUI.buttons["vehicleMenu"].settings[1].text = "Vehicle God ~r~[OFF]"
		vehicleGod = false
	end
end

function vehicle.toggleJumpKey()
	if jumpKey == false then
		GUI.buttons["vehicleMenu"].settings[5].text = "Jump Key ~g~[ON]"
		jumpKey = true
	elseif jumpKey == true then
		GUI.buttons["vehicleMenu"].settings[5].text = "Jump Key ~r~[OFF]"
		jumpKey = false
	end
end

function vehicle.toggleBoostKey()
	if boostKey == false then
		GUI.buttons["vehicleMenu"].settings[2].text = "Boost Key ~g~[ON]"
		boostKey = true
	elseif boostKey == true then
		GUI.buttons["vehicleMenu"].settings[2].text = "Boost Key ~r~[OFF]"
		boostKey = false
	end
end

function vehicle.toggleFixKey()
	if fixKey == false then
		GUI.buttons["vehicleMenu"].settings[3].text = "Fix Key ~g~[ON]"
		fixKey = true
	elseif fixKey == true then
		GUI.buttons["vehicleMenu"].settings[3].text = "Fix Key ~r~[OFF]"
		fixKey = false
	end
end

function vehicle.toggleLicensePlate()
	if scrollingLicense == false then
		GUI.buttons["vehicleMenu"].settings[4].text = "Scrolling License ~g~[ON]"
		scrollingLicense = true
	elseif scrollingLicense == true then
		GUI.buttons["vehicleMenu"].settings[4].text = "Scrolling License ~r~[OFF]"
		scrollingLicense = false
	end
end
function vehicle.upgradePVehicle()
	if LocalPlayer():IsInVehicle() then
		vehicle.fullyUpgrade(LocalPlayer():GetVehicle().ID)
	end
end
function vehicle.fullyUpgrade(veh)
	if veh == nil then
	else

		natives.VEHICLE.SET_VEHICLE_MOD_KIT(veh, 0)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 0, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 0) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 1, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 1) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 2, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 2) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 3, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 3) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 4, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 4) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 5, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 5) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 6, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 6) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 7, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 7) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 8, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 8) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 9, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 9) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 10, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 10) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 11, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 11) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 12, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 12) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 13, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 13) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 14, 10, false)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 15, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 15) - 1, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 16, natives.VEHICLE.GET_NUM_VEHICLE_MODS(veh, 16) - 1, true)
		natives.VEHICLE.SET_VEHICLE_WHEEL_TYPE(veh, 7)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 23, 19, true)
		natives.VEHICLE.SET_VEHICLE_MOD(veh, 24, 30, true)
		natives.VEHICLE.TOGGLE_VEHICLE_MOD(veh, 18, true)
		natives.VEHICLE.TOGGLE_VEHICLE_MOD(veh, 20, true)
		natives.VEHICLE.TOGGLE_VEHICLE_MOD(veh, 22, true)
		natives.VEHICLE.SET_VEHICLE_TYRE_SMOKE_COLOR(veh, 255, 255, 255)
		natives.VEHICLE.SET_VEHICLE_WINDOW_TINT(veh, 1)
		natives.VEHICLE.SET_VEHICLE_TYRES_CAN_BURST(veh, false)
		natives.VEHICLE.SET_VEHICLE_NUMBER_PLATE_TEXT(veh, 'Kaney')
		natives.VEHICLE.SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, 0, 0, 0)
		natives.VEHICLE.SET_VEHICLE_MOD_COLOR_1(veh, 3, 0, 0)
		natives.VEHICLE.SET_VEHICLE_MOD_COLOR_2(veh, 3, 0, 0)
		natives.VEHICLE.SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, 0, 0, 0)
		GUI.updateStatusText("Fully upgraded!", 1000)
	end
end

function vehicle.fixVehicle()
	if LocalPlayer():IsInVehicle() then
		LocalPlayer():GetVehicle():Fix()
	end
end

function vehicle.vehicleInvincible(b)
	local veh = LocalPlayer():GetVehicle().ID
    natives.ENTITY.SET_ENTITY_INVINCIBLE(veh, b)
	natives.VEHICLE.SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(veh, b) 
	natives.VEHICLE.SET_VEHICLE_TYRES_CAN_BURST(veh, b)
	natives.VEHICLE.SET_VEHICLE_WHEELS_CAN_BREAK(veh, b)
end

function vehicle.spawnVeh(hash)
	local plyPed = LocalPlayer().ID
	local coords = natives.ENTITY.GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(plyPed, 0, 5, 2)
	local heading = natives.ENTITY.GET_ENTITY_HEADING(plyPed) + 90

	streaming.RequestModel(hash)
	
	local veh = natives.VEHICLE.CREATE_VEHICLE(hash, coords.x, coords.y, coords.z, heading, true, true)
	print(natives.VEHICLE.IS_VEHICLE_STOLEN(veh))
	natives.VEHICLE.SET_VEHICLE_IS_STOLEN(veh, false)

	vehicle.fullyUpgrade(veh)
	c_veh = CMemoryBlock(4)
	c_veh:WriteDWORD32(0, veh)
	natives.ENTITY.SET_VEHICLE_AS_NO_LONGER_NEEDED(c_veh)
	c_veh:Release()
end

function vehicle.tick()

	if boostKey == true and IsKeyDown(KEY_NUMPAD1) and LocalPlayer():IsInVehicle() then
	
		local speed = natives.ENTITY.GET_ENTITY_SPEED(LocalPlayer():GetVehicle().ID)
		local speed = speed + 2
		natives.VEHICLE.SET_VEHICLE_FORWARD_SPEED(LocalPlayer():GetVehicle().ID,speed)
	end
	
	
	if fixKey == true and IsKeyDown(KEY_NUMPAD3) and LocalPlayer():IsInVehicle()then
		LocalPlayer():GetVehicle():Fix()
	end

	if vehicleGod == true then
		if LocalPlayer():IsInVehicle() then
			vehicle.vehicleInvincible(true)
		end
	end
	
	if jumpKey == true and IsKeyDown(KEY_SPACE) and LocalPlayer():IsInVehicle()then
		local veh = LocalPlayer():GetVehicle().ID
		local ent_vel = natives.ENTITY.GET_ENTITY_VELOCITY(veh)
		natives.ENTITY.SET_ENTITY_VELOCITY(veh, ent_vel.x, ent_vel.y, 10)
	end

	-- Scrolling license plate || CREDITS to kmc NOT made by me. ||
	if(scrollingLicense and LocalPlayer():IsInVehicle()) then
		if (done or done==nil) then
			time = natives.GAMEPLAY.GET_GAME_TIMER()+200
			done = false
		end
		
		if(time < natives.GAMEPLAY.GET_GAME_TIMER()) then
			SLPText = string.sub(SLPText,2)..string.sub(SLPText,1,1)
			veh = LocalPlayer():GetVehicle().ID
			natives.VEHICLE.SET_VEHICLE_NUMBER_PLATE_TEXT(veh,SLPText)
			done = true
		end
	end
end



menuInit3="EX"