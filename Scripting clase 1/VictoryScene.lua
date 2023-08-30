require("scenes")

VictoryScene = {}
VictoryScene.__index = VictoryScene
setmetatable(VictoryScene, {__index = scenes})

function VictoryScene:new()
local this = scenes:New()
 setmetatable(this, self)
 return this
end

function Update()
 print("You Win")
end

function Render()
 print("Rendering your Victory")
end