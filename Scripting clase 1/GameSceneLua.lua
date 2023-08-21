require("scenes")

GameSceneLua = {}
GameSceneLua.__index = GameSceneLua
setmetatable(GameSceneLua, {__index = scenes})

--p = Player:New("NEW PLAYER")

function GameSceneLua:New()
 local this = scenes:New()
 setmetatable(this, self)
 return this
end

function Update()
 --print(p.base.myNum)  -- Para Player
 --print(e.base.myNum)  -- Para Enemy
 print("Game scene update")
end

function Render()
 print("Game scene render")
end
