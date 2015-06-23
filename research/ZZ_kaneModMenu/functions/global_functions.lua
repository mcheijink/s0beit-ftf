global = {}

function global.requestEntityControl(entity)
        natives.ENTITY.SET_ENTITY_AS_MISSION_ENTITY(entity, false, false)
       
        if entity == 0 then return end
 
        local tick = 0
        while natives.NETWORK.NETWORK_HAS_CONTROL_OF_ENTITY(entity) == false do
                tick = tick + 1
                natives.NETWORK.NETWORK_REQUEST_CONTROL_OF_ENTITY(entity)
 
                if tick > 300 then
                        tick = 0
                       
                        print("Unable to request control...")
                        return false
                end
 
                kanesMenu:Wait(5)
        end
       
        if natives.NETWORK.NETWORK_HAS_CONTROL_OF_ENTITY(entity) then
            return true
        end
end