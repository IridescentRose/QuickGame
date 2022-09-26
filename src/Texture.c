#include <QuickGame.h>
#include <Texture.h>
#include <stb_image.h>
#include <gu2gl.h>
#include <pspkernel.h>

void swizzle_fast(u8 *out, const u8 *in, const u32 width, const u32 height) {
    u32 blockx, blocky;
    u32 j;

    u32 width_blocks = (width / 16);
    u32 height_blocks = (height / 8);

    u32 src_pitch = (width - 16) / 4;
    u32 src_row = width * 8;

    const u8 *ysrc = in;
    u32 *dst = (u32 *)out;

    for (blocky = 0; blocky < height_blocks; ++blocky) {
        const u8 *xsrc = ysrc;
        for (blockx = 0; blockx < width_blocks; ++blockx) {
            const u32 *src = (u32 *)xsrc;
            for (j = 0; j < 8; ++j) {
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                *(dst++) = *(src++);
                src += src_pitch;
            }
            xsrc += 16;
        }
        ysrc += src_row;
    }
}

u32 pow2(const u32 value) {
    u32 poweroftwo = 1;
    while (poweroftwo < value) {
        poweroftwo <<= 1;
    }
    return poweroftwo;
}

void copy_texture_data(void* dest, const void* src, const int pW, const int width, const int height){
    for (u32 y = 0; y < height; y++) {
        for (u32 x = 0; x < width; x++) {
            ((u32*)dest)[x + y * pW] = ((u32 *)src)[x + y * width];
        }
    }
}

QGTexture_t QuickGame_Texture_Load_Alt(const QGTexInfo tex_info){
    return QuickGame_Texture_Load(tex_info.filename, tex_info.flip, tex_info.vram);
}

QGTexture_t QuickGame_Texture_Load(const char* filename, const bool flip, const bool vram) {
    
    int width, height, nrChannels;    
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(filename, &width, &height,
                                    &nrChannels, STBI_rgb_alpha);

    if(!data)
        return NULL;

    QGTexture_t tex = (QGTexture_t)QuickGame_Allocate(sizeof(QGTexture));
    if(!tex) {
        stbi_image_free(data);
        return NULL;
    }
    
    tex->width = width;
    tex->height = height;
    tex->pWidth = pow2(width);
    tex->pHeight = pow2(height);

    u32 *dataBuffer = QuickGame_Allocate_Aligned(16, tex->pHeight * tex->pWidth * 4);
    if(!dataBuffer) {
        stbi_image_free(data);
        QuickGame_Destroy(tex);
        return NULL;
    }

    // Copy to Data Buffer
    copy_texture_data(dataBuffer, data, tex->pWidth, tex->width, tex->height);

    stbi_image_free(data);

    u32* swizzled_pixels = NULL;
    size_t size = tex->pHeight * tex->pWidth * 4;
    if(vram){
        swizzled_pixels = getStaticVramTexture(tex->pWidth, tex->pHeight, GU_PSM_8888);
    } else {
        swizzled_pixels = QuickGame_Allocate_Aligned(16, size);
    }

    if(!swizzled_pixels) {
        QuickGame_Destroy(dataBuffer);
        QuickGame_Destroy(tex);
        return NULL;
    }
    
    swizzle_fast((u8*)swizzled_pixels, (const u8*)dataBuffer, tex->pWidth * 4, tex->pHeight);

    QuickGame_Destroy(dataBuffer);
    tex->data = swizzled_pixels;

    sceKernelDcacheWritebackInvalidateAll();

    return tex;
}

void QuickGame_Texture_Destroy(QGTexture_t* texture) {
    if(!texture || !*texture)
        return;
    
    QuickGame_Destroy((*texture)->data);
    QuickGame_Destroy(*texture);
    *texture = NULL;
}

void QuickGame_Texture_Bind(const QGTexture_t texture) {
    if(texture == NULL)
        return;

    glEnable(GL_TEXTURE_2D);
    glTexMode(GU_PSM_8888, 0, 0, 1);
    glTexFunc(GL_TFX_MODULATE, GL_TCC_RGBA);
    glTexFilter(GL_NEAREST, GL_NEAREST);
    glTexWrap(GL_REPEAT, GL_REPEAT);
    glTexImage(0, texture->pWidth, texture->pHeight, texture->pWidth, texture->data);
}

void QuickGame_Texture_Unbind() {
    glDisable(GL_TEXTURE_2D);
    glTexImage(0, 0, 0, 0, 0);
}