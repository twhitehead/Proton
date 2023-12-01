#include <stdarg.h>
#include <stddef.h>

#include "windef.h"
#include "winbase.h"

#define COBJMACROS
#include "d3d11_4.h"
#include "dxvk-interop.h"
#include "vrclient_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(vrclient);

struct submit_state
{
    union
    {
        w_Texture_t texture;
        w_VRTextureWithPose_t pose;
        w_VRTextureWithDepth_t depth;
        w_VRTextureWithPoseAndDepth_t pose_depth;
    } texture;
    union
    {
        w_VRVulkanTextureData_t texture;
        w_VRVulkanTextureArrayData_t array;
    } vkdata, vkdata_depth;
    VkImageLayout image_layout, image_layout_depth;
    VkImageSubresourceRange subresources, subresources_depth;
    IDXGIVkInteropSurface *dxvk_surface, *dxvk_surface_depth;
};

static const w_Texture_t *load_compositor_texture_dxvk( uint32_t eye, const w_Texture_t *texture, uint32_t *flags,
                                                        struct submit_state *state )
{
    static const uint32_t supported_flags = Submit_LensDistortionAlreadyApplied | Submit_FrameDiscontinuty |
            Submit_TextureWithPose | Submit_TextureWithDepth;
    VkImageCreateInfo image_info, image_info_depth;
    void **p_texture_depth_handle = NULL;
    const w_Texture_t *result = &state->texture.texture;

    TRACE( "texture = %p\n", texture );

    if (*flags & ~supported_flags) FIXME( "Unhandled flags %#x.\n", *flags );

    /* The extended pose, depth, and both pose and depth info all have different layouts */
    switch (*flags & (Submit_TextureWithPose | Submit_TextureWithDepth))
    {
    default:
        state->texture.texture = *texture;
        break;
    case Submit_TextureWithPose:
        state->texture.pose = *(w_VRTextureWithPose_t*)texture;
        break;
    case Submit_TextureWithDepth:
        state->texture.depth = *(w_VRTextureWithDepth_t*)texture;
        p_texture_depth_handle = &state->texture.depth.depth.handle;
        break;
    case Submit_TextureWithPose | Submit_TextureWithDepth:
        state->texture.pose_depth = *(w_VRTextureWithPoseAndDepth_t*)texture;
        p_texture_depth_handle = &state->texture.pose_depth.depth.handle;
        break;
    }

    /* Handle the texture */
    state->texture.texture.eType = TextureType_Vulkan;
    if ( !(state->texture.texture.handle = vrclient_translate_surface_dxvk( state->texture.texture.handle,
                   &state->vkdata.texture, &state->dxvk_surface, &state->image_layout, &image_info,
                   &state->subresources )) )
        result = texture;

    if (image_info.arrayLayers > 1)
    {
        state->vkdata.array.m_unArrayIndex = eye;
        state->vkdata.array.m_unArraySize = image_info.arrayLayers;
        *flags = *flags | Submit_VulkanTextureWithArrayData;
    }

    /* Handle the optional depth texture */
    if (*flags & Submit_TextureWithDepth)
    {
        if ( !(*p_texture_depth_handle = vrclient_translate_surface_dxvk( *p_texture_depth_handle,
                       &state->vkdata_depth.texture, &state->dxvk_surface_depth, &state->image_layout_depth,
                       &image_info_depth, &state->subresources_depth )) )
          result = texture;

        if (image_info.arrayLayers > 1 || image_info_depth.arrayLayers > 1)
        {
            if (image_info.arrayLayers > 1 && image_info_depth.arrayLayers > 1)
            {
                state->vkdata_depth.array.m_unArrayIndex = eye;
                state->vkdata_depth.array.m_unArraySize = image_info_depth.arrayLayers;
            }
            else
            {
                ERR( "D3D11 texture and depth texture disagree on being layered.\n" );
                result = texture;
            }
        }
    }

    /* Flush, and lock the device */
    compositor_data.dxvk_device->lpVtbl->FlushRenderingCommands( compositor_data.dxvk_device );
    compositor_data.dxvk_device->lpVtbl->LockSubmissionQueue( compositor_data.dxvk_device );

    return result;
}

static void free_compositor_texture_dxvk( struct submit_state *state )
{
    if (!compositor_data.dxvk_device)
        return;

    compositor_data.dxvk_device->lpVtbl->ReleaseSubmissionQueue( compositor_data.dxvk_device );

    if (state->dxvk_surface)
    {
        compositor_data.dxvk_device->lpVtbl->TransitionSurfaceLayout( compositor_data.dxvk_device,
                state->dxvk_surface, &state->subresources, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                state->image_layout );
        state->dxvk_surface->lpVtbl->Release( state->dxvk_surface );
    }

    if (state->dxvk_surface_depth)
    {
        compositor_data.dxvk_device->lpVtbl->TransitionSurfaceLayout( compositor_data.dxvk_device,
                state->dxvk_surface_depth, &state->subresources_depth, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                state->image_layout_depth );
        state->dxvk_surface_depth->lpVtbl->Release( state->dxvk_surface_depth );
    }
}

struct set_skybox_override_state
{
    w_Texture_t textures[6];
    w_VRVulkanTextureData_t vkdata[6];
};

static const w_Texture_t *set_skybox_override_dxvk_init( const w_Texture_t *textures, uint32_t count, struct set_skybox_override_state *state )
{
    IDXGIVkInteropSurface *dxvk_surface;
    unsigned int i;

    for (i = 0; i < count; ++i)
    {
        VkImageSubresourceRange subresources;
        VkImageCreateInfo image_info;
        VkImageLayout image_layout;

        state->textures[i] = textures[i];
        state->textures[i].eType = TextureType_Vulkan;
        if ( !(state->textures[i].handle = vrclient_translate_surface_dxvk( state->textures[i].handle,
                       &state->vkdata[i], &dxvk_surface, &image_layout, &image_info, &subresources )) )
            state->textures[i] = textures[i];

        if ( dxvk_surface )
            dxvk_surface->lpVtbl->Release( dxvk_surface );
    }

    compositor_data.dxvk_device->lpVtbl->FlushRenderingCommands( compositor_data.dxvk_device );
    compositor_data.dxvk_device->lpVtbl->LockSubmissionQueue( compositor_data.dxvk_device );

    return state->textures;
}

static const w_Texture_t *set_skybox_override_init( const w_Texture_t *textures, uint32_t count, struct set_skybox_override_state *state )
{
    unsigned int i;

    if (!count || count > 6)
    {
        WARN( "Invalid texture count %u.\n", count );
        return textures;
    }

    for (i = 0; i<count; ++i) if (textures[i].eType != TextureType_DirectX) {
        FIXME( "Conversion for type %u is not supported.\n", textures[0].eType );
        return textures;
    }

    return set_skybox_override_dxvk_init( textures, count, state );
}

static void set_skybox_override_done( const w_Texture_t *textures, uint32_t count )
{
    if (!count || count > 6) return;
    while (count--) if (textures[count].eType != TextureType_DirectX) return;
    compositor_data.dxvk_device->lpVtbl->ReleaseSubmissionQueue( compositor_data.dxvk_device );
}

static void post_present_handoff_init( void *linux_side, unsigned int version )
{
    if (!compositor_data.dxvk_device) return;
    compositor_data.dxvk_device->lpVtbl->LockSubmissionQueue( compositor_data.dxvk_device );
}

static void post_present_handoff_done(void)
{
    compositor_data.handoff_called = TRUE;
    if (!compositor_data.dxvk_device) return;
    compositor_data.dxvk_device->lpVtbl->ReleaseSubmissionQueue( compositor_data.dxvk_device );
}

static void wait_get_poses_init( void *linux_side )
{
    if (!compositor_data.dxvk_device) return;
    compositor_data.dxvk_device->lpVtbl->LockSubmissionQueue( compositor_data.dxvk_device );
}

static void wait_get_poses_done( void *linux_side )
{
    if (!compositor_data.dxvk_device) return;
    compositor_data.dxvk_device->lpVtbl->ReleaseSubmissionQueue( compositor_data.dxvk_device );
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_009_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_009_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_009_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_009_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_009_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 9 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_009_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_009_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_009_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_009_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_010_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_010_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_010_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_010_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_010_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 10 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_010_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_010_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_010_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_010_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_011_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_011_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_011_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_011_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_011_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 11 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_011_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_011_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_011_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_011_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_012_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_012_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_012_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_012_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_012_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 12 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_012_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_012_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_012_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_012_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_013_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_013_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_013_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_013_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_013_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 13 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_013_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_013_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_013_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_013_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_014_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_014_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_014_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_014_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_014_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 14 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_014_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_014_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_014_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_014_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_015_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_015_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_015_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_015_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_015_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 15 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_015_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_015_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_015_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_015_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_016_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_016_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_016_WaitGetPoses, &params );
    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_016_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_016_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_016_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_016_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_016_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 16 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_016_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_016_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_016_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_016_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_017_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_017_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_017_WaitGetPoses, &params );
    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_017_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_017_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_017_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_017_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_017_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 17 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_017_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_017_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_017_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_017_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_018_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_018_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_018_WaitGetPoses, &params );
    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_018_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_018_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_018_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_018_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_018_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 18 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_018_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_018_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_018_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_018_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_019_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_019_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_019_WaitGetPoses, &params );
    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_019_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_019_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_019_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_019_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_019_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 19 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_019_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_019_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_019_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_019_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_020_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_020_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_020_WaitGetPoses, &params );
    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_020_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_020_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_020_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_020_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_020_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 20 );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_020_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_020_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_020_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_020_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_021_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_021_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff && !compositor_data.handoff_called)
    {
        struct IVRCompositor_IVRCompositor_021_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
        /* Calling handoff after submit is optional for d3d11 but mandatory for Vulkan
         * if explicit timing mode is set. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_PostPresentHandoff, &params );
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_WaitGetPoses, &params );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_021_SubmitExplicitTimingData_params params = {.linux_side = _this->u_iface};
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_SubmitExplicitTimingData, &params );
    }

    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_021_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_021_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_021_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_021_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 21 );

    if (compositor_data.dxvk_device && !compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_021_SetExplicitTimingMode_params params =
        {
            .linux_side = _this->u_iface,
            .bExplicitTimingMode = TRUE,
        };

        /* PostPresentHandoff can be used with d3d11 without SetExplicitTimingMode
         * (which is Vulkan / d3d12 only), but doing the same with Vulkan results
         * in lockups and crashes. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_SetExplicitTimingMode, &params );
        compositor_data.d3d11_explicit_handoff = TRUE;
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_021_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_021_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_021_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_022_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_022_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff && !compositor_data.handoff_called)
    {
        struct IVRCompositor_IVRCompositor_022_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
        /* Calling handoff after submit is optional for d3d11 but mandatory for Vulkan
         * if explicit timing mode is set. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_PostPresentHandoff, &params );
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_WaitGetPoses, &params );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_022_SubmitExplicitTimingData_params params = {.linux_side = _this->u_iface};
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_SubmitExplicitTimingData, &params );
    }

    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_022_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_022_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_022_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_022_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 22 );

    if (compositor_data.dxvk_device && !compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_022_SetExplicitTimingMode_params params =
        {
            .linux_side = _this->u_iface,
            .eTimingMode = VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff,
        };

        /* PostPresentHandoff can be used with d3d11 without SetExplicitTimingMode
         * (which is Vulkan / d3d12 only), but doing the same with Vulkan results
         * in lockups and crashes. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_SetExplicitTimingMode, &params );
        compositor_data.d3d11_explicit_handoff = TRUE;
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_022_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_022_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_022_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_024_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_024_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff && !compositor_data.handoff_called)
    {
        struct IVRCompositor_IVRCompositor_024_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
        /* Calling handoff after submit is optional for d3d11 but mandatory for Vulkan
         * if explicit timing mode is set. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_PostPresentHandoff, &params );
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_WaitGetPoses, &params );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_024_SubmitExplicitTimingData_params params = {.linux_side = _this->u_iface};
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_SubmitExplicitTimingData, &params );
    }

    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_024_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_024_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_024_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_024_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 24 );

    if (compositor_data.dxvk_device && !compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_024_SetExplicitTimingMode_params params =
        {
            .linux_side = _this->u_iface,
            .eTimingMode = VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff,
        };

        /* PostPresentHandoff can be used with d3d11 without SetExplicitTimingMode
         * (which is Vulkan / d3d12 only), but doing the same with Vulkan results
         * in lockups and crashes. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_SetExplicitTimingMode, &params );
        compositor_data.d3d11_explicit_handoff = TRUE;
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_024_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_024_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_024_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_026_WaitGetPoses( struct w_steam_iface *_this,
                                                                     TrackedDevicePose_t *pRenderPoseArray, uint32_t unRenderPoseArrayCount,
                                                                     TrackedDevicePose_t *pGamePoseArray, uint32_t unGamePoseArrayCount )
{
    struct IVRCompositor_IVRCompositor_026_WaitGetPoses_params params =
    {
        .linux_side = _this->u_iface,
        .pRenderPoseArray = pRenderPoseArray,
        .unRenderPoseArrayCount = unRenderPoseArrayCount,
        .pGamePoseArray = pGamePoseArray,
        .unGamePoseArrayCount = unGamePoseArrayCount,
    };
    TRACE( "%p\n", _this );
    wait_get_poses_init( _this->u_iface );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff && !compositor_data.handoff_called)
    {
        struct IVRCompositor_IVRCompositor_026_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
        /* Calling handoff after submit is optional for d3d11 but mandatory for Vulkan
         * if explicit timing mode is set. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_PostPresentHandoff, &params );
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_WaitGetPoses, &params );

    if (compositor_data.dxvk_device && compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_026_SubmitExplicitTimingData_params params = {.linux_side = _this->u_iface};
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_SubmitExplicitTimingData, &params );
    }

    wait_get_poses_done( _this->u_iface );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_026_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_026_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_026_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_026_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 26 );

    if (compositor_data.dxvk_device && !compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_026_SetExplicitTimingMode_params params =
        {
            .linux_side = _this->u_iface,
            .eTimingMode = VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff,
        };

        /* PostPresentHandoff can be used with d3d11 without SetExplicitTimingMode
         * (which is Vulkan / d3d12 only), but doing the same with Vulkan results
         * in lockups and crashes. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_SetExplicitTimingMode, &params );
        compositor_data.d3d11_explicit_handoff = TRUE;
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_026_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_026_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_026_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_027_Submit( struct w_steam_iface *_this,
                                                               uint32_t eEye, const w_Texture_t *pTexture,
                                                               const VRTextureBounds_t *pBounds, uint32_t nSubmitFlags )
{
    struct submit_state state = {0};
    struct IVRCompositor_IVRCompositor_027_Submit_params params =
    {
        .linux_side = _this->u_iface,
        .eEye = eEye,
        .pTexture = pTexture,
        .pBounds = pBounds,
        .nSubmitFlags = nSubmitFlags,
    };
    TRACE( "_this %p, eEye %u, pTexture %p (eType %u), pBounds %p, nSubmitFlags %#x\n", _this, eEye, pTexture, pTexture->eType, pBounds, nSubmitFlags );

    compositor_data.handoff_called = FALSE;
    if (pTexture->eType == TextureType_DirectX)
        params.pTexture = load_compositor_texture_dxvk( eEye, pTexture, &params.nSubmitFlags, &state );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_027_Submit, &params );
    if (pTexture->eType == TextureType_DirectX) free_compositor_texture_dxvk( &state );
    return params._ret;
}

void __thiscall winIVRCompositor_IVRCompositor_027_PostPresentHandoff( struct w_steam_iface *_this )
{
    struct IVRCompositor_IVRCompositor_027_PostPresentHandoff_params params = {.linux_side = _this->u_iface};
    TRACE( "%p\n", _this );
    post_present_handoff_init( _this->u_iface, 27 );

    if (compositor_data.dxvk_device && !compositor_data.d3d11_explicit_handoff)
    {
        struct IVRCompositor_IVRCompositor_027_SetExplicitTimingMode_params params =
        {
            .linux_side = _this->u_iface,
            .eTimingMode = VRCompositorTimingMode_Explicit_ApplicationPerformsPostPresentHandoff,
        };

        /* PostPresentHandoff can be used with d3d11 without SetExplicitTimingMode
         * (which is Vulkan / d3d12 only), but doing the same with Vulkan results
         * in lockups and crashes. */
        VRCLIENT_CALL( IVRCompositor_IVRCompositor_027_SetExplicitTimingMode, &params );
        compositor_data.d3d11_explicit_handoff = TRUE;
    }

    VRCLIENT_CALL( IVRCompositor_IVRCompositor_027_PostPresentHandoff, &params );
    post_present_handoff_done();
}

uint32_t __thiscall winIVRCompositor_IVRCompositor_027_SetSkyboxOverride( struct w_steam_iface *_this,
                                                                          const w_Texture_t *pTextures, uint32_t unTextureCount )
{
    struct set_skybox_override_state state = {0};
    struct IVRCompositor_IVRCompositor_027_SetSkyboxOverride_params params =
    {
        .linux_side = _this->u_iface,
        .pTextures = set_skybox_override_init( pTextures, unTextureCount, &state ),
        .unTextureCount = unTextureCount,
    };
    TRACE( "%p\n", _this );
    VRCLIENT_CALL( IVRCompositor_IVRCompositor_027_SetSkyboxOverride, &params );
    set_skybox_override_done( pTextures, unTextureCount );
    return params._ret;
}
