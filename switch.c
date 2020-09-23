switch (opcode)
{
case 0x00: /* NOP */
	/*printf("%02x NOP\n", opcode);*/
	break;
	
case 0x01: /* LD BC, d16 */
	d16 = read16(cpu, cpu->pc);
	cpu->reg.wr.bc = d16;
	printf("%02x LD BC, d16\n", opcode);
	cpu->pc += 2;
	break;
	
case 0x02: /* LD (BC), A */
	write8(cpu, cpu->reg.wr.bc, cpu->reg.br.a);
	printf("%02x LD (BC), A\n", opcode);
	break;
	
case 0x03: /* INC BC */
	old_8reg = cpu->reg.wr.bc;
	cpu->reg.wr.bc += 1;
	printf("%02x INC BC\n", opcode);
	if (cpu->reg.wr.bc == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.bc))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x04: /* INC B */
	old_8reg = cpu->reg.br.b;
	cpu->reg.br.b += 1;
	printf("%02x INC B\n", opcode);
	if (cpu->reg.br.b == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.b))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x05: /* DEC B */
	old_8reg = cpu->reg.br.b;
	cpu->reg.br.b -= 1;
	/*printf("%02x DEC B\n", opcode);*/
	if (cpu->reg.br.b == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.b))
	    cpu->reg.flag.half_carry = true;
	
	/*assert(false); [> flags changed Z1H- <]*/
	break;
	
case 0x06: /* LD B, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.b = d8;
	/*printf("%02x LD B, d8\n", opcode);*/
	cpu->pc += 1;
	break;
	
case 0x07: /* RLCA */
	printf("%02x RLCA\n", opcode);
	assert(false);
	assert(false); /* flags changed 000C */
	break;
	
case 0x08: /* LD (a16), SP */
	a16 = read16(cpu, cpu->pc);
	write8(cpu, a16, cpu->sp);
	printf("%02x LD (a16), SP\n", opcode);
	cpu->pc += 2;
	break;
	
case 0x09: /* ADD HL, BC */
	printf("%02x ADD HL, BC\n", opcode);
	assert(false);
	assert(false); /* flags changed -0HC */
	break;
	
case 0x0A: /* LD A, (BC) */
	deref = read8(cpu, cpu->reg.wr.bc);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (BC)\n", opcode);
	break;
	
case 0x0B: /* DEC BC */
	old_8reg = cpu->reg.wr.bc;
	cpu->reg.wr.bc -= 1;
	printf("%02x DEC BC\n", opcode);
	if (cpu->reg.wr.bc == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.bc))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x0C: /* INC C */
	old_8reg = cpu->reg.br.c;
	cpu->reg.br.c += 1;
	printf("%02x INC C\n", opcode);
	if (cpu->reg.br.c == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.c))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x0D: /* DEC C */
	old_8reg = cpu->reg.br.c;
	cpu->reg.br.c -= 1;
	/*printf("%02x DEC C\n", opcode);*/
	if (cpu->reg.br.c == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.c))
	    cpu->reg.flag.half_carry = true;
	
	/*assert(false); [> flags changed Z1H- <]*/
	break;
	
case 0x0E: /* LD C, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.c = d8;
	/*printf("%02x LD C, d8\n", opcode);*/
	cpu->pc += 1;
	break;
	
case 0x0F: /* RRCA */
	printf("%02x RRCA\n", opcode);
	assert(false);
	assert(false); /* flags changed 000C */
	break;
	
case 0x10: /* STOP */
	printf("%02x STOP\n", opcode);
	assert(false);
	break;
	
case 0x11: /* LD DE, d16 */
	d16 = read16(cpu, cpu->pc);
	cpu->reg.wr.de = d16;
	printf("%02x LD DE, d16\n", opcode);
	cpu->pc += 2;
	break;
	
case 0x12: /* LD (DE), A */
	write8(cpu, cpu->reg.wr.de, cpu->reg.br.a);
	printf("%02x LD (DE), A\n", opcode);
	break;
	
case 0x13: /* INC DE */
	old_8reg = cpu->reg.wr.de;
	cpu->reg.wr.de += 1;
	printf("%02x INC DE\n", opcode);
	if (cpu->reg.wr.de == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.de))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x14: /* INC D */
	old_8reg = cpu->reg.br.d;
	cpu->reg.br.d += 1;
	printf("%02x INC D\n", opcode);
	if (cpu->reg.br.d == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.d))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x15: /* DEC D */
	old_8reg = cpu->reg.br.d;
	cpu->reg.br.d -= 1;
	printf("%02x DEC D\n", opcode);
	if (cpu->reg.br.d == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.d))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x16: /* LD D, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.d = d8;
	printf("%02x LD D, d8\n", opcode);
	cpu->pc += 1;
	break;
	
case 0x17: /* RLA */
	printf("%02x RLA\n", opcode);
	assert(false);
	assert(false); /* flags changed 000C */
	break;
	
case 0x18: /* JR r8 */
	r8 = read8(cpu, cpu->pc);
	cpu->pc += r8;
	printf("%02x JR r8\n", opcode);
	assert(false);
	break;
	
case 0x19: /* ADD HL, DE */
	printf("%02x ADD HL, DE\n", opcode);
	assert(false);
	assert(false); /* flags changed -0HC */
	break;
	
case 0x1A: /* LD A, (DE) */
	deref = read8(cpu, cpu->reg.wr.de);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (DE)\n", opcode);
	break;
	
case 0x1B: /* DEC DE */
	old_8reg = cpu->reg.wr.de;
	cpu->reg.wr.de -= 1;
	printf("%02x DEC DE\n", opcode);
	if (cpu->reg.wr.de == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.de))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x1C: /* INC E */
	old_8reg = cpu->reg.br.e;
	cpu->reg.br.e += 1;
	printf("%02x INC E\n", opcode);
	if (cpu->reg.br.e == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.e))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x1D: /* DEC E */
	old_8reg = cpu->reg.br.e;
	cpu->reg.br.e -= 1;
	printf("%02x DEC E\n", opcode);
	if (cpu->reg.br.e == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.e))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x1E: /* LD E, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.e = d8;
	printf("%02x LD E, d8\n", opcode);
	cpu->pc += 1;
	break;
	
case 0x1F: /* RRA */
	printf("%02x RRA\n", opcode);
	assert(false);
	assert(false); /* flags changed 000C */
	break;
	
case 0x20: /* JR NZ, r8 */
	r8 = read8(cpu, cpu->pc);
	if (!cpu->reg.flag.zero)
	{
	    cpu->pc += r8;
	}
	else
	{
	    cpu->pc += 1;
	}
	/*printf("%02x JR NZ, r8\n", opcode);*/
	/*assert(false);*/
	break;
	
case 0x21: /* LD HL, d16 */
	d16 = read16(cpu, cpu->pc);
	cpu->reg.wr.hl = d16;
	/*printf("%02x LD HL, d16\n", opcode);*/
	cpu->pc += 2;
	break;
	
case 0x22: /* LD (HL+), A */
	write8(cpu, cpu->reg.wr.hl++, cpu->reg.br.a);
	printf("%02x LD (HL+), A\n", opcode);
	break;
	
case 0x23: /* INC HL */
	old_8reg = cpu->reg.wr.hl;
	cpu->reg.wr.hl += 1;
	printf("%02x INC HL\n", opcode);
	if (cpu->reg.wr.hl == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.hl))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x24: /* INC H */
	old_8reg = cpu->reg.br.h;
	cpu->reg.br.h += 1;
	printf("%02x INC H\n", opcode);
	if (cpu->reg.br.h == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.h))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x25: /* DEC H */
	old_8reg = cpu->reg.br.h;
	cpu->reg.br.h -= 1;
	printf("%02x DEC H\n", opcode);
	if (cpu->reg.br.h == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.h))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x26: /* LD H, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.h = d8;
	printf("%02x LD H, d8\n", opcode);
	cpu->pc += 1;
	break;
	
case 0x27: /* DAA */
	printf("%02x DAA\n", opcode);
	assert(false);
	assert(false); /* flags changed Z-0C */
	break;
	
case 0x28: /* JR Z, r8 */
	r8 = read8(cpu, cpu->pc);
	if (cpu->reg.flag.zero)
	{
	    cpu->pc += r8;
	}
	else
	{
	    cpu->pc += 1;
	}
	printf("%02x JR Z, r8\n", opcode);
	assert(false);
	break;
	
case 0x29: /* ADD HL, HL */
	printf("%02x ADD HL, HL\n", opcode);
	assert(false);
	assert(false); /* flags changed -0HC */
	break;
	
case 0x2A: /* LD A, (HL+) */
	deref = read8(cpu, cpu->reg.wr.hl++);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (HL+)\n", opcode);
	break;
	
case 0x2B: /* DEC HL */
	old_8reg = cpu->reg.wr.hl;
	cpu->reg.wr.hl -= 1;
	printf("%02x DEC HL\n", opcode);
	if (cpu->reg.wr.hl == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.hl))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x2C: /* INC L */
	old_8reg = cpu->reg.br.l;
	cpu->reg.br.l += 1;
	printf("%02x INC L\n", opcode);
	if (cpu->reg.br.l == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.l))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x2D: /* DEC L */
	old_8reg = cpu->reg.br.l;
	cpu->reg.br.l -= 1;
	printf("%02x DEC L\n", opcode);
	if (cpu->reg.br.l == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.l))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x2E: /* LD L, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.l = d8;
	printf("%02x LD L, d8\n", opcode);
	cpu->pc += 1;
	break;
	
case 0x2F: /* CPL */
	printf("%02x CPL\n", opcode);
	assert(false);
	assert(false); /* flags changed -11- */
	break;
	
case 0x30: /* JR NC, r8 */
	r8 = read8(cpu, cpu->pc);
	if (!cpu->reg.flag.carry)
	{
	    cpu->pc += r8;
	}
	else
	{
	    cpu->pc += 1;
	}
	printf("%02x JR NC, r8\n", opcode);
	assert(false);
	break;
	
case 0x31: /* LD SP, d16 */
	d16 = read16(cpu, cpu->pc);
	cpu->sp = d16;
	printf("%02x LD SP, d16\n", opcode);
	cpu->pc += 2;
	break;
	
case 0x32: /* LD (HL), A */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.a);
	/*printf("%02x LD (HL), A\n", opcode);*/
	break;
	
case 0x33: /* INC SP */
	old_8reg = cpu->sp;
	cpu->sp += 1;
	printf("%02x INC SP\n", opcode);
	if (cpu->sp == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->sp))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x34: /* INC (HL) */
	old_8reg = cpu->reg.wr.hl;
	cpu->reg.wr.hl += 1;
	printf("%02x INC (HL)\n", opcode);
	if (cpu->reg.wr.hl == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.hl))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x35: /* DEC (HL) */
	old_8reg = cpu->reg.wr.hl;
	cpu->reg.wr.hl -= 1;
	printf("%02x DEC (HL)\n", opcode);
	if (cpu->reg.wr.hl == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.wr.hl))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x36: /* LD (HL), d8 */
	d8 = read8(cpu, cpu->pc);
	write8(cpu, cpu->reg.wr.hl, d8);
	printf("%02x LD (HL), d8\n", opcode);
	cpu->pc += 1;
	break;
	
case 0x37: /* SCF */
	printf("%02x SCF\n", opcode);
	assert(false);
	assert(false); /* flags changed -001 */
	break;
	
case 0x38: /* JR C, r8 */
	r8 = read8(cpu, cpu->pc);
	if (cpu->reg.flag.carry)
	{
	    cpu->pc += r8;
	}
	else
	{
	    cpu->pc += 1;
	}
	printf("%02x JR C, r8\n", opcode);
	assert(false);
	break;
	
case 0x39: /* ADD HL, SP */
	printf("%02x ADD HL, SP\n", opcode);
	assert(false);
	assert(false); /* flags changed -0HC */
	break;
	
case 0x3A: /* LD A, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (HL)\n", opcode);
	break;
	
case 0x3B: /* DEC SP */
	old_8reg = cpu->sp;
	cpu->sp -= 1;
	printf("%02x DEC SP\n", opcode);
	if (cpu->sp == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->sp))
	    cpu->reg.flag.half_carry = true;
	
	break;
	
case 0x3C: /* INC A */
	old_8reg = cpu->reg.br.a;
	cpu->reg.br.a += 1;
	printf("%02x INC A\n", opcode);
	if (cpu->reg.br.a == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.a))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z0H- */
	break;
	
case 0x3D: /* DEC A */
	old_8reg = cpu->reg.br.a;
	cpu->reg.br.a -= 1;
	printf("%02x DEC A\n", opcode);
	if (cpu->reg.br.a == 0)
	    cpu->reg.flag.zero = true;
	
	cpu->reg.flag.add_or_sub = true;
	
	if(bit4(old_8reg) != bit4(cpu->reg.br.a))
	    cpu->reg.flag.half_carry = true;
	
	assert(false); /* flags changed Z1H- */
	break;
	
case 0x3E: /* LD A, d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.a = d8;
	/*printf("%02x LD A, d8\n", opcode);*/
	cpu->pc += 1;
	break;
	
case 0x3F: /* CCF */
	printf("%02x CCF\n", opcode);
	assert(false);
	assert(false); /* flags changed -00C */
	break;
	
case 0x40: /* LD B, B */
	cpu->reg.br.b = cpu->reg.br.b;
	printf("%02x LD B, B\n", opcode);
	break;
	
case 0x41: /* LD B, C */
	cpu->reg.br.b = cpu->reg.br.c;
	printf("%02x LD B, C\n", opcode);
	break;
	
case 0x42: /* LD B, D */
	cpu->reg.br.b = cpu->reg.br.d;
	printf("%02x LD B, D\n", opcode);
	break;
	
case 0x43: /* LD B, E */
	cpu->reg.br.b = cpu->reg.br.e;
	printf("%02x LD B, E\n", opcode);
	break;
	
case 0x44: /* LD B, H */
	cpu->reg.br.b = cpu->reg.br.h;
	printf("%02x LD B, H\n", opcode);
	break;
	
case 0x45: /* LD B, L */
	cpu->reg.br.b = cpu->reg.br.l;
	printf("%02x LD B, L\n", opcode);
	break;
	
case 0x46: /* LD B, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.b = deref;
	printf("%02x LD B, (HL)\n", opcode);
	break;
	
case 0x47: /* LD B, A */
	cpu->reg.br.b = cpu->reg.br.a;
	printf("%02x LD B, A\n", opcode);
	break;
	
case 0x48: /* LD C, B */
	cpu->reg.br.c = cpu->reg.br.b;
	printf("%02x LD C, B\n", opcode);
	break;
	
case 0x49: /* LD C, C */
	cpu->reg.br.c = cpu->reg.br.c;
	printf("%02x LD C, C\n", opcode);
	break;
	
case 0x4A: /* LD C, D */
	cpu->reg.br.c = cpu->reg.br.d;
	printf("%02x LD C, D\n", opcode);
	break;
	
case 0x4B: /* LD C, E */
	cpu->reg.br.c = cpu->reg.br.e;
	printf("%02x LD C, E\n", opcode);
	break;
	
case 0x4C: /* LD C, H */
	cpu->reg.br.c = cpu->reg.br.h;
	printf("%02x LD C, H\n", opcode);
	break;
	
case 0x4D: /* LD C, L */
	cpu->reg.br.c = cpu->reg.br.l;
	printf("%02x LD C, L\n", opcode);
	break;
	
case 0x4E: /* LD C, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.c = deref;
	printf("%02x LD C, (HL)\n", opcode);
	break;
	
case 0x4F: /* LD C, A */
	cpu->reg.br.c = cpu->reg.br.a;
	printf("%02x LD C, A\n", opcode);
	break;
	
case 0x50: /* LD D, B */
	cpu->reg.br.d = cpu->reg.br.b;
	printf("%02x LD D, B\n", opcode);
	break;
	
case 0x51: /* LD D, C */
	cpu->reg.br.d = cpu->reg.br.c;
	printf("%02x LD D, C\n", opcode);
	break;
	
case 0x52: /* LD D, D */
	cpu->reg.br.d = cpu->reg.br.d;
	printf("%02x LD D, D\n", opcode);
	break;
	
case 0x53: /* LD D, E */
	cpu->reg.br.d = cpu->reg.br.e;
	printf("%02x LD D, E\n", opcode);
	break;
	
case 0x54: /* LD D, H */
	cpu->reg.br.d = cpu->reg.br.h;
	printf("%02x LD D, H\n", opcode);
	break;
	
case 0x55: /* LD D, L */
	cpu->reg.br.d = cpu->reg.br.l;
	printf("%02x LD D, L\n", opcode);
	break;
	
case 0x56: /* LD D, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.d = deref;
	printf("%02x LD D, (HL)\n", opcode);
	break;
	
case 0x57: /* LD D, A */
	cpu->reg.br.d = cpu->reg.br.a;
	printf("%02x LD D, A\n", opcode);
	break;
	
case 0x58: /* LD E, B */
	cpu->reg.br.e = cpu->reg.br.b;
	printf("%02x LD E, B\n", opcode);
	break;
	
case 0x59: /* LD E, C */
	cpu->reg.br.e = cpu->reg.br.c;
	printf("%02x LD E, C\n", opcode);
	break;
	
case 0x5A: /* LD E, D */
	cpu->reg.br.e = cpu->reg.br.d;
	printf("%02x LD E, D\n", opcode);
	break;
	
case 0x5B: /* LD E, E */
	cpu->reg.br.e = cpu->reg.br.e;
	printf("%02x LD E, E\n", opcode);
	break;
	
case 0x5C: /* LD E, H */
	cpu->reg.br.e = cpu->reg.br.h;
	printf("%02x LD E, H\n", opcode);
	break;
	
case 0x5D: /* LD E, L */
	cpu->reg.br.e = cpu->reg.br.l;
	printf("%02x LD E, L\n", opcode);
	break;
	
case 0x5E: /* LD E, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.e = deref;
	printf("%02x LD E, (HL)\n", opcode);
	break;
	
case 0x5F: /* LD E, A */
	cpu->reg.br.e = cpu->reg.br.a;
	printf("%02x LD E, A\n", opcode);
	break;
	
case 0x60: /* LD H, B */
	cpu->reg.br.h = cpu->reg.br.b;
	printf("%02x LD H, B\n", opcode);
	break;
	
case 0x61: /* LD H, C */
	cpu->reg.br.h = cpu->reg.br.c;
	printf("%02x LD H, C\n", opcode);
	break;
	
case 0x62: /* LD H, D */
	cpu->reg.br.h = cpu->reg.br.d;
	printf("%02x LD H, D\n", opcode);
	break;
	
case 0x63: /* LD H, E */
	cpu->reg.br.h = cpu->reg.br.e;
	printf("%02x LD H, E\n", opcode);
	break;
	
case 0x64: /* LD H, H */
	cpu->reg.br.h = cpu->reg.br.h;
	printf("%02x LD H, H\n", opcode);
	break;
	
case 0x65: /* LD H, L */
	cpu->reg.br.h = cpu->reg.br.l;
	printf("%02x LD H, L\n", opcode);
	break;
	
case 0x66: /* LD H, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.h = deref;
	printf("%02x LD H, (HL)\n", opcode);
	break;
	
case 0x67: /* LD H, A */
	cpu->reg.br.h = cpu->reg.br.a;
	printf("%02x LD H, A\n", opcode);
	break;
	
case 0x68: /* LD L, B */
	cpu->reg.br.l = cpu->reg.br.b;
	printf("%02x LD L, B\n", opcode);
	break;
	
case 0x69: /* LD L, C */
	cpu->reg.br.l = cpu->reg.br.c;
	printf("%02x LD L, C\n", opcode);
	break;
	
case 0x6A: /* LD L, D */
	cpu->reg.br.l = cpu->reg.br.d;
	printf("%02x LD L, D\n", opcode);
	break;
	
case 0x6B: /* LD L, E */
	cpu->reg.br.l = cpu->reg.br.e;
	printf("%02x LD L, E\n", opcode);
	break;
	
case 0x6C: /* LD L, H */
	cpu->reg.br.l = cpu->reg.br.h;
	printf("%02x LD L, H\n", opcode);
	break;
	
case 0x6D: /* LD L, L */
	cpu->reg.br.l = cpu->reg.br.l;
	printf("%02x LD L, L\n", opcode);
	break;
	
case 0x6E: /* LD L, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.l = deref;
	printf("%02x LD L, (HL)\n", opcode);
	break;
	
case 0x6F: /* LD L, A */
	cpu->reg.br.l = cpu->reg.br.a;
	printf("%02x LD L, A\n", opcode);
	break;
	
case 0x70: /* LD (HL), B */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.b);
	printf("%02x LD (HL), B\n", opcode);
	break;
	
case 0x71: /* LD (HL), C */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.c);
	printf("%02x LD (HL), C\n", opcode);
	break;
	
case 0x72: /* LD (HL), D */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.d);
	printf("%02x LD (HL), D\n", opcode);
	break;
	
case 0x73: /* LD (HL), E */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.e);
	printf("%02x LD (HL), E\n", opcode);
	break;
	
case 0x74: /* LD (HL), H */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.h);
	printf("%02x LD (HL), H\n", opcode);
	break;
	
case 0x75: /* LD (HL), L */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.l);
	printf("%02x LD (HL), L\n", opcode);
	break;
	
case 0x76: /* HALT */
	printf("%02x HALT\n", opcode);
	assert(false);
	break;
	
case 0x77: /* LD (HL), A */
	write8(cpu, cpu->reg.wr.hl, cpu->reg.br.a);
	printf("%02x LD (HL), A\n", opcode);
	break;
	
case 0x78: /* LD A, B */
	cpu->reg.br.a = cpu->reg.br.b;
	printf("%02x LD A, B\n", opcode);
	break;
	
case 0x79: /* LD A, C */
	cpu->reg.br.a = cpu->reg.br.c;
	printf("%02x LD A, C\n", opcode);
	break;
	
case 0x7A: /* LD A, D */
	cpu->reg.br.a = cpu->reg.br.d;
	printf("%02x LD A, D\n", opcode);
	break;
	
case 0x7B: /* LD A, E */
	cpu->reg.br.a = cpu->reg.br.e;
	printf("%02x LD A, E\n", opcode);
	break;
	
case 0x7C: /* LD A, H */
	cpu->reg.br.a = cpu->reg.br.h;
	printf("%02x LD A, H\n", opcode);
	break;
	
case 0x7D: /* LD A, L */
	cpu->reg.br.a = cpu->reg.br.l;
	printf("%02x LD A, L\n", opcode);
	break;
	
case 0x7E: /* LD A, (HL) */
	deref = read8(cpu, cpu->reg.wr.hl);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (HL)\n", opcode);
	break;
	
case 0x7F: /* LD A, A */
	cpu->reg.br.a = cpu->reg.br.a;
	printf("%02x LD A, A\n", opcode);
	break;
	
case 0x80: /* ADD A, B */
	printf("%02x ADD A, B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x81: /* ADD A, C */
	printf("%02x ADD A, C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x82: /* ADD A, D */
	printf("%02x ADD A, D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x83: /* ADD A, E */
	printf("%02x ADD A, E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x84: /* ADD A, H */
	printf("%02x ADD A, H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x85: /* ADD A, L */
	printf("%02x ADD A, L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x86: /* ADD A, (HL) */
	printf("%02x ADD A, (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x87: /* ADD A, A */
	printf("%02x ADD A, A\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x88: /* ADC A, B */
	printf("%02x ADC A, B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x89: /* ADC A, C */
	printf("%02x ADC A, C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8A: /* ADC A, D */
	printf("%02x ADC A, D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8B: /* ADC A, E */
	printf("%02x ADC A, E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8C: /* ADC A, H */
	printf("%02x ADC A, H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8D: /* ADC A, L */
	printf("%02x ADC A, L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8E: /* ADC A, (HL) */
	printf("%02x ADC A, (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x8F: /* ADC A, A */
	printf("%02x ADC A, A\n", opcode);
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0x90: /* SUB B */
	printf("%02x SUB B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x91: /* SUB C */
	printf("%02x SUB C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x92: /* SUB D */
	printf("%02x SUB D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x93: /* SUB E */
	printf("%02x SUB E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x94: /* SUB H */
	printf("%02x SUB H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x95: /* SUB L */
	printf("%02x SUB L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x96: /* SUB (HL) */
	printf("%02x SUB (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x97: /* SUB A */
	printf("%02x SUB A\n", opcode);
	assert(false);
	assert(false); /* flags changed 11HC */
	break;
	
case 0x98: /* SBC A, B */
	printf("%02x SBC A, B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x99: /* SBC A, C */
	printf("%02x SBC A, C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9A: /* SBC A, D */
	printf("%02x SBC A, D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9B: /* SBC A, E */
	printf("%02x SBC A, E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9C: /* SBC A, H */
	printf("%02x SBC A, H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9D: /* SBC A, L */
	printf("%02x SBC A, L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9E: /* SBC A, (HL) */
	printf("%02x SBC A, (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0x9F: /* SBC A, A */
	printf("%02x SBC A, A\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xA0: /* AND B */
	printf("%02x AND B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA1: /* AND C */
	printf("%02x AND C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA2: /* AND D */
	printf("%02x AND D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA3: /* AND E */
	printf("%02x AND E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA4: /* AND H */
	printf("%02x AND H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA5: /* AND L */
	printf("%02x AND L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA6: /* AND (HL) */
	printf("%02x AND (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA7: /* AND A */
	printf("%02x AND A\n", opcode);
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xA8: /* XOR B */
	cpu->reg.br.a ^= cpu->reg.br.b;
	printf("%02x XOR B\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xA9: /* XOR C */
	cpu->reg.br.a ^= cpu->reg.br.c;
	printf("%02x XOR C\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAA: /* XOR D */
	cpu->reg.br.a ^= cpu->reg.br.d;
	printf("%02x XOR D\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAB: /* XOR E */
	cpu->reg.br.a ^= cpu->reg.br.e;
	printf("%02x XOR E\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAC: /* XOR H */
	cpu->reg.br.a ^= cpu->reg.br.h;
	printf("%02x XOR H\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAD: /* XOR L */
	cpu->reg.br.a ^= cpu->reg.br.l;
	printf("%02x XOR L\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAE: /* XOR (HL) */
	cpu->reg.br.a ^= cpu->reg.wr.hl;
	printf("%02x XOR (HL)\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xAF: /* XOR A */
	cpu->reg.br.a ^= cpu->reg.br.a;
	/*printf("%02x XOR A\n", opcode);*/
	/*assert(false); [> flags changed 1000 <]*/
	break;
	
case 0xB0: /* OR B */
	cpu->reg.br.a |= cpu->reg.br.b;
	printf("%02x OR B\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB1: /* OR C */
	cpu->reg.br.a |= cpu->reg.br.c;
	printf("%02x OR C\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB2: /* OR D */
	cpu->reg.br.a |= cpu->reg.br.d;
	printf("%02x OR D\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB3: /* OR E */
	cpu->reg.br.a |= cpu->reg.br.e;
	printf("%02x OR E\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB4: /* OR H */
	cpu->reg.br.a |= cpu->reg.br.h;
	printf("%02x OR H\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB5: /* OR L */
	cpu->reg.br.a |= cpu->reg.br.l;
	printf("%02x OR L\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB6: /* OR (HL) */
	cpu->reg.br.a |= cpu->reg.wr.hl;
	printf("%02x OR (HL)\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB7: /* OR A */
	cpu->reg.br.a |= cpu->reg.br.a;
	printf("%02x OR A\n", opcode);
	assert(false); /* flags changed Z000 */
	break;
	
case 0xB8: /* CP B */
	printf("%02x CP B\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xB9: /* CP C */
	printf("%02x CP C\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBA: /* CP D */
	printf("%02x CP D\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBB: /* CP E */
	printf("%02x CP E\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBC: /* CP H */
	printf("%02x CP H\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBD: /* CP L */
	printf("%02x CP L\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBE: /* CP (HL) */
	printf("%02x CP (HL)\n", opcode);
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xBF: /* CP A */
	printf("%02x CP A\n", opcode);
	assert(false);
	assert(false); /* flags changed 11HC */
	break;
	
case 0xC0: /* RET NZ */
	printf("%02x RET NZ\n", opcode);
	assert(false);
	break;
	
case 0xC1: /* POP BC */
	printf("%02x POP BC\n", opcode);
	assert(false);
	break;
	
case 0xC2: /* JP NZ, a16 */
	a16 = read16(cpu, cpu->pc);
	if (!cpu->reg.flag.zero)
	{
	    cpu->pc = a16;
	}
	else
	{
	    cpu->pc += 2;
	}
	printf("%02x JP NZ, a16\n", opcode);
	break;
	
case 0xC3: /* JP a16 */
	a16 = read16(cpu, cpu->pc);
	cpu->pc = a16;
	/*printf("%02x JP a16\n", opcode);*/
	break;
	
case 0xC4: /* CALL NZ, a16 */
	a16 = read16(cpu, cpu->pc);
	printf("%02x CALL NZ, a16\n", opcode);
	cpu->pc += 2;
	assert(false);
	break;
	
case 0xC5: /* PUSH BC */
	printf("%02x PUSH BC\n", opcode);
	assert(false);
	break;
	
case 0xC6: /* ADD A, d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x ADD A, d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0xC7: /* RST 00H */
	printf("%02x RST 00H\n", opcode);
	assert(false);
	break;
	
case 0xC8: /* RET Z */
	printf("%02x RET Z\n", opcode);
	assert(false);
	break;
	
case 0xC9: /* RET */
	printf("%02x RET\n", opcode);
	assert(false);
	break;
	
case 0xCA: /* JP Z, a16 */
	a16 = read16(cpu, cpu->pc);
	if (cpu->reg.flag.zero)
	{
	    cpu->pc = a16;
	}
	else
	{
	    cpu->pc += 2;
	}
	printf("%02x JP Z, a16\n", opcode);
	break;
	
case 0xCB: /* PREFIX */
	printf("%02x PREFIX\n", opcode);
	assert(false);
	break;
	
case 0xCC: /* CALL Z, a16 */
	a16 = read16(cpu, cpu->pc);
	printf("%02x CALL Z, a16\n", opcode);
	cpu->pc += 2;
	assert(false);
	break;
	
case 0xCD: /* CALL a16 */
	a16 = read16(cpu, cpu->pc);
	printf("%02x CALL a16\n", opcode);
	cpu->pc += 2;
	assert(false);
	break;
	
case 0xCE: /* ADC A, d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x ADC A, d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z0HC */
	break;
	
case 0xCF: /* RST 08H */
	printf("%02x RST 08H\n", opcode);
	assert(false);
	break;
	
case 0xD0: /* RET NC */
	printf("%02x RET NC\n", opcode);
	assert(false);
	break;
	
case 0xD1: /* POP DE */
	printf("%02x POP DE\n", opcode);
	assert(false);
	break;
	
case 0xD2: /* JP NC, a16 */
	a16 = read16(cpu, cpu->pc);
	if (!cpu->reg.flag.carry)
	{
	    cpu->pc = a16;
	}
	else
	{
	    cpu->pc += 2;
	}
	printf("%02x JP NC, a16\n", opcode);
	break;
	
case 0xD3: /* ILLEGAL_D3 */
	printf("%02x ILLEGAL_D3\n", opcode);
	assert(false);
	break;
	
case 0xD4: /* CALL NC, a16 */
	a16 = read16(cpu, cpu->pc);
	printf("%02x CALL NC, a16\n", opcode);
	cpu->pc += 2;
	assert(false);
	break;
	
case 0xD5: /* PUSH DE */
	printf("%02x PUSH DE\n", opcode);
	assert(false);
	break;
	
case 0xD6: /* SUB d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x SUB d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xD7: /* RST 10H */
	printf("%02x RST 10H\n", opcode);
	assert(false);
	break;
	
case 0xD8: /* RET C */
	printf("%02x RET C\n", opcode);
	assert(false);
	break;
	
case 0xD9: /* RETI */
	printf("%02x RETI\n", opcode);
	assert(false);
	break;
	
case 0xDA: /* JP C, a16 */
	a16 = read16(cpu, cpu->pc);
	if (cpu->reg.flag.carry)
	{
	    cpu->pc = a16;
	}
	else
	{
	    cpu->pc += 2;
	}
	printf("%02x JP C, a16\n", opcode);
	break;
	
case 0xDB: /* ILLEGAL_DB */
	printf("%02x ILLEGAL_DB\n", opcode);
	assert(false);
	break;
	
case 0xDC: /* CALL C, a16 */
	a16 = read16(cpu, cpu->pc);
	printf("%02x CALL C, a16\n", opcode);
	cpu->pc += 2;
	assert(false);
	break;
	
case 0xDD: /* ILLEGAL_DD */
	printf("%02x ILLEGAL_DD\n", opcode);
	assert(false);
	break;
	
case 0xDE: /* SBC A, d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x SBC A, d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xDF: /* RST 18H */
	printf("%02x RST 18H\n", opcode);
	assert(false);
	break;
	
case 0xE0: /* LDH (a8), A */
	a8 = read8(cpu, cpu->pc);
	printf("%02x LDH (a8), A\n", opcode);
	cpu->pc += 1;
	assert(false);
	break;
	
case 0xE1: /* POP HL */
	printf("%02x POP HL\n", opcode);
	assert(false);
	break;
	
case 0xE2: /* LD (C), A */
	write8(cpu, cpu->reg.br.c, cpu->reg.br.a);
	printf("%02x LD (C), A\n", opcode);
	break;
	
case 0xE3: /* ILLEGAL_E3 */
	printf("%02x ILLEGAL_E3\n", opcode);
	assert(false);
	break;
	
case 0xE4: /* ILLEGAL_E4 */
	printf("%02x ILLEGAL_E4\n", opcode);
	assert(false);
	break;
	
case 0xE5: /* PUSH HL */
	printf("%02x PUSH HL\n", opcode);
	assert(false);
	break;
	
case 0xE6: /* AND d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x AND d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z010 */
	break;
	
case 0xE7: /* RST 20H */
	printf("%02x RST 20H\n", opcode);
	assert(false);
	break;
	
case 0xE8: /* ADD SP, r8 */
	r8 = read8(cpu, cpu->pc);
	printf("%02x ADD SP, r8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed 00HC */
	break;
	
case 0xE9: /* JP HL */
	cpu->pc = cpu->reg.wr.hl;
	printf("%02x JP HL\n", opcode);
	break;
	
case 0xEA: /* LD (a16), A */
	a16 = read16(cpu, cpu->pc);
	write8(cpu, a16, cpu->reg.br.a);
	printf("%02x LD (a16), A\n", opcode);
	cpu->pc += 2;
	break;
	
case 0xEB: /* ILLEGAL_EB */
	printf("%02x ILLEGAL_EB\n", opcode);
	assert(false);
	break;
	
case 0xEC: /* ILLEGAL_EC */
	printf("%02x ILLEGAL_EC\n", opcode);
	assert(false);
	break;
	
case 0xED: /* ILLEGAL_ED */
	printf("%02x ILLEGAL_ED\n", opcode);
	assert(false);
	break;
	
case 0xEE: /* XOR d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.a ^= d8;
	printf("%02x XOR d8\n", opcode);
	cpu->pc += 1;
	assert(false); /* flags changed Z000 */
	break;
	
case 0xEF: /* RST 28H */
	printf("%02x RST 28H\n", opcode);
	assert(false);
	break;
	
case 0xF0: /* LDH A, (a8) */
	a8 = read8(cpu, cpu->pc);
	printf("%02x LDH A, (a8)\n", opcode);
	cpu->pc += 1;
	assert(false);
	break;
	
case 0xF1: /* POP AF */
	printf("%02x POP AF\n", opcode);
	assert(false);
	assert(false); /* flags changed ZNHC */
	break;
	
case 0xF2: /* LD A, (C) */
	deref = read8(cpu, cpu->reg.br.c);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (C)\n", opcode);
	break;
	
case 0xF3: /* DI */
	printf("%02x DI\n", opcode);
	assert(false);
	break;
	
case 0xF4: /* ILLEGAL_F4 */
	printf("%02x ILLEGAL_F4\n", opcode);
	assert(false);
	break;
	
case 0xF5: /* PUSH AF */
	printf("%02x PUSH AF\n", opcode);
	assert(false);
	break;
	
case 0xF6: /* OR d8 */
	d8 = read8(cpu, cpu->pc);
	cpu->reg.br.a |= d8;
	printf("%02x OR d8\n", opcode);
	cpu->pc += 1;
	assert(false); /* flags changed Z000 */
	break;
	
case 0xF7: /* RST 30H */
	printf("%02x RST 30H\n", opcode);
	assert(false);
	break;
	
case 0xF8: /* LD HL, SP+ */
	cpu->reg.wr.hl = cpu->sp++;
	printf("%02x LD HL, SP+\n", opcode);
	assert(false); /* flags changed 00HC */
	break;
	
case 0xF9: /* LD SP, HL */
	cpu->sp = cpu->reg.wr.hl;
	printf("%02x LD SP, HL\n", opcode);
	break;
	
case 0xFA: /* LD A, (a16) */
	a16 = read16(cpu, cpu->pc);
	deref = read8(cpu, a16);
	cpu->reg.br.a = deref;
	printf("%02x LD A, (a16)\n", opcode);
	cpu->pc += 2;
	break;
	
case 0xFB: /* EI */
	printf("%02x EI\n", opcode);
	assert(false);
	break;
	
case 0xFC: /* ILLEGAL_FC */
	printf("%02x ILLEGAL_FC\n", opcode);
	assert(false);
	break;
	
case 0xFD: /* ILLEGAL_FD */
	printf("%02x ILLEGAL_FD\n", opcode);
	assert(false);
	break;
	
case 0xFE: /* CP d8 */
	d8 = read8(cpu, cpu->pc);
	printf("%02x CP d8\n", opcode);
	cpu->pc += 1;
	assert(false);
	assert(false); /* flags changed Z1HC */
	break;
	
case 0xFF: /* RST 38H */
	printf("%02x RST 38H\n", opcode);
	assert(false);
	break;
	
default:
	break;
}
