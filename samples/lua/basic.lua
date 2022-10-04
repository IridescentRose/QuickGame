clear_col = Color.create(32, 32, 32, 255)
Graphics.set_clear_color(clear_col)

texture = Texture.load("circle.png", 0, 0)
sprite = Sprite.create(240, 136, 256, 256, texture)

while(QuickGame.running()) do
    Graphics.start_frame()
    Graphics.clear()
    
    sprite:draw()

    Graphics.end_frame(true)
end