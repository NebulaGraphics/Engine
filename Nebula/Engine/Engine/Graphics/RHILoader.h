#pragma once
#include "Common/CommandHeaders.h"
#include "RHI/Instance.h"
#include "../EngineCommon.h"

namespace NebulaEngine::Graphics
{
    class DLL RHILoader
    {
    public:
        NO_COPY_NO_MOVE_NO_DEFAULT(RHILoader)

        static void SetCurrentGraphicsAPI(RHI::GraphsicsAPI api_type);
        static RHI::Instance* CreateInstance(RHI::AppInfo&& app_info);
        static void Dispose();
    private:

        static inline RHI::GraphsicsAPI _api_type {RHI::GraphsicsAPI::None};
        static inline HMODULE _rhi_dll {NULL};
    };

    extern "C" DLL void SetGraphicsAPI(RHI::GraphsicsAPI api_type);
    inline void SetGraphicsAPI(RHI::GraphsicsAPI api_type)
    {
        RHILoader::SetCurrentGraphicsAPI(api_type);
    }

    extern "C" DLL RHI::Instance* CreateInstance(RHI::AppInfo&& app_info);
    inline RHI::Instance* CreateInstance(RHI::AppInfo&& app_info)
    {
        return RHILoader::CreateInstance(std::move(app_info));
    }

}
