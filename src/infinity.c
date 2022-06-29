#include "infinity.h"

#include "logger.h"
#include "enfusion.h"

// main entrypoint
// runs when library is loaded into reforger
void InfinityMain() {
    EEngineType etype = GetEnfusionEngineType();
    if(etype == ET_OTHER) return; // do not load infinity in unknown apps
    
    Println(LT_INFO, "Infinity loading...");
    Println(LT_DEBUG, "Engine type: %d", etype);
    
    if(!InitEnfusion())
    {
        Println(LT_ERROR, "Failed to initialize infinity!");
        return;
    }
    
}