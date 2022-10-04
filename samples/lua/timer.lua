timer = Timer.create()

while(QuickGame.running()) do
    delta = timer:delta()
    print(tostring(delta))
end