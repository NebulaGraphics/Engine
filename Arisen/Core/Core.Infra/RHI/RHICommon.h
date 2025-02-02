#pragma once
#include "../Common/CommandHeaders.h"
#include "Enums/Pipeline/EShaderStage.h"

namespace ArisenEngine::RHI
{
    typedef struct GPUProgramDesc
    {
        size_t codeSize;
        void* byteCode;
        const char* entry;
        const char* name;
        EShaderStage stage;
    } GPUProgramDesc;
    
}
