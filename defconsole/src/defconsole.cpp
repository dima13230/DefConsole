#define LIB_NAME "DefConsole"
#define MODULE_NAME "defconsole"

// include the Defold SDK
#include <dmsdk/sdk.h>
#include <dmsdk/dlib/log.h>

dmScript::LuaCallbackInfo* log_callback;

static void InvokeCallback(dmScript::LuaCallbackInfo* cbk, const char* domain, const char* message)
{
    if (!dmScript::IsCallbackValid(cbk)) return;
    lua_State* L = dmScript::GetCallbackLuaContext(cbk);
    DM_LUA_STACK_CHECK(L, 0);
    if (!dmScript::SetupCallback(cbk))
    {
        dmLogError("Failed to setup callback");
        return;
    }
    lua_pushstring(L, domain);
    lua_pushstring(L, message);
    dmScript::PCall(L, 3, 0);       // instance + 2
    dmScript::TeardownCallback(cbk);
}

static void LogCallback(LogSeverity severity, const char* domain, const char* formattedString)
{
    InvokeCallback(log_callback, domain, formattedString);
}

static int Init(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    
    log_callback = dmScript::CreateCallback(L, 1);
    
    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"init", Init},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    // Register lua names
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result AppInitializeMyExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result InitializeMyExtension(dmExtension::Params* params)
{   
    // Init Lua
    LuaInit(params->m_L);

    dmLogRegisterListener(LogCallback);
    
    printf("Registered %s Extension\n", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

dmExtension::Result AppFinalizeMyExtension(dmExtension::AppParams* params)
{
    return dmExtension::RESULT_OK;
}

dmExtension::Result FinalizeMyExtension(dmExtension::Params* params)
{
    return dmExtension::RESULT_OK;
}

DM_DECLARE_EXTENSION(DefConsole, LIB_NAME, AppInitializeMyExtension, AppFinalizeMyExtension, InitializeMyExtension, 0, 0, FinalizeMyExtension)