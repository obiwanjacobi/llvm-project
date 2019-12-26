//= Z80ELFObjetcWriter.h - Write ELF Object data -------------------*- C++ -*-//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef Z80ELFOBJECTWRITER_H
#define Z80ELFOBJECTWRITER_H

#include "Z80MCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

namespace llvm {

std::unique_ptr<MCObjectTargetWriter> createZ80ELFObjectWriter(uint8_t OSABI);

}   // end namespace
#endif // Z80ELFOBJECTWRITER_H