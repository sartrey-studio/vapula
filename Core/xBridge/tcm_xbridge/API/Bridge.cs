﻿using System;
using System.Runtime.InteropServices;

namespace TCM.API
{
    internal class Bridge
    {
        /// <summary>
        /// 转换P/Invoke返回的字符串
        /// </summary>
        public static string MarshalString(IntPtr ptr, bool unicode = true)
        {
            string ret = null;
            if (unicode) ret = Marshal.PtrToStringUni(ptr);
            else ret = Marshal.PtrToStringAnsi(ptr);
            return ret;
        }

        #region Base
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmDeleteObject",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void DeleteObject(IntPtr obj);
        #endregion

        #region Driver
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetDriverCount",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetDriverCount();

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmLinkDriver",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool LinkDriver(string id);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmKickDriver",
            CharSet = CharSet.Ansi,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool KickDriver(string id);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmKickAllDrivers",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void KickAllDrivers();
        #endregion

        #region Library
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetLibraryCount",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetLibraryCount();

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmLoadLibraryW",
            CharSet = CharSet.Unicode,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr LoadLibrary(string path);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetLibraryRuntime",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetLibraryRuntime(IntPtr lib);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetLibraryId",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetLibraryId(IntPtr lib);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmMountLibrary",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool MountLibrary(IntPtr lib);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmUnmountLibrary",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void UnmountLibrary(IntPtr lib);
        #endregion

        #region Executor
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmCreateExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateExecutor(IntPtr lib, int fid);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetFunctionId",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetFunctionId(IntPtr lib);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmStartExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool StartExecutor(IntPtr exec);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmStopExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void StopExecutor(IntPtr exec, uint wait);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmPauseExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void PauseExecutor(IntPtr exec, uint wait);
        
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmResumeExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void ResumeExecutor(IntPtr exec);
        
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmRestartExecutor",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void RestartExecutor(IntPtr exec, uint wait);
        #endregion

        #region Token
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetContextToken",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetContextToken(IntPtr exec);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmStampContext",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr StampContext(IntPtr ctx);
        #endregion

        #region Context
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetContext",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetContext(IntPtr exec);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetCtrlCode",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetCtrlCode(IntPtr ctx);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmSetCtrlCode",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetCtrlCode(IntPtr ctx, int ctrl_code, IntPtr token);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmReplyCtrlCode",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReplyCtrlCode(IntPtr ctx);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetProgress",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern float GetProgress(IntPtr ctx);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmSetProgress",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetProgress(IntPtr ctx, float prog);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetState",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetState(IntPtr ctx);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmSetState",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetState(IntPtr ctx, int state, IntPtr token);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetReturnCode",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern int GetReturnCode(IntPtr ctx);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmSetReturnCode",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetReturnCode(IntPtr ctx, int return_code, IntPtr token);
        #endregion

        #region Envelope
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetEnvelope",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr GetEnvelope(IntPtr exec);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmParseEnvelopeW",
            CharSet = CharSet.Unicode,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ParseEnvelope(string xml);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmWriteEnvelopeW",
            CharSet = CharSet.Unicode,
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void WriteEnvelope(IntPtr env, int id, string value);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmReadEnvelopeW",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr ReadEnvelope(IntPtr env, int id);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmDeliverEnvelope",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void DeliverEnvelope(IntPtr src, IntPtr dst, int from, int to);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmCastDeliverEnvelope",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void CastDeliverEnvelope(IntPtr src, IntPtr dst, int from, int to);
        #endregion

        #region Pipe
        [DllImport("tcm_bridge.dll", EntryPoint = "tcmCreatePipe",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreatePipe();

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmListenPipe",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr PipeListen(IntPtr pipe);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmGetPipeFlag",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern bool GetPipeFlag(IntPtr pipe, int action);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmSetPipeFlag",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetPipeFlag(IntPtr pipe, int action, bool value);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmWritePipe",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void WritePipe(IntPtr pipe, IntPtr value, uint size);

        [DllImport("tcm_bridge.dll", EntryPoint = "tcmReadPipe",
            CallingConvention = CallingConvention.Cdecl)]
        public static extern void ReadPipe(IntPtr pipe, IntPtr data);
        #endregion
    }
}