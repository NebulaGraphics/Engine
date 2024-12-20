﻿#include "RHIVkFrameBuffer.h"
#include "Logger/Logger.h"
#include "RHI/Memory/ImageView.h"

NebulaEngine::RHI::RHIVkFrameBuffer::RHIVkFrameBuffer(VkDevice device, u32 maxFramesInFlight): FrameBuffer(maxFramesInFlight), m_VkDevice(device)
{
    m_VkFrameBuffers.resize(maxFramesInFlight);
    for (int i = 0; i < maxFramesInFlight; ++i)
    {
        m_VkFrameBuffers[i] = VK_NULL_HANDLE;
    }
}

NebulaEngine::RHI::RHIVkFrameBuffer::~RHIVkFrameBuffer() noexcept
{
   FreeAllFrameBuffers();
}

void* NebulaEngine::RHI::RHIVkFrameBuffer::GetHandle(u32 currentFrameIndex)
{
    ASSERT(m_VkFrameBuffers[currentFrameIndex % m_MaxFramesInFlight] != VK_NULL_HANDLE);
    return m_VkFrameBuffers[currentFrameIndex % m_MaxFramesInFlight];
}

void NebulaEngine::RHI::RHIVkFrameBuffer::SetAttachment(u32 frameIndex, ImageView* imageView, GPURenderPass* renderPass)
{
    // TODO: use cache?
    FreeFrameBuffer(frameIndex);

    m_ImageView = imageView;
    
    VkFramebufferCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    createInfo.renderPass = static_cast<VkRenderPass>(renderPass->GetHandle(frameIndex));
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = static_cast<const VkImageView*>(imageView->GetViewPointer());
    createInfo.width = imageView->GetWidth();
    createInfo.height = imageView->GetHeight();
    createInfo.layers = imageView->GetLayerCount();

    if (vkCreateFramebuffer(m_VkDevice, &createInfo, nullptr, &m_VkFrameBuffers[frameIndex % m_MaxFramesInFlight]) != VK_SUCCESS)
    {
        LOG_FATAL_AND_THROW("[RHIVkFrameBuffer::SetAttachment]: failed to create framebuffer!");
    }

    LOG_DEBUG("[RHIVkFrameBuffer::SetAttachment]: create vulkan frame buffer.");
    m_RenderArea.height = imageView->GetHeight();
    m_RenderArea.width = imageView->GetWidth();
    m_RenderArea.offsetX = 0;
    m_RenderArea.offsetY = 0;
}

NebulaEngine::RHI::Format NebulaEngine::RHI::RHIVkFrameBuffer::GetAttachFormat()
{
    ASSERT(m_ImageView != nullptr);
    return m_ImageView->GetFormat();
}

void NebulaEngine::RHI::RHIVkFrameBuffer::FreeFrameBuffer(u32 currentFrameIndex)
{
    if(m_VkFrameBuffers[currentFrameIndex % m_MaxFramesInFlight] != VK_NULL_HANDLE)
    {
        vkDestroyFramebuffer(m_VkDevice, m_VkFrameBuffers[currentFrameIndex % m_MaxFramesInFlight], nullptr);
        LOG_DEBUG("## Destroy Vulkan Frame Buffer ##");
        m_VkFrameBuffers[currentFrameIndex % m_MaxFramesInFlight] = VK_NULL_HANDLE;
    }

    m_ImageView = nullptr;
}

void NebulaEngine::RHI::RHIVkFrameBuffer::FreeAllFrameBuffers()
{
    for (int i = 0; i < m_VkFrameBuffers.size(); ++i)
    {
        if(m_VkFrameBuffers[i] != VK_NULL_HANDLE)
        {
            vkDestroyFramebuffer(m_VkDevice, m_VkFrameBuffers[i], nullptr);
            m_VkFrameBuffers[i] = VK_NULL_HANDLE;
        }
    }
    LOG_DEBUG("## Destroy All Vulkan Frame Buffers ##");
    m_VkFrameBuffers.clear();
}
