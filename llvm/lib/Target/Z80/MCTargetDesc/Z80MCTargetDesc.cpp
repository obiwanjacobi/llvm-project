//===-- Z80MCTargetDesc.cpp - Z80 Target Descriptions -----------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Z80 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "Z80MCTargetDesc.h"
#include "Z80MCAsmInfo.h"
#include "Z80InstPrinter.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Z80GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "Z80GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Z80GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createZ80MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitZ80MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createZ80MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitZ80MCRegisterInfo(X, Z80::PC);
  return X;
}

static MCSubtargetInfo *createZ80MCSubtargetInfo(const Triple &TT,
                       StringRef CPU, StringRef Features) {
    //MCSubtargetInfo *X = new MCSubtargetInfo();
    //InitZ80MCSubtargetInfo(X, TT, CPU, FS);
    return createZ80MCSubtargetInfoImpl(TT, CPU, Features);
}

static MCInstPrinter *createZ80MCInstPrinter(const Triple &T,
  unsigned SyntaxVariant, const MCAsmInfo &MAI, const MCInstrInfo &MII,
  const MCRegisterInfo &MRI) {

    return new Z80InstPrinter(MAI, MII, MRI);
}

static MCAsmInfo *createZ80MCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT, const MCTargetOptions &Options) {
  return new Z80MCAsmInfo(TT);
}

extern "C" void LLVMInitializeZ80TargetMC() {
  RegisterMCAsmInfoFn X(TheZ80Target, createZ80MCAsmInfo);

  TargetRegistry::RegisterMCInstrInfo(TheZ80Target, createZ80MCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(TheZ80Target, createZ80MCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(TheZ80Target, createZ80MCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(TheZ80Target, createZ80MCInstPrinter);
  TargetRegistry::RegisterMCCodeEmitter(TheZ80Target, createZ80MCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(TheZ80Target, createZ80AsmBackend);
  
  //TargetRegistry::RegisterAsmStreamer(TheZ80Target, createZ80AsmStreamer)
}
