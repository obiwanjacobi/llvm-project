//===-- Z80TargetObjectFile.h - Z80 Object Files --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
//
//===----------------------------------------------------------------------===//

#ifndef Z80TARGETLOWERINGOBJECTFILE_H
#define Z80TARGETLOWERINGOBJECTFILE_H

#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
    class Z80TargetLoweringObjectFile : public TargetLoweringObjectFileELF {

    };
}

#endif  // Z80TARGETLOWERINGOBJECTFILE_H