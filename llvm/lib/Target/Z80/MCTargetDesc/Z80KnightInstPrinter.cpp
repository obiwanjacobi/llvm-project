//===-- Z80KnightInstPrinter.cpp - Convert Z80 MCInst to assembly syntax --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class prints an Z80 MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "Z80KnightInstPrinter.h"
#include "Z80.h"
#include "Z80InstrInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

// Include the auto-generated portion of the assembler writer
#include "Z80GenAsmWriter1.inc"
//#define GET_INSTRINFO_ENUM
//#include "Z80GenInstrInfo.inc"

void Z80KnightInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const
{
  OS << getRegisterName(RegNo);
}

void Z80KnightInstPrinter::printInst(const MCInst *MI, raw_ostream &O,
  StringRef Annot, const MCSubtargetInfo &STI)
{
    if (MI->getOpcode() == Z80::LD16ri && 
            MI->getOperand(1).isExpr() && 
            MI->getOperand(1).getExpr()->getKind() == MCExpr::SymbolRef) {
        //Use the Knight macro for ld
        O << "\tkld(";
        printOperand(MI, 0, O);
        O << ", ";
        printOperand(MI, 1, O);
        O << ")";
    }else if (MI->getOpcode() == Z80::CALL && 
            MI->getOperand(0).isExpr() && 
            MI->getOperand(0).getExpr()->getKind() == MCExpr::SymbolRef) {
        
        //Use the Knight macro for call
        O << "\tkcall(";
        printOperand(MI, 0, O);
        O << ")";
        
    }else if (MI->getOpcode() == Z80::JP && 
            MI->getOperand(0).isExpr() && 
            MI->getOperand(0).getExpr()->getKind() == MCExpr::SymbolRef) {
        
        O << "\tkjp(";
        printOperand(MI, 0, O);
        O << ")";
        
    }else if (MI->getOpcode() == Z80::JPCC && 
            MI->getOperand(0).isExpr() && 
            MI->getOperand(0).getExpr()->getKind() == MCExpr::SymbolRef) {
        
        O << "\tkjp(";
        printCCOperand(MI, 1, O); 
        O << ", ";
        printOperand(MI, 0, O);
        O << ")";
        
    }else {
        printInstruction(MI, O);
    }
    printAnnotation(O, Annot);
}

void Z80KnightInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
  raw_ostream &O)
{
  const MCOperand &Op = MI->getOperand(OpNo);

  if (Op.isReg())
    O << getRegisterName(Op.getReg());
  else if (Op.isImm())
    O << Op.getImm();
  else if (Op.isExpr())
    O << *Op.getExpr();
  else assert(0 && "unknown operand kind in printOperand");
}

void Z80KnightInstPrinter::printCCOperand(const MCInst *MI, unsigned OpNo,
  raw_ostream &O)
{
  const MCOperand &Op = MI->getOperand(OpNo);
  assert(Op.isImm() && "Invalid CC operand");

  const char *cond;

  switch (Op.getImm())
  {
  default:
    llvm_unreachable("Invalid CC operand");
  case Z80::COND_NZ:
    cond = "nz";
    break;
  case Z80::COND_Z:
    cond = "z";
    break;
  case Z80::COND_NC:
    cond = "nc";
    break;
  case Z80::COND_C:
    cond = "c";
    break;
  case Z80::COND_PO:
    cond = "po";
    break;
  case Z80::COND_PE:
    cond = "pe";
    break;
  case Z80::COND_P:
    cond = "p";
    break;
  case Z80::COND_M:
    cond = "m";
    break;
  }
  O << cond;
}

void Z80KnightInstPrinter::printXMemOperand(const MCInst *MI, unsigned OpNo,
  raw_ostream &O)
{
  const MCOperand &Base = MI->getOperand(OpNo);
  const MCOperand &Disp = MI->getOperand(OpNo+1);

  if (Base.isReg())
  {
    assert(Disp.isImm() && "Expected immediate in displacement field");
    int64_t Offset = Disp.getImm();
    O << getRegisterName(Base.getReg());
    if (Offset >= 0) O << '+';
    O << Offset;
  }
  else llvm_unreachable("Invalid operand");
}
