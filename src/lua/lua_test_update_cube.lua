function Start()
  print "Starting CUBE from LUA!"
  Rotate(0.0, 0.0, 0.0)
  AddComponent(0)
  SetGeometry("Sphere")
  SetDrawMode("Triangles")
end

local rotation = 0
function Update()
  print "Updating CUBE from LUA!"
  rotation = rotation + 0.01
  Rotate(rotation, 0.0, 0.0);
  Translate(math.sin(os.clock()) * 5.0, math.cos(os.clock()) * 5.0, 0.0)
end