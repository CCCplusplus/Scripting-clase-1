scenes = {}
scenes.__index = scenes

function scenes:New()
 local this = {}
 setmetatable(this, self)
 return this
end

function Update()
 print("Base scene update")
end

function Render()
 print("Base scene render")
end
