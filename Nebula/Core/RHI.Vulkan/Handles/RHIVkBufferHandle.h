#pragma once
#include "../CommandBuffer/RHIVkCommandBuffer.h"
#include "RHI/Handles/BufferHandle.h"

namespace NebulaEngine::RHI
{
    class RHIVkBufferHandle final : public BufferHandle
    {
   
    public:
        NO_COPY_NO_MOVE(RHIVkBufferHandle)
        explicit RHIVkBufferHandle(Device* device);
        ~RHIVkBufferHandle() noexcept override;
        void* GetHandle() const override;

        bool AllocBufferHandle(BufferAllocDesc && desc) override;
        void FreeBufferHandle() override;

        bool AllocBufferMemory(u32 memoryPropertiesBits) override;
        void FreeBufferMemory() override;
        void MemoryCopy(void const* src, u32 offset) override;
    private:
        
        VkBuffer m_VkBuffer { VK_NULL_HANDLE };
        Device* m_Device;
        
    };
}
