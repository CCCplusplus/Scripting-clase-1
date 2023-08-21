Entity = {}
Entity.__index = Entity

function Entity:New(num)
local this = 
{
	myNum = num
}

setmetatable(this,self)
return this
end

function Entity:print()
print("entity")
end