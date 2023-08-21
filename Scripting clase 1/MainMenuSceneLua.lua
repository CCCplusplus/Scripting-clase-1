require("scenes")

MainMenuSceneLua = {}
MainMenuSceneLua.__index = MainMenuSceneLua
setmetatable(MainMenuSceneLua, {__index = scenes})

function MainMenuSceneLua:New()
 local this = scenes:New()
 setmetatable(this, self)
 return this
end

function Update()
 print("Main menu scene update")
end

function Render()
 print("Main menu scene render")
end
