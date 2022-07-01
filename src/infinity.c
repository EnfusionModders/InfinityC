#include "infinity.h"

#include "logger.h"
#include "enfusion.h"
#include "plugins.h"





// main entrypoint
// runs when library is loaded into reforger
void* InfinityMain(void* arg) {
    EEngineType etype = GetEnfusionEngineType();
    if(etype == ET_OTHER) return 0; // do not load infinity in unknown apps
    
    Println(LT_INFO, "Infinity loading...");
    
    // read patterns / pull static offsets from enfusion
    if(!InitEnfusion())
    {
        Println(LT_FATAL, "Failed to initialize infinity!");
        return 0;
    }
    
    // wait for everyhting to get ready
    if(!WaitForGlobalRegistratorTable())
    {
        Println(LT_FATAL,"Failed to find global registrator table!");
        return 0;
    }
    
    // load our plugins
    LoadPlugins();
    Println(LT_INFO, "Infinity loaded.");
    
    return 0;
}