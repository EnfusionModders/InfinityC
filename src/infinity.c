#include "infinity.h"

#include "logger.h"
#include "enfusion.h"
#include "plugins.h"





// main entrypoint
// runs when library is loaded into reforger
void InfinityMain() {
    EEngineType etype = GetEnfusionEngineType();
    if(etype == ET_OTHER) return; // do not load infinity in unknown apps
    
    Println(LT_INFO, "Infinity loading...");
    Println(LT_DEBUG, "Engine type: %d", etype);
    
    // read patterns / pull static offsets from enfusion
    if(!InitEnfusion())
    {
        Println(LT_ERROR, "Failed to initialize infinity!");
        return;
    }
    // wait for everyhting to get ready
    if(!WaitForGlobalRegistratorTable())
    {
        Println(LT_ERROR,"Failed to find global registrator table!");
        return;
    }
    
    // load our plugins
    LoadPlugins();
    Println(LT_INFO, "Infinity loaded.");
}