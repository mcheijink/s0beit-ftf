bodyguard = {}
bodyguards = {}

assault_rifles = {}
local weaponHashes = {	"WEAPON_PISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG", 
	"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
	"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
	"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
	"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_SPECIALCARBINE"}
	
function bodyguard.createBodyguard(hash)
	local coords = LocalPlayer():GetPosition()
	local coords = Vector(coords.x,coords.y+1,coords.z)
	streaming.RequestModel(hash)
	bodyguards[#bodyguards+1] = game.CreatePed(hash,coords)
	streaming.ReleaseModel(hash)
end

function bodyguard.removeAll()
	for _, b in pairs(bodyguards) do
		if b:Exists() then
			b:SetInvincible(false)
			b:Delete()
		end
	end
end

function bodyguard.makeBodyguard()
	for _, b in pairs(bodyguards) do
		if b:Exists() then
			b:AddGroupMember(LocalPlayer())
		end
	end
end


function bodyguard.giveWeapon(h)
	for _, b in pairs(bodyguards) do
		if b:Exists() then
			b:AllowWeaponSwitching(true)
			b:DelayedGiveWeapon(h, 1000)
		end
	end
end

-- Menu creation
GUI.createMenu("bodyguardMenu", "mainMenu", "Bodyguards", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
GUI.createMenu("bodyguardSettings", "bodyguardMenu", "Bodyguard options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
GUI.createMenu("bodyguardWeapons", "bodyguardSettings", "Weapon options", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
GUI.createMenu("bodyguardSpawnMenu", "bodyguardMenu", "Bodyguard spawning", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)
GUI.createMenu("bodyguardSpawnMenuLawEnforcement", "bodyguardSpawnMenu", "Law enforcement", 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 4)

-- Main
GUI.addButton("bodyguardMenu", "Bodyguard settings", GUI.setActiveMenu, "bodyguardSettings", false, 0.5, 4,1)
GUI.addButton("bodyguardMenu", "Spawn menu", GUI.setActiveMenu, "bodyguardSpawnMenu", false, 0.5, 4,1)

-- Spawn menu
GUI.addButton("bodyguardSpawnMenu", "Law enforcement", GUI.setActiveMenu, "bodyguardSpawnMenuLawEnforcement", false, 0.5, 4,1)

-- Law enforcement/Healthcare
GUI.addButton("bodyguardSpawnMenuLawEnforcement", "Spawn FIB Officer", bodyguard.createBodyguard, -306416314, false, 0.5, 4,1)
GUI.addButton("bodyguardSpawnMenuLawEnforcement", "Spawn Military", bodyguard.createBodyguard, 0xF2DAA2ED, false, 0.5, 4,1)

-- 

-- Settings
GUI.addButton("bodyguardSettings", "Remove all", bodyguard.removeAll, nil, false, 0.5, 4,1)
GUI.addButton("bodyguardSettings", "Bodyguard all", bodyguard.makeBodyguard, nil, false, 0.5, 4,1)
GUI.addButton("bodyguardSettings", "Weapons", GUI.setActiveMenu, "bodyguardWeapons", false, 0.5, 4,1)

-- Weapons menu
for _, w in pairs(weaponHashes) do
	GUI.addButton("bodyguardWeapons", w, bodyguard.giveWeapon, w, false, 0.5, 4,1)
end

