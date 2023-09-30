/* This file is auto-generated, do not edit. */
#include "unix_private.h"

NTSTATUS IVROverlay_IVROverlay_007_FindOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_FindOverlay_params *params = (struct IVROverlay_IVROverlay_007_FindOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->FindOverlay( params->pchOverlayKey, params->pOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_CreateOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_CreateOverlay_params *params = (struct IVROverlay_IVROverlay_007_CreateOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->CreateOverlay( params->pchOverlayKey, params->pchOverlayFriendlyName, params->pOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_DestroyOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_DestroyOverlay_params *params = (struct IVROverlay_IVROverlay_007_DestroyOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->DestroyOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetHighQualityOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_SetHighQualityOverlay_params *params = (struct IVROverlay_IVROverlay_007_SetHighQualityOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetHighQualityOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetHighQualityOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_GetHighQualityOverlay_params *params = (struct IVROverlay_IVROverlay_007_GetHighQualityOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint64_t)iface->GetHighQualityOverlay(  );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayKey( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayKey_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayKey_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayKey( params->ulOverlayHandle, params->pchValue, params->unBufferSize, params->pError );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayName( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayName_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayName_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayName( params->ulOverlayHandle, params->pchValue, params->unBufferSize, params->pError );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayImageData( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayImageData_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayImageData_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayImageData( params->ulOverlayHandle, params->pvBuffer, params->unBufferSize, params->punWidth, params->punHeight );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayErrorNameFromEnum( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayErrorNameFromEnum_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayErrorNameFromEnum_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (const char *)iface->GetOverlayErrorNameFromEnum( params->error );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayFlag( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayFlag_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayFlag_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayFlag( params->ulOverlayHandle, params->eOverlayFlag, params->bEnabled );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayFlag( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayFlag_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayFlag_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayFlag( params->ulOverlayHandle, params->eOverlayFlag, params->pbEnabled );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayColor( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayColor_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayColor_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayColor( params->ulOverlayHandle, params->fRed, params->fGreen, params->fBlue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayColor( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayColor_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayColor_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayColor( params->ulOverlayHandle, params->pfRed, params->pfGreen, params->pfBlue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayAlpha( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayAlpha_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayAlpha_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayAlpha( params->ulOverlayHandle, params->fAlpha );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayAlpha( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayAlpha_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayAlpha_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayAlpha( params->ulOverlayHandle, params->pfAlpha );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayWidthInMeters( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayWidthInMeters_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayWidthInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayWidthInMeters( params->ulOverlayHandle, params->fWidthInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayWidthInMeters( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayWidthInMeters_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayWidthInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayWidthInMeters( params->ulOverlayHandle, params->pfWidthInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayAutoCurveDistanceRangeInMeters( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayAutoCurveDistanceRangeInMeters_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayAutoCurveDistanceRangeInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayAutoCurveDistanceRangeInMeters( params->ulOverlayHandle, params->fMinDistanceInMeters, params->fMaxDistanceInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayAutoCurveDistanceRangeInMeters( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayAutoCurveDistanceRangeInMeters_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayAutoCurveDistanceRangeInMeters_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayAutoCurveDistanceRangeInMeters( params->ulOverlayHandle, params->pfMinDistanceInMeters, params->pfMaxDistanceInMeters );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayTextureColorSpace( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayTextureColorSpace_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayTextureColorSpace_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTextureColorSpace( params->ulOverlayHandle, params->eTextureColorSpace );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayTextureColorSpace( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayTextureColorSpace_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayTextureColorSpace_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTextureColorSpace( params->ulOverlayHandle, params->peTextureColorSpace );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayTextureBounds( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayTextureBounds_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayTextureBounds_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTextureBounds( params->ulOverlayHandle, params->pOverlayTextureBounds );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayTextureBounds( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayTextureBounds_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayTextureBounds_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTextureBounds( params->ulOverlayHandle, params->pOverlayTextureBounds );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayTransformType( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayTransformType_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayTransformType_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformType( params->ulOverlayHandle, params->peTransformType );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayTransformAbsolute( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayTransformAbsolute_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayTransformAbsolute_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTransformAbsolute( params->ulOverlayHandle, params->eTrackingOrigin, params->pmatTrackingOriginToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayTransformAbsolute( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayTransformAbsolute_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayTransformAbsolute_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformAbsolute( params->ulOverlayHandle, params->peTrackingOrigin, params->pmatTrackingOriginToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayTransformTrackedDeviceRelative( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayTransformTrackedDeviceRelative_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayTransformTrackedDeviceRelative_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTransformTrackedDeviceRelative( params->ulOverlayHandle, params->unTrackedDevice, params->pmatTrackedDeviceToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayTransformTrackedDeviceRelative( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayTransformTrackedDeviceRelative_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayTransformTrackedDeviceRelative_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayTransformTrackedDeviceRelative( params->ulOverlayHandle, params->punTrackedDevice, params->pmatTrackedDeviceToOverlayTransform );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ShowOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_ShowOverlay_params *params = (struct IVROverlay_IVROverlay_007_ShowOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->ShowOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_HideOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_HideOverlay_params *params = (struct IVROverlay_IVROverlay_007_HideOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->HideOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_IsOverlayVisible( void *args )
{
    struct IVROverlay_IVROverlay_007_IsOverlayVisible_params *params = (struct IVROverlay_IVROverlay_007_IsOverlayVisible_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->IsOverlayVisible( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_PollNextOverlayEvent( void *args )
{
    struct IVROverlay_IVROverlay_007_PollNextOverlayEvent_params *params = (struct IVROverlay_IVROverlay_007_PollNextOverlayEvent_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    u_VREvent_t_0912 u_pEvent;
    if (params->pEvent) u_pEvent = *params->pEvent;
    params->_ret = (bool)iface->PollNextOverlayEvent( params->ulOverlayHandle, params->pEvent ? &u_pEvent : nullptr );
    if (params->pEvent) *params->pEvent = u_pEvent;
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayInputMethod( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayInputMethod_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayInputMethod_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayInputMethod( params->ulOverlayHandle, params->peInputMethod );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayInputMethod( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayInputMethod_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayInputMethod_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayInputMethod( params->ulOverlayHandle, params->eInputMethod );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetOverlayMouseScale( void *args )
{
    struct IVROverlay_IVROverlay_007_GetOverlayMouseScale_params *params = (struct IVROverlay_IVROverlay_007_GetOverlayMouseScale_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetOverlayMouseScale( params->ulOverlayHandle, params->pvecMouseScale );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayMouseScale( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayMouseScale_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayMouseScale_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayMouseScale( params->ulOverlayHandle, params->pvecMouseScale );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ComputeOverlayIntersection( void *args )
{
    struct IVROverlay_IVROverlay_007_ComputeOverlayIntersection_params *params = (struct IVROverlay_IVROverlay_007_ComputeOverlayIntersection_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->ComputeOverlayIntersection( params->ulOverlayHandle, params->pParams, params->pResults );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_HandleControllerOverlayInteractionAsMouse( void *args )
{
    struct IVROverlay_IVROverlay_007_HandleControllerOverlayInteractionAsMouse_params *params = (struct IVROverlay_IVROverlay_007_HandleControllerOverlayInteractionAsMouse_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->HandleControllerOverlayInteractionAsMouse( params->ulOverlayHandle, params->unControllerDeviceIndex );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_IsHoverTargetOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_IsHoverTargetOverlay_params *params = (struct IVROverlay_IVROverlay_007_IsHoverTargetOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->IsHoverTargetOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetGamepadFocusOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_GetGamepadFocusOverlay_params *params = (struct IVROverlay_IVROverlay_007_GetGamepadFocusOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint64_t)iface->GetGamepadFocusOverlay(  );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetGamepadFocusOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_SetGamepadFocusOverlay_params *params = (struct IVROverlay_IVROverlay_007_SetGamepadFocusOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetGamepadFocusOverlay( params->ulNewFocusOverlay );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayNeighbor( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayNeighbor_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayNeighbor_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayNeighbor( params->eDirection, params->ulFrom, params->ulTo );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_MoveGamepadFocusToNeighbor( void *args )
{
    struct IVROverlay_IVROverlay_007_MoveGamepadFocusToNeighbor_params *params = (struct IVROverlay_IVROverlay_007_MoveGamepadFocusToNeighbor_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->MoveGamepadFocusToNeighbor( params->eDirection, params->ulFrom );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayTexture( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayTexture_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayTexture_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayTexture( params->ulOverlayHandle, params->pTexture );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ClearOverlayTexture( void *args )
{
    struct IVROverlay_IVROverlay_007_ClearOverlayTexture_params *params = (struct IVROverlay_IVROverlay_007_ClearOverlayTexture_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->ClearOverlayTexture( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayRaw( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayRaw_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayRaw_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayRaw( params->ulOverlayHandle, params->pvBuffer, params->unWidth, params->unHeight, params->unDepth );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetOverlayFromFile( void *args )
{
    struct IVROverlay_IVROverlay_007_SetOverlayFromFile_params *params = (struct IVROverlay_IVROverlay_007_SetOverlayFromFile_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetOverlayFromFile( params->ulOverlayHandle, params->pchFilePath );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_CreateDashboardOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_CreateDashboardOverlay_params *params = (struct IVROverlay_IVROverlay_007_CreateDashboardOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->CreateDashboardOverlay( params->pchOverlayKey, params->pchOverlayFriendlyName, params->pMainHandle, params->pThumbnailHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_IsDashboardVisible( void *args )
{
    struct IVROverlay_IVROverlay_007_IsDashboardVisible_params *params = (struct IVROverlay_IVROverlay_007_IsDashboardVisible_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->IsDashboardVisible(  );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_IsActiveDashboardOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_IsActiveDashboardOverlay_params *params = (struct IVROverlay_IVROverlay_007_IsActiveDashboardOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (bool)iface->IsActiveDashboardOverlay( params->ulOverlayHandle );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_SetDashboardOverlaySceneProcess( void *args )
{
    struct IVROverlay_IVROverlay_007_SetDashboardOverlaySceneProcess_params *params = (struct IVROverlay_IVROverlay_007_SetDashboardOverlaySceneProcess_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->SetDashboardOverlaySceneProcess( params->ulOverlayHandle, params->unProcessId );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetDashboardOverlaySceneProcess( void *args )
{
    struct IVROverlay_IVROverlay_007_GetDashboardOverlaySceneProcess_params *params = (struct IVROverlay_IVROverlay_007_GetDashboardOverlaySceneProcess_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetDashboardOverlaySceneProcess( params->ulOverlayHandle, params->punProcessId );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ShowDashboard( void *args )
{
    struct IVROverlay_IVROverlay_007_ShowDashboard_params *params = (struct IVROverlay_IVROverlay_007_ShowDashboard_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    iface->ShowDashboard( params->pchOverlayToShow );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ShowKeyboard( void *args )
{
    struct IVROverlay_IVROverlay_007_ShowKeyboard_params *params = (struct IVROverlay_IVROverlay_007_ShowKeyboard_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->ShowKeyboard( params->eInputMode, params->eLineInputMode, params->pchDescription, params->unCharMax, params->pchExistingText, params->bUseMinimalMode, params->uUserValue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_ShowKeyboardForOverlay( void *args )
{
    struct IVROverlay_IVROverlay_007_ShowKeyboardForOverlay_params *params = (struct IVROverlay_IVROverlay_007_ShowKeyboardForOverlay_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->ShowKeyboardForOverlay( params->ulOverlayHandle, params->eInputMode, params->eLineInputMode, params->pchDescription, params->unCharMax, params->pchExistingText, params->bUseMinimalMode, params->uUserValue );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_GetKeyboardText( void *args )
{
    struct IVROverlay_IVROverlay_007_GetKeyboardText_params *params = (struct IVROverlay_IVROverlay_007_GetKeyboardText_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    params->_ret = (uint32_t)iface->GetKeyboardText( params->pchText, params->cchText );
    return 0;
}

NTSTATUS IVROverlay_IVROverlay_007_HideKeyboard( void *args )
{
    struct IVROverlay_IVROverlay_007_HideKeyboard_params *params = (struct IVROverlay_IVROverlay_007_HideKeyboard_params *)args;
    struct u_IVROverlay_IVROverlay_007 *iface = (struct u_IVROverlay_IVROverlay_007 *)params->linux_side;
    iface->HideKeyboard(  );
    return 0;
}

