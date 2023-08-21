require("Entity")

Player = {}
Player.__index = Player

function Player:New(num)
 local this = 
 {
	base = Entity:New(num)
 }
 setmetatable(this,self)
 return this
end
