// ----------------------------------------------------------------------------
// <auto-generated>
// This is autogenerated code by CppSharp.
// Do not edit this file or all your changes will be lost after re-generation.
// </auto-generated>
// ----------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;
using __CallingConvention = global::System.Runtime.InteropServices.CallingConvention;
using __IntPtr = global::System.IntPtr;

#pragma warning disable CS0109 // Member does not hide an inherited member; new keyword is not required

namespace NebulaEngine
{
    namespace Platforms
    {
        [SuppressUnmanagedCodeSecurity, UnmanagedFunctionPointer(__CallingConvention.Cdecl)]
        public unsafe delegate long WindowProc(global::System.IntPtr __0, uint __1, ulong __2, long __3);

        [SuppressUnmanagedCodeSecurity, UnmanagedFunctionPointer(__CallingConvention.Cdecl)]
        public unsafe delegate void WindowExitResize(global::System.IntPtr __0, uint __1, uint __2);

        public unsafe partial class WindowInitInfo : IDisposable
        {
            [StructLayout(LayoutKind.Sequential, Size = 48)]
            public partial struct __Internal
            {
                internal __IntPtr callback;
                internal __IntPtr resizeCallback;
                internal global::System.IntPtr parent;
                internal __IntPtr caption;
                internal int left;
                internal int top;
                internal int width;
                internal int height;

                [SuppressUnmanagedCodeSecurity, DllImport("Core.Platform.dll", EntryPoint = "??0WindowInitInfo@Platforms@NebulaEngine@@QEAA@XZ", CallingConvention = __CallingConvention.Cdecl)]
                internal static extern __IntPtr ctor(__IntPtr __instance);

                [SuppressUnmanagedCodeSecurity, DllImport("Core.Platform.dll", EntryPoint = "??0WindowInitInfo@Platforms@NebulaEngine@@QEAA@AEBU012@@Z", CallingConvention = __CallingConvention.Cdecl)]
                internal static extern __IntPtr cctor(__IntPtr __instance, __IntPtr _0);
            }

            public __IntPtr __Instance { get; protected set; }

            internal static readonly new global::System.Collections.Concurrent.ConcurrentDictionary<IntPtr, global::NebulaEngine.Platforms.WindowInitInfo> NativeToManagedMap =
                new global::System.Collections.Concurrent.ConcurrentDictionary<IntPtr, global::NebulaEngine.Platforms.WindowInitInfo>();

            internal static void __RecordNativeToManagedMapping(IntPtr native, global::NebulaEngine.Platforms.WindowInitInfo managed)
            {
                NativeToManagedMap[native] = managed;
            }

            internal static bool __TryGetNativeToManagedMapping(IntPtr native, out global::NebulaEngine.Platforms.WindowInitInfo managed)
            {
    
                return NativeToManagedMap.TryGetValue(native, out managed);
            }

            private bool __caption_OwnsNativeMemory = false;
            protected bool __ownsNativeInstance;

            internal static WindowInitInfo __CreateInstance(__IntPtr native, bool skipVTables = false)
            {
                if (native == __IntPtr.Zero)
                    return null;
                return new WindowInitInfo(native.ToPointer(), skipVTables);
            }

            internal static WindowInitInfo __GetOrCreateInstance(__IntPtr native, bool saveInstance = false, bool skipVTables = false)
            {
                if (native == __IntPtr.Zero)
                    return null;
                if (__TryGetNativeToManagedMapping(native, out var managed))
                    return (WindowInitInfo)managed;
                var result = __CreateInstance(native, skipVTables);
                if (saveInstance)
                    __RecordNativeToManagedMapping(native, result);
                return result;
            }

            internal static WindowInitInfo __CreateInstance(__Internal native, bool skipVTables = false)
            {
                return new WindowInitInfo(native, skipVTables);
            }

            private static void* __CopyValue(__Internal native)
            {
                var ret = Marshal.AllocHGlobal(sizeof(__Internal));
                *(__Internal*) ret = native;
                return ret.ToPointer();
            }

            private WindowInitInfo(__Internal native, bool skipVTables = false)
                : this(__CopyValue(native), skipVTables)
            {
                __ownsNativeInstance = true;
                __RecordNativeToManagedMapping(__Instance, this);
            }

            protected WindowInitInfo(void* native, bool skipVTables = false)
            {
                if (native == null)
                    return;
                __Instance = new __IntPtr(native);
            }

            public WindowInitInfo()
            {
                __Instance = Marshal.AllocHGlobal(sizeof(global::NebulaEngine.Platforms.WindowInitInfo.__Internal));
                __ownsNativeInstance = true;
                __RecordNativeToManagedMapping(__Instance, this);
                __Internal.ctor(__Instance);
            }

            public WindowInitInfo(global::NebulaEngine.Platforms.WindowInitInfo _0)
            {
                __Instance = Marshal.AllocHGlobal(sizeof(global::NebulaEngine.Platforms.WindowInitInfo.__Internal));
                __ownsNativeInstance = true;
                __RecordNativeToManagedMapping(__Instance, this);
                *((global::NebulaEngine.Platforms.WindowInitInfo.__Internal*) __Instance) = *((global::NebulaEngine.Platforms.WindowInitInfo.__Internal*) _0.__Instance);
                if (_0.__caption_OwnsNativeMemory)
                    this.Caption = _0.Caption;
            }

            public void Dispose()
            {
                Dispose(disposing: true, callNativeDtor : __ownsNativeInstance );
            }

            partial void DisposePartial(bool disposing);

            internal protected virtual void Dispose(bool disposing, bool callNativeDtor )
            {
                if (__Instance == IntPtr.Zero)
                    return;
                NativeToManagedMap.TryRemove(__Instance, out _);
                DisposePartial(disposing);
                if (__caption_OwnsNativeMemory)
                    Marshal.FreeHGlobal(((__Internal*)__Instance)->caption);
                if (__ownsNativeInstance)
                    Marshal.FreeHGlobal(__Instance);
                __Instance = IntPtr.Zero;
            }

            public global::NebulaEngine.Platforms.WindowProc Callback
            {
                get
                {
                    var __ptr0 = ((__Internal*)__Instance)->callback;
                    return __ptr0 == IntPtr.Zero? null : (global::NebulaEngine.Platforms.WindowProc) Marshal.GetDelegateForFunctionPointer(__ptr0, typeof(global::NebulaEngine.Platforms.WindowProc));
                }

                set
                {
                    ((__Internal*)__Instance)->callback = value == null ? global::System.IntPtr.Zero : Marshal.GetFunctionPointerForDelegate(value);
                }
            }

            public global::NebulaEngine.Platforms.WindowExitResize ResizeCallback
            {
                get
                {
                    var __ptr0 = ((__Internal*)__Instance)->resizeCallback;
                    return __ptr0 == IntPtr.Zero? null : (global::NebulaEngine.Platforms.WindowExitResize) Marshal.GetDelegateForFunctionPointer(__ptr0, typeof(global::NebulaEngine.Platforms.WindowExitResize));
                }

                set
                {
                    ((__Internal*)__Instance)->resizeCallback = value == null ? global::System.IntPtr.Zero : Marshal.GetFunctionPointerForDelegate(value);
                }
            }

            public global::System.IntPtr Parent
            {
                get
                {
                    return ((__Internal*)__Instance)->parent;
                }

                set
                {
                    ((__Internal*)__Instance)->parent = value;
                }
            }

            public string Caption
            {
                get
                {
                    return CppSharp.Runtime.MarshalUtil.GetString(global::System.Text.Encoding.Unicode, ((__Internal*)__Instance)->caption);
                }

                set
                {
                    if (__caption_OwnsNativeMemory)
                        Marshal.FreeHGlobal(((__Internal*)__Instance)->caption);
                    __caption_OwnsNativeMemory = true;
                    if (value == null)
                    {
                        ((__Internal*)__Instance)->caption = global::System.IntPtr.Zero;
                        return;
                    }
                    var __bytePtr0 = Marshal.StringToHGlobalUni(value);
                    ((__Internal*)__Instance)->caption = (__IntPtr) __bytePtr0;
                }
            }

            public int Left
            {
                get
                {
                    return ((__Internal*)__Instance)->left;
                }

                set
                {
                    ((__Internal*)__Instance)->left = value;
                }
            }

            public int Top
            {
                get
                {
                    return ((__Internal*)__Instance)->top;
                }

                set
                {
                    ((__Internal*)__Instance)->top = value;
                }
            }

            public int Width
            {
                get
                {
                    return ((__Internal*)__Instance)->width;
                }

                set
                {
                    ((__Internal*)__Instance)->width = value;
                }
            }

            public int Height
            {
                get
                {
                    return ((__Internal*)__Instance)->height;
                }

                set
                {
                    ((__Internal*)__Instance)->height = value;
                }
            }
        }
    }
}