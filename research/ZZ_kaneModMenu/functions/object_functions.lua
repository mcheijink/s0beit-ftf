object = {}
firework_trail = {}
object_c = 0

object_names = {"Cable car","Ferris wheel","Soccer ball","Weed plant"}
object_hash = {-733833763,-1003748966,-717142483,452618762}
object_menu = {"Big objects","Big objects","Small props","Small props"}
curr_objects = {}

function object.simpleSpawn(hash)
	local p_pos = LocalPlayer():GetPosition()
	curr_objects[#curr_objects+1] = natives.OBJECT.CREATE_OBJECT(hash,p_pos.x+1,p_pos.y+1,p_pos.z-1,true,true,false)
	natives.ENTITY.FREEZE_ENTITY_POSITION(curr_objects[#curr_objects], true)
end

function object.advancedSpawn(hash,vec,freeze,heading)
	local new_obj = natives.OBJECT.CREATE_OBJECT(hash,vec.x,vec.y,vec.z-1,true,true,false)
	if freeze == nil then freeze = false end
	if heading == nil then heading = LocalPlayer():GetHeading() end
	natives.ENTITY.FREEZE_ENTITY_POSITION(new_obj, freeze)
	new_obj:SetHeading(heading)
end

function object.RemoveAll()
	for _,o in pairs (curr_objects) do
		local player_loc = LocalPlayer():GetPosition()
		natives.ENTITY.FREEZE_ENTITY_POSITION(o, false)
		natives.ENTITY.SET_ENTITY_COORDS(o,player_loc.x+3000,player_loc.y+3000,player_loc.z+3000,true,true,true,true)
	end
end

function handleCreateM() 
if LocalPlayer():Exists() then
	gui.NotifyAboveMap ( isMenuDone, 2000 )
end
end


function object.spawnHydrant(p,h)
	local coords = Player(p):GetPosition()
	natives.FIRE.ADD_EXPLOSION(coords.x, coords.y, coords.z-1, h, 50, true, false, 0)
end

function object.addObjects()
for n,h in pairs(object_hash) do
	if GUI.menu[object_menu[n]] == nil then
		GUI.createMenu(object_menu[n], "objectMenu", object_menu[n], 0.1, 0.06, 0.150, 0.0400, 0.000, 0.6, 7)
		GUI.addButton("objectMenu", object_menu[n], GUI.setActiveMenu, object_menu[n], false, 0.5, 4,4)
		gui.NotifyAboveMap ( "", 2000 )
	end
	local obj_name = object_names[n]
	local hash = object_hash[n]
	GUI.addButton(object_menu[n], obj_name, object.simpleSpawn, hash, false, 0.5, 4,1)
	
end

end
