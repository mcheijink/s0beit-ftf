--[[
	create menus with GUI.createMenu(menuName, prevMenu, title, xpos, ypos, xscale, yscale, buttonSpacing, textScale, font)

	add buttons to each menu with GUI.addButton(parentMenu, text, funct, args, toggleable, textScale, font)
]]



GUI = {}
GUI.menu = {}
GUI.buttons = {}
GUI.navButtons = 	{
				["menuOpen"] = 
				{
					["keys"] = {},
					["menu"] = ""
				}, 
				["menuClose"] = {["keys"] = {}},
				["menuPrev"] = {["keys"] = {}},
				["navUp"] = {["keys"] = {}},
				["navDown"] = {["keys"] = {}},
				["select"] = {["keys"] = {}},
				["navBack"] = {["keys"] = {}}
			}
GUI.activeButton = 1
GUI.activeMenu = ""
GUI.statusText = {["text"] = "", ["time"] = 0}

GUI.titleColor = {["r"] = 255, ["g"] = 100, ["b"] = 100, ["a"] = 200}
GUI.buttonColor = {["r"] = 20, ["g"] = 20, ["b"] = 20, ["a"] = 200}
GUI.activeButtonColor = {["r"] = 111, ["g"] = 111, ["b"] = 111, ["a"] = 200}



function GUI.createMenu(menuName, prevMenu, title, xpos, ypos, xscale, yscale, buttonSpacing, textScale, font, saveButtonPos)
	if(GUI.menu[menuName] == nil) then
		GUI.menu[menuName] = {}
		lastOffset = ypos + yscale + buttonSpacing
	end
	
	GUI.menu[menuName] = {
		["prevMenu"] = prevMenu,
		["title"] = title,
		["xpos"] = xpos,
		["ypos"] = ypos,
		["xscale"] = xscale,
		["yscale"] = yscale,
		["spacing"] = buttonSpacing,
		["lastOffset"] = lastOffset,
		["numButtons"] = 0,
		["textScale"] = textScale,
		["lastButton"] = 1,
		["saveButtonPos"] = saveButtonPos,
		["font"] = font
	}
end

function GUI.addButton(parentMenu, text, funct, args, toggleable, textScale, font)
	--I tried to make this easy to follow (it probably doesn't help read it, but oh well), but basically,
	--
	if(GUI.buttons[parentMenu] == nil or GUI.buttons[parentMenu]["settings"] == nil) then
		GUI.buttons[parentMenu] = {["settings"] = {}}
	end

	local currButtonNum = #GUI.buttons[parentMenu].settings + 1
	GUI.menu[parentMenu].numButtons = currButtonNum
	--in other words, position the button x.spacing under the previous button

	if(toggleable) then
		toggledOn = false
	else
	    toggledOn = nil
	end

	GUI.buttons[parentMenu].settings[currButtonNum] = {
		["parentMenu"] = parentMenu,
		["text"] = text,
		["funct"] = funct,
		["args"] = args,
		["font"] = font,
		["xpos"] = GUI.menu[parentMenu].xpos,
		["ypos"] = GUI.menu[parentMenu].lastOffset,
		["xscale"] = GUI.menu[parentMenu].xscale,
		["yscale"] = GUI.menu[parentMenu].yscale,
		["textScale"] = textScale,
		["toggleable"] = toggleable,
		["toggledOn"] = toggledOn
	}

	GUI.menu[parentMenu]["lastOffset"] = (GUI.menu[parentMenu].lastOffset + GUI.menu[parentMenu].yscale + GUI.menu[parentMenu].spacing)
end

function GUI.setActiveMenu(menuName)
	GUI.activeMenu = menuName
	if(GUI.menu[GUI.activeMenu] ~= nil) then
		if(GUI.menu[GUI.activeMenu].saveButtonPos or GUI.menu[GUI.activeMenu].saveButtonPos == nil) then
			GUI.activeButton = GUI.menu[GUI.activeMenu].lastButton
		else
		    GUI.activeButton = 1
		end
	end
end

function GUI.updateStatusText(text, time)
	GUI.statusText = {["text"] = text, ["time"] = time}
end

function GUI.isActiveButtonToggledOn()
	local activeButton = GUI.buttons[GUI.activeMenu].settings[GUI.activeButton]
	if(activeButton.toggleable) then
		return activeButton.toggledOn
	elseif(activeButton.toggleable == false) then
	    return nil
	end
end

function GUI.isButtonToggledOn(menu, index)
	local activeButton = GUI.buttons[menu].settings[index]
	if(activeButton.toggleable) then
		return activeButton.toggledOn
	elseif(activeButton.toggleable == false) then
	    return nil
	end
end

function GUI.toggleActiveButtonState()
	local activeButton = GUI.buttons[GUI.activeMenu].settings[GUI.activeButton]


	if(GUI.isActiveButtonToggledOn() and activeButton.toggleable) then
		activeButton.toggledOn = false
	elseif(GUI.isActiveButtonToggledOn() == false and activeButton.toggleable) then
		activeButton.toggledOn = true
	end
end

function GUI.toggleButtonState(menu, index)
	local activeButton = GUI.buttons[menu].settings[index]
	
	if(GUI.isButtonToggledOn(menu, index) and activeButton.toggleable) then
		activeButton.toggledOn = false
	elseif(GUI.isButtonToggledOn(menu, index) == false and activeButton.toggleable) then
		if(GUI.runButtonFunct(activeButton)) then
			activeButton.toggledOn = true
		end
	end
end

--todo
function GUI.removeButton(parentMenu, index)
	GUI.buttons[parentMenu].settings[index] = nil
	GUI.menu[parentMenu]["lastOffset"] = (GUI.menu[parentMenu].lastOffset - GUI.menu[parentMenu].yscale - GUI.menu[parentMenu].spacing)
end

--todo
function GUI.removeMenu(menuName)
	GUI.menu[menuName] = nil
end

function GUI.drawStatusText()
	--this is called every frame from GUI.tick()
	--this is pretty much a work around because using a while loop causes the game to freeze/crash
	--and using main:Wait(0) causes the text to flash instead of constant
	if(nextDrawTime == nil or prevText ~= GUI.statusText.text) then
		nextDrawTime = natives.GAMEPLAY.GET_GAME_TIMER() + GUI.statusText.time
	end

	if(nextDrawTime > natives.GAMEPLAY.GET_GAME_TIMER()) then
		prevText = GUI.statusText.text
		natives.UI.SET_TEXT_FONT(0)
		natives.UI.SET_TEXT_SCALE(0.55, 0.55)
		natives.UI.SET_TEXT_COLOUR(255, 255, 255, 255)
		natives.UI.SET_TEXT_WRAP(0.0, 1.0)
		natives.UI.SET_TEXT_CENTRE(true)
		natives.UI.SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0)
		natives.UI.SET_TEXT_EDGE(1, 0, 0, 0, 205)
		natives.UI._SET_TEXT_ENTRY("STRING")
		natives.UI._ADD_TEXT_COMPONENT_STRING(GUI.statusText.text)
		natives.UI._DRAW_TEXT(0.5, 0.9)
	else
		--clear the text on screen when time is up
		GUI.statusText = {["text"] = "", ["time"] = 0}
		nextDrawTime = nil
	end
end

function GUI.drawGUI()
	--this is pretty much a work around because using a while loop causes the game to freeze/crash
	--and using main:Wait(0) causes the text to flash instead of constant
	if(GUI.activeMenu ~= "" and GUI.activeMenu ~= nil) then
		local name = GUI.activeMenu

		if(GUI.menu[name] ~= nil) then
			--draw title for one frame
			local xpos = GUI.menu[name].xpos
			local ypos = GUI.menu[name].ypos
			local xscale = GUI.menu[name].xscale
			local yscale = GUI.menu[name].yscale
			
			local text = GUI.menu[name].title
			local textScale = GUI.menu[name].textScale
			local font = GUI.menu[name].font
			
			local colors = GUI.titleColor

			addButtonText(text, xpos, ypos - 0.007, textScale, font)
			natives.GRAPHICS.DRAW_RECT(xpos, ypos, xscale, yscale, colors.r, colors.g, colors.b, colors.a);

			--done drawing the title for that frame, now draw the buttons
			if(GUI.buttons[name] ~= nil) then
				for i, v in pairs(GUI.buttons[name].settings) do
					local buttonSettings = GUI.buttons[name].settings[i]
					local xpos = buttonSettings.xpos
					local ypos = buttonSettings.ypos
					local xscale = buttonSettings.xscale
					local yscale = buttonSettings.yscale
					
					local font = buttonSettings.font
					local text = buttonSettings.text
					local textScale = buttonSettings.textScale
					local colors = GUI.buttonColor

					if(buttonSettings.toggledOn == true) then
						text = buttonSettings.text .. " [ON]"
					elseif(buttonSettings.toggledOn == false) then
						text = buttonSettings.text .. " [OFF]"
					end
					
					if(i == GUI.activeButton) then
						colors = GUI.activeButtonColor
					end

					addButtonText(text, xpos, ypos, textScale, font)
					natives.GRAPHICS.DRAW_RECT(xpos, ypos, xscale, yscale, colors.r, colors.g, colors.b, colors.a)
				end
			else
				print("Menu ", name, " has no buttons!")
				GUI.setActiveMenu("")
			end
		else
			print("No menu created with the name: ", GUI.activeMenu)
			GUI.setActiveMenu("")
		end
	end
end

function addButtonText(text, xpos, ypos, textScale, font)
	if(text ~= nil and xpos ~= nil and ypos ~= nil and textScale ~= nil and font ~= nil) then
		natives.UI.SET_TEXT_FONT(font)
		natives.UI.SET_TEXT_SCALE(0.0, textScale)
		natives.UI.SET_TEXT_COLOUR(255, 255, 255, 255)
		natives.UI.SET_TEXT_CENTRE(true)
		natives.UI.SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0)
		natives.UI.SET_TEXT_EDGE(0, 0, 0, 0, 0)
		natives.UI._SET_TEXT_ENTRY("STRING")
		natives.UI._ADD_TEXT_COMPONENT_STRING(text)
		natives.UI._DRAW_TEXT(xpos, ypos - 0.0125)
	else
		print("text: ", text, ", xpos: ", xpos, ", ypos: ", ypos, ", textScale: ", textScale, ", font: ", font)
	    print("There seems to be a nil value when trying to add text to button (see above)")
	    GUI.setActiveMenu("")
	end
end

function GUI.runButtonFunct(currButton)
	--getting the type of a table broke in one of the updates so this is a workaround
	if(type(currButton.funct) == "function" and currButton.args ~= nil and type(currButton.args) ~= "string" and type(currButton.args) ~= "number" and type(currButton.args) ~= "boolean") then
		currButton.funct(currButton.args[1], currButton.args[2], currButton.args[3], currButton.args[4], currButton.args[5], currButton.args[6], currButton.args[7], currButton.args[8], currButton.args[9], currButton.args[10], currButton.args[11], currButton.args[12], currButton.args[13], currButton.args[14], currButton.args[15], currButton.args[16], currButton.args[17], currButton.args[18], currButton.args[19], currButton.args[20])
		return true
	end

	if(type(currButton.funct) == "function" and type(currButton.args) == "string" or type(currButton.args) == "number" or type(currButton.args) == "boolean") then
		currButton.funct(currButton.args)
		return true
	end

	if(currButton.funct ~= nil and currButton.args == nil  ) then
		currButton.funct()
		return true
	end

	if(currButton.funct == nil) then
		print("Unabled to run the function")
		return false
	end
end

--this needs to be called every frame
function GUI.tick()
	--this is pretty much a work around because using a while loop causes the game to freeze/crash
	--and using main:Wait(0) causes the text to flash instead of constant
	--this is called with the main:Run() loop
	GUI.drawStatusText()
	GUI.drawGUI()

	--on menu open key press
	for i, key in pairs(GUI.navButtons.menuOpen.keys) do
		if(IsKeyDown(key)) then
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
			if(GUI.activeMenu == GUI.navButtons.menuOpen.menu) then
				--if menu that is trying to be drawn is already drawn, go to the previous menu that is set for that menu 
				GUI.setActiveMenu(GUI.menu[GUI.activeMenu].prevMenu)
			else
				--if it isn't already drawn, draw as normal
			    GUI.setActiveMenu(GUI.navButtons.menuOpen.menu)
			    GUI.currentSelection = 1
			end
		end
	end

	--on menu close key press
	for i, key in pairs(GUI.navButtons.menuClose.keys) do
		if(IsKeyDown(key)) then
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
			GUI.setActiveMenu("")
		end
	end

	--if the navUp key is pressed, move up (down numerically) in the menu
	for k, key in pairs(GUI.navButtons.navUp.keys) do
		if(IsKeyDown(key) and GUI.activeMenu ~= "") then
			GUI.activeButton = GUI.activeButton - 1
			GUI.menu[GUI.activeMenu].lastButton = GUI.activeButton
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)
			
			--loop selection to the last button if <= 0
			if(GUI.activeButton <= 0) then
				GUI.activeButton = GUI.menu[GUI.activeMenu].numButtons
				GUI.menu[GUI.activeMenu].lastButton = GUI.activeButton
			end
		end
	end

	--if the navDown key is pressed, move down (up numerically) in the menu
	for k, key in pairs(GUI.navButtons.navDown.keys) do
		if(IsKeyDown(key) and GUI.activeMenu ~= "") then
			GUI.activeButton = GUI.activeButton + 1
			GUI.menu[GUI.activeMenu].lastButton = GUI.activeButton
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)

			--loop selection to the first button if > the last button
			if(GUI.activeButton > GUI.menu[GUI.activeMenu].numButtons) then
				GUI.activeButton = 1
				GUI.menu[GUI.activeMenu].lastButton = GUI.activeButton
			end
		end
	end

	--if the select key is pressed, call the function the button was pressed on
	for k, key in pairs(GUI.navButtons.select.keys) do
		if(IsKeyDown(key) and GUI.activeMenu ~= "") then
			
			local currButton = GUI.buttons[GUI.activeMenu].settings[GUI.activeButton]
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false)

			if(GUI.runButtonFunct(currButton)) then
				if(currButton.toggleable) then
					GUI.toggleActiveButtonState()
				end
			end
		end
	end

	--if the navBack key is pressed, draw the prevMenu
	for k, key in pairs(GUI.navButtons.navBack.keys) do
		if(IsKeyDown(key) and GUI.activeMenu ~= "") then
			GUI.setActiveMenu(GUI.menu[GUI.activeMenu].prevMenu)
			natives.AUDIO.PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
		end
	end
end