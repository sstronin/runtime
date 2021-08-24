// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

#include "../../AnyOS/entrypoints.h"

// Include System.Native headers
#include "pal_autoreleasepool.h"
#include "pal_console.h"
#include "pal_datetime.h"
#include "pal_errno.h"
#include "pal_interfaceaddresses.h"
#include "pal_io.h"
#include "pal_iossupportversion.h"
#include "pal_log.h"
#include "pal_memory.h"
#include "pal_mount.h"
#include "pal_networkchange.h"
#include "pal_networking.h"
#include "pal_networkstatistics.h"
#include "pal_process.h"
#include "pal_random.h"
#include "pal_runtimeextensions.h"
#include "pal_runtimeinformation.h"
#include "pal_searchpath.h"
#include "pal_signal.h"
#include "pal_string.h"
#include "pal_sysctl.h"
#include "pal_tcpstate.h"
#include "pal_threading.h"
#include "pal_time.h"
#include "pal_uid.h"

static const Entry s_sysNative[] =
{
    DllImportEntry(SystemNative_FStat)
    DllImportEntry(SystemNative_GetWindowSize)
    DllImportEntry(SystemNative_IsATty)
    DllImportEntry(SystemNative_InitializeTerminalAndSignalHandling)
    DllImportEntry(SystemNative_SetKeypadXmit)
    DllImportEntry(SystemNative_GetControlCharacters)
    DllImportEntry(SystemNative_StdinReady)
    DllImportEntry(SystemNative_InitializeConsoleBeforeRead)
    DllImportEntry(SystemNative_UninitializeConsoleAfterRead)
    DllImportEntry(SystemNative_ConfigureTerminalForChildProcess)
    DllImportEntry(SystemNative_ReadStdin)
    DllImportEntry(SystemNative_GetSignalForBreak)
    DllImportEntry(SystemNative_SetSignalForBreak)
    DllImportEntry(SystemNative_GetSystemTimeAsTicks)
    DllImportEntry(SystemNative_ConvertErrorPlatformToPal)
    DllImportEntry(SystemNative_ConvertErrorPalToPlatform)
    DllImportEntry(SystemNative_StrErrorR)
    DllImportEntry(SystemNative_EnumerateInterfaceAddresses)
    DllImportEntry(SystemNative_GetNetworkInterfaces)
    DllImportEntry(SystemNative_EnumerateGatewayAddressesForInterface)
    DllImportEntry(SystemNative_Stat)
    DllImportEntry(SystemNative_LStat)
    DllImportEntry(SystemNative_Open)
    DllImportEntry(SystemNative_Close)
    DllImportEntry(SystemNative_Dup)
    DllImportEntry(SystemNative_Unlink)
    DllImportEntry(SystemNative_ShmOpen)
    DllImportEntry(SystemNative_ShmUnlink)
    DllImportEntry(SystemNative_GetReadDirRBufferSize)
    DllImportEntry(SystemNative_ReadDirR)
    DllImportEntry(SystemNative_OpenDir)
    DllImportEntry(SystemNative_CloseDir)
    DllImportEntry(SystemNative_Pipe)
    DllImportEntry(SystemNative_FcntlSetFD)
    DllImportEntry(SystemNative_FcntlGetFD)
    DllImportEntry(SystemNative_FcntlCanGetSetPipeSz)
    DllImportEntry(SystemNative_FcntlGetPipeSz)
    DllImportEntry(SystemNative_FcntlSetPipeSz)
    DllImportEntry(SystemNative_FcntlSetIsNonBlocking)
    DllImportEntry(SystemNative_FcntlGetIsNonBlocking)
    DllImportEntry(SystemNative_MkDir)
    DllImportEntry(SystemNative_ChMod)
    DllImportEntry(SystemNative_FChMod)
    DllImportEntry(SystemNative_FSync)
    DllImportEntry(SystemNative_FLock)
    DllImportEntry(SystemNative_ChDir)
    DllImportEntry(SystemNative_Access)
    DllImportEntry(SystemNative_LSeek)
    DllImportEntry(SystemNative_Link)
    DllImportEntry(SystemNative_SymLink)
    DllImportEntry(SystemNative_MksTemps)
    DllImportEntry(SystemNative_MMap)
    DllImportEntry(SystemNative_MUnmap)
    DllImportEntry(SystemNative_MAdvise)
    DllImportEntry(SystemNative_MSync)
    DllImportEntry(SystemNative_SysConf)
    DllImportEntry(SystemNative_FTruncate)
    DllImportEntry(SystemNative_Poll)
    DllImportEntry(SystemNative_PosixFAdvise)
    DllImportEntry(SystemNative_PosixFAllocate)
    DllImportEntry(SystemNative_Read)
    DllImportEntry(SystemNative_ReadLink)
    DllImportEntry(SystemNative_Rename)
    DllImportEntry(SystemNative_RmDir)
    DllImportEntry(SystemNative_Sync)
    DllImportEntry(SystemNative_Write)
    DllImportEntry(SystemNative_CopyFile)
    DllImportEntry(SystemNative_INotifyInit)
    DllImportEntry(SystemNative_INotifyAddWatch)
    DllImportEntry(SystemNative_INotifyRemoveWatch)
    DllImportEntry(SystemNative_RealPath)
    DllImportEntry(SystemNative_GetPeerID)
    DllImportEntry(SystemNative_GetFileSystemType)
    DllImportEntry(SystemNative_LockFileRegion)
    DllImportEntry(SystemNative_LChflags)
    DllImportEntry(SystemNative_LChflagsCanSetHiddenFlag)
    DllImportEntry(SystemNative_ReadProcessStatusInfo)
    DllImportEntry(SystemNative_Log)
    DllImportEntry(SystemNative_AlignedAlloc)
    DllImportEntry(SystemNative_AlignedFree)
    DllImportEntry(SystemNative_AlignedRealloc)
    DllImportEntry(SystemNative_Calloc)
    DllImportEntry(SystemNative_Free)
    DllImportEntry(SystemNative_GetUsableSize)
    DllImportEntry(SystemNative_Malloc)
    DllImportEntry(SystemNative_MemSet)
    DllImportEntry(SystemNative_Realloc)
    DllImportEntry(SystemNative_GetSpaceInfoForMountPoint)
    DllImportEntry(SystemNative_GetFormatInfoForMountPoint)
    DllImportEntry(SystemNative_GetAllMountPoints)
    DllImportEntry(SystemNative_ReadEvents)
    DllImportEntry(SystemNative_CreateNetworkChangeListenerSocket)
    DllImportEntry(SystemNative_CloseNetworkChangeListenerSocket)
    DllImportEntry(SystemNative_GetHostEntryForName)
    DllImportEntry(SystemNative_FreeHostEntry)
    DllImportEntry(SystemNative_GetNameInfo)
    DllImportEntry(SystemNative_GetDomainName)
    DllImportEntry(SystemNative_GetHostName)
    DllImportEntry(SystemNative_GetIPSocketAddressSizes)
    DllImportEntry(SystemNative_GetAddressFamily)
    DllImportEntry(SystemNative_SetAddressFamily)
    DllImportEntry(SystemNative_GetPort)
    DllImportEntry(SystemNative_SetPort)
    DllImportEntry(SystemNative_GetIPv4Address)
    DllImportEntry(SystemNative_SetIPv4Address)
    DllImportEntry(SystemNative_GetIPv6Address)
    DllImportEntry(SystemNative_SetIPv6Address)
    DllImportEntry(SystemNative_GetControlMessageBufferSize)
    DllImportEntry(SystemNative_TryGetIPPacketInformation)
    DllImportEntry(SystemNative_GetIPv4MulticastOption)
    DllImportEntry(SystemNative_SetIPv4MulticastOption)
    DllImportEntry(SystemNative_GetIPv6MulticastOption)
    DllImportEntry(SystemNative_SetIPv6MulticastOption)
    DllImportEntry(SystemNative_GetLingerOption)
    DllImportEntry(SystemNative_SetLingerOption)
    DllImportEntry(SystemNative_SetReceiveTimeout)
    DllImportEntry(SystemNative_SetSendTimeout)
    DllImportEntry(SystemNative_Receive)
    DllImportEntry(SystemNative_ReceiveMessage)
    DllImportEntry(SystemNative_Send)
    DllImportEntry(SystemNative_SendMessage)
    DllImportEntry(SystemNative_Accept)
    DllImportEntry(SystemNative_Bind)
    DllImportEntry(SystemNative_Connect)
    DllImportEntry(SystemNative_GetPeerName)
    DllImportEntry(SystemNative_GetSockName)
    DllImportEntry(SystemNative_Listen)
    DllImportEntry(SystemNative_Shutdown)
    DllImportEntry(SystemNative_GetSocketErrorOption)
    DllImportEntry(SystemNative_GetSockOpt)
    DllImportEntry(SystemNative_GetRawSockOpt)
    DllImportEntry(SystemNative_SetSockOpt)
    DllImportEntry(SystemNative_SetRawSockOpt)
    DllImportEntry(SystemNative_Socket)
    DllImportEntry(SystemNative_GetSocketType)
    DllImportEntry(SystemNative_GetAtOutOfBandMark)
    DllImportEntry(SystemNative_GetBytesAvailable)
    DllImportEntry(SystemNative_CreateSocketEventPort)
    DllImportEntry(SystemNative_CloseSocketEventPort)
    DllImportEntry(SystemNative_CreateSocketEventBuffer)
    DllImportEntry(SystemNative_FreeSocketEventBuffer)
    DllImportEntry(SystemNative_TryChangeSocketEventRegistration)
    DllImportEntry(SystemNative_WaitForSocketEvents)
    DllImportEntry(SystemNative_PlatformSupportsDualModeIPv4PacketInfo)
    DllImportEntry(SystemNative_GetPeerUserName)
    DllImportEntry(SystemNative_GetDomainSocketSizes)
    DllImportEntry(SystemNative_GetMaximumAddressSize)
    DllImportEntry(SystemNative_SendFile)
    DllImportEntry(SystemNative_Disconnect)
    DllImportEntry(SystemNative_InterfaceNameToIndex)
    DllImportEntry(SystemNative_GetTcpGlobalStatistics)
    DllImportEntry(SystemNative_GetIPv4GlobalStatistics)
    DllImportEntry(SystemNative_GetUdpGlobalStatistics)
    DllImportEntry(SystemNative_GetIcmpv4GlobalStatistics)
    DllImportEntry(SystemNative_GetIcmpv6GlobalStatistics)
    DllImportEntry(SystemNative_GetEstimatedTcpConnectionCount)
    DllImportEntry(SystemNative_GetActiveTcpConnectionInfos)
    DllImportEntry(SystemNative_GetEstimatedUdpListenerCount)
    DllImportEntry(SystemNative_GetActiveUdpListeners)
    DllImportEntry(SystemNative_GetNativeIPInterfaceStatistics)
    DllImportEntry(SystemNative_GetNumRoutes)
    DllImportEntry(SystemNative_ForkAndExecProcess)
    DllImportEntry(SystemNative_GetRLimit)
    DllImportEntry(SystemNative_SetRLimit)
    DllImportEntry(SystemNative_Kill)
    DllImportEntry(SystemNative_GetPid)
    DllImportEntry(SystemNative_GetSid)
    DllImportEntry(SystemNative_SysLog)
    DllImportEntry(SystemNative_WaitIdAnyExitedNoHangNoWait)
    DllImportEntry(SystemNative_WaitPidExitedNoHang)
    DllImportEntry(SystemNative_PathConf)
    DllImportEntry(SystemNative_GetPriority)
    DllImportEntry(SystemNative_SetPriority)
    DllImportEntry(SystemNative_GetCwd)
    DllImportEntry(SystemNative_SchedSetAffinity)
    DllImportEntry(SystemNative_SchedGetAffinity)
    DllImportEntry(SystemNative_GetProcessPath)
    DllImportEntry(SystemNative_GetNonCryptographicallySecureRandomBytes)
    DllImportEntry(SystemNative_GetCryptographicallySecureRandomBytes)
    DllImportEntry(SystemNative_GetNodeName)
    DllImportEntry(SystemNative_GetUnixName)
    DllImportEntry(SystemNative_GetUnixRelease)
    DllImportEntry(SystemNative_GetUnixVersion)
    DllImportEntry(SystemNative_GetOSArchitecture)
    DllImportEntry(SystemNative_GetProcessArchitecture)
    DllImportEntry(SystemNative_SearchPath)
    DllImportEntry(SystemNative_SearchPath_TempDirectory)
    DllImportEntry(SystemNative_RegisterForSigChld)
    DllImportEntry(SystemNative_SetDelayedSigChildConsoleConfigurationHandler)
    DllImportEntry(SystemNative_SetTerminalInvalidationHandler)
    DllImportEntry(SystemNative_InitializeTerminalAndSignalHandling)
    DllImportEntry(SystemNative_SNPrintF)
    DllImportEntry(SystemNative_Sysctl)
    DllImportEntry(SystemNative_MapTcpState)
    DllImportEntry(SystemNative_LowLevelMonitor_Destroy)
    DllImportEntry(SystemNative_LowLevelMonitor_Acquire)
    DllImportEntry(SystemNative_LowLevelMonitor_Release)
    DllImportEntry(SystemNative_LowLevelMonitor_Wait)
    DllImportEntry(SystemNative_LowLevelMonitor_TimedWait)
    DllImportEntry(SystemNative_LowLevelMonitor_Signal_Release)
    DllImportEntry(SystemNative_UTimensat)
    DllImportEntry(SystemNative_GetTimestamp)
    DllImportEntry(SystemNative_GetCpuUtilization)
    DllImportEntry(SystemNative_GetPwUidR)
    DllImportEntry(SystemNative_GetPwNamR)
    DllImportEntry(SystemNative_GetEUid)
    DllImportEntry(SystemNative_GetEGid)
    DllImportEntry(SystemNative_SetEUid)
    DllImportEntry(SystemNative_GetGroupList)
    DllImportEntry(SystemNative_GetUid)
    DllImportEntry(SystemNative_LowLevelMonitor_Create)
    DllImportEntry(SystemNative_CreateAutoreleasePool)
    DllImportEntry(SystemNative_DrainAutoreleasePool)
    DllImportEntry(SystemNative_iOSSupportVersion)
    DllImportEntry(SystemNative_GetErrNo)
    DllImportEntry(SystemNative_SetErrNo)
    DllImportEntry(SystemNative_PRead)
    DllImportEntry(SystemNative_PWrite)
    DllImportEntry(SystemNative_PReadV)
    DllImportEntry(SystemNative_PWriteV)
    DllImportEntry(SystemNative_EnablePosixSignalHandling)
    DllImportEntry(SystemNative_DisablePosixSignalHandling)
    DllImportEntry(SystemNative_HandleNonCanceledPosixSignal)
    DllImportEntry(SystemNative_SetPosixSignalHandler)
    DllImportEntry(SystemNative_GetPlatformSignalNumber)
    DllImportEntry(SystemNative_GetGroups)
};

EXTERN_C const void* SystemResolveDllImport(const char* name);

EXTERN_C const void* SystemResolveDllImport(const char* name)
{
    return ResolveDllImport(s_sysNative, lengthof(s_sysNative), name);
}
