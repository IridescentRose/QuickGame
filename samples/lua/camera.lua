clear_col = Color.create(32, 32, 32, 255)

tri_color = Color.create(255, 0, 0, 255)
rect_color = Color.create(0, 255, 0, 255)
circle_color = Color.create(0, 0, 255, 255)

Graphics.set_clear_color(clear_col)

timer = Timer.create()
camera = Camera.create()
cx = 0.0
cy = 0.0
cr = 0.0

Graphics.set_camera(camera)

while(QuickGame.running()) do
    Input.update()

    dt = timer:delta()

    if Input.button_held(PSP_RIGHT) then
        cx = cx + dt * 40.0
    end
    if Input.button_held(PSP_LEFT) then
        cx = cx - dt * 40.0
    end

    if Input.button_held(PSP_UP) then
        cy = cy + dt * 40.0
    end
    if Input.button_held(PSP_DOWN) then
        cy = cy - dt * 40.0
    end

    if Input.button_held(PSP_LTRIGGER) then
        cr = cr - dt * 40.0
    end
    if Input.button_held(PSP_RTRIGGER) then
        cr = cr + dt * 40.0
    end

    camera:set_position(cx, cy)
    camera:set_rotation(cr)

    Graphics.start_frame()
    Graphics.clear()

    Primitive.draw_triangle(120, 136, 40, 40, tri_color, 0.0)
    Primitive.draw_rectangle(240, 136, 40, 40, rect_color, 0.0)
    Primitive.draw_circle(360, 136, 40, 40, circle_color, 0.0)
    
    Graphics.end_frame(true)
end