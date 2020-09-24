text = """
  [$FF05] = $00   ; TIMA
  [$FF06] = $00   ; TMA
  [$FF07] = $00   ; TAC
  [$FF10] = $80   ; NR10
  [$FF11] = $BF   ; NR11
  [$FF12] = $F3   ; NR12
  [$FF14] = $BF   ; NR14
  [$FF16] = $3F   ; NR21
  [$FF17] = $00   ; NR22
  [$FF19] = $BF   ; NR24
  [$FF1A] = $7F   ; NR30
  [$FF1B] = $FF   ; NR31
  [$FF1C] = $9F   ; NR32
  [$FF1E] = $BF   ; NR33
  [$FF20] = $FF   ; NR41
  [$FF21] = $00   ; NR42
  [$FF22] = $00   ; NR43
  [$FF23] = $BF   ; NR44
  [$FF24] = $77   ; NR50
  [$FF25] = $F3   ; NR51
  [$FF26] = $F1   ; NR52
  [$FF40] = $91   ; LCDC
  [$FF42] = $00   ; SCY
  [$FF43] = $00   ; SCX
  [$FF45] = $00   ; LYC
  [$FF47] = $FC   ; BGP
  [$FF48] = $FF   ; OBP0
  [$FF49] = $FF   ; OBP1
  [$FF4A] = $00   ; WY
  [$FF4B] = $00   ; WX
  [$FFFF] = $00   ; IE
  """.strip().translate(str.maketrans('','', '[]$'))

lines = text.split('\n')
for line in lines:
    body, comment = (x.strip() for x in line.split(';'))
    lhs, rhs = (x.strip().lower() for x in body.split('='))
    # print(lhs, rhs, comment)
    print("cpu->memory[0x%s] = 0x%s; /* %s */" % (lhs, rhs, comment))
