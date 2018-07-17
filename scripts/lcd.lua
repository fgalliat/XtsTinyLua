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

