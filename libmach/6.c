/*
 * x86-amd64 definition
 */
#include <lib9.h>
#include <bio.h>
#include "ureg6.h"
#include "mach.h"

#define	REGOFF(x)	(uvlong)(&((struct Ureg *) 0)->x)

#define PC		REGOFF(pc)
#define SP		REGOFF(sp)
#define	AX		REGOFF(ax)

#define	REGSIZE		sizeof(struct Ureg)
#define FP_CTLS(x)	(REGSIZE+2*(x))
#define FP_CTL(x)	(REGSIZE+4*(x))
#define FP_REG(x)	(FP_CTL(8)+16*(x))
#define XM_REG(x)	(FP_CTL(8)+8*16+16*(x))

#define	FPREGSIZE	512	/* TO DO? currently only 0x1A0 used */

Reglist amd64reglist[] = {
	{"R15",		REGOFF(r15),	RINT, 'Y'},
	{"R14",		REGOFF(r14),	RINT, 'Y'},
	{"R13",		REGOFF(r13),	RINT, 'Y'},
	{"R12",		REGOFF(r12),	RINT, 'Y'},
	{"R11",		REGOFF(r11),	RINT, 'Y'},
	{"R10",		REGOFF(r10),	RINT, 'Y'},
	{"R9",		REGOFF(r9),	RINT, 'Y'},
	{"R8",		REGOFF(r8),	RINT, 'Y'},
	{"DI",		REGOFF(di),	RINT, 'X'},
	{"SI",		REGOFF(si),	RINT, 'Y'},
	{"BP",		REGOFF(bp),	RINT, 'Y'},
	{"BX",		REGOFF(bx),	RINT, 'Y'},
	{"DX",		REGOFF(dx),	RINT, 'Y'},
	{"CX",		REGOFF(cx),	RINT, 'Y'},
	{"AX",		REGOFF(ax),	RINT, 'Y'},
	{"GS",		REGOFF(gs),	RINT, 'Y'},
	{"FS",		REGOFF(fs),	RINT, 'Y'},
	{"ES",		REGOFF(es),	RINT, 'Y'},
	{"DS",		REGOFF(ds),	RINT, 'Y'},
	{"TRAP",	REGOFF(trap), 	RINT, 'Y'},
	{"ECODE",	REGOFF(ecode),	RINT, 'Y'},
	{"PC",		PC,		RINT, 'Y'},
	{"CS",		REGOFF(cs),	RINT, 'Y'},
	{"EFLAGS",	REGOFF(flags),	RINT, 'Y'},
	{"SP",		SP,		RINT, 'Y'},
	{"SS",		REGOFF(ss),	RINT, 'Y'},

	{"FCW",		FP_CTLS(0),	RFLT, 'x'},
	{"FSW",		FP_CTLS(1),	RFLT, 'x'},
	{"FTW",		FP_CTLS(2),	RFLT, 'x'},
	{"FOP",		FP_CTLS(3),	RFLT, 'x'},
	{"FPC",		FP_CTL(2),	RFLT, 'Y'},
	{"RDP",		FP_CTL(4),	RFLT, 'Y'},
	{"MXCSR",		FP_CTL(6),	RFLT, 'X'},
	{"MXCSRMSK",	FP_CTL(7),	RFLT, 'X'},
	{"M0",		FP_REG(0),	RFLT, 'F'},	/* assumes double */
	{"M1",		FP_REG(1),	RFLT, 'F'},
	{"M2",		FP_REG(2),	RFLT, 'F'},
	{"M3",		FP_REG(3),	RFLT, 'F'},
	{"M4",		FP_REG(4),	RFLT, 'F'},
	{"M5",		FP_REG(5),	RFLT, 'F'},
	{"M6",		FP_REG(6),	RFLT, 'F'},
	{"M7",		FP_REG(7),	RFLT, 'F'},
	{"X0",		XM_REG(0),	RFLT, 'F'},	/* assumes double */
	{"X1",		XM_REG(1),	RFLT, 'F'},
	{"X2",		XM_REG(2),	RFLT, 'F'},
	{"X3",		XM_REG(3),	RFLT, 'F'},
	{"X4",		XM_REG(4),	RFLT, 'F'},
	{"X5",		XM_REG(5),	RFLT, 'F'},
	{"X6",		XM_REG(6),	RFLT, 'F'},
	{"X7",		XM_REG(7),	RFLT, 'F'},
	{"X8",		XM_REG(8),	RFLT, 'F'},
	{"X9",		XM_REG(9),	RFLT, 'F'},
	{"X10",		XM_REG(10),	RFLT, 'F'},
	{"X11",		XM_REG(11),	RFLT, 'F'},
	{"X12",		XM_REG(12),	RFLT, 'F'},
	{"X13",		XM_REG(13),	RFLT, 'F'},
	{"X14",		XM_REG(14),	RFLT, 'F'},
	{"X15",		XM_REG(15),	RFLT, 'F'},
	{"X16",		XM_REG(16),	RFLT, 'F'},
/*
	{"F0",		FP_REG(7),	RFLT, '3'},
	{"F1",		FP_REG(6),	RFLT, '3'},
	{"F2",		FP_REG(5),	RFLT, '3'},
	{"F3",		FP_REG(4),	RFLT, '3'},
	{"F4",		FP_REG(3),	RFLT, '3'},
	{"F5",		FP_REG(2),	RFLT, '3'},
	{"F6",		FP_REG(1),	RFLT, '3'},
	{"F7",		FP_REG(0),	RFLT, '3'},
*/
	{  0 }
};

Mach mamd64=
{
	"amd64",
	MI386,		/* machine type */	/* TO DO */
	amd64reglist,	/* register list */
	REGSIZE,	/* size of registers in bytes */
	FPREGSIZE,	/* size of fp registers in bytes */
	"PC",		/* name of PC */
	"SP",		/* name of SP */
	0,		/* link register */
	"setSB",	/* static base register name (bogus anyways) */
	0,		/* static base register value */
	0x1000,		/* page size */
	0x80100000,	/* kernel base */	/* TO DO: uvlong or vlong */
	0,		/* kernel text mask */
	1,		/* quantization of pc */
	8,		/* szaddr */
	4,		/* szreg */
	4,		/* szfloat */
	8,		/* szdouble */
};
