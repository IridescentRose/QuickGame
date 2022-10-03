clear_col1 = Color.create(255, 0, 255, 255)
clear_col2 = Color.create(0, 255, 0, 255)

while(QuickGame.running()) do
    Input.update()

    if Input.button_held(PSP_CROSS) then
        Graphics.set_clear_color(clear_col1)
    else
        Graphics.set_clear_color(clear_col2)
    end

    Graphics.start_frame()
    Graphics.clear()
    
    Graphics.end_frame(true)
end