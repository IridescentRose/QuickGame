/**
 * @file QuickGame.hpp
 * @author Nathan Bourgeois (iridescentrosesfall@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <QuickGame.h>
#include <stdexcept>
#include <vector>
#include <string.h>

namespace QuickGame {
/**
 * @brief Initializes the game engine
 * @throw Throws a runtime error exception on failure
 */
inline auto init() -> void {
    if(QuickGame_Init() < 0)
        throw std::runtime_error("Failed to initialize!");
}

/**
 * @brief Tells whether the game is running
 * 
 */
inline auto running() noexcept -> bool {
    return QuickGame_Running();
}

/**
 * @brief Terminates the game engine
 * 
 */
inline auto terminate() noexcept -> void {
    QuickGame_Terminate();
}

/**
 * @brief Requests an exit from the game engine
 * 
 */
inline auto request_exit() noexcept -> void {
    QuickGame_Request_Exit();
} 

/**
 * MEMORY ALLOCATION
 * TO OVERRIDE THESE FUNCTIONS
 * #define QUICKGAME_CUSTOM_ALLOCATOR
 */

/**
 * @brief Allocates memory of size n
 * 
 * @param n Size in bytes to allocate
 * @return anyopaque* Result or NULL if failed
 */
inline auto allocate(usize n) -> anyopaque* {
    return QuickGame_Allocate(n);
}

/**
 * @brief Allocates memory of size n and aligned to a bytes
 * 
 * @param a 
 * @param n 
 * @return anyopaque* 
 */
inline auto allocate_aligned(usize a, usize n) -> anyopaque* {
    return QuickGame_Allocate_Aligned(a, n);
}

/**
 * @brief Destroyes memory allocation
 * 
 * @param src Memory allocation to destroy
 */
inline auto destroy(anyopaque* src) -> void {
    return QuickGame_Destroy(src);
}

namespace Graphics{
/**
 * @brief Initializes the graphics context
 * 
 */
inline auto init() -> void {
    QuickGame_Graphics_Init();
}

/**
 * @brief Terminates the graphics context
 * 
 */
inline auto terminate() noexcept -> void {
    QuickGame_Graphics_Terminate();
} 

/**
 * @brief Sets a dialog mode
 * 
 * @param mode Are we inside a dialog mode?
 */
inline auto set_dialog_mode(const bool&& mode) noexcept -> void {
    QuickGame_Graphics_Set_Dialog_Mode(mode);
}


/**
 * @brief Sets wireframe mode
 * 
 * @param mode Draw in wireframe mode?
 */
inline auto set_wireframe_mode(const bool&& mode) noexcept -> void {
    QuickGame_Graphics_Set_Wireframe_Mode(mode);
}

/**
 * @brief Starts a new frame
 * 
 */
inline auto start_frame() noexcept -> void {
    QuickGame_Graphics_Start_Frame();
}

/**
 * @brief Ends the frame and draws to screen
 * 
 * @param vsync Whether or not to VSync?
 */
inline auto end_frame(const bool&& vsync) noexcept -> void {
    QuickGame_Graphics_End_Frame(vsync);
}

/**
 * @brief Sets the clear color of the screen
 * 
 * @param color Background color
 */
inline auto set_clear_color(const QGColor&& color) noexcept -> void {
    QuickGame_Graphics_Set_Clear_Color(color);
}

/**
 * @brief Clears the screen
 * 
 */
inline auto clear() noexcept -> void {
    QuickGame_Graphics_Clear();
}

/**
 * @brief Sets rendering for 2D -- must be called inside of StartFrame() EndFrame()
 * 
 */
inline auto set2D() noexcept -> void {
    QuickGame_Graphics_Set2D();
}

/**
 * @brief Sets a camera to track
 * 
 * @param camera Camera to track
 */
inline auto set_camera(QGCamera2D& camera) {
    QuickGame_Graphics_Set_Camera(&camera);
}

/**
 * @brief Stops tracking the previously set camera.
 * 
 */
inline auto unset_camera() {
    QuickGame_Graphics_Unset_Camera();
}

class Mesh {
    public:
    Mesh() : ir(NULL) {}

    /**
     * @brief Construct a new Mesh object
     * 
     * @param type Vertex Type
     * @param vcount Vertex Count
     * @param icount Index Count
     */
    Mesh(const u8 type, const usize vcount, const usize icount) : ir(NULL) {
        create_mesh(type, vcount, icount);
    }

    virtual ~Mesh() {
        delete_data();
    }

    /**
     * @brief Create a mesh
     * 
     * @param type Vertex Type
     * @param vcount Vertex Count
     * @param icount Index Count
     */
    inline auto create_mesh(const u8 type, const usize vcount, const usize icount) -> void {
        if(ir != NULL) 
            delete_data();
        else 
            ir = QuickGame_Graphics_Create_Mesh(type, vcount, icount);
        
        if(ir == NULL)
            throw std::runtime_error("Mesh creation failed!");
    }

    /**
     * @brief Add Data - this copies the data and does not take ownership!
     * 
     * @param verts Vertex data
     * @param vcount Vertex Count
     * @param indices Index data
     * @param icount Index Count
     */
    inline auto add_data(const void* verts, size_t vcount, const u16* indices, size_t icount) -> void {
        if(verts == nullptr || indices == nullptr)
            throw std::runtime_error("Mesh data null!");

        int size = 0;
        switch(ir->type) {
            case QG_VERTEX_TYPE_COLORED:
                size = sizeof(QGColoredVertex);
                break;
            case QG_VERTEX_TYPE_FULL:
                size = sizeof(QGFullVertex);
                break;
            case QG_VERTEX_TYPE_TEXTURED:
                size = sizeof(QGTexturedVertex);
                break;
            case QG_VERTEX_TYPE_SIMPLE:
                size = sizeof(QGSimpleVertex);
                break;
        }         

        memcpy(ir->data, verts, vcount * size);
        memcpy(ir->indices, indices, icount * sizeof(u16));
    }

    /**
     * @brief Draws the mesh
     * 
     */
    inline auto draw() noexcept -> void {
        QuickGame_Graphics_Draw_Mesh(ir);
    }

    /**
     * @brief Deletes data -- you need to call create after this to reuse
     * 
     */
    inline auto delete_data() noexcept -> void {
        QuickGame_Graphics_Destroy_Mesh(&ir);
    }

    protected:
    QGVMesh_t ir;
};

class Texture {
    public:

        /**
         * @brief Load a texture from disk
         * 
         * @param filename File to load
         * @param vram Whether the texture should be stored in VRAM
         * @return QGTexture_t Texture loaded or NULL if failed
         */
        Texture(const char* filename, const bool flip, const bool vram) : ir(NULL) {
            ir = QuickGame_Texture_Load(filename, flip, vram);
            if(ir == nullptr)
                throw std::runtime_error("Could not load texture!");
        }

        /**
         * @brief Load a texture from disk
         * 
         * @param tex_info Texture information about loading
         * @return QGTexture_t Texture loaded of NULL if failed
         */
        Texture(const QGTexInfo tex_info) {
            ir = QuickGame_Texture_Load_Alt(tex_info);
            if(ir == nullptr)
                throw std::runtime_error("Could not load texture!");
        }

        /**
         * @brief Texture to bind to the graphics engine
         * 
         * @param texture Texture to bind
         */
        inline auto bind() noexcept -> void {
            QuickGame_Texture_Bind(ir);
        }

        /**
         * @brief Texture to unbind from the graphics engine
         * 
         */
        inline auto unbind() noexcept -> void {
            QuickGame_Texture_Unbind();
        }

        virtual ~Texture() {
            QuickGame_Texture_Destroy(&ir);
        }

        friend class Sprite;

    protected:
    QGTexture_t ir;
};

class Tilemap {
    public:

    /**
     * @brief Create a tilemap
     * 
     * @param texture_atlas Texture Atlas size 
     * @param texture Texture to use
     * @param size Size of tile map
     * @return QGTilemap_t Created tilemap or NULL on failure
     */
    Tilemap(QGTextureAtlas texture_atlas, QGTexture_t texture, QGVector2 size) {
        ir = QuickGame_Tilemap_Create(texture_atlas, texture, size);
    }
    ~Tilemap() {
        QuickGame_Tilemap_Destroy(&ir);
    }

    inline auto intersects(QGTransform2D transform) noexcept -> bool {
        return QuickGame_Tilemap_Intersects(ir, transform);
    }

    inline auto draw_string(std::string str, QGVector2 position) noexcept -> void {
        return QuickGame_Tilemap_Draw_String(ir, str.c_str(), position);
    }

    inline auto build() noexcept -> void {
        QuickGame_Tilemap_Build(ir);
    }
    inline auto draw() noexcept -> void {
        QuickGame_Tilemap_Draw(ir);
    }

    protected:
    QGTilemap_t ir;
};

class Sprite {
    public:
    QGTransform2D transform;
    i32 layer;
    QGColor color;

    /**
     * @brief Creates a sprite
     * 
     * @param position Position for sprite
     * @param size Size of sprite
     * @param texture Texture to use
     * @return Sprite Sprite result or NULL if failed
     */
    Sprite(const QGVector2 position, const QGVector2 size, Texture* texture) {
        transform = {position, 0, size};
        layer = 0;
        color.color = 0xFFFFFFFF;

        ir = QuickGame_Sprite_Create(position, size, texture->ir);

        if(ir == NULL)
            throw std::runtime_error("Could not make sprite!");
    }

    /**
     * @brief Creates a sprite and loads a texture. This texture is owned by the sprite and destroyed on sprite destroy.
     * 
     * @param position Position for sprite
     * @param size Size of sprite
     * @param tex_info Information about the texture to load
     * @return QGSprite_t Sprite result or NULL if failed
     */
    Sprite(const QGVector2&& position, const QGVector2&& size, const QGTexInfo tex_info) {
        transform = {position, 0, size};
        layer = 0;
        color.color = 0xFFFFFFFF;

        ir = QuickGame_Sprite_Create_Contained(position.x, position.y, size.x, size.y, tex_info);

        if(ir == NULL)
            throw std::runtime_error("Could not make sprite!");
    }

    virtual ~Sprite() {
        QuickGame_Sprite_Destroy(&ir);
    }

    inline auto draw() noexcept -> void{
        if(ir == nullptr)
            return;

        ir->transform = transform;
        ir->layer = layer;

        QuickGame_Sprite_Draw(ir);
    }

    inline auto intersects(Sprite& other) noexcept -> bool {
        return QuickGame_Sprite_Intersects(ir, other.ir);
    }



    inline auto intersection(Sprite& other) noexcept -> int {
        return QuickGame_Sprite_Intersect_Direction(ir, other.ir);
    }

    private:
    QGSprite_t ir;
};


/**
 * @brief Intersection Detection
 * 
 * @param a Transform A
 * @param b Transform B
 * @return true Transforms intersect
 * @return false Transforms do not intersect
 */
inline auto intersect_transform(QGTransform2D a, QGTransform2D b) noexcept -> bool {
    return QuickGame_Intersect_Transform(a, b);
}

} // Graphics

class Timer {
    public:
    Timer() {
        QuickGame_Timer_Start(&t);
    }
    virtual ~Timer() {
        reset();
    }

    inline auto deltaTime() noexcept -> double {
        return QuickGame_Timer_Delta(&t);
    }

    inline auto elapsed() noexcept -> double {
        return QuickGame_Timer_Elapsed(&t);
    }

    inline auto reset() noexcept -> void {
        QuickGame_Timer_Reset(&t);
    }

    private:
    QGTimer t;
};

namespace Audio {
/**
 * @brief Initializes the audio subsystem
 * 
 */
inline auto init() noexcept -> void{
    QuickGame_Audio_Init();
}

/**
 * @brief Terminates the audio subsystem
 * 
 */
inline auto terminate() noexcept -> void{
    QuickGame_Audio_Terminate();
}

class Clip{
    public:

    /**
     * @brief Loads an audio clip
     * 
     * @param filename File name
     * @param looping Whether or not the audio is looping
     * @param streaming Whether or not we should stream the audio from disk
     * @return QGAudioClip_t Result audio clip or NULL on failure
     */
    Clip(const char* filename, bool looping, bool streaming) {
        ir = QuickGame_Audio_Load(filename, looping, streaming);
    }

    ~Clip() {
        QuickGame_Audio_Destroy(&ir);
    }
    /**
     * @brief Sets the clip's looping mode
     * 
     * @param looping Whether or not the clip should play in a loop
     */
    inline auto set_looping(bool looping) noexcept -> void {
        QuickGame_Audio_Set_Looping(ir, looping);
    }

    /**
     * @brief Sets the clip's volume
     * 
     * @param volume Volume of the clip [0, 1]
     */
    inline auto set_volume(f32 volume) noexcept -> void {
        QuickGame_Audio_Set_Volume(ir, volume);
    }

    /**
     * @brief Sets the clips' panning
     * 
     * @param pan Panning from [-1, 1]
     */
    inline auto set_pan(f32 pan) noexcept -> void {
        QuickGame_Audio_Set_Pan(ir, pan);
    }

    /**
     * @brief Plays an audio clip on a channel. There are channels 0-8
     * 
     * @param channel Clip channel
     */
    inline auto play(u8 channel) noexcept -> void {
        QuickGame_Audio_Play(ir, channel);
    }

    /**
     * @brief Pauses an audio clip (this toggles if you call pause on a paused clip)
     * 
     * @param clip Clip to pause
     */
    inline auto pause() noexcept -> void {
        QuickGame_Audio_Pause(ir);
    }

    /**
     * @brief Stops an audio clip
     * 
     */
    inline auto stop() noexcept -> void {
        QuickGame_Audio_Stop(ir);
    }

    private:
    QGAudioClip_t ir;

};

}

namespace Primitive {
    /**
 * @brief Initialize Primitive Drawings
 * 
 * returns int < 0 on failure.
 */
int init();

/**
 * @brief Terminate Primitives
 * 
 */
void terminate();

/**
 * @brief Draw a rectangle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void draw_rectangle(QGTransform2D transform, QGColor color);

/**
 * @brief Draw a triangle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void draw_triangle(QGTransform2D transform, QGColor color);

/**
 * @brief Draw a circle with a given transform and color
 * 
 * @param transform Position, Rotation, Size
 * @param color Color to draw with
 */
void draw_circle(QGTransform2D transform, QGColor color);
}

namespace Input {

/**
 * @brief Initialize the input system -- does not need termination
 * 
 */
inline auto init() noexcept -> void {
    QuickGame_Input_Init();
}

/**
 * @brief Update the input system
 * 
 */
inline auto update() noexcept -> void {
    QuickGame_Input_Update();
}

/**
 * @brief Is Button Pressed? This will only return true on the very FIRST time the button (combination) is pressed until it is released
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true Button is pressed
 * @return false Button is not pressed
 */
inline auto button_pressed(u32 buttons) noexcept -> bool {
    return QuickGame_Button_Pressed(buttons);
}

/**
 * @brief Is Button Held? This will return true on the subsequent times the button  (combination) is held until it is released
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true Button is held
 * @return false Button is not held
 */
inline auto button_held(u32 buttons) noexcept -> bool {
    return QuickGame_Button_Held(buttons);
}

/**
 * @brief Is Button Released? Only returns true if this is the EXACT moment of release. This only trigger when a button (combination) stops being pressed.
 * 
 * @param buttons Button or button combination from PSP CTRL
 * @return true 
 * @return false 
 */
inline auto button_released(u32 buttons) noexcept -> bool {
    return QuickGame_Button_Released(buttons);
}


/**
 * @brief Gets the current analog X position, scaled to [-1, 1]
 * 
 * @return f32 X position
 */
inline auto analog_x() noexcept -> f32 {
    return QuickGame_Analog_X();
}

/**
 * @brief Gets the current analog Y position, scaled to [-1, 1]
 * 
 * @return f32 Y position
 */
inline auto analog_y() noexcept -> f32 {
    return QuickGame_Analog_Y();
}

}

} // QuickGame