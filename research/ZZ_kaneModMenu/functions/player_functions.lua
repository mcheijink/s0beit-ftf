ply = {}
menuInit4="CLU"
function ply.killPlayer(p)
	Player(p):SetHealth(0)
end

function ply.toggleGod()
	if godMode == false then 
		godMode = true
		GUI.buttons["playerMenu"].settings[1].text = "God ~g~[ON]"
	elseif godMode == true then
		
		godMode = false
		LocalPlayer():SetInvincible(false)
		GUI.buttons["playerMenu"].settings[1].text = "God ~r~[OFF]"
	end
end

function ply.playAnim(anim_dict, anim)
	natives.STREAMING.REQUEST_ANIM_DICT(anim_dict)
	natives.AI.TASK_PLAY_ANIM(LocalPlayer().ID, anim_dict, anim, 8, -4, 10000, 0.1, 0, false, false, true)
end

function ply.toggleNoCops()
	if noCops == false then
		GUI.buttons["playerMenu"].settings[2].text = "NoCops ~g~[ON]"
		noCops = true
	elseif noCops == true then
		GUI.buttons["playerMenu"].settings[2].text = "NoCops ~r~[OFF]"
		noCops = false
	end
end

function ply.toggleUnlimitedAmmo()
	if unlimitedAmmo == false then
		GUI.buttons["playerMenu"].settings[3].text = "Unlimited Ammo ~g~[ON]"
		unlimitedAmmo = true
	elseif unlimitedAmmo == true then
		GUI.buttons["playerMenu"].settings[3].text = "Unlimited Ammo ~r~[OFF]"
		unlimitedAmmo = false
	end
end

function ply.noclipToggle()
	if noClip == false then
		GUI.buttons["specialMenu"].settings[1].text = "Noclip ~g~[ON]"
		noClip = true
	elseif noClip == true then
		GUI.buttons["specialMenu"].settings[1].text = "Noclip ~r~[OFF]"
		natives.ENTITY.FREEZE_ENTITY_POSITION(LocalPlayer().ID,false)
		noClip = false
	end	
end

function ply.toggleNoRagdoll()
	if noRagdoll == false then
		natives.PED.SET_PED_CAN_RAGDOLL(LocalPlayer().ID,false)
		GUI.buttons["playerMenu"].settings[4].text = "No ragdoll ~g~[ON]"
		noRagdoll = true
	elseif noRagdoll == true then
		natives.PED.SET_PED_CAN_RAGDOLL(LocalPlayer().ID,true)
		GUI.buttons["playerMenu"].settings[4].text = "No ragdoll ~r~[OFF]"
		noRagdoll = false
	end
end

function ply.toggleVisible()
	if visible == true then
		GUI.buttons["playerMenu"].settings[5].text = "Visible ~g~[INVISIBLE]"
		natives.ENTITY.SET_ENTITY_VISIBLE(LocalPlayer().ID,false)
		visible = false
	elseif visible == false then
		GUI.buttons["playerMenu"].settings[5].text = "Visible ~r~[VISIBLE]"
		natives.ENTITY.SET_ENTITY_VISIBLE(LocalPlayer().ID,true)
		visible = true
	end
end

-- Unlimited ammo CREDITS TO SuperXElite
function ply.handleNoReload()
  local PlayerPed = natives.PLAYER.PLAYER_PED_ID()
  local PlayerExists = natives.ENTITY.DOES_ENTITY_EXIST(PlayerPed)
 
  if PlayerExists then
    local c_out_hash = CMemoryBlock(4) -- allocate 4 bytes (32bit int)
    if natives.WEAPON.GET_CURRENT_PED_WEAPON(PlayerPed, c_out_hash, true) then
      local hash = c_out_hash:ReadDWORD32(0) -- read DWORD 32bit
      if natives.WEAPON.IS_WEAPON_VALID(hash) then
        local c_maxAmmo = CMemoryBlock(4) -- allocate 4 bytes (32bit int)
        if natives.WEAPON.GET_MAX_AMMO(PlayerPed, hash, c_maxAmmo) then
          local maxAmmo = c_maxAmmo:ReadDWORD32(0) -- read DWORD 32bit
          natives.WEAPON.SET_PED_AMMO(PlayerPed, hash, maxAmmo)
          maxAmmo = natives.WEAPON.GET_MAX_AMMO_IN_CLIP(PlayerPed, hash, true)
          if (maxAmmo > 0) then
            natives.WEAPON.SET_AMMO_IN_CLIP(PlayerPed, hash, maxAmmo)
          end
        end
          c_maxAmmo:Release()
      end
    end
  c_out_hash:Release()
  end
end

function ply.GetDirectionFromCam()	
    local rot = natives.CAM.GET_GAMEPLAY_CAM_ROT(2)
	local coord = natives.CAM.GET_GAMEPLAY_CAM_COORD()

    local tZ = rot.z * 0.0174532924;
    local tX = rot.x * 0.0174532924;
    local num = math.abs(math.cos(tX));

    coord.x = (-math.sin(tZ)) * (num)
    coord.y = (math.cos(tZ)) * (num)
    coord.z = math.sin(tX)

	return coord
end

function ply.setCoords(x, y, z)
	natives.ENTITY.SET_ENTITY_COORDS_NO_OFFSET(plyPed, x, y, z, false, false, true)
end


function ply.isControlDown(key)
	return natives.CONTROLS.IS_CONTROL_PRESSED(2, key)
end

function ply.gameNoclipListen()
	local veh = natives.PED.GET_VEHICLE_PED_IS_USING(plyPed)
	local plyPed = LocalPlayer().ID
	if(natives.PED.IS_PED_IN_VEHICLE(plyPed, veh, true) == false) then
		local forward = ply.GetDirectionFromCam()
		local coords = natives.ENTITY.GET_ENTITY_COORDS(plyPed, true)
		local roll = natives.ENTITY.GET_ENTITY_ROTATION(plyPed, 0)
		local speed = {}

		speed.x = forward.x / 2
		speed.y = forward.y / 2
		speed.z = .5
		
		rollSpeed = 2

		--shift
		if(natives.CONTROLS.IS_CONTROL_PRESSED(2, 21)) then
			speed.x = forward.x * 2
			speed.y = forward.y * 2
			speed.z = speed.z * 2
			rollSpeed = 4
		end

		--space
		if(ply.isControlDown(22)) then
			ply.setCoords(coords.x, coords.y, coords.z + speed.z)
		end

		if(natives.ENTITY.GET_ENTITY_HEIGHT_ABOVE_GROUND(plyPed) > -1000) then
			natives.ENTITY.FREEZE_ENTITY_POSITION(plyPed, true)

			--huge thanks to Woovie for helping me figure this out
			if forward.x > 0 and forward.y > 0  then--0 to 90
				forwardDeg = (forward.y*90)+270
			elseif forward.x < 0 and forward.y > 0 then--271 to 360
				forwardDeg = math.abs(forward.x)*90
			elseif forward.x < 0 and forward.y < 0 then--181 to 270
				forwardDeg = forward.x*90+180
			elseif forward.x > 0 and forward.y < 0 then-- 91 to 180
				forwardDeg = (math.abs(forward.x)*90)+180
			end

			natives.ENTITY.SET_ENTITY_ROTATION(plyPed, 0, 0, forwardDeg, 0, false)


			--w+space
			if(ply.isControlDown(32) and ply.isControlDown(22)) then
				ply.setCoords(coords.x + speed.x, coords.y + speed.y, coords.z + speed.z)
			--w+ctrl
			elseif(ply.isControlDown(32) and ply.isControlDown(36)) then
				ply.setCoords(coords.x + speed.x, coords.y + speed.y, coords.z - speed.z)
			--w
			elseif(ply.isControlDown(32)) then
				ply.setCoords(coords.x + speed.x, coords.y + speed.y, coords.z)
			end

			
			--s+space
			if(ply.isControlDown(31) and ply.isControlDown(22)) then
				ply.setCoords(coords.x - speed.x, coords.y - speed.y, coords.z + speed.z)
			--s+ctrl
			elseif ply.isControlDown(31) and ply.isControlDown(36) then
				ply.setCoords(coords.x - speed.x, coords.y - speed.y, coords.z - speed.z)
			--s
			elseif(ply.isControlDown(31)) then
				ply.setCoords(coords.x - speed.x, coords.y - speed.y, coords.z)
			end

			--ctrl
			if(ply.isControlDown(36)) then
				ply.setCoords(coords.x, coords.y, coords.z - speed.z)
			end

			--a + w
			if(ply.isControlDown(34) and ply.isControlDown(32)) then
				--do nothing for now, will add this in later
				ply.setCoords(coords.x - speed.y, coords.y + speed.x, coords.z)
			elseif(ply.isControlDown(34)) then
				ply.setCoords(coords.x - speed.y, coords.y + speed.x, coords.z)
			end

			--d+w
			if(ply.isControlDown(35) and ply.isControlDown(31)) then
				--do nothing different for now, will add this in later
				ply.setCoords(coords.x + speed.y, coords.y - speed.x, coords.z)
			elseif(ply.isControlDown(35)) then
				ply.setCoords(coords.x + speed.y, coords.y - speed.x, coords.z)
			end
	
		else
		    natives.ENTITY.FREEZE_ENTITY_POSITION(plyPed, false)
		end
	end
end

function ply.tick()
	
	if godMode == true then
		LocalPlayer():SetInvincible(true)
	elseif godMode == false then
		LocalPlayer():SetInvincible(false)
	end
	
	if instakill == true then
		natives.PLAYER.SET_PLAYER_WEAPON_DAMAGE_MODIFIER(natives.PLAYER.PLAYER_ID(), 999999999)
	else
		natives.PLAYER.SET_PLAYER_WEAPON_DAMAGE_MODIFIER(natives.PLAYER.PLAYER_ID(), 1)
	end
	
	if noClip then
		ply.gameNoclipListen()
	end

	if noCops == true then
		LocalPlayer():SetWantedLevel(0)
	end
	

	if unlimitedAmmo == true then
		ply.handleNoReload() 
	end


	if visible == false then
		natives.ENTITY.SET_ENTITY_VISIBLE(LocalPlayer().ID,false)
	end
end

function test()
	GUI.NotifyAboveMap ( "Kanersps", 1000 )
end