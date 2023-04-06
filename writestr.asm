; writestr.asm

prints:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer newl:
        stod 4094
        push
        subd c255:
        jneg newl:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump prints:
newl:    lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
        retn

numoff: 48
nxtchr: 0
numptr: binum1:
binum1: 0
binum2: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
neg:    -1      ; this is for negative val
c10:    10
c255:   255
sum:    0
numcnt: 1
c0:     0
pstr1:  0
ct:     0
str1:   "Please enter a 1-5 digit number followed by enter"
str2:    "THE SUM OF THESE INTEGERS IS: "
str3:    "OVERFLOW, NO SUM POSSIBLE:"

