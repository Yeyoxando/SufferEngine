function Start()

end

local rotation_ = 0
local speed_ = 10
function Rotation()
  rotation_ = rotation_ + 0.01
  if rotation_>=(2 * 3.141592) then rotation_ = 0 end
  Rotate(0.0, rotation_, 0.0)
end

local x = 0
local speed = 0
function Update()
  Rotation()
  x = x + 0.001
end