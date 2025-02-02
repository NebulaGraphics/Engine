using CppSharp;
using CppSharp.AST;
using CppSharp.Generators;

namespace CppSharpCsharp;

public class EngineLibrary : ILibrary
{
    public void Preprocess(Driver driver, ASTContext ctx)
    {
        // throw new NotImplementedException();
    }

    public void Postprocess(Driver driver, ASTContext ctx)
    {
        // throw new NotImplementedException();
    }
    
    void SetupDebugger(Driver driver)
    {
        var options = driver.Options;
        options.GeneratorKind = GeneratorKind.CSharp;
        options.OutputDir = @"D:\EngineSource\Arisen\Engine\Arisen\Test\CppSharpInvokerTest\";
        var module = options.AddModule("Debugger");
        module.OutputNamespace = "";
        // Core.Debugger
        module.IncludeDirs.AddRange(new string[]
        {
            @"D:\EngineSource\Arisen\Engine\Arisen\Core\Core.Infra\",
            @"D:\EngineSource\Arisen\Engine\Arisen\Core\Core.Debugger\"
        });  
        module.Headers.AddRange(new string[]
        {
            @"Common/CommandHeaders.h",
            @"DllHeader.h",
            @"Logger\Logger.h"
        });
        // lib
        module.LibraryDirs.Add(@"D:\EngineSource\Arisen\Engine\Arisen\x64\Debug");
        module.Libraries.Add("Core.Debugger.lib");
        module.Libraries.Add("Core.Infra.lib");
    }
    
    public void Setup(Driver driver)
    {
        SetupDebugger(driver);
        
        // var options = driver.Options;
        // options.GeneratorKind = GeneratorKind.CSharp;
        // options.OutputDir = "./output";
        // var module = options.AddModule("Debugger");
        //
        // #region Infra
        //
        // // infra
        // module.IncludeDirs.Add(@"D:\EngineSource\Arisen\Engine\Arisen\Core\Core.Infra\");  
        // module.Headers.AddRange(new string[]
        // {
        //     @"Common/CommandHeaders.h",
        //     @"RHI/GraphsicsAPI.h",
        //     @"RHI/Instance.h"
        // });
        // // lib
        // module.LibraryDirs.Add(@"D:\EngineSource\Arisen\Engine\Arisen\x64\Debug");
        // module.Libraries.Add("Core.Infra.lib");
        //
        // #endregion
        //
        // #region Engine
        //
        // // Engine
        // module.IncludeDirs.Add(@"D:\EngineSource\Arisen\Engine\Arisen\Engine\Engine\");  
        // module.Headers.AddRange(new string[]
        // {
        //     @"EngineCommon.h",
        //     @"Debugger\LoggerAPI.h",
        //     @"Graphics\RHILoader.h",
        // });
        //
        // // lib
        // module.LibraryDirs.Add(@"D:\EngineSource\Arisen\Engine\Arisen\x64\Debug");
        // module.Libraries.Add("Engine.lib");
        //
        // #endregion
    }

    public void SetupPasses(Driver driver)
    {
        // throw new NotImplementedException();
    }
}