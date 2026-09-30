# *Star Trek: Armada* Mission SDK

This project exists to provide the programming resources needed to build missions for
[Star Trek: Armada](https://wikipedia.org/wiki/Star_Trek%3A_Armada).

Armada missions are Windows DLLs. Building them requires a Windows C++ development environment
including the MSVC 32-bit (x86) build tools and the Windows SDK. Visual Studio or another
IDE/build system capable of invoking the required MSVC compiler and linker may be used.

To build a map for your mission, you must use the Armada
[map editor](http://armadafiles.com/files/armada/utilities/mapping-tools/armada-map-editor/details).

## What this SDK provides

> [!NOTE]
> The Armada API is still being studied, so documentation may be incomplete or missing.

- `Armada.h` A C++ header describing the API exported by the game.
- `Armada.lib` An import library used to link against the game executable.

## Disclaimer

Armada Mission SDK is an unofficial, community-created project and is not affiliated with,
endorsed by, sponsored by, or officially associated with Activision or any other rights holder
associated with Star Trek: Armada. It is not an official Activision product or software development
kit.

The SDK contains independently created code, interfaces, definitions, and reverse-engineered
information intended to facilitate compatibility with the original game. It does not include
or redistribute the original game's proprietary assets or binaries.
