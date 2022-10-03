clear_col = Color.create(32, 32, 32, 255)

Graphics.set_clear_color(clear_col)

while(QuickGame.running()) do
    Graphics.start_frame()
    Graphics.clear()

    tri_color = Color.create(255, 0, 0, 255)
    rect_color = Color.create(0, 255, 0, 255)
    circle_color = Color.create(0, 0, 255, 255)
    
    Primitive.draw_triangle(120, 136, 40, 40, tri_color, 0.0)
    Primitive.draw_rectangle(240, 136, 40, 40, rect_color, 0.0)
    Primitive.draw_circle(360, 136, 40, 40, circle_color, 0.0)
    
    Graphics.end_frame(true)
end