#pragma once

#include <stdexcept>

#include <Windows.h>

namespace FireHack
{
	/// @brief The global pseudo-index
	constexpr auto LUA_GLOBALSINDEX = -10002;

	/// @brief Initialize
	/// @throw std::runtime_error Thrown if FireHack or an export cannot be found
	void Initialize ();

	/// @brief Get the FireHack module.
	/// @return The FireHack module
	HMODULE GetModule () noexcept;

	/// @brief Add a callback to be called when Lua is to be loaded.
	/// @param Callback The callback
	void AddLuaLoadCallback (void (* Callback)()) noexcept;

	/// @brief Remove a callback previously registered with AddLuaLoadCallback.
	/// @param Callback The callback
	void RemoveLuaLoadCallback (void (* Callback)()) noexcept;

	/// @brief Add a callback to be called each frame.
	/// @param Callback The callback
	void AddFrameCallback (void (* Callback)()) noexcept;

	/// @brief Remove a callback previously registered with AddFrameCallback.
	/// @param Callback The callback
	void RemoveLuaCallback (void (* Callback)()) noexcept;

	/// @brief Get the Lua state.
	/// @return The Lua state
	void* GetLuaState () noexcept;

	/// @brief Execute a Lua string.
	/// @param String The Lua string
	/// @param Name The string name
	void ExecuteLua (const char* String, const char* Name) noexcept;

	/// @brief Register a Lua C function.
	/// @param Name The function name
	/// @param Function The Lua C function
	void RegisterFunction (const char* Name, int (* Function)(void* State)) noexcept;

	/// @brief Get whether in-game.
	/// @return Whether in-game
	bool IsInGame () noexcept;

	void luaL_error (void* State, const char* Error) noexcept;
	bool lua_toboolean (void* State, int Index) noexcept;
	void lua_pushboolean (void* State, bool Bool) noexcept;
	double lua_tonumber (void* State, int Index) noexcept;
	void lua_pushnumber (void* State, double Number) noexcept;
	const char* lua_tostring (void* State, int Index) noexcept;
	void lua_pushstring (void* State, const char* String) noexcept;
	void lua_createtable (void* State, int Array, int NonArray) noexcept;
	void lua_settable (void* State, int Index) noexcept;
	void lua_setfield (void* State, int Index, const char* Key) noexcept;
	void lua_getfield (void* State, int Index, const char* Key) noexcept;
	void lua_pcall (void* State, int Arguments, int Results, int ErrorFunction) noexcept;
	int lua_type (void* State, int Index) noexcept;
	int lua_gettop (void* State) noexcept;
	void lua_settop (void* State, int Index) noexcept;
	int luaB_loadstring (void* State) noexcept;
}