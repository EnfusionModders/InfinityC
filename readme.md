# Infinity 'C'

A cross-platform plugin framework for the [Enfusion Engine](#). Infinity empowers modders with the ability to extend the Enfusion Engine with custom native functionality. 

Put simply, Infinity provides the framework to implement custom `proto` definitions. With this, modders can call their own underlying C++ functionality.

## Plugins 

Plugins provide modders a way to easily develop native code for their mods without conflict. Plugins are native shared library files automatically loaded from the `Plugins` directory.

### Example Plugin

Enscript code:

```c
sealed class Example {
	static proto void Test();
}
```

Native code:

```c
#include "infinityplugin.h"

InfinityCore* g_pCore = 0;

void* Test(void* args, void* result)
{
	g_pCore->printToLogf(LVL_INFO, "THIS CAME FROM NATIVE CODE");
	return result;
}

EXPORT void OnPluginLoad(InfinityCore* pCore)
{
    g_pCore = pCore;
    ScriptClass* pClass = pCore->registerClass("Example");
    pCore->registerFunction(pClass, "Test", &Test);
    g_pCore->printToLogf(LVL_INFO, "Example plugin loaded.");
}
```

## Building

I have included a `makefile` with all the necessary commands to build on each platform.

### Windows

You need to install [MinGW-w64](https://www.mingw-w64.org/downloads/) to build.

You need to install [make](#) to run the make commands.

I recommend installing [Msys2](https://www.msys2.org/) which can provide both of the binaries above.

Run `make windows` to build on windows for windows targets.

### Linux

You need to install [GCC](#)

You need to install [MAKE](#)

Run `make linux` to build on linux for linux targets.

_Note: WSL is supported for linux builds._

__Linux is not yet supported.__

## Installing

Create a `Plugins` folder in the root ArmaReforgerServer or Workbench directory.

### Windows

Drop `secur32.dll` in the root directory.

Drop plugins in your `Plugins` folder.

### Linux

Use `LD_PRELOAD` to load `infinity.so` into your reforger server.

__Install steps incomplete. Linux not yet supported__

