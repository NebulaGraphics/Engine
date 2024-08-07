#pragma once
#include <filesystem>
#include "Windows/PlatformTypes.h"
#include "Test.h"
#include "Graphics\RHILoader.h"
#include "RHI/Instance.h"
#include "RHI/Enums/Pipeline/EAccessFlag.h"
#include "RHI/Enums/Pipeline/EColorComponentFlag.h"
#include "RHI/Surfaces/Surface.h"
#include "RHI/Handles/ImageHandle.h"
#include "RHI/Memory/ImageView.h"
#include "RHI/Program/GPUPipelineManager.h"
#include "RHI/Program/GPUSubPass.h"
#include "RHI/Program/GPUPipelineStateObject.h"
#include "Windows/RenderWindowAPI.h"
#include "ShaderCompiler/ShaderCompilerAPI.h"

using namespace NebulaEngine;

#ifdef TEST_WINDOWS

struct RenderContext
{
    u32 windowId;
    RHI::Device* device;
    std::shared_ptr<RHI::GPURenderPass> renderPass;
    std::shared_ptr<RHI::FrameBuffer> frameBuffer;
    RHI::RHICommandBufferPool* commandPool;
    Containers::Vector<u32> gpuPrograms;
};

Containers::Vector<RenderContext> g_RenderContexts;

const int k_WindowsCount = 1;

LRESULT WinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }

        break;
    case WM_SYSCHAR:
        {
            if (wparam == VK_RETURN && (HIWORD(lparam) & KF_ALTDOWN))
            {
                return 0;
            }
        }
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}


class EngineTest : public Test
{
private:
    RHI::Instance* m_Instance{};

public:
    EngineTest(): m_Instance(nullptr)
    {
    }

    bool Initialize() override
    {
        if (!NebulaEngine::Debugger::Logger::GetInstance().Initialize())
        {
            throw std::exception(" Logger initialize failed.");
        }

        // Debugger::Logger::GetInstance().SetServerityLevel(Debugger::Logger::LogLevel::Log);
        
        LOG_INFO("Logger initialized..");

        g_RenderContexts.resize(k_WindowsCount);

        for (int i = 0; i < k_WindowsCount; ++i)
        {
            auto windowId = Platforms::CreateRenderWindow(nullptr, WinProc, 640, 480);
            g_RenderContexts[i] = RenderContext
            {
                windowId
            };
        }

        // auto window2 = Platforms::CreateRenderWindow(nullptr, WinProc, 400, 680);
        // auto window3 = Platforms::CreateRenderWindow(nullptr, WinProc, 600, 380);

        RHI::InstanceInfo app_info
        {
            /** app name */
            " Engine Test",
            /** engine name */
            "Engine Test",
            /** enable validation layer */
            true,
            /** API Version */
            0, 1, 3, 0,
            /** App Version */
            1, 0, 0,
            /** App Version */
            1, 0, 0
        };

        Graphics::RHILoader::SetCurrentGraphicsAPI(RHI::GraphsicsAPI::Vulkan);
        m_Instance = Graphics::RHILoader::CreateInstance(std::move(app_info));
        auto env = m_Instance->GetEnvString();
        // LOG_INFO(std::move(env));

        // init surfaces
        for (auto& renderContext : g_RenderContexts)
        {
            m_Instance->CreateSurface(std::move(renderContext.windowId));
        }

        // pick physical device
        m_Instance->PickPhysicalDevice();

        // init logical devices
        m_Instance->InitLogicDevices();

        for (int i = 0; i < k_WindowsCount; ++i)
        {
            g_RenderContexts[i].device = &m_Instance->GetLogicalDevice(g_RenderContexts[i].windowId);
            auto poolId = g_RenderContexts[i].device->CreateCommandBufferPool();
            g_RenderContexts[i].commandPool = g_RenderContexts[i].device->GetCommandBufferPool(poolId);
            g_RenderContexts[i].renderPass = g_RenderContexts[i].device->GetRenderPass();
            g_RenderContexts[i].frameBuffer = g_RenderContexts[i].device->GetFrameBuffer();
        }

        Platforms::InitDXC();

        namespace fs = std::filesystem;
        auto currentPath = fs::current_path().generic_wstring() + L"\\Shader";
        auto path = currentPath + L"\\FullScreen.hlsl";

        Platforms::ShaderCompileParams vertexParams
        {
            path,
            L"Vert",
            L"6_0",
            L"-spirv",
            m_Instance->GetEnvString(),
            L"0",
            RHI::ProgramStage::Vertex,
            {},
            {},
            currentPath + L"\\FullScreen.vert.spirv",
            true
        };

        Platforms::ShaderCompilerOutput outputVertex;
        if (Platforms::CompileShaderFromFile(std::move(vertexParams), outputVertex))
        {
            LOG_DEBUG("Vertex Shader Compilation done.");
        }

        for (int i = 0; i < k_WindowsCount; ++i)
        {
            auto programId = g_RenderContexts[i].device->CreateGPUProgram();
            auto desc = RHI::GPUProgramDesc
            {
                outputVertex.codeSize,
                outputVertex.codePointer,
                "Vert",
                String::WStringToString(path).c_str(),
                RHI::SHADER_STAGE_VERTEX_BIT
            };
            g_RenderContexts[i].device->AttachProgramByteCode(programId, std::move(desc));
            g_RenderContexts[i].gpuPrograms.emplace_back(programId);
        }


        Platforms::ShaderCompileParams fragmentParams
        {
            path,
            L"Frag",
            L"6_0",
            L"-spirv",
            m_Instance->GetEnvString(),
            L"0",
            RHI::ProgramStage::Fragment,
            {},
            {},
            currentPath + L"\\FullScreen.frag.spirv",
            true
        };

        Platforms::ShaderCompilerOutput outputfragment;
        if (Platforms::CompileShaderFromFile(std::move(fragmentParams), outputfragment))
        {
            LOG_DEBUG("Fragment Shader Compilation done.");
        }

        for (int i = 0; i < k_WindowsCount; ++i)
        {
            auto programId = g_RenderContexts[i].device->CreateGPUProgram();
            auto desc = RHI::GPUProgramDesc
            {
                outputfragment.codeSize,
                outputfragment.codePointer,
                "Frag",
                String::WStringToString(path).c_str(),
                RHI::SHADER_STAGE_FRAGMENT_BIT
            };
            g_RenderContexts[i].device->AttachProgramByteCode(programId, std::move(desc));
            g_RenderContexts[i].gpuPrograms.emplace_back(programId);
        }

        return true;
    }

    void Run() override
    {
        for (int i = 0; i < k_WindowsCount; ++i)
        {
            RecordSubmitPresent(std::move(g_RenderContexts[i]));
        }
    }

    void RecordSubmitPresent(RenderContext&& context)
    {
        auto commandBuffer = context.commandPool->GetCommandBuffer();

        // Record cmd
        commandBuffer->Begin();

        {
            auto renderPass = context.renderPass.get();
            auto frameBuffer = context.frameBuffer.get();
            auto backBuffer = context.device->GetSurface()->GetSwapChain()->AquireCurrentImage();
            auto backBufferView = static_cast<RHI::ImageView*>(backBuffer->GetMemoryView());
            auto format = backBufferView->GetFormat();
            
            renderPass->FreeRenderPass();
            
            renderPass->AddAttachmentAction(
                format, RHI::SAMPLE_COUNT_1_BIT,
                RHI::ATTACHMENT_LOAD_OP_CLEAR, RHI::ATTACHMENT_STORE_OP_STORE,
                RHI::ATTACHMENT_LOAD_OP_DONT_CARE, RHI::ATTACHMENT_STORE_OP_DONT_CARE,
                RHI::IMAGE_LAYOUT_UNDEFINED, RHI::IMAGE_LAYOUT_PRESENT_SRC_KHR
            );

            auto subpass = renderPass->AddSubPass();

            {
                // setup subpass
                subpass->SetDependency(
                    m_Instance->GetExternalIndex(),
                    RHI::EPipelineStageFlag::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                    0,
                    RHI::EPipelineStageFlag::PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                    RHI::EAccessFlagBits::ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                    0
                );
                subpass->SetBindPoint(RHI::PIPELINE_BIND_POINT_GRAPHICS);
                subpass->AddColorReference(0, RHI::IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
                subpass->SetSubPassDescriptionFlag(0);
            }

            renderPass->AllocRenderPass();

            frameBuffer->SetAttachment(backBufferView, renderPass);

            {
                RHI::RenderPassBeginDesc desc
                {
                    renderPass,
                    frameBuffer,
                    RHI::SUBPASS_CONTENTS_INLINE
                };


                commandBuffer->BeginRenderPass(std::move(desc));

                {
                    auto pipelineManager = context.device->GetGPUPipelineManager();

                    auto pipelineState = pipelineManager->GetPipelineState();
                    for (auto programId : context.gpuPrograms)
                    {
                        pipelineState->AddProgram(programId);
                    }

                    {
                        // Pipeline State Object
                        pipelineState->AddDynamicPipelineState(RHI::DYNAMIC_STATE_SCISSOR);
                        pipelineState->AddDynamicPipelineState(RHI::DYNAMIC_STATE_VIEWPORT);
                        pipelineState->SetPrimitiveState(RHI::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, false);
                        pipelineState->SetDepthClampEnable(false);
                        pipelineState->SetRasterizerDiscardEnable(false);
                        pipelineState->SetPolygonMode(RHI::EPOLYGON_MODE_FILL);
                        pipelineState->SetLineWidth(1.0F);
                        pipelineState->SetCullMode(RHI::CULL_MODE_NONE);
                        pipelineState->SetFrontFace(RHI::FRONT_FACE_CLOCKWISE);
                        pipelineState->SetDepthBiasEnable(false);
                        pipelineState->SetSampleShading(false);
                        pipelineState->SetSampleCount(RHI::SAMPLE_COUNT_1_BIT);
                        pipelineState->AddBlendAttachmentState(false,
                                                               RHI::EColorComponentFlagBits::COLOR_COMPONENT_R_BIT |
                                                               RHI::EColorComponentFlagBits::COLOR_COMPONENT_G_BIT |
                                                               RHI::EColorComponentFlagBits::COLOR_COMPONENT_B_BIT |
                                                               RHI::EColorComponentFlagBits::COLOR_COMPONENT_A_BIT);
                        pipelineState->SetLogicOp(false, RHI::LOGIC_OP_COPY);
                        pipelineState->SetBlendConstants(0.0f, 0.0f, 0.0f, 0.0f);

                        auto pipeline = pipelineManager->GetGraphicsPipeline(pipelineState.get());

                        pipeline->AllocGraphicPipeline(subpass);
                        commandBuffer->BindPipeline(pipeline);
                    }

                    {
                        // viewport scissor
                        commandBuffer->SetViewport(0, 0, static_cast<f32>(backBufferView->GetWidth()), static_cast<
                                                       f32>(backBufferView->GetHeight()), 0, 1);
                        commandBuffer->SetScissor(0, 0, backBufferView->GetWidth(), backBufferView->GetHeight());
                    }

                    {
                        // draw call
                        commandBuffer->Draw(3, 1, 0, 0);
                    }
                }
                commandBuffer->EndRenderPass();
            }
        }

        commandBuffer->End();

        {
            // Submit
            context.device->Submit(commandBuffer.get());
        }

        {
            // Present
            context.device->GetSurface()->GetSwapChain()->Present();
        }
    }

    void Shutdown() override
    {
        LOG_INFO(" Shut down ...");

        for (auto renderContext : g_RenderContexts)
        {
            renderContext.device->DeviceWaitIdle();
        }
        g_RenderContexts.clear();
        
        // RHI dispose
        delete m_Instance;
        
        Platforms::ReleaseDXC();

        // rhi loader dispose 
        Graphics::RHILoader::Dispose();

        // NOTE: logger must be dispose at the last
        Debugger::Logger::Dispose();
    }
};

#endif
