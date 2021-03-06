#ifndef _pin_magic_
#define _pin_magic_

#include "Arduino.h"

// This header file serves two purposes:
//
// 1) Isolate non-portable MCU port- and pin-specific identifiers and
// operations so the library code itself remains somewhat agnostic
// (PORTs and pin numbers are always referenced through macros).
//
// 2) GCC doesn't always respect the "inline" keyword, so this is a
// ham-fisted manner of forcing the issue to minimize function calls.
// This sometimes makes the library a bit bigger than before, but fast++.
// However, because they're macros, we need to be SUPER CAREFUL about
// parameters -- for example, write8(x) may expand to multiple PORT
// writes that all refer to x, so it needs to be a constant or fixed
// variable and not something like *ptr++ (which, after macro
// expansion, may increment the pointer repeatedly and run off into
// la-la land). Macros also give us fine-grained control over which
// operations are inlined on which boards (balancing speed against
// available program space).
// When using the TFT shield, control and data pins exist in set physical
// locations, but the ports and bitmasks corresponding to each vary among
// boards. A separate set of pin definitions is given for each supported
// board type.
// When using the TFT breakout board, control pins are configurable but
// the data pins are still fixed -- making every data pin configurable
// would be much too slow. The data pin layouts are not the same between
// the shield and breakout configurations -- for the latter, pins were
// chosen to keep the tutorial wiring manageable more than making optimal
// use of ports and bitmasks. So there's a second set of pin definitions
// given for each supported board.
// Shield pin usage:

// Pixel read operations require a minimum 400 nS delay from RD_ACTIVE
// to polling the input pins. At 16 MHz, one machine cycle is 62.5 nS.
// This code burns 7 cycles (437.5 nS) doing nothing; the RJMPs are
// equivalent to two NOPs each, final NOP burns the 7th cycle, and the
// last line is a radioactive mutant emoticon.
/*#define DELAY7 \
asm volatile( \
"rjmp .+0" "\n\t" \
"rjmp .+0" "\n\t" \
"rjmp .+0" "\n\t" \
"nop" "\n" \
::);*/
// As part of the inline control, macros reference other macros...if any
// of these are left undefined, an equivalent function version (non-inline)
// is declared later. The Uno has a moderate amount of program space, so
// only write8() is inlined -- that one provides the most performance
// benefit, but unfortunately also generates the most bloat. This is
// why only certain cases are inlined for each board.
//Uno w/Breakout board
// Uno dig. pin : 7 6 5 4 3 2 9 8
// Maple /pin : PD7 PD6 PD5 PD4 PD3 PD2 PB1 PB0


#define write8inline(d) { \ 
  GPIOB_BASE->BSRR =  0b11111100000000000000000000000000 | ( d & 252) << 8 ; \      
  GPIOA_BASE->BSRR =  0b11000000000000000000000000000000 | ( d & 3 )  << 14; \ 
  WR_STROBE; }
  
#define read8inline(result) { \
RD_ACTIVE; \
RD_IDLE; }
//DELAY7; \
//result = (PIND & B11111100) | (PINB & B00000011); \


#define setWriteDirInline() { /*DDRD |= B11111100; DDRB |= B00000011;*/ }       //??
#define setReadDirInline() { /*DDRD &= ~B11111100; DDRB &= ~B00000011;*/ }      //??

#define write8 write8inline

#define read8 read8inline

#define setWriteDir setWriteDirInline

#define setReadDir setReadDirInline

#define writeRegister8 writeRegister8inline
#define writeRegister16 writeRegister16inline
#define writeRegisterPair writeRegisterPairInline

// When using the TFT breakout board, control pins are configurable.
#define RD_ACTIVE                   *rdport &= ~rdmask;             //  AVR spceific code *rdPort &= rdPinUnset active low ???
#define RD_IDLE                     *rdport |= rdmask;              //  AVR specific code *rdPort |= rdPinSet
#define WR_ACTIVE                   *wrport &= ~wrmask
#define WR_IDLE                     *wrport |= wrmask;
#define CD_COMMAND                  *cdport &= ~cdmask
#define CD_DATA                     *cdport |= cdmask;
#define CS_ACTIVE                   *csport &= ~csmask;
#define CS_IDLE                     *csport |= csmask;

// Data read and write strobes, ~2 instructions and always inline
#define RD_STROBE { RD_ACTIVE; RD_IDLE; }
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }

// These higher-level operations are usually functionalized,
// except on Mega where's there's gobs and gobs of program space.
// Set value of TFT register: 8-bit address, 8-bit value

#define writeRegister8inline(a, d) { \
CD_COMMAND; write8(a); CD_DATA; write8(d); }
// Set value of TFT register: 16-bit address, 16-bit value
// See notes at top about macro expansion, hence hi & lo temp vars

#define writeRegister16inline(a, d) { \
uint8_t hi, lo; \
hi = (a) >> 8; lo = (a); CD_COMMAND; write8(hi); write8(lo); \
hi = (d) >> 8; lo = (d); CD_DATA ; write8(hi); write8(lo); }

// Set value of 2 TFT registers: Two 8-bit addresses (hi & lo), 16-bit value
#define writeRegisterPairInline(aH, aL, d) { \
uint8_t hi = (d) >> 8, lo = (d); \
CD_COMMAND; write8(aH); CD_DATA; write8(hi); \
CD_COMMAND; write8(aL); CD_DATA; write8(lo); }

#endif

