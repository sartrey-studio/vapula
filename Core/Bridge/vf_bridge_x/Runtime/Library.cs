﻿using System;

namespace Vapula.Runtime
{
    public class Library : Sartrey.DisposableObject
    {
        protected IntPtr _Handle 
            = IntPtr.Zero;

        public Library(IntPtr handle)
        {
            _Handle = handle;
        }

        /// <summary>
        /// load library from file
        /// </summary>
        public static Library Load(string path)
        {
            IntPtr handle = Bridge.LoadLibrary(path);
            if (handle == IntPtr.Zero)
                return null;
            Library library = new Library(handle);
            return library;
        }

        /// <summary>
        /// get library id
        /// </summary>
        public string LibraryId
        {
            get 
            {
                string value = 
                    Base.ToStringAnsi(
                    Bridge.GetLibraryId(_Handle));
                return value;
            }
        }

        /// <summary>
        /// get runtime id
        /// </summary>
        public string RuntimeId
        {
            get 
            { 
                string value = 
                    Base.ToStringAnsi(
                    Bridge.GetRuntime(_Handle));
                return value;
            }
        }

        public void LinkHub() 
        {
            Bridge.LinkLibrary(_Handle);
        }

        public void KickHub() 
        {
            Bridge.KickLibrary(_Handle);
        }

		/// <summary>
        /// create task for method
		/// </summary>
        public Task CreateTask(string id)
        {
            IntPtr ptr = Bridge.CreateTask(_Handle, id);
            Task inv = new Task(ptr);
            return inv;
        }

        /// <summary>
        /// get method process symbol
        /// </summary>
        public string GetProcessSym(string id)
        {
            string sym = 
                Base.ToStringAnsi(
                Bridge.GetProcessSym(_Handle, id));
            return sym;
        }

        /// <summary>
        /// get method rollback symbol
        /// </summary>
        public string GetRollbackSym(string id)
        {
            string sym =
                Base.ToStringAnsi(
                Bridge.GetRollbackSym(_Handle, id));
            return sym;
        }

		/// <summary>
		/// mount library
		/// </summary>
        public bool Mount()
        {
            return Bridge.MountLibrary(_Handle);
        }

		/// <summary>
        /// unmount library
		/// </summary>
        public void Unmount()
        {
            if (_Handle != IntPtr.Zero)
                Bridge.UnmountLibrary(_Handle);
        }

        protected override void DisposeManaged()
        {
        }

        protected override void DisposeNative()
        {
            Unmount();
            if (_Handle != IntPtr.Zero)
            {
                Bridge.DeleteData(_Handle);
                _Handle = IntPtr.Zero;
            }
        }
    }
}
