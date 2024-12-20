#pragma once
#include "SwapChain.h"
#include "../../Common/CommandHeaders.h"
#include "RHI/Instance.h"

namespace NebulaEngine::RHI 
{
	class Surface 
	{
	public:
		NO_COPY_NO_MOVE_NO_DEFAULT(Surface)
		virtual ~Surface() noexcept
		{
			m_RenderWindowId = InvalidID;
			m_Instance = nullptr;
		}
		explicit Surface(u32&& id, Instance* instance): m_RenderWindowId(id), m_Instance(instance) { };
		virtual void* GetHandle() const = 0;
		virtual void InitSwapChain() = 0;

		virtual SwapChain* GetSwapChain() = 0;
	protected:
		u32 m_RenderWindowId;
		Instance* m_Instance;
	
	};
}
