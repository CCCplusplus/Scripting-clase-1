require("scenes")

EditorSceneLua = {}
EditorSceneLua.__index = EditorSceneLua
setmetatable(EditorSceneLua, {__index = scenes})

function EditorSceneLua:New()
 local this = scenes:New()
 setmetatable(this, self)
 return this
end

function Update()
 print("Editor scene update")
end

function Render()
 print("Editor scene render")
end
