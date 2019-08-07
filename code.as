.define sz = 5      
XYZ: .data 7, -57, 17, 18, 12, 31
STR: .string "absdasda"
MAIN: mov r1, XYZ[5]
      cmp #5, XYZ[sz]
