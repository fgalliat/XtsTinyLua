print("A.1\n")

lcdsetup()

--lcdbpp("/BLAST.BPP")
lcdpct("/CARO.PCT", 0, 0)
lcdpct("", 160, 0)
lcdpct("",   0, 128)
lcdpct("", 160, 128)


lcdprint( "coucou\n" )
lcdprint( "".. 3.14 .."\n" )

lcdrect( 10, 10, 128, 64, 1, 8 )
lcdrect( 10, 10, 128, 64, 0, 6 )

delay(1000)

--print("A.2\n")
--dofile("scripts/starfieldFX.lua")
--print("A.3\n")

local e
e=1
print("A.4\n")

print("A.5\n")

lcdcls()
while e <= 40 do
--print("A.5.1\n")

--lcdblitt(0)
--  lcdcls() 
  lcdbackg(1, 45+e, 90, 45+e, 6); -- draw "Balls", GREEN
--lcdblitt(2)

  e = e+1
end


e=1
lcdcls()
while e <= 100 do
--print("A.5.1\n")

--lcdblitt(0)
--  lcdcls() 
  --drawStarFieldFrame(e)
  lcdbackg(2, 50, 100, 1, 8); -- draw "Starfield", 50starts, 100% speed, 1, PINK
--lcdblitt(2)

  e = e+1
end
print("A.7\n")

