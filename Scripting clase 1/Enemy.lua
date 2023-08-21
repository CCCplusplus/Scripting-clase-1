require("Entity")

Enemy = {}
Enemy.__index = Enemy

function Enemy:New(num)
 local this = 
 {
	base = Entity:New(num)
 }
 setmetatable(this, self)
 return this
end
