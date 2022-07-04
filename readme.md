# Infinity 'C'

A cross-platform plugin framework for the [Enfusion Engine](#). Infinity empowers modders with the ability to extend the Enfusion Engine with custom native functionality. 

Put simply, Infinity provides the framework to implement custom `proto` definitions. With this, modders can call their own underlying C/C++ functionality.

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
	g_pCore->Print(LVL_INFO, "THIS CAME FROM NATIVE CODE");
	return result;
}

EXPORT void OnPluginLoad(InfinityCore* pCore)
{
    g_pCore = pCore;
    ScriptClass* pClass = pCore->RegisterClass("Example");
    pCore->RegisterFunction(pClass, "Test", &Test);
    g_pCore->Print(LVL_INFO, "Example plugin loaded.");
}
```

## Building

I have included a `makefile` with all the necessary commands to build on each platform.

Run: `make build`

### Windows Prereqs

You need to install [MinGW-w64](https://www.mingw-w64.org/downloads/) to build. 
You need to install `make` to run the make commands.

I recommend installing [Msys2](https://www.msys2.org/) which can provide both of the binaries above.

### Linux Prereqs

You need to install [GCC 12.1](https://tutorialforlinux.com/2022/05/25/step-by-step-gcc-12-1-ubuntu-20-04-installation-guide/)
You need to install MAKE.

_Note: WSL is supported for linux builds_

## Installing

Create a `plugins` folder in the root ArmaReforgerServer or Workbench directory.

### Windows

Drop `secur32.dll` in the root directory.
Drop plugins in your `plugins` folder.

### Linux

Use `LD_PRELOAD` to load `infinity.so` into your reforger server. This is done by adding `LD_PRELOAD` prior to the launch application in your startup script. Here is an example:

`LD_PRELOAD=/full/path/to/infinityc.so ./ArmaReforgerServer [reforger args here]`

Drop plugins into your `plugins` folder.


## Unit Tests

There is some issue with GCC tests on windows. The test only works from inside a bash command prompt. This isn't a problem when running tests from the make command. 

Run: `make test`