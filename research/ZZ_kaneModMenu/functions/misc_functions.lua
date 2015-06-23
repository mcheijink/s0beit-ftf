misc = {}


function misc.toggleRadio()
	if radioDisabled == true then
		GUI.buttons["miscMenu"].settings[2].text = "Radio Disabled ~r~[OFF]"
		radioDisabled = false
	else
		GUI.buttons["miscMenu"].settings[2].text = "Radio Disabled ~g~[ON]"
		radioDisabled = true
	end
end

function misc.toggleSeatBelt()
	if seatbelt == false then
		GUI.buttons["miscMenu"].settings[1].text = "Seatbelt ~g~[ON]"
		seatbelt = true
	else
		GUI.buttons["miscMenu"].settings[1].text = "Seatbelt ~r~[OFF]"
		seatbelt = false
	end
end


function misc.tick()
	-- Radio disabling
	if radioDisabled then
		if(natives.PED.IS_PED_IN_ANY_VEHICLE(LocalPlayer().ID,true)) then
			local veh = natives.PED.GET_VEHICLE_PED_IS_IN(LocalPlayer().ID,false)
			natives.AUDIO.SET_VEH_RADIO_STATION(veh,0)
			natives.AUDIO.SET_VEHICLE_RADIO_ENABLED(veh,false)
		end
	else
		if(natives.PED.IS_PED_IN_ANY_VEHICLE(LocalPlayer().ID,true)) then
			local veh = natives.PED.GET_VEHICLE_PED_IS_IN(LocalPlayer().ID,false)
			natives.AUDIO.SET_VEHICLE_RADIO_ENABLED(veh,true)
		end
	end
	
	-- seatbelt
	if seatbelt then
		if lastVehTime == nil then
			lastVehTime = natives.GAMEPLAY.GET_GAME_TIMER()+150
		end
		
		if lastVehTime > natives.GAMEPLAY.GET_GAME_TIMER() then
			if natives.PED.IS_PED_RAGDOLL(LocalPlayer().ID) then
				local veh = natives.PED.GET_VEHICLE_PED_IS_IN(LocalPlayer().ID,true)
				natives.PED.SET_PED_INTO_VEHICLE(LocalPlayer().ID,veh,-1)
			end
		else
			if natives.PED.GET_VEHICLE_PED_IS_IN(LocalPlayer().ID,false) ~= 0 then lastVehTime = nil end
		end
	end
end
