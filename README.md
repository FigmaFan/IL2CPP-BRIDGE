# Unity IL2CPP Bridge

[![Stars][stars-shield]][stars-url] [![Forks][forks-shield]][forks-url] [![Contributors][contributors-shield]][contributors-url] [![License][license-shield]][license-url]

## About The Project

**Unity IL2CPP Bridge** is a small, header-only C++ library that resolves Unity IL2CPP metadata and functions at runtime — no hardcoded offsets required. It dynamically finds classes, methods, and fields and lets you call managed methods safely. All operations return a `Result<T>` with explicit status codes, and the library automatically attaches the calling thread to the IL2CPP domain when needed.

### Features

- **Dynamic export resolution** from `GameAssembly.dll` (with caching and thread-safety).
- **Class/Method lookup** via namespace, class, method, and assembly name.
- **Managed calls** to static and instance methods using a type-safe template API.
- **Field accessors** for both instance and static fields.
- **String helpers** to create `System.String` and convert to `std::string`.
- **Array helpers** for 1D arrays: length and element access.
- **Version-friendly**: resilient as long as IL2CPP signatures remain stable.

## Built With

- C++17
- Windows API (Win32)
- MSVC recommended

## Getting Started

### Prerequisites

- Windows
- C++17 compiler (MSVC recommended)
- IL2CPP-based Unity application (with `GameAssembly.dll`)

### Installation

1) Include the header:
```cpp
#include "il2cpp_resolver.hpp"
```

2) Initialize early (e.g., in your DLL entry point):
```cpp
const auto st = il2cpp::init();
if (st != Il2CppStatus::OK) {
    // Handle error / log status
}
```

> `il2cpp::init()` locates `GameAssembly.dll` and binds the required IL2CPP exports.

---

## Usage

### Working with `Result<T>`

Every resolver/caller returns `Result<T>`:
```cpp
auto mi = il2cpp::get_method("Assets.Scripts.Unity", "Game", "get_Player", "Assembly-CSharp");
if (!mi) {
    // Inspect mi.status
}
// Use the value:
auto* methodInfo = mi.value;
```

For `void` returns you’ll get `Result<void>` (with only `status`).

---

### Resolve Classes & Methods

```cpp
// Class:
auto klass = il2cpp::find_class("Assets.Scripts.Unity", "Game", "Assembly-CSharp");
if (!klass) { /* check klass.status */ }

// Method (optional: param_count for overloads)
auto getPlayer = il2cpp::get_method(
    "Assets.Scripts.Unity", "Game", "get_Player", "Assembly-CSharp" /*, std::optional<int>{0} */
);
if (!getPlayer) { /* check getPlayer.status */ }
```

---

### Managed Calls (static & instance)

`call_function<Ret>(methodInfo, args...)` invokes the IL2CPP **MethodPointer** (fastcall).  
The thread is automatically attached to the IL2CPP domain when needed.

**Example: static getter without parameters**
```cpp
auto mi = il2cpp::get_method("Assets.Scripts.Unity", "Game", "get_Player", "Assembly-CSharp");
if (mi) {
    auto playerRes = il2cpp::call_function<void*>(mi.value /* no instance */, 0 /* if signature expects a dummy */);
    if (playerRes) {
        void* pPlayer = playerRes.value;
        // ...
    }
}
```

**Example: instance method**
```cpp
void* pPlayer = /* instance */;
auto mi = il2cpp::get_method("Assets.Scripts.Unity.Player", "Btd6Player", "GainPlayerXP", "Assembly-CSharp", 2);
if (mi) {
    // Signature example: void GainPlayerXP(float xp, int someFlag)
    auto res = il2cpp::call_function<void>(mi.value, pPlayer, 1234.0f, 0);
    if (!res) { /* handle res.status */ }
}
```

**Return value**
```cpp
auto mi = il2cpp::get_method("System", "Array", "GetLength", "mscorlib", 1);
if (!mi) mi = il2cpp::get_method("System", "Array", "GetLength", "System.Private.CoreLib", 1);
if (mi) {
    auto len = il2cpp::call_function<int>(mi.value, someArray, 0);
    if (len) {
        int n = len.value;
    }
}
```

---

### Fields: instance & static

**Instance field get/set**
```cpp
// Read
auto val = il2cpp::get_object_field_value<int>(
    instance, "Assets.Scripts.Unity.Player", "Btd6Player", "someField", "Assembly-CSharp"
);
if (val) {
    int x = val.value;
}

// Write
auto st = il2cpp::set_object_field_value<int>(
    instance, "Assets.Scripts.Unity.Player", "Btd6Player", "someField", 42, "Assembly-CSharp"
);
```

**Static field get/set**
```cpp
auto cls = il2cpp::find_class("Assets.Scripts.Unity.UI_New.Popups", "PopupScreen", "Assembly-CSharp");
if (cls) {
    auto s = il2cpp::get_static_field_value<void*>(cls.value, "instance");
    if (s) {
        void* pSingleton = s.value;
    }
}
```

---

### Strings

```cpp
// Create System.String
auto s = il2cpp::CreateNewString("hello");
if (s) {
    void* sysStr = s.value;
}

// System.String -> std::string
std::string cpp = il2cpp::convert_to_std_string(sysStr);
```

> `CreateNewString` and `call_function` manage `ensure_thread_attached()` for you.

---

### Arrays (1D helpers)

```cpp
auto len = il2cpp::array_get_length_1d(arrPtr); // Result<int>
if (len) {
    for (int i = 0; i < len.value; ++i) {
        auto elem = il2cpp::array_get_element_1d<void*>(arrPtr, i); // templated
        if (elem) {
            void* e = elem.value;
            // ...
        }
    }
}
```

---

## Status & Error Text

Each operation yields an `Il2CppStatus`. For logging:
```cpp
LOG(INFO, "status: ", to_string(result.status));
```

**Notable statuses**
- `GameAssemblyNotFound`, `GetProcAddressFailed`
- `DomainUnavailable`, `AssemblyNotFound`, `ImageUnavailable`
- `ClassNotFound`, `MethodNotFound`, `FieldNotFound`
- `MethodPointerNull`, `ThreadAttachUnavailable`
- `InvalidArgs`, `OK`

---

## Cleanup

Optionally clean up on unload:
```cpp
il2cpp::cleanup(); // detach thread, clear caches
```

---

## Notes & Tips

- Depending on Unity/.NET, the core assembly can be **`mscorlib`** or **`System.Private.CoreLib`**. Array helpers try both automatically.
- For ambiguous overloads specify `param_count` (5th argument of `get_method`).
- `call_function<Ret>` uses **fastcall**, matching IL2CPP `MethodPointer` ABI.
- The helpers are **header-only** and thread-safe when resolving exports (internal mutex + cache).

---

## Contributing

Contributions are welcome! Please open issues/PRs with a minimal repro and test against the current header.

## License

MIT — see LICENSE.

[license-shield]: https://img.shields.io/github/license/FigmaFan/il2cpp-bridge.svg?style=for-the-badge
[license-url]: https://github.com/FigmaFan/il2cpp-bridge/blob/master/LICENSE.txt
[stars-shield]: https://img.shields.io/github/stars/FigmaFan/il2cpp-bridge.svg?style=for-the-badge
[stars-url]: https://github.com/FigmaFan/your_repo/stargazers
[forks-shield]: https://img.shields.io/github/forks/FigmaFan/il2cpp-bridge.svg?style=for-the-badge
[forks-url]: https://github.com/FigmaFan/il2cpp-bridge/network/members
[contributors-shield]: https://img.shields.io/github/contributors/FigmaFan/il2cpp-bridge.svg?style=for-the-badge
[contributors-url]: https://github.com/FigmaFan/il2cpp-bridge/graphs/contributors
