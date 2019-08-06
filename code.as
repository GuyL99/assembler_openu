.define sz = 5      
.extern Y
XYZ: .data 7, -57, 17, 18, 12, 31
STR: .string "absdasda"
MAIN: mov r1, XYZ[sz]
      cmp #5, XYZ[sz]
