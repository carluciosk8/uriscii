/*

  (c) 1998 Claudionor Jose Nunes Coelho Junior

 */

#ifndef _SIM_H_
#define _SIM_H_

#define SIGNAL int

#define AND2(out,in1,in2) out=in1&in2
#define AND3(out,in1,in2,in3) out=in1&in2&in3
#define NAND2(out,in1,in2) out=!(in1&in2)
#define NAND3(out,in1,in2,in3) out=!(in1&in2&in3)
#define OR2(out,in1,in2) out=in1|in2
#define OR3(out,in1,in2,in3) out=in1|in2|in3
#define NOR2(out,in1,in2) out=!(in1|in2)
#define NOR3(out,in1,in2,in3) out=!(in1|in2|in3)
#define XOR2(out,in1,in2) out=in1^in2
#define XOR3(out,in1,in2,in3) out=in1^in2^in3
#define MUX2(out,in0,in1,cont) out=(cont == 0)?in0:in1
#define LATCH(out,in) out=in
#define NOT(out,in) out=!in
#define BUF(out,in) out=in

#endif
