//===-- Z80AsmPrinter.cpp - Z80 LLVM Assembly Printer ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to Z80 machine code.
//
//===----------------------------------------------------------------------===//

#include "Z80AsmPrinter.h"
#include "Z80.h"
#include "Z80MCInstLower.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/MC/MCInst.h"
using namespace llvm;

Z80AsmPrinter::Z80AsmPrinter(TargetMachine& TM, std::unique_ptr<MCStreamer> Streamer): 
  AsmPrinter(TM, std::move(Streamer)) {
}

void Z80AsmPrinter::EmitInstruction(const MachineInstr *MI)
{
  //Z80MCInstLower MCInstLowering(Mang, *MF, *this);
  Z80MCInstLower MCInstLowering(*MF, *this);

  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);
  OutStreamer->EmitInstruction(TmpInst, getSubtargetInfo());
}

//===----------------------------------------------------------------------===//
// Target Registry Stuff
//===----------------------------------------------------------------------===//

extern "C" void LLVMInitializeZ80AsmPrinter()
{
  RegisterAsmPrinter<Z80AsmPrinter> X(TheZ80Target);
}
