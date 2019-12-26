//===-- Z80ELFObjectWriter.cpp - Z80 ELF Object Writer --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Z80ELFObjectWriter.h"
#include "Z80MCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
    class Z80ELFObjectWriter : public MCELFObjectTargetWriter {
        public:
        Z80ELFObjectWriter(uint8_t OSABI)
            : MCELFObjectTargetWriter(/*Is64Bit*/ false, OSABI, 
                                    280, // Z80 ELF Machine Type !! NOT OFFICIAL !!
                                    /*HasRelocationAddend*/ false) {}
        ~Z80ELFObjectWriter() override {}

        unsigned getRelocType(MCContext &Ctx, const MCValue &Target,
                                const MCFixup &Fixup, bool IsPCRel) const override 
        {
            return 0;
        }
    };
} // namespace


std::unique_ptr<MCObjectTargetWriter>
llvm::createZ80ELFObjectWriter(uint8_t OSABI) {
  return std::make_unique<Z80ELFObjectWriter>(OSABI);
}
