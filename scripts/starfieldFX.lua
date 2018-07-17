--
-- Star Field FX routines
--

SCREEN_WIDTH=320
SCREEN_HEIGHT=240

-- ========= PUBLIC API ================
function drawStarFieldFrame(screenIter)
--	for i = 1, size do
-- no for loops in this LVM

local i


--print( speed .."\n" )



i=1
while i <= size do

--		x = width / 2 + starfield[i].x / starfield[i].z
--		y = height / 2 + starfield[i].y / starfield[i].z
--		lcdrect(x,y,1,1, 1, 0)


 		--starfield[i].z = starfield[i].z - speed
		if starfield[i].z <= speed then 
		  --print("NEW STAR \n")
		  createStar(i)
		else
		  starfield[i].z = starfield[i].z - speed
		end
		
		x = width / 2 + starfield[i].x / starfield[i].z
		y = height / 2 + starfield[i].y / starfield[i].z
--		
--	if i=1 then
--	  print( "x="..x.." y=".. y .." z=".. starfield[i].z  .."\n" )
--        print( "w="..width.." h="..height.."\n" )
--	end	
		
 		if x < 0 or y < 0 or x >= width or y >= height then
              		--print("NEW STAR (2) [".. i .."] \n")
 			createStar(i)
 		else
 			-- --screen:pixel(x, y, white)
 			lcdrect(x,y,1,1, 1, 1)
		end

i=i+1

 	end
end
-- ========= PUBLIC API ================

--size = 200
size = 50
zMax = 5
--speed = 0.1
speed = 0.5

width = SCREEN_WIDTH 
height = SCREEN_HEIGHT

starfield = @{}
--math.randomseed(os.time())

function createStar(i)
	starfield[i] = @{}
	--starfield[i].x = math.random(2*width) - width
	starfield[i].x = rnd(2*width) - width
	starfield[i].y = rnd(2*height) - height
	starfield[i].z = zMax
end

local i
--for i = 1, size do
i=1
while i <= size do
	createStar(i)
	starfield[i].z = rnd(zMax)
i=i+1
end

