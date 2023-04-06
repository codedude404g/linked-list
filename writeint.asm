; writeint.asm

Divloop: lodd c10:
         push
         lodd sum:
         push
         DIV
         lodl 0
         stod sum:
         lodl 1
         insp 4 ; increaments the stack pointer
         push
         lodd ct:
         addd c1:
         stod ct:
         lodd sum:
         JZER Divdone:
         jump Divloop:
Divdone: lodd ct:
         JZER Divdonee:
         lodd ct:
         subd c1:
         stod ct:
         pop
         addd numoff:
         stod 4094
         call xbsywt:
         jump Divdone:
Divdonee: lodd c0:
        halt

overflow: loco str3:
          call prints:
         lodd neg:
         halt         ; this is where you would go to add the binums

