# IL2CPP Bridge

[![License][license-shield]][license-url]

## About The Project

**IL2CPP Bridge** is a lightweight, dynamic C++ library designed to interface with Unity IL2CPP applications. It enables dynamic resolution of IL2CPP exports, methods, and fields without relying on hardcoded offsets or version-specific details. This makes your tool more resilient to changes between Unity versions, as long as the underlying IL2CPP signatures remain compatible.

### Features

- **Dynamic Export Resolution:** Automatically resolve IL2CPP exports at runtime using caching and thread-safe mechanisms.
- **Dynamic Method Invocation:** Call both instance and static methods with ease using simple helper functions.
- **Dynamic Field Access:** Retrieve and set both instance and static field values dynamically.
- **Version Independence:** Designed to work with multiple Unity versions without needing extensive modifications.

## Built With

- C++17
- Windows API

## Getting Started

### Prerequisites

- A C++17 compliant compiler (e.g. MSVC, Clang, or GCC on Windows)
- Windows operating system
- An IL2CPP-based Unity application (e.g. with a `GameAssembly.dll`)

### Installation

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/your_username/il2cpp-bridge.git
   ```
2. **Include the Header:**
   ```C++
   #include "il2cpp_resolver.h"
   ```

### Usage

**Library Initialization**
Before using any functionality, initialize the library by supplying the assembly file and assembly name:
```C++
if (!il2cpp::API::InitializeLibrary("GameAssembly.dll", "Assembly-CSharp")) {
    MessageBoxW(NULL, L"Could not initialize IL2CPP API", L"IL2CPP Error", MB_OK | MB_ICONERROR);
    return;
}
```

**Dynamic Method Invocation**
Call instance methods:
```C++
// Example: Call an instance method 'get_Health' from the 'Player' class.
void* player = /* pointer to player object */;
int health = il2cpp::API::CallMethod<int, int>("Assets.Scripts.Unity", "Player", "get_Health", player, 0);
```

Call static methods:
```C++
// Example: Call a static method 'get_PlayerScore' from the 'Game' class.
int score = il2cpp::API::CallStaticMethod<int, int>("Assets.Scripts.Unity", "Game", "get_PlayerScore", 42);
```

**Dynamic Field Access**
For instance fields:
```C++
// Access an instance field from a player object.
il2cpp::API::DynamicFieldInfo playerFields(player, "Assets.Scripts.Unity", "Player");
int currentScore = playerFields.Get<int>("score");
playerFields.Set<int>("score", currentScore + 10);
```

For static fields:
```C++
// Access a static field from the Game class.
il2cpp::API::DynamicStaticFieldInfo gameStaticFields("Assets.Scripts.Unity", "Game");
int highScore = gameStaticFields.Get<int>("highScore");
gameStaticFields.Set<int>("highScore", 200);
```

## Contributing

Contributions are welcome! If you have suggestions or improvements, please fork the repository and open a pull request. For major changes, please open an issue first to discuss your ideas.

## License

Distributed under the MIT License. See the LICENSE file for more details.
