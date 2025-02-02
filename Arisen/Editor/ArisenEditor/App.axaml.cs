
using System;
using System.Diagnostics;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using System.Threading.Tasks;
using ArisenEditor.ViewModels.Startup;
using Avalonia.Controls;
using ArisenEngine;

namespace ArisenEditor
{
    public partial class App : Application
    {
        public override void Initialize()
        {
            AvaloniaXamlLoader.Load(this);
        }

        public override async void OnFrameworkInitializationCompleted()
        {
            if (OperatingSystem.IsWindows())
            {
                ArisenApplication.s_Platform = RuntimePlatform.Windows;
                    
            } else if (OperatingSystem.IsMacOS())
            {
                ArisenApplication.s_Platform = RuntimePlatform.MacOS;
            }

            EnterNormally();
            
            base.OnFrameworkInitializationCompleted();
        }

        private async void EnterNormally()
        {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                desktop.ShutdownMode = ShutdownMode.OnExplicitShutdown;
                
                var mainWindowViewModel = new MainWindowViewModel();
                var splashWindow = new Splash();
                desktop.MainWindow = splashWindow;
                splashWindow.Show();

                int resultCode = await mainWindowViewModel.LoadEditorConfigAsync();
                if ( resultCode != 0 ) {

                    splashWindow.Close();
                    base.OnFrameworkInitializationCompleted();

                    System.Environment.Exit( resultCode );

                    return;
                }

               
                await Task.Delay( 1000 );

                var mainWindow = new Windows.MainWindow()
                {
                    DataContext = mainWindowViewModel
                };

                desktop.MainWindow = mainWindow;
                
                mainWindow.Show();

                splashWindow.Close();

            }
        }

        public object CreateView(Window window)
        {
            throw new System.NotImplementedException();
        }
        
        private static bool IsProduction()
        {
#if DEBUG
            return false;
#else
        return true;
#endif
        }

        public static void Shutdown(IClassicDesktopStyleApplicationLifetime desktop)
        {
            // ArisenInstance.DisposeLogger();
            desktop.Shutdown();
        }
    }
}