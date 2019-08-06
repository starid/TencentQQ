using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace MainQQ.Models
{
    public class IocpParam : IDataErrorInfo
    {
        #region Creation

        public static IocpParam CreateIocpParam()
        {
            return new IocpParam();
        }

        protected IocpParam()
        {
            iMaxNumberOfConnections = 1201;
            iMaxNrOfFreeBuff = 0;
            iMaxNrOfFreeContext = 0;
            iNrOfIOWorkers = 1;
            iNrOfLogicalWorkers = 0;
            iPortNr = -1;
            bReadInOrder = true;
            bSendInOrder = true;
            iNrOfPendlingReads = 4;
            bEnableSet = true;
            bStart = false;
        }

        public IocpParam( IocpParam IocpParam)
        {
            iMaxNumberOfConnections = IocpParam.iMaxNumberOfConnections;
            iMaxNrOfFreeBuff = IocpParam.iMaxNrOfFreeBuff;
            iMaxNrOfFreeContext = IocpParam.iMaxNrOfFreeContext;
            iNrOfIOWorkers = IocpParam.iNrOfIOWorkers;
            iNrOfLogicalWorkers = IocpParam.iNrOfIOWorkers;
            iPortNr = IocpParam.iPortNr;
            bReadInOrder = IocpParam.bReadInOrder;
            bSendInOrder = IocpParam.bSendInOrder;
            iNrOfPendlingReads = IocpParam.iNrOfPendlingReads;
            bEnableSet = IocpParam.bEnableSet;
        }

        #endregion // Creation


        #region State Properties

        public uint iMaxNumberOfConnections { get; set; }

        public uint iMaxNrOfFreeBuff { get; set; }

        public uint iMaxNrOfFreeContext { get; set; }

        public uint iNrOfIOWorkers { get; set; }

        public uint iNrOfLogicalWorkers { get; set; }

        public int iPortNr { get; set; }

        public bool bReadInOrder { get; set; }

        public bool bSendInOrder { get; set; }

        public uint iNrOfPendlingReads { get; set; }

        public bool bEnableSet { get; set; }

        public bool bStart { get; set; }

        #endregion

        #region IDataErrorInfo Members

        string IDataErrorInfo.Error { get { return null; } }

        string IDataErrorInfo.this[string propertyName]
        {
            get { return this.GetValidationError(propertyName); }
        }

        #endregion // IDataErrorInfo Members

        #region Validation

        /// <summary>
        /// Returns true if this object has no validation errors.
        /// </summary>
        public bool IsValid
        {
            get
            {
                foreach (string property in ValidatedProperties)
                    if (GetValidationError(property) != null)
                        return false;

                return true;
            }
        }

        static readonly string[] ValidatedProperties = 
        { 
            "iMaxNumberOfConnections",
            "iMaxNrOfFreeBuff",
            "iMaxNrOfFreeContext",
            "iNrOfIOWorkers",
            "iNrOfLogicalWorkers",
            "iPortNr",
            "bReadInOrder",
            "bSendInOrder",
            "iNrOfPendlingReads"
        };

        string GetValidationError(string propertyName)
        {
            if (Array.IndexOf(ValidatedProperties, propertyName) < 0)
                return null;

            string error = null;

            switch (propertyName)
            {
                case "iMaxNumberOfConnections":
                    error = Validate(iMaxNumberOfConnections);
                    break;
                case "iMaxNrOfFreeBuff":
                    error = Validate(iMaxNrOfFreeBuff);
                    break;
                case "iMaxNrOfFreeContext":
                    error = Validate(iMaxNrOfFreeContext);
                    break;
                case "iNrOfIOWorkers":
                    error = Validate(iNrOfIOWorkers);
                    break;
                case "iNrOfLogicalWorkers":
                    error = Validate(iNrOfLogicalWorkers);
                    break;
                case "iPortNr":
                    error = Validate((uint)(iPortNr));
                    break;
                case "bReadInOrder":
                    error = null;
                    break;
                case "bSendInOrder":
                    error = null;
                    break;
                case "iNrOfPendlingReads":
                    error = Validate(iNrOfPendlingReads);
                    break;
                default:
                    Debug.Fail("Unexpected property being validated on Customer: " + propertyName);
                    break;
            }

            return error;
        }

        string Validate(uint mParam)
        {
            if (IsStringMissing(mParam.ToString()))
            {
                return MainQQ.Properties.Resources.Error_Default;
            }
            return null;
        }

        static bool IsStringMissing(string value)
        {
            return
                String.IsNullOrEmpty(value) ||
                value.Trim() == String.Empty;
        }

        #endregion // Validation
    }
}
