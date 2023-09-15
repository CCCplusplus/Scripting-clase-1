require("scenes")

GameSceneLua = {}
GameSceneLua.__index = GameSceneLua
setmetatable(GameSceneLua, {__index = scenes})

function InitializeGameScene()
    InitEnemy()
    InitMusic()
    InitFont()
    InitText()
    InitBulletT()
    InitBGTexture()
end

function InitializeGameValues()
    setVictoryValue(10)
    setDowntimeValue(0.0)
    setPausetimeValue(0.0)
    setQuittimeValue(0.0)
    setActiveEnemiesValue(0)
end

function InitEnemy()
    setEnemySprite("Enemy.png")
end


function InitBGTexture()
    setBackgroundTexture("GameSceneBG.jpg")
end

function InitFont()
    setGameFont("OptimusPrinceps.ttf")
end

function InitText()
    setHPTextAttributes(60, "white", 10, 10)
    setVictoryCounterAttributes(60, "white", 1320, 10)
end

function InitBulletT()
    setBulletTextures("Hadouken.png", "BlackHole.png")
end

function InitMusic()
    setMusicFile("Level.mp3")
    setMusicVolume(6)
end

function GameSceneLua:New()
 local this = scenes:New()
 setmetatable(this, self)
 return this
end

function Update()
 --print(p.base.myNum)  -- Para Player
 --print(e.base.myNum)  -- Para Enemy
 --print("Game scene update")
end

function Render()
 print("Game scene render")
end
