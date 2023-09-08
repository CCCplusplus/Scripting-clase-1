require("scenes")

EditorSceneLua = {}
EditorSceneLua.__index = EditorSceneLua
setmetatable(EditorSceneLua, {__index = scenes})

function EditorSceneLua:New()
 local this = scenes:New()
 setmetatable(this, self)
 return this
end

function InitializeEditor()
    InitFont()
    InitBGTexture()
    InitMusic()
end

function InitFont()
    setFontFile("OptimusPrinceps.ttf")
end

function InitBGTexture()
    setBackgroundTexture("GameOver.jpg")
end

function InitMusic()
    setMusicFile("Sadness.mp3")
    setMusicVolume(6)
end

function Update()
    print("Editor scene update")
end

function Render()
    print("Editor scene render")
end

