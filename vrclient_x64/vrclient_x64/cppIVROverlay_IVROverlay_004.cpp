/* This file is auto-generated, do not edit. */
#include "unix_private.h"

NTSTATUS IVROverlay_IVROverlay_004_FindOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_FindOverlay_params *params = (struct IVROverlay_IVROverlay_004_FindOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->FindOverlay( params->pchOverlayKey, params->pOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_CreateOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_CreateOverlay_params *params = (struct IVROverlay_IVROverlay_004_CreateOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->CreateOverlay( params->pchOverlayKey, params->pchOverlayFriendlyName, params->pOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_DestroyOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_DestroyOverlay_params *params = (struct IVROverlay_IVROverlay_004_DestroyOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->DestroyOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetHighQualityOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_SetHighQualityOverlay_params *params = (struct IVROverlay_IVROverlay_004_SetHighQualityOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetHighQualityOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetHighQualityOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_GetHighQualityOverlay_params *params = (struct IVROverlay_IVROverlay_004_GetHighQualityOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint64_t)iface->GetHighQualityOverlay(  );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayKey( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayKey_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayKey_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayKey( params->ulOverlayHandle, params->pchValue, params->unBufferSize, params->pError );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayName( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayName_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayName_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayName( params->ulOverlayHandle, params->pchValue, params->unBufferSize, params->pError );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayImageData( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayImageData_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayImageData_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayImageData( params->ulOverlayHandle, params->pvBuffer, params->unBufferSize, params->punWidth, params->punHeight );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayErrorNameFromEnum( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayErrorNameFromEnum_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayErrorNameFromEnum_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (const char *)iface->GetOverlayErrorNameFromEnum( params->error );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayFlag( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayFlag_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayFlag_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayFlag( params->ulOverlayHandle, params->eOverlayFlag, params->bEnabled );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayFlag( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayFlag_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayFlag_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayFlag( params->ulOverlayHandle, params->eOverlayFlag, params->pbEnabled );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayColor( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayColor_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayColor_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayColor( params->ulOverlayHandle, params->fRed, params->fGreen, params->fBlue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayColor( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayColor_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayColor_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayColor( params->ulOverlayHandle, params->pfRed, params->pfGreen, params->pfBlue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayAlpha( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayAlpha_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayAlpha_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayAlpha( params->ulOverlayHandle, params->fAlpha );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayAlpha( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayAlpha_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayAlpha_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayAlpha( params->ulOverlayHandle, params->pfAlpha );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayGamma( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayGamma_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayGamma_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayGamma( params->ulOverlayHandle, params->fGamma );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayGamma( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayGamma_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayGamma_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayGamma( params->ulOverlayHandle, params->pfGamma );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayWidthInMeters( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayWidthInMeters_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayWidthInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayWidthInMeters( params->ulOverlayHandle, params->fWidthInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayWidthInMeters( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayWidthInMeters_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayWidthInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayWidthInMeters( params->ulOverlayHandle, params->pfWidthInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayAutoCurveDistanceRangeInMeters( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayAutoCurveDistanceRangeInMeters_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayAutoCurveDistanceRangeInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayAutoCurveDistanceRangeInMeters( params->ulOverlayHandle, params->fMinDistanceInMeters, params->fMaxDistanceInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayAutoCurveDistanceRangeInMeters( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayAutoCurveDistanceRangeInMeters_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayAutoCurveDistanceRangeInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayAutoCurveDistanceRangeInMeters( params->ulOverlayHandle, params->pfMinDistanceInMeters, params->pfMaxDistanceInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayTextureBounds( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayTextureBounds_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayTextureBounds_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTextureBounds( params->ulOverlayHandle, params->pOverlayTextureBounds );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayTextureBounds( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayTextureBounds_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayTextureBounds_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTextureBounds( params->ulOverlayHandle, params->pOverlayTextureBounds );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayTransformType( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayTransformType_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayTransformType_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformType( params->ulOverlayHandle, params->peTransformType );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayTransformAbsolute( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayTransformAbsolute_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayTransformAbsolute_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTransformAbsolute( params->ulOverlayHandle, params->eTrackingOrigin, params->pmatTrackingOriginToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayTransformAbsolute( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayTransformAbsolute_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayTransformAbsolute_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformAbsolute( params->ulOverlayHandle, params->peTrackingOrigin, params->pmatTrackingOriginToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayTransformTrackedDeviceRelative( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayTransformTrackedDeviceRelative_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayTransformTrackedDeviceRelative_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTransformTrackedDeviceRelative( params->ulOverlayHandle, params->unTrackedDevice, params->pmatTrackedDeviceToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayTransformTrackedDeviceRelative( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayTransformTrackedDeviceRelative_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayTransformTrackedDeviceRelative_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformTrackedDeviceRelative( params->ulOverlayHandle, params->punTrackedDevice, params->pmatTrackedDeviceToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_ShowOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_ShowOverlay_params *params = (struct IVROverlay_IVROverlay_004_ShowOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->ShowOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_HideOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_HideOverlay_params *params = (struct IVROverlay_IVROverlay_004_HideOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->HideOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_IsOverlayVisible( void *args )
{
    struct IVROverlay_IVROverlay_004_IsOverlayVisible_params *params = (struct IVROverlay_IVROverlay_004_IsOverlayVisible_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (bool)iface->IsOverlayVisible( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_PollNextOverlayEvent( void *args )
{
    struct IVROverlay_IVROverlay_004_PollNextOverlayEvent_params *params = (struct IVROverlay_IVROverlay_004_PollNextOverlayEvent_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    u_VREvent_t_097 u_pEvent;
    if (params->pEvent) u_pEvent = *params->pEvent;
    params->_ret = (bool)iface->PollNextOverlayEvent( params->ulOverlayHandle, params->pEvent ? &u_pEvent : nullptr );
    if (params->pEvent) *params->pEvent = u_pEvent;
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayInputMethod( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayInputMethod_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayInputMethod_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayInputMethod( params->ulOverlayHandle, params->peInputMethod );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayInputMethod( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayInputMethod_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayInputMethod_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayInputMethod( params->ulOverlayHandle, params->eInputMethod );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetOverlayMouseScale( void *args )
{
    struct IVROverlay_IVROverlay_004_GetOverlayMouseScale_params *params = (struct IVROverlay_IVROverlay_004_GetOverlayMouseScale_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayMouseScale( params->ulOverlayHandle, params->pvecMouseScale );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayMouseScale( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayMouseScale_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayMouseScale_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayMouseScale( params->ulOverlayHandle, params->pvecMouseScale );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_ComputeOverlayIntersection( void *args )
{
    struct IVROverlay_IVROverlay_004_ComputeOverlayIntersection_params *params = (struct IVROverlay_IVROverlay_004_ComputeOverlayIntersection_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (bool)iface->ComputeOverlayIntersection( params->ulOverlayHandle, params->pParams, params->pResults );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_HandleControllerOverlayInteractionAsMouse( void *args )
{
    struct IVROverlay_IVROverlay_004_HandleControllerOverlayInteractionAsMouse_params *params = (struct IVROverlay_IVROverlay_004_HandleControllerOverlayInteractionAsMouse_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (bool)iface->HandleControllerOverlayInteractionAsMouse( params->ulOverlayHandle, params->unControllerDeviceIndex );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayTexture( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayTexture_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayTexture_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTexture( params->ulOverlayHandle, params->eTextureType, params->pTexture );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_ClearOverlayTexture( void *args )
{
    struct IVROverlay_IVROverlay_004_ClearOverlayTexture_params *params = (struct IVROverlay_IVROverlay_004_ClearOverlayTexture_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->ClearOverlayTexture( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayRaw( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayRaw_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayRaw_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayRaw( params->ulOverlayHandle, params->pvBuffer, params->unWidth, params->unHeight, params->unDepth );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetOverlayFromFile( void *args )
{
    struct IVROverlay_IVROverlay_004_SetOverlayFromFile_params *params = (struct IVROverlay_IVROverlay_004_SetOverlayFromFile_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayFromFile( params->ulOverlayHandle, params->pchFilePath );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_CreateDashboardOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_CreateDashboardOverlay_params *params = (struct IVROverlay_IVROverlay_004_CreateDashboardOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->CreateDashboardOverlay( params->pchOverlayKey, params->pchOverlayFriendlyName, params->pMainHandle, params->pThumbnailHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_IsDashboardVisible( void *args )
{
    struct IVROverlay_IVROverlay_004_IsDashboardVisible_params *params = (struct IVROverlay_IVROverlay_004_IsDashboardVisible_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (bool)iface->IsDashboardVisible(  );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_IsActiveDashboardOverlay( void *args )
{
    struct IVROverlay_IVROverlay_004_IsActiveDashboardOverlay_params *params = (struct IVROverlay_IVROverlay_004_IsActiveDashboardOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (bool)iface->IsActiveDashboardOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_SetDashboardOverlaySceneProcess( void *args )
{
    struct IVROverlay_IVROverlay_004_SetDashboardOverlaySceneProcess_params *params = (struct IVROverlay_IVROverlay_004_SetDashboardOverlaySceneProcess_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetDashboardOverlaySceneProcess( params->ulOverlayHandle, params->unProcessId );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_GetDashboardOverlaySceneProcess( void *args )
{
    struct IVROverlay_IVROverlay_004_GetDashboardOverlaySceneProcess_params *params = (struct IVROverlay_IVROverlay_004_GetDashboardOverlaySceneProcess_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetDashboardOverlaySceneProcess( params->ulOverlayHandle, params->punProcessId );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_004_ShowDashboard( void *args )
{
    struct IVROverlay_IVROverlay_004_ShowDashboard_params *params = (struct IVROverlay_IVROverlay_004_ShowDashboard_params *)args;
    struct u_IVROverlay_IVROverlay_004 *iface = (struct u_IVROverlay_IVROverlay_004 *)params->linux_side;
    iface->ShowDashboard( params->pchOverlayToShow );
    return 0;
}

