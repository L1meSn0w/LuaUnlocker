#include "FireHack.hpp"
#include "pch.h"
#include <string>
#include <stdexcept>

#include <Psapi.h>

using std::runtime_error;
using std::string;

#define IMPORT(Name) ::FireHack::Imports::Name = ::FireHack::Imports::Get<decltype(::FireHack::Imports::Name)>(#Name)

namespace FireHack
{
	namespace Imports
	{
		HMODULE Module;

		void (* AddLuaLoaderCallback)(void (* Callback)());
		void (* RemoveLuaLoaderCallback)(void (* Callback)());
		void (* AddFrameCallback)(void (* Callback)());
		void (* RemoveFrameCallback)(void (* Callback)());
		void* (* GetState)();
		void (* ExecuteLua)(const char* String, const char* Name);
		void (* RegisterFunction)(const char* Name, int (* Function)(void* State));
		bool (* IsInGame)();

		void (* luaL_error)(void* State, const char* Error);
		bool (* lua_toboolean)(void* State, int Index);
		void (* lua_pushboolean)(void* State, bool Bool);
		double (* lua_tonumber)(void* State, int Index);
		void (* lua_pushnumber)(void* State, double Number);
		const char* (* lua_tostring)(void* State, int Index);
		void (* lua_pushstring)(void* State, const char* String);
		void (* lua_createtable)(void* State, int Array, int NonArray);
		void (* lua_settable)(void* State, int Index);
		void (* lua_setfield)(void* State, int Index, const char* Key);
		void (* lua_getfield)(void* State, int Index, const char* Key);
		void (* lua_pcall)(void* State, int Arguments, int Results, int ErrorFunction);
		int (* lua_type)(void* State, int Index);
		int (* lua_gettop)(void* State);
		void (* lua_settop)(void* State, int Index);
		int (* luaB_loadstring)(void* State);

		HMODULE FindModule ()
		{
			HMODULE Modules [0x100];
			DWORD BytesRequired;
			if (!EnumProcessModules(GetCurrentProcess(), Modules, sizeof(Modules), &BytesRequired))
			{
				throw runtime_error("Could not get the module list.");
			}

			for (auto Index = 0; Index < BytesRequired / sizeof(HMODULE); ++Index)
			{
				if (GetProcAddress(Modules[Index], "AddLuaLoaderCallback"))
				{
					return Modules[Index];
				}
			}

			throw runtime_error("Batdll is not loaded.");
		}

		template <typename Type>
		Type Get (const char* Name)
		{
			if (const auto Pointer = reinterpret_cast<Type>(GetProcAddress(Module, Name)))
			{
				return Pointer;
			}

			throw runtime_error("Batdll export " + string(Name) + " not found.");
		}
	}

	void Initialize ()
	{
		Imports::Module = Imports::FindModule();

		IMPORT(AddLuaLoaderCallback);
		IMPORT(RemoveLuaLoaderCallback);
		IMPORT(AddFrameCallback);
		IMPORT(RemoveFrameCallback);
		IMPORT(GetState);
		IMPORT(ExecuteLua);
		IMPORT(RegisterFunction);
		IMPORT(IsInGame);

		IMPORT(luaL_error);
		IMPORT(lua_toboolean);
		IMPORT(lua_pushboolean);
		IMPORT(lua_tonumber);
		IMPORT(lua_pushnumber);
		IMPORT(lua_tostring);
		IMPORT(lua_pushstring);
		IMPORT(lua_createtable);
		IMPORT(lua_settable);
		IMPORT(lua_setfield);
		IMPORT(lua_getfield);
		IMPORT(lua_pcall);
		IMPORT(lua_type);
		IMPORT(lua_gettop);
		IMPORT(lua_settop);
		IMPORT(luaB_loadstring);
	}

	HMODULE GetModule () noexcept
	{
		return Imports::Module;
	}

	void AddLuaLoadCallback (void (* Callback)()) noexcept
	{
		Imports::AddLuaLoaderCallback(Callback);
	}

	void RemoveLuaLoadCallback (void (* Callback)()) noexcept
	{
		Imports::RemoveLuaLoaderCallback(Callback);
	}

	void AddFrameCallback (void (* Callback)()) noexcept
	{
		Imports::AddFrameCallback(Callback);
	}

	void RemoveFrameCallback (void (* Callback)()) noexcept
	{
		Imports::RemoveFrameCallback(Callback);
	}

	void* GetLuaState () noexcept
	{
		return Imports::GetState();
	}

	void ExecuteLua (const char* String, const char* Name) noexcept
	{
		Imports::ExecuteLua(String, Name);
	}

	void RegisterFunction (const char* Name, int (* Function)(void* State)) noexcept
	{
		Imports::RegisterFunction(Name, Function);
	}

	bool IsInGame () noexcept
	{
		return Imports::IsInGame();
	}

	void luaL_error (void* State, const char* Error) noexcept
	{
		Imports::luaL_error(State, Error);
	}

	bool lua_toboolean (void* State, int Index) noexcept
	{
		return Imports::lua_toboolean(State, Index);
	}

	void lua_pushboolean (void* State, bool Bool) noexcept
	{
		Imports::lua_pushboolean(State, Bool);
	}

	double lua_tonumber (void* State, int Index) noexcept
	{
		return Imports::lua_tonumber(State, Index);
	}

	void lua_pushnumber (void* State, double Number) noexcept
	{
		Imports::lua_pushnumber(State, Number);
	}

	const char* lua_tostring (void* State, int Index) noexcept
	{
		return Imports::lua_tostring(State, Index);
	}

	void lua_pushstring (void* State, const char* String) noexcept
	{
		Imports::lua_pushstring(State, String);
	}

	void lua_createtable (void* State, int Array, int NonArray) noexcept
	{
		Imports::lua_createtable(State, Array, NonArray);
	}

	void lua_settable (void* State, int Index) noexcept
	{
		Imports::lua_settable(State, Index);
	}

	void lua_setfield (void* State, int Index, const char* Key) noexcept
	{
		Imports::lua_setfield(State, Index, Key);
	}

	void lua_getfield (void* State, int Index, const char* Key) noexcept
	{
		Imports::lua_getfield(State, Index, Key);
	}

	void lua_pcall (void* State, int Arguments, int Results, int ErrorFunction) noexcept
	{
		Imports::lua_pcall(State, Arguments, Results, ErrorFunction);
	}

	int lua_type (void* State, int Index) noexcept
	{
		return Imports::lua_type(State, Index);
	}

	int lua_gettop (void* State) noexcept
	{
		return Imports::lua_gettop(State);
	}

	void lua_settop (void* State, int Index) noexcept
	{
		Imports::lua_settop(State, Index);
	}

	int luaB_loadstring (void* State) noexcept
	{
		return Imports::luaB_loadstring(State);
	}
}