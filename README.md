# IL2CPP-BRIDGE
provides an easy-to-use API to interact with Unity IL2CPP from native C++ code (internal)(C++20+)

# how to use
include il2cpp_bridge.h in your project

call ```il2cpp::api::init()``` exactly once before using it.

# doc

HUGE REWORK CURRENTLY WIP

## how to call a function
```C++
auto result = il2cpp::call_function<[return type]>(il2cpp::get_method("[namespace]", "[class_name]", "[method_name]"), [class_instance], [argument(s)], [method]);
```
example:
```C++
il2cpp::call_function<void>(il2cpp::get_method("Assets.Scripts.Unity.Player", "Btd6Player", "AddItemToInventory"), p_btd6_player, p_item_id, 0);
```
## how to read value of a field
```C++
auto result = il2cpp::get_object_field_value<[field_type]>([class_instance], "[namespace]", "[class_name]", "[field_name]");
```
example:
```C++
int32_t currAmmo = il2cpp::get_object_field_value<int32_t>(pLocalPlayer, "Assets.Scripts.Unity.Player", "LocalPlayer", "ammoInClip");
```
## how to write value to a field
```C++
il2cpp::set_object_field_value<[field_type]>([class_instance], "[namespace]", "[class_name]", "[field_name]", [value]);
```
example:
```
il2cpp::set_object_field_value<int32_t>(pLocalPlayer, "Assets.Scripts.Unity.Player", "LocalPlayer", "ammoInClip", 999);
```
## how to read value of a static field
```C++
auto result = il2cpp::get_static_field_value<[field_type]>(il2cpp::find_class("[namespace]", "[class_name]"), "[field_name]");
```
example:
```C++
float maxHealth = il2cpp::get_static_field_value<float>(il2cpp::find_class("Assets.Scripts.Unity.Player", "PlayerEntity"), "maxHealth");
```
## how to write value to a static field
```C++
il2cpp::set_static_field_value<[field_type]>(il2cpp::find_class("[namespace]", "[class_name]"), "[field_name]", [value]);
```
example:
```C++
il2cpp::set_static_field_value<float>(il2cpp::find_class("Assets.Scripts.Unity.Player", "PlayerEntity"), "maxHealth", 120.0f);
```
## how to convert "il2cpp string" to std::string
```C++
std::string converted_string = il2cpp::to_string([string_to_convert]);
```
example:
```C++
System_String_o* p_sys_str = ...;
std::string str = il2cpp::to_string(p_sys_str);
```
## how to convert std::string to "il2cpp string"
```C++
System_String_o* converted_string = il2cpp::create_new_string([string_to_convert]);
```
example:
```C++
std::string tower_id("DartMonkey");
System_String_o* p_sys_str = il2cpp::create_new_string(tower_id.c_str());
```
## how to get System.Array size
```C++
soon
```
example:
```C++
soon
```
## how to get System.Array elements
```C++
soon
```
example:
```C++
soon
```
## how to convert System.Collections.ArrayList to System.Array
```C++
soon
```
example:
```C++
soon
```
