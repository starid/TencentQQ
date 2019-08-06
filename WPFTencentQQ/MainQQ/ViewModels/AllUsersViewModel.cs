using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using MainQQ.DataAccess;
using MainQQ.Properties;

namespace MainQQ.ViewModels
{
    /// <summary>
    /// Represents a container of UserViewModel objects
    /// that has support for staying synchronized with the
    /// UserRepository.  This class also provides information
    /// related to multiple selected Users.
    /// </summary>
    public class AllUsersViewModel : WorkspaceViewModel
    {
        #region Fields

        readonly UserRepository _UserRepository;

        public event EventHandler<UserMsgViewEventArgs> MsgViewModelEvent;

        #endregion // Fields

        #region Constructor

        public AllUsersViewModel(UserRepository UserRepository)
        {
            if (UserRepository == null)
                throw new ArgumentNullException("UserRepository");

            base.DisplayName = Resources.AllUsersViewModel_DisplayName;            

            _UserRepository = UserRepository;

            // Subscribe for notifications of when a new User is saved.
            _UserRepository.UserAdded += this.OnUserAddedToRepository;
            _UserRepository.UserDel += this.OnUserDelToRepository;

            // Populate the AllUsers collection with UserViewModels.
            this.CreateAllUsers();
        }

        void CreateAllUsers()
        {
            List<UserViewModel> all =
                (from cust in _UserRepository.GetUsers()
                 select new UserViewModel(cust, _UserRepository)).ToList();

            foreach (UserViewModel cvm in all)
            {
                cvm.PropertyChanged += this.OnUserViewModelPropertyChanged;
                cvm.MsgViewModelEvent += new EventHandler<UserMsgViewEventArgs>(OnMsgViewAddToWorkspaces);
            }
            this.AllUsers = new ObservableCollection<UserViewModel>(all);
            this.AllUsers.CollectionChanged += this.OnCollectionChanged;
        }

        #endregion // Constructor

        #region Public Interface

        /// <summary>
        /// Returns a collection of all the UserViewModel objects.
        /// </summary>
        public ObservableCollection<UserViewModel> AllUsers { get; private set; }


        /// <summary>
        /// Returns the total sales sum of all selected customers.
        /// </summary>
        public UInt32 TotalUsers
        {
            get
            {
                return (UInt32)this.AllUsers.Sum(
                    custVM => custVM.IsSelected ? 1:0);
            }
        }


        #endregion // Public Interface

        #region Private Helpers

 
        #endregion

        #region  Base Class Overrides

        protected override void OnDispose()
        {
            foreach (UserViewModel custVM in this.AllUsers)
                custVM.Dispose();

            this.AllUsers.Clear();
            this.AllUsers.CollectionChanged -= this.OnCollectionChanged;

            _UserRepository.UserAdded -= this.OnUserAddedToRepository;
            _UserRepository.UserDel -= this.OnUserDelToRepository;

            if (MsgViewModelEvent != null)
            {
                Delegate[] dels = MsgViewModelEvent.GetInvocationList();
                foreach (Delegate d in dels)
                {
                    object delObj = d.GetType().GetProperty("Method").GetValue(d, null);
                    string funcName = (string)delObj.GetType().GetProperty("Name").GetValue(delObj, null);
                    MsgViewModelEvent -= d as EventHandler<UserMsgViewEventArgs>;
                }
            }
        }

        #endregion // Base Class Overrides

        #region Event Handling Methods

        void OnCollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.NewItems != null && e.NewItems.Count != 0)
                foreach (UserViewModel custVM in e.NewItems)
                    custVM.PropertyChanged += this.OnUserViewModelPropertyChanged;

            if (e.OldItems != null && e.OldItems.Count != 0)
                foreach (UserViewModel custVM in e.OldItems)
                    custVM.PropertyChanged -= this.OnUserViewModelPropertyChanged;
        }

        void OnUserViewModelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            string IsSelected = "IsSelected";

            // Make sure that the property name we're referencing is valid.
            // This is a debugging technique, and does not execute in a Release build.
            (sender as UserViewModel).VerifyPropertyName(IsSelected);

            // When a User is selected or unselected, we must let the
            // world know that the TotalSelectedSales property has changed,
            // so that it will be queried again for a new value.
            if (e.PropertyName == IsSelected)
                this.OnPropertyChanged("TotalUsers");
        }

        void OnUserAddedToRepository(object sender, UserAddedEventArgs e)
        {
            var viewModel = new UserViewModel(e.NewUser, _UserRepository);
            viewModel.MsgViewModelEvent += new EventHandler<UserMsgViewEventArgs>(OnMsgViewAddToWorkspaces);
            this.AllUsers.Add(viewModel);
        }

        void OnUserDelToRepository(object sender,UserAddedEventArgs e)
        {
            foreach (UserViewModel mUserViewModel in AllUsers)
            {
                if(mUserViewModel.GetUser == e.NewUser)
                {
                    AllUsers.Remove(mUserViewModel);
                    break;
                }
            }
        }

        void OnMsgViewAddToWorkspaces(object sender, UserMsgViewEventArgs e)
        {
            MsgViewModelEvent(sender, e);
        }
        #endregion // Event Handling Methods
    }
}