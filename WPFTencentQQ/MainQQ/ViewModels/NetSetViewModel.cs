using MainQQ.DataAccess;
using MainQQ.LibInterface;
using MainQQ.Models;
using System;
using System.ComponentModel;
using System.Windows.Input;

namespace MainQQ.ViewModels
{
    class NetSetViewModel : WorkspaceViewModel, IDataErrorInfo
    {
        #region Fields

        readonly IocpParam _IocpParam;
        readonly UserRepository _UserRepository;
        RelayCommand _saveCommand;
        #endregion // Fields

        #region Constructor

        public NetSetViewModel(IocpParam IocpParam, UserRepository UserRepository)
        {
            if (IocpParam == null)
                throw new ArgumentNullException("IocpParam");

            if (UserRepository == null)
                throw new ArgumentNullException("UserRepository");

            _IocpParam = IocpParam;
            _UserRepository = UserRepository;
        }

        #endregion // Constructor

        #region NetSetViewModel Properties
        public uint iMaxNumberOfConnections
        {
            get { return _IocpParam.iMaxNumberOfConnections; }
            set
            {
                if (value == _IocpParam.iMaxNumberOfConnections)
                    return;

                _IocpParam.iMaxNumberOfConnections = value;

                base.OnPropertyChanged("iMaxNumberOfConnections");
            }
        }

        public uint iMaxNrOfFreeBuff
        {
            get { return _IocpParam.iMaxNrOfFreeBuff; }
            set
            {
                if (value == _IocpParam.iMaxNrOfFreeBuff)
                    return;

                _IocpParam.iMaxNrOfFreeBuff = value;

                base.OnPropertyChanged("iMaxNrOfFreeBuff");
            }
        }

        public uint iMaxNrOfFreeContext
        {
            get { return _IocpParam.iMaxNrOfFreeContext; }
            set
            {
                if (value == _IocpParam.iMaxNrOfFreeContext)
                    return;

                _IocpParam.iMaxNrOfFreeContext = value;

                base.OnPropertyChanged("iMaxNrOfFreeContext");
            }
        }

        public uint iNrOfIOWorkers
        {
            get { return _IocpParam.iNrOfIOWorkers; }
            set
            {
                if (value == _IocpParam.iNrOfIOWorkers)
                    return;

                _IocpParam.iNrOfIOWorkers = value;

                base.OnPropertyChanged("iNrOfIOWorkers");
            }
        }

        public uint iNrOfLogicalWorkers
        {
            get { return _IocpParam.iNrOfLogicalWorkers; }
            set
            {
                if (value == _IocpParam.iNrOfLogicalWorkers)
                    return;

                _IocpParam.iNrOfLogicalWorkers = value;

                base.OnPropertyChanged("iNrOfLogicalWorkers");
            }
        }

        public int iPortNr
        {
            get { return _IocpParam.iPortNr; }
            set
            {
                if (value == _IocpParam.iPortNr)
                    return;

                _IocpParam.iPortNr = value;

                base.OnPropertyChanged("iPortNr");
            }
        }
        public bool bReadInOrder
        {
            get { return _IocpParam.bReadInOrder; }
            set
            {
                if (value == _IocpParam.bReadInOrder)
                    return;

                _IocpParam.bReadInOrder = value;

                base.OnPropertyChanged("bReadInOrder");
            }
        }

        public bool bSendInOrder
        {
            get { return _IocpParam.bSendInOrder; }
            set
            {
                if (value == _IocpParam.bSendInOrder)
                    return;

                _IocpParam.bSendInOrder = value;

                base.OnPropertyChanged("bSendInOrder");
            }
        }

        public uint iNrOfPendlingReads
        {
            get { return _IocpParam.iNrOfPendlingReads; }
            set
            {
                if (value == _IocpParam.iNrOfPendlingReads)
                    return;

                _IocpParam.iNrOfPendlingReads = value;

                base.OnPropertyChanged("iNrOfPendlingReads");
            }
        }

        public bool bEnableSet 
        {
            get { return _IocpParam.bEnableSet; }
            set
            {
                if (value == _IocpParam.bEnableSet)
                    return;

                _IocpParam.bEnableSet = value;

                base.OnPropertyChanged("bEnableSet");
            }
        }
        #endregion // User Properties

        #region Presentation Properties

        public override string DisplayName
        {
            get
            {
                return String.Format("{0}", "IocpParam");
            }
        }

        /// <summary>
        /// Returns a command that saves the User.
        /// </summary>
        public ICommand SaveCommand
        {
            get
            {
                if (_saveCommand == null)
                {
                    _saveCommand = new RelayCommand(
                        param => this.Save(),
                        param => this.CanSave
                        );
                }
                return _saveCommand;
            }
        }

        #endregion // Presentation Properties

        #region Public Methods

        /// <summary>
        /// Saves the IocpParam to the repository.  This method is invoked by the SaveCommand.
        /// </summary>
        public void Save()
        {
            bEnableSet = false;
            _UserRepository.SetIocpParam(_IocpParam);
            MyLibInterface.StartTheSystem(
                _UserRepository.GetIocpParam().iPortNr,
                _UserRepository.GetIocpParam().iMaxNumberOfConnections,
                _UserRepository.GetIocpParam().iNrOfIOWorkers,
                _UserRepository.GetIocpParam().iNrOfLogicalWorkers,
                _UserRepository.GetIocpParam().iMaxNrOfFreeBuff,
                _UserRepository.GetIocpParam().iMaxNrOfFreeContext,
                _UserRepository.GetIocpParam().bSendInOrder,
                _UserRepository.GetIocpParam().bReadInOrder,
                _UserRepository.GetIocpParam().iNrOfPendlingReads);
        }

        #endregion // Public Methods

        #region Private Helpers


        /// <summary>
        /// Returns true if the User is valid and can be saved.
        /// </summary>
        bool CanSave
        {
            get { return _IocpParam.IsValid; }
        }

        #endregion // Private Helpers

        #region IDataErrorInfo Members

        string IDataErrorInfo.Error
        {
            get { return (_IocpParam as IDataErrorInfo).Error; }
        }

        string IDataErrorInfo.this[string propertyName]
        {
            get
            {
                string error = null;
                error = (_IocpParam as IDataErrorInfo)[propertyName];

                // Dirty the commands registered with CommandManager,
                // such as our Save command, so that they are queried
                // to see if they can execute now.
                CommandManager.InvalidateRequerySuggested();

                return error;
            }
        }

        #endregion // IDataErrorInfo Members
    }
}
