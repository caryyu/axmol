/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __TOLUA_FIX_H_
#define __TOLUA_FIX_H_

#include "tolua++.h"

#include <string>

#define TOLUA_REFID_PTR_MAPPING "toluafix_refid_ptr_mapping"
#define TOLUA_REFID_TYPE_MAPPING "toluafix_refid_type_mapping"
#define TOLUA_REFID_FUNCTION_MAPPING "toluafix_refid_function_mapping"

/**
 * @addtogroup lua
 * @{
 */
/// @cond
TOLUA_API void toluafix_open(lua_State* L);
/// @endcond

/**
 * Push the userdata correspondings to the ptr on the top index of the Lua stack.
 * If the userdata correspondings to the ptr don't exist, it would call lua_newuserdata to new a userdata.
 * If the userdata correspondings to the ptr exist,it would update the metatable information of the super.
 * In addition, this function would update some table in the Lua registry,such as toluafix_refid_ptr_mapping,
 * toluafix_refid_type_mapping,tolua_value_root,and so on. Meanwhile, Add a reference about the userdata corresponding
 * to the ptr in the tolua_ubox table. The ptr should be point to a Object object.
 *
 * @param L the current lua_State.
 * @param uid the object id of the ptr.
 * @param p_refid the pointer points to the Lua reference id of the ptr.
 * @param ptr the pointer points to the Object object.
 * @param type the type name of the ptr.
 * @return -1 if the p_refid equal to nullptr or ptr equal to nullptr, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_pushusertype_object(lua_State* L, int uid, int* p_refid, void* ptr, const char* type);

/**
 * Find the value of Object object pointer in the Lua registry by the refid.
 * Then, remove the corresponding reference in some table in the Lua registry by refid, such as
 * toluafix_refid_type_mapping, toluafix_refid_ptr_mapping,tolua_value_root,and so on. Set the value of userdata nullptr
 * and remove the reference of userdata in the tolua_ubox table. This function is called in the destructor of the Object
 * automatically.
 *
 * @param L the current lua_State.
 * @param refid the value of the _luaID of a Object object.
 * @return -1,if refid equals to 0 , type name found by refid equals to nil or corresponding userdata pointer equal to
 * nullptr; return -2, if the Object object pointer found by refid is nullptr; return 3, if the value corresponding to the
 * Object object pointer in the tolua_ubox is nil; otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_remove_ccobject_by_refid(lua_State* L, int refid);

/**
 * Get the reference id of the Lua function at the given acceptable index lo of stack.
 * Meanwhile add reference about the Lua function through the toluafix_refid_function_mapping table in the Lua registry.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param def useless.
 * @return 0 if the type of value at the given acceptable index lo of stack is not LUA_TFUNCTION; otherwise return the
 * reference id.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_ref_function(lua_State* L, int lo, int def);

/**
 * Push the Lua function found by the refid in the toluafix_refid_function_mapping table in the Lua registry on the top
 * index of the current stack.
 *
 * @param L the current lua_State.
 * @param refid reference id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_get_function_by_refid(lua_State* L, int refid);

/**
 * Remove the reference of the Lua function corresponding to the refid in the toluafix_refid_function_mapping table in
 * the Lua registry.
 *
 * @param L the current lua_State.
 * @param refid reference id corresponding to the Lua function.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_remove_function_by_refid(lua_State* L, int refid);

/**
 * Verify the value at the given acceptable index is a function or not.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param type useless.
 * @param def useless.
 * @param err if trigger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a function, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_isfunction(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/// @cond
TOLUA_API int toluafix_totable(lua_State* L, int lo, int def);
/// @endcond

/**
 * Verify the value at the given acceptable index is a table or not.
 *
 * @param L the current lua_State.
 * @param lo the given acceptable index lo of stack.
 * @param type useless.
 * @param def whether has the default value.
 * @param err if trigger the error, record the error message to err.
 * @return 1 if the value at the given acceptable index is a table or have def value is not 0, otherwise return 0.
 * @lua NA
 * @js NA
 */
TOLUA_API int toluafix_istable(lua_State* L, int lo, const char* type, int def, tolua_Error* err);

/**
 * Print all information of the stack from the top index.
 * If the type corresponding to the index of the stack is LUA_TSTRING, LUA_TBOOLEAN or LUA_TNUMBER, it would output the
 * value of the index,otherwise output the type name of the index.
 *
 * @param L the current lua_State.
 * @param label the string pointer to define the label of the dump information.
 * @lua NA
 * @js NA
 */
TOLUA_API void toluafix_stack_dump(lua_State* L, const char* label);

inline void tolua_pushsv (lua_State* L, const std::string_view& v)
{
    lua_pushlstring(L, !v.empty() ? v.data() : "", v.length());
}


// end group
/// @}

#endif  // __TOLUA_FIX_H_
