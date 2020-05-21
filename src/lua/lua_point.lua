function Start()
  print "Starting Light from LUA!"
  SetDrawMode("Triangles")

end

local speed = 0.1
function Update()
  Translate(0.0, 
            math.cos(os.clock()) * 5.0 + speed + 183.0, 
            0.0)
end