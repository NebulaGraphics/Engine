#pragma once


#include "../Common.h"
#include "RHI/Devices/Device.h"

namespace NebulaEngine::RHI
{
	 class DX12Device final : public Device
	{
	public:

		
	};

}

extern "C" RHI_DX12_DLL NebulaEngine::RHI::Device * CreateDevice();


