﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using dms.solvers.decision_tree.C4_5;
using dms.models;

namespace dms.view_models
{
    public class DecisionTreeC4_5ParametersViewModel : ISolverParameterViewModel
    {
        public event Action CanCreateChanged;
        public int MaxTreeDepth { get; set; }
        public int Inputs { get; set; }
        public int Outputs { get; set; }

        public bool CanCreateSolver(string name, models.Task task)
        {
            return true;
        }

        public void CreateSolver(string name, models.Task task)
        {
            int depth = MaxTreeDepth;

            //WARNING!!!
            //Here must be selected task template 
            //and number of inputs and outputs in it.
            TreeDescriptionC4_5 td = new TreeDescriptionC4_5(Inputs, Outputs, depth);

            TaskSolver ts = new TaskSolver()
            {
                Name = name,
                TypeName = "DecisionTreeC4_5",
                TaskID = task.ID,
                Description = td
            };
            ts.save();
        }
    }
}
