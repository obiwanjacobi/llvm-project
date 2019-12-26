//===-- Z80AsmBackend.cpp - Z80 Assembler Backend -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/Z80MCTargetDesc.h"
#include "MCTargetDesc/Z80FixupKinds.h"
#include "MCTargetDesc/Z80ELFObjectWriter.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCMachObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/Endian.h"

using namespace llvm;

namespace {
  class Z80AsmBackend : public MCAsmBackend {
  public:
    Z80AsmBackend(const Target &T)
      : MCAsmBackend(support::endianness::little) {}

    unsigned getNumFixupKinds() const {
      return Z80::NumTargetFixupKinds;
    }

    const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const {
      if (Kind >= FirstTargetFixupKind) assert("Invalid kind!");

      return MCAsmBackend::getFixupKindInfo(Kind);
    }

    /// \name Target Relaxation Interfaces
    /// @{
    /// Check whether the given instruction may need relaxation.
    ///
    /// \param Inst - The instruction to test.
    /// \param STI - The MCSubtargetInfo in effect when the instruction was
    /// encoded.
    bool mayNeedRelaxation(const MCInst &Inst,
                                  const MCSubtargetInfo &STI) const {
        // FIXME: implement?
        return false;
    }

    /// Simple predicate for targets where !Resolved implies requiring relaxation
    bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                                      const MCRelaxableFragment *DF,
                                      const MCAsmLayout &Layout) const {
        // FIXME: implement?
        return false;
    }

    /// Relax the instruction in the given fragment to the next wider instruction.
    ///
    /// \param Inst The instruction to relax, which may be the same as the
    /// output.
    /// \param STI the subtarget information for the associated instruction.
    /// \param [out] Res On return, the relaxed instruction.
    void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                                  MCInst &Res) const {
    }

    /// Apply the \p Value for given \p Fixup into the provided data fragment, at
    /// the offset specified by the fixup and following the fixup kind as
    /// appropriate. Errors (such as an out of range fixup value) should be
    /// reported via \p Ctx.
    /// The  \p STI is present only for fragments of type MCRelaxableFragment and
    /// MCDataFragment with hasInstructions() == true.
    void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                            const MCValue &Target, MutableArrayRef<char> Data,
                            uint64_t Value, bool IsResolved,
                            const MCSubtargetInfo *STI) const {
    }

    bool writeNopData(raw_ostream &OS, uint64_t Count) const {
      for (uint64_t i = 0; i < Count; i++) {
        OS.write(0);
      }
      return true;
    }

    std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const {
      return createZ80ELFObjectWriter(0);
    }

  }; // end class Z80AsmBackend
} // end namespace

MCAsmBackend *llvm::createZ80AsmBackend(const Target &T,
                                        const MCSubtargetInfo &STI,
                                        const MCRegisterInfo &MRI,
                                        const MCTargetOptions &Options) {
  return new Z80AsmBackend(T);
}
