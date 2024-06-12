#include <iostream>
#include "../hwrtl_pvs.h"
#include "example_common.h"

#ifndef ENABLE_PVS_EXAMPLE
#define ENABLE_PVS_EXAMPLE 1
#endif

using namespace hwrtl;
using namespace hwrtl::pvs;

#if ENABLE_PVS_EXAMPLE
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(463);
    {
        InitPVSGenerator();
        AddOccluderBound(SOccluderBound{ Vec3(0,0,0),Vec3(1,1,1) }, 0);
        AddPlayerCell(SPVSCell{ Vec3(-1, -1, -1), Vec3(-0.5, -0.5, -0.5) });
        GenerateVisibility();
        GetVisibility(0);
        DestoryPVSGenerator();
        std::cout << "end pvs example";
    }
    _CrtDumpMemoryLeaks();
    return 0;
}
#endif