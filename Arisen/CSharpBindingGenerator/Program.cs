﻿// See https://aka.ms/new-console-template for more information

using CppSharp;
using CSharpBindingGenerator;


static void DeleteDirectory(string directoryPath, List<string> skipFolders, List<string> excludedExtensions)
{
    var directoryInfo = new DirectoryInfo(directoryPath);
    if (skipFolders.Contains(directoryInfo.Name))
    {
        return;
    }
    
    bool hasSkipFile = false;
    var files = Directory.GetFiles(directoryPath);
    foreach (var file in files)
    {
        var fileInfo = new FileInfo(file);
        if (excludedExtensions.Count > 0 && excludedExtensions.Contains(fileInfo.Extension))
        {
            hasSkipFile = true;
            continue;
        }
                
        File.Delete(file);
    }
            
    foreach (var directory in Directory.GetDirectories(directoryPath))
    {
        DeleteDirectory(directory, skipFolders, excludedExtensions);
    }
    
    if (hasSkipFile)
    {
        return;
    }

    Directory.Delete(directoryPath);
            
}

Console.WriteLine("Start Generate Binding ...");

DeleteDirectory(@"../../../../AutoGenerated", new List<string>(){"obj"}, new List<string>() {".csproj"});

// TODO
ConsoleDriver.Run(new DebuggerLibrary());
ConsoleDriver.Run(new PlatformLibrary());