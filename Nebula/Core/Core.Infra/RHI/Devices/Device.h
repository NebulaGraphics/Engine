#pragma once
#include "../../Common/CommandHeaders.h"
#include "../RHICommon.h"
#include "RHI/CommandBuffer/RHICommandBufferPool.h"

namespace NebulaEngine::RHI
{
    class RHICommandBuffer;
    class GPUProgram;
}

namespace NebulaEngine::RHI
{
    class GPUPipelineManager;
    class Instance;
    class Surface;
    class RHICommandBufferPool;
    class GPURenderPass;
    class FrameBuffer;
    
    class Device
    {
    public:
        NO_COPY_NO_MOVE_NO_DEFAULT(Device)
        virtual ~Device() noexcept
        {
            m_Instance = nullptr;
            m_Surface = nullptr;
        }

        Surface* GetSurface() const { return m_Surface; }
        
        virtual void* GetHandle() const = 0;
        virtual void DeviceWaitIdle() const = 0;
        virtual u32 CreateGPUProgram() = 0;
        virtual GPUProgram* GetGPUProgram(u32 programId) = 0;
        virtual void DestroyGPUProgram(u32 programId) = 0;
        virtual bool AttachProgramByteCode(u32 programId, GPUProgramDesc&& desc) = 0;
        virtual u32 CreateCommandBufferPool() = 0;
        virtual RHICommandBufferPool* GetCommandBufferPool(u32 id) = 0;

        virtual std::shared_ptr<GPURenderPass> GetRenderPass() = 0;
        virtual void ReleaseRenderPass(std::shared_ptr<GPURenderPass> renderPass) = 0;

        virtual std::shared_ptr<FrameBuffer> GetFrameBuffer() = 0;
        virtual void ReleaseFrameBuffer(std::shared_ptr<FrameBuffer> frameBuffer) = 0;

        virtual GPUPipelineManager* GetGPUPipelineManager() const = 0;

        virtual void Submit(RHICommandBuffer* commandBuffer) = 0;
    protected:
        
        Instance* m_Instance;
        Surface* m_Surface;
        Device(Instance* instance, Surface* surface): m_Instance(instance), m_Surface(surface) {}
    private:
        
    };
}
