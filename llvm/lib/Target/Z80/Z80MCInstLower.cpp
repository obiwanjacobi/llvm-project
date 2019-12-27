//===-- Z80MCInstLower.cpp - Convert Z80 MachineInstr to an MCInst --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains code to lower Z80 MachineInstrs to their corresponding
// MCInst records.
//
//===----------------------------------------------------------------------===//

#include "Z80MCInstLower.h"
#include "Z80AsmPrinter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/IR/Mangler.h"
using namespace llvm;

Z80MCInstLower::Z80MCInstLower(const MachineFunction &mf, Z80AsmPrinter &asmprinter)
  : Ctx(mf.getContext()), MF(mf), TM(mf.getTarget()),
  MAI(*TM.getMCAsmInfo()), AsmPrinter(asmprinter)
{}

void Z80MCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const
{
  OutMI.setOpcode(MI->getOpcode());

  for (unsigned i = 0, e = MI->getNumOperands(); i != e; i++)
  {
    const MachineOperand &MO = MI->getOperand(i);

    MCOperand MCOp;
    switch (MO.getType())
    {
    default:
      MI->dump();
      llvm_unreachable("unknown operand type");
    case MachineOperand::MO_Register:
      // Ignore all implicit register operands
      if (MO.isImplicit()) continue;
      MCOp = MCOperand::createReg(MO.getReg());
      break;
    case MachineOperand::MO_Immediate:
      MCOp = MCOperand::createImm(MO.getImm());
      break;
    case MachineOperand::MO_MachineBasicBlock:
      MCOp = MCOperand::createExpr(MCSymbolRefExpr::create(
        MO.getMBB()->getSymbol(), Ctx));
      break;
    case MachineOperand::MO_GlobalAddress:
      MCOp = LowerSymbolOperand(MO, GetGlobalAddressSymbol(MO));
      break;
    case MachineOperand::MO_ExternalSymbol:
      MCOp = LowerSymbolOperand(MO, GetExternalSymbolSymbol(MO));
      break;
    case MachineOperand::MO_RegisterMask:
      // Ignore call clobbers.
      continue;
    }
    OutMI.addOperand(MCOp);
  }
}

MCOperand Z80MCInstLower::LowerSymbolOperand(const MachineOperand &MO,
  MCSymbol *Sym) const
{
  if (MO.getTargetFlags() != 0)
    llvm_unreachable("Unknown target flag on GV operand");

  const MCExpr *Expr = MCSymbolRefExpr::create(Sym, Ctx);
  return MCOperand::createExpr(Expr);
}

MCSymbol *Z80MCInstLower::GetGlobalAddressSymbol(
  const MachineOperand &MO) const
{
  if (MO.getTargetFlags() != 0)
    llvm_unreachable("Unknown target flag on GV operand");
  return AsmPrinter.getSymbol(MO.getGlobal());
}

MCSymbol *Z80MCInstLower::GetExternalSymbolSymbol(
  const MachineOperand &MO) const
{
  if (MO.getTargetFlags() != 0)
    llvm_unreachable("Unknown target flag on GV operand");
  return AsmPrinter.GetExternalSymbolSymbol(MO.getSymbolName());
}
