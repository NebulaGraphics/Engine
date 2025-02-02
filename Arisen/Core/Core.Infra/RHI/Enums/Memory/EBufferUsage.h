﻿#pragma once
namespace ArisenEngine::RHI
{
    typedef enum EBufferUsageFlagBits {
        BUFFER_USAGE_TRANSFER_SRC_BIT = 0x00000001,
        BUFFER_USAGE_TRANSFER_DST_BIT = 0x00000002,
        BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT = 0x00000004,
        BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT = 0x00000008,
        BUFFER_USAGE_UNIFORM_BUFFER_BIT = 0x00000010,
        BUFFER_USAGE_STORAGE_BUFFER_BIT = 0x00000020,
        BUFFER_USAGE_INDEX_BUFFER_BIT = 0x00000040,
        BUFFER_USAGE_VERTEX_BUFFER_BIT = 0x00000080,
        BUFFER_USAGE_INDIRECT_BUFFER_BIT = 0x00000100,
        BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT = 0x00020000,
        BUFFER_USAGE_VIDEO_DECODE_SRC_BIT_KHR = 0x00002000,
        BUFFER_USAGE_VIDEO_DECODE_DST_BIT_KHR = 0x00004000,
        BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT = 0x00000800,
        BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT = 0x00001000,
        BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT = 0x00000200,
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        VK_BUFFER_USAGE_EXECUTION_GRAPH_SCRATCH_BIT_AMDX = 0x02000000,
    #endif
        BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR = 0x00080000,
        BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR = 0x00100000,
        BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR = 0x00000400,
        BUFFER_USAGE_VIDEO_ENCODE_DST_BIT_KHR = 0x00008000,
        BUFFER_USAGE_VIDEO_ENCODE_SRC_BIT_KHR = 0x00010000,
        BUFFER_USAGE_SAMPLER_DESCRIPTOR_BUFFER_BIT_EXT = 0x00200000,
        BUFFER_USAGE_RESOURCE_DESCRIPTOR_BUFFER_BIT_EXT = 0x00400000,
        BUFFER_USAGE_PUSH_DESCRIPTORS_DESCRIPTOR_BUFFER_BIT_EXT = 0x04000000,
        BUFFER_USAGE_MICROMAP_BUILD_INPUT_READ_ONLY_BIT_EXT = 0x00800000,
        BUFFER_USAGE_MICROMAP_STORAGE_BIT_EXT = 0x01000000,
        BUFFER_USAGE_RAY_TRACING_BIT_NV = BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR,
        BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT = BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR = BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
        BUFFER_USAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
    } EBufferUsageFlagBits;
    
}