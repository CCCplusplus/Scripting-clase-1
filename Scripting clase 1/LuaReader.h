#pragma once
class LuaReader
{
private:
	lua_State* L;

	std::string lua_state_file;
public:
	

	LuaReader(const char* lua_State_file);

	~LuaReader();

	void LoadFile();

	inline lua_State* getLuaState() { return this->L; }

	void Update();

	void Render();

	std::map<std::string, int> GetKeys();

};

