using System;
using System.IO;
using Avalonia.Controls;
using Avalonia.Controls.Models.TreeDataGrid;
using ArisenEngine;

namespace ArisenEditor.ViewModels;

public class TestTreeViewModel : ViewModelBase
{
    private HierarchicalTreeDataGridSource<FileTreeNode> m_Source;

    public HierarchicalTreeDataGridSource<FileTreeNode> Source
    {
        get
        {
            if (m_Source == null)
            {
                InitializeSource();
            }

            return m_Source;
        }
    }
    
    private void InitializeSource()
    {
        m_Source = new HierarchicalTreeDataGridSource<FileTreeNode>(Array.Empty<FileTreeNode>())
        {
            Columns =
            {
                new TemplateColumn<FileTreeNode>("Header","NameCell"),
                new TemplateColumn<FileTreeNode>("Header","NameCell")
            }
        };
        
        m_Source.RowSelection!.SingleSelect = false;
        
        m_Source.Items = new FileTreeNode[]
        {
            new FileTreeNode("A", Path.Combine(ArisenApplication.s_ProjectRoot, "Assets"), true, isRoot: true, true),
            new FileTreeNode("B", Path.Combine(ArisenApplication.s_ProjectRoot, "Packages"), true, isRoot: true, true),
            new FileTreeNode("C", Path.Combine(ArisenApplication.s_ProjectRoot, "Assets"), true, isRoot: true, true),
            new FileTreeNode("D", Path.Combine(ArisenApplication.s_ProjectRoot, "Packages"), true, isRoot: true, true),
            new FileTreeNode("E", Path.Combine(ArisenApplication.s_ProjectRoot, "Assets"), true, isRoot: true, true),
            new FileTreeNode("F", Path.Combine(ArisenApplication.s_ProjectRoot, "Packages"), true, isRoot: true, true),
        };
        
    }
}