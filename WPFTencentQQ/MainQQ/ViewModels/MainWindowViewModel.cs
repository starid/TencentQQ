using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Windows.Data;
using MainQQ.DataAccess;
using MainQQ.Models;
using MainQQ.Properties;

namespace MainQQ.ViewModels
{
    /// <summary>
    /// The ViewModel for the application's main window.
    /// </summary>
    public class MainWindowViewModel : WorkspaceViewModel
    {
        #region Fields
                
        ReadOnlyCollection<CommandViewModel> _commands;
        readonly UserRepository _UserRepository;
        ObservableCollection<WorkspaceViewModel> _workspaces;

        #endregion // Fields

        #region Constructor

        public MainWindowViewModel(string UserDataFile)
        {
            base.DisplayName = Resources.MainWindowViewModel_DisplayName;

            _UserRepository = new UserRepository(UserDataFile);

            //foreach(User _user in _UserRepository.GetUsers())
            //{
            //    _user.MsgViewModelEvent += OnMsgViewAddToWorkspaces;
            //}
        }

        #endregion // Constructor

        #region Commands

        /// <summary>
        /// Returns a read-only list of commands 
        /// that the UI can display and execute.
        /// </summary>
        public ReadOnlyCollection<CommandViewModel> Commands
        {
            get
            {
                if (_commands == null)
                {
                    List<CommandViewModel> cmds = this.CreateCommands();
                    _commands = new ReadOnlyCollection<CommandViewModel>(cmds);
                }
                return _commands;
            }
        }

        List<CommandViewModel> CreateCommands()
        {
            return new List<CommandViewModel>
            {
                new CommandViewModel(
                    Resources.MainWindowViewModel_Command_ViewAllUsers,
                    new RelayCommand(param => this.ShowAllUsers())),

                new CommandViewModel(
                    Resources.MainWindowViewModel_Command_SaveNewUser,
                    new RelayCommand(param => this.SaveNewUser())),

                new CommandViewModel(
                    Resources.MainWindowViewModel_Command_NetSet,
                    new RelayCommand(param => this.NetSet()))
            };
        }

        #endregion // Commands

        #region Workspaces

        /// <summary>
        /// Returns the collection of available workspaces to display.
        /// A 'workspace' is a ViewModel that can request to be closed.
        /// </summary>
        public ObservableCollection<WorkspaceViewModel> Workspaces
        {
            get
            {
                if (_workspaces == null)
                {
                    _workspaces = new ObservableCollection<WorkspaceViewModel>();
                    _workspaces.CollectionChanged += this.OnWorkspacesChanged;
                }
                return _workspaces;
            }
        }

        void OnWorkspacesChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null && e.NewItems.Count != 0)
                foreach (WorkspaceViewModel workspace in e.NewItems)
                    workspace.RequestClose += this.OnWorkspaceRequestClose;

            if (e.OldItems != null && e.OldItems.Count != 0)
                foreach (WorkspaceViewModel workspace in e.OldItems)
                    workspace.RequestClose -= this.OnWorkspaceRequestClose;
        }

        void OnWorkspaceRequestClose(object sender, EventArgs e)
        {
            WorkspaceViewModel workspace = sender as WorkspaceViewModel;
            workspace.Dispose();
            this.Workspaces.Remove(workspace);
        }

        #endregion // Workspaces

        #region Private Helpers

        void SaveNewUser()
        {
            //User newUser = User.CreateNewUser();
            //UserViewModel workspace = new UserViewModel(newUser, _UserRepository);
            //this.Workspaces.Add(workspace);
            //this.SetActiveWorkspace(workspace);

            UserViewModel workspace =
               this.Workspaces.FirstOrDefault(vm => vm is UserViewModel)
               as UserViewModel;
            if (workspace == null)
            {
                User newUser = User.CreateNewUser();
                workspace = new UserViewModel(newUser, _UserRepository);
                workspace.CloseViewEvent+=new EventHandler<EventArgs>(CloseViewEvent);
                this.Workspaces.Add(workspace);
            }
            this.SetActiveWorkspace(workspace);
        }

        void ShowAllUsers()
        {
            AllUsersViewModel workspace =
                this.Workspaces.FirstOrDefault(vm => vm is AllUsersViewModel)
                as AllUsersViewModel;

            if (workspace == null)
            {
                workspace = new AllUsersViewModel(_UserRepository);
                workspace.MsgViewModelEvent += new EventHandler<UserMsgViewEventArgs>(OnMsgViewAddToWorkspaces);
                this.Workspaces.Add(workspace);
            }

            this.SetActiveWorkspace(workspace);
        }

        void NetSet()
        {
            NetSetViewModel workspace =
                this.Workspaces.FirstOrDefault(vm => vm is NetSetViewModel)
                as NetSetViewModel;

            if (workspace == null)
            {
                if (_UserRepository.GetIocpParam() == null)
                {
                    IocpParam mIocpParam = IocpParam.CreateIocpParam();
                    workspace = new NetSetViewModel(_UserRepository.GetIocpParam(), _UserRepository);
                }
                else
                {
                    workspace = new NetSetViewModel(_UserRepository.GetIocpParam(), _UserRepository);
                }
                this.Workspaces.Add(workspace);
            }
            this.SetActiveWorkspace(workspace);
        }

        void SetActiveWorkspace(WorkspaceViewModel workspace)
        {
            Debug.Assert(this.Workspaces.Contains(workspace));

            ICollectionView collectionView = CollectionViewSource.GetDefaultView(this.Workspaces);
            if (collectionView != null)
                collectionView.MoveCurrentTo(workspace);
        }

        #endregion // Private Helpers

        #region Public Method

        void CloseViewEvent(object sender,EventArgs e)
        {
            OnWorkspaceRequestClose(sender, null);
        }

        #endregion  //Public Method

        #region  Base Class Overrides
        protected override void OnDispose()
        {
        }

        #endregion // Base Class Overrides

        #region Event Handling Methods
        void OnMsgViewAddToWorkspaces(object sender, UserMsgViewEventArgs e)
        {
            User _user=sender as User;
            MsgViewModel workspace = new MsgViewModel(e._User,e._BindType);
            this.Workspaces.Add(workspace);
            this.SetActiveWorkspace(workspace);
        }

        #endregion // Event Handling Methods

    }
}