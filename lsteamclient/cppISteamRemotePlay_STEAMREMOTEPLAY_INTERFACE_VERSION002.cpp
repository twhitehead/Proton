#include "steam_defs.h"
#pragma push_macro("__cdecl")
#undef __cdecl
#define __cdecl
#include "steamworks_sdk_158/steam_api.h"
#include "steamworks_sdk_158/steamnetworkingtypes.h"
#pragma pop_macro("__cdecl")
#include "steamclient_private.h"
#ifdef __cplusplus
extern "C" {
#endif
#define SDKVER_158
#include "struct_converters.h"
#include "cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002.h"
uint32 cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_GetSessionCount(void *linux_side)
{
    return ((ISteamRemotePlay*)linux_side)->GetSessionCount();
}

RemotePlaySessionID_t cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_GetSessionID(void *linux_side, int iSessionIndex)
{
    return ((ISteamRemotePlay*)linux_side)->GetSessionID((int)iSessionIndex);
}

CSteamID cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_GetSessionSteamID(void *linux_side, RemotePlaySessionID_t unSessionID)
{
    return ((ISteamRemotePlay*)linux_side)->GetSessionSteamID((RemotePlaySessionID_t)unSessionID);
}

const char * cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_GetSessionClientName(void *linux_side, RemotePlaySessionID_t unSessionID)
{
    return ((ISteamRemotePlay*)linux_side)->GetSessionClientName((RemotePlaySessionID_t)unSessionID);
}

ESteamDeviceFormFactor cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_GetSessionClientFormFactor(void *linux_side, RemotePlaySessionID_t unSessionID)
{
    return ((ISteamRemotePlay*)linux_side)->GetSessionClientFormFactor((RemotePlaySessionID_t)unSessionID);
}

bool cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_BGetSessionClientResolution(void *linux_side, RemotePlaySessionID_t unSessionID, int * pnResolutionX, int * pnResolutionY)
{
    return ((ISteamRemotePlay*)linux_side)->BGetSessionClientResolution((RemotePlaySessionID_t)unSessionID, (int *)pnResolutionX, (int *)pnResolutionY);
}

bool cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_BStartRemotePlayTogether(void *linux_side, bool bShowOverlay)
{
    return ((ISteamRemotePlay*)linux_side)->BStartRemotePlayTogether((bool)bShowOverlay);
}

bool cppISteamRemotePlay_STEAMREMOTEPLAY_INTERFACE_VERSION002_BSendRemotePlayTogetherInvite(void *linux_side, CSteamID steamIDFriend)
{
    return ((ISteamRemotePlay*)linux_side)->BSendRemotePlayTogetherInvite((CSteamID)steamIDFriend);
}

#ifdef __cplusplus
}
#endif