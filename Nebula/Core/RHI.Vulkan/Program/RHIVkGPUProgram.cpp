#include "RHIVkGPUProgram.h"
#include "Logger/Logger.h"

NebulaEngine::RHI::RHIVkGPUProgram::RHIVkGPUProgram(VkDevice device): GPUProgram(), m_VkDevice(device), m_VkShaderModule(VK_NULL_HANDLE)
{
}

NebulaEngine::RHI::RHIVkGPUProgram::~RHIVkGPUProgram() noexcept
{
    DestroyHandle();
}

bool NebulaEngine::RHI::RHIVkGPUProgram::AttachProgramByteCode(GPUProgramDesc&& desc)
{

    if (m_VkShaderModule != VK_NULL_HANDLE)
    {
        DestroyHandle();
    }
    
    VkShaderModuleCreateInfo createInfo {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = desc.codeSize;
    createInfo.pCode = desc.byteCode;
    
    if (vkCreateShaderModule(m_VkDevice, &createInfo, nullptr, &m_VkShaderModule) != VK_SUCCESS)
    {
        LOG_ERROR("[RHIVkGPUProgram::AttachProgramByteCode]: failed to create shader module!");

        return false;
    }

    m_Stage = desc.stage;
    
    return true;
}

void NebulaEngine::RHI::RHIVkGPUProgram::DestroyHandle()
{
    ASSERT(m_VkDevice != VK_NULL_HANDLE && m_VkShaderModule != VK_NULL_HANDLE);
    vkDestroyShaderModule(m_VkDevice, m_VkShaderModule, nullptr);
    m_VkShaderModule = VK_NULL_HANDLE;
    LOG_DEBUG("## Destory Vulkan Shader Module. ##");
}