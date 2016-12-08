﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using dms.view_models;

namespace dms.gui
{
    /// <summary>
    /// Interaction logic for TaskCreation.xaml
    /// </summary>
    public partial class TaskCreationWindow : Window
    {
        TaskCreationViewModel viewModel;
        public TaskCreationWindow(TaskCreationViewModel vm)
        {
            InitializeComponent();

            viewModel = vm;
            DataContext = viewModel;
            viewModel.OnCreatingSelection += (s, e) => CreateSelectionAddPane(e.Data);
        }

        public void CreateSelectionAddPane(SelectionCreationViewModel vm)
        {

        }
    }
}
