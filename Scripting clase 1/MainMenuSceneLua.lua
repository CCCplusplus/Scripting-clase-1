require("scenes")

MainMenuSceneLua = {}
MainMenuSceneLua.__index = MainMenuSceneLua
setmetatable(MainMenuSceneLua, {__index = scenes})

function MainMenuSceneLua:New()
    local this = scenes:New()
    setmetatable(this, self)
    return this
end

function InitializeMainMenu()
    InitMusic()
    InitFont()
    InitBGTexture()
end

function InitMusic()
    setMusicFile("Starto.mp3")
    setMusicVolume(50)
end


function InitFont()
    setFontFile("OptimusPrinceps.ttf")
end

function InitBGTexture()
    setBackgroundTexture("MainMenuBG.jpg")
end


function Update()
    print("Main menu scene update")
    
end

function Render()
    print("Main menu scene render")
end

