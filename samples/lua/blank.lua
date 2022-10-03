clear_col = Color.create(255, 0, 255, 255)

Graphics.set_clear_color(clear_col)

while(QuickGame.running()) do
    Graphics.start_frame()
    Graphics.clear()
    
    Graphics.end_frame(true)
end