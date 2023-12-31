#include "pch.h"
#include "LuaReader.h"

LuaReader::LuaReader(const char* lua_State_file)
{
	this->L = luaL_newstate();
	luaL_openlibs(this->L);

	this->lua_state_file = lua_State_file;
}

LuaReader::~LuaReader()
{
	lua_close(this->L);
}

void LuaReader::LoadFile()
{
	int error = luaL_dofile(this->L, this->lua_state_file.c_str());
	if (error) 
	{
		std::cout << "Lua::Error:State::Constroctor" << lua_tostring(this->L, -1) << "\n";
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP::ERROR::CONSTROCTOR::COULD NOT OPEN FILE %s", this->lua_state_file.c_str());
	}
}

void LuaReader::Update()
{
	lua_getglobal(this->L, "Update");
	int error = lua_pcall(this->L, 0, 0, 0);
	if (error)
	{
		std::cout << "Lua::Error:State::Constroctor" << lua_tostring(this->L, -1) << "\n";
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP::ERROR::CONSTROCTOR::CANNOT CALL UPDATE FUNCTION");
	}
}

void LuaReader::Render()
{
	lua_getglobal(this->L, "Render");
	int error = lua_pcall(this->L, 0, 0, 0);
	if (error)
	{
		std::cout << "Lua::Error:State::Constroctor" << lua_tostring(this->L, -1) << "\n";
		lua_pop(this->L, lua_gettop(this->L));
		throw("CPP::ERROR::CONSTROCTOR::CANNOT CALL UPDATE FUNCTION");
	}
}

std::map<std::string, int> LuaReader::GetKeys() {
	std::map<std::string, int> keys;

	lua_getglobal(L, "keys");
	lua_pushnil(L);  // First key
	while (lua_next(L, -2)) {
		const char* keyName = lua_tostring(L, -2);
		int keyValue = lua_tointeger(L, -1);
		keys[keyName] = keyValue;
		lua_pop(L, 1);  // Removes 'value'; keeps 'key' for next iteration
	}

	return keys;
}

