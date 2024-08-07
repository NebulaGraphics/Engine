﻿#pragma once
#include "../../Common/CommandHeaders.h"
#include "RHI/Enums/Memory/ImageViewType.h"
#include "RHI/Enums/Memory/MemoryViewType.h"
#include "RHI/Handles/ComponentMapping.h"
#include "RHI/Enums/Image/Format.h"

namespace NebulaEngine::RHI
{
    typedef struct ImageViewDesc
    {
        u32 createFlags;
        ImageViewType type;
        Format format;
        ComponentMapping componentMapping;
        u32 width;
        u32 height;
        // subresource
        u32 aspectMask;
        u32 baseMipLevel;
        u32 levelCount;
        u32 baseArrayLayer;
        u32 layerCount;
        std::optional<const void*> customData;
    } ImageViewDesc;

    
    class MemoryView
    {
    public:
        NO_COPY_NO_MOVE_NO_DEFAULT(MemoryView)
        MemoryView(MemoryViewType type) : m_ViewType(type) { }
        VIRTUAL_DECONSTRUCTOR(MemoryView)
        virtual void* GetView() = 0;
        virtual void* GetViewPointer() = 0;
        const MemoryViewType GetViewType() const { return m_ViewType; }
    protected:
        MemoryViewType m_ViewType;
        std::optional<ImageViewDesc> m_ImageViewDesc;
    };
}
