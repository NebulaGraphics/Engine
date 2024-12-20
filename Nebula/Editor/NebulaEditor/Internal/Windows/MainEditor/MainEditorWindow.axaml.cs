
using Avalonia.Controls;
using Avalonia.Interactivity;
using NebulaEditor.ViewModels;
using NebulaEngine;
using System.Threading.Tasks;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Data;
using Avalonia.Threading;
using NebulaEditor.Utilities;
using NebulaEditor.ViewModels.Startup;
using NebulaEngine.Debugger;
using NebulaEngine.Views.Rendering;

namespace NebulaEditor.Windows.MainEditor
{
    using Logger = NebulaEngine.Debug.Logger;
    public partial class MainEditorWindow : Window
    {
        private NebulaFileSystemWatcher m_FileSystemWatcher;
        
        public MainEditorWindow()
        {
            InitializeComponent();
        }

        /// <inheritdoc/>
        protected override void OnLoaded(RoutedEventArgs e)
        {
            base.OnLoaded(e);
            this.Title = NebulaApplication.s_ProjectName;
            
            // File Watcher
            m_FileSystemWatcher = new NebulaFileSystemWatcher();

            // Menu Items
            HeaderMenuContainer.Children.Clear();
            HeaderMenuContainer.Children.Add(ControlsFactory.CreateMenu(ControlsFactory.MenuType.Header));
            
            // Preview
            SceneView.Children.Add(new RenderSurfaceView()
            {
                ParentWindow = this,
                IsSceneView = true,
                SurfaceType = NebulaEngine.Rendering.SurfaceType.SceneView,
                DataContext = new RenderSurfaceViewModel(true)
            });
            
            GameView.Children.Add(new RenderSurfaceView()
            {
                ParentWindow = this,
                IsSceneView = false,
                SurfaceType = NebulaEngine.Rendering.SurfaceType.GameView,
                DataContext = new RenderSurfaceViewModel(false)
            });
            
            Dispatcher.UIThread.InvokeAsync(() =>
            {
                if (NebulaInstance.Run("Nebula Instance (Attach to Editor)") != 0)
                {
                    Logger.Error("Nebula instance run error.");
                }
                
            });
            
        }

        // TODO: remove this
        private async Task<int> LoadEditorConfigAsync(MainWindowViewModel mainWindowViewModel)
        {
            int code = await mainWindowViewModel.LoadEditorConfigAsync();
            return code;
        }

        protected override void OnUnloaded(RoutedEventArgs e)
        {
            base.OnUnloaded(e);
            Logger.Log("Close Editor Window.");
            m_FileSystemWatcher.Dispose();
            m_FileSystemWatcher = null;
            // NebulaInstance.End();
            
            if (App.Current.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                var mainWindowViewModel = new MainWindowViewModel();

                int resultCode = LoadEditorConfigAsync(mainWindowViewModel).Result;
                if (resultCode != 0)
                {
                    App.Shutdown(desktop);

                    return;
                }

                desktop.MainWindow = new MainWindow()
                {
                    DataContext = mainWindowViewModel
                };

                desktop.MainWindow.Show();
            }
        }
    }
}