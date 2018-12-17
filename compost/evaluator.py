from ctypes import CFUNCTYPE, c_int32

import llvmlite.binding as llvm

from .generator import LLVMCodeGenerator
from .parse import ast as astree
from .parser import Parser


class Evaluator:
    def __init__(self):
        llvm.initialize()
        llvm.initialize_native_target()
        llvm.initialize_native_asmparser()
        llvm.initialize_native_asmprinter()

        self.generator = LLVMCodeGenerator()
        self.target = llvm.Target.from_default_triple()

    def evaluate(self, codestr, optimize=True, llvmdump=False):
        ast, _ = Parser().parse_stream(codestr)
        self.generator.generate_code(ast)

        if llvmdump:
            print('========= Unoptimized LLVM IR')
            print(str(self.generator.module))

        if not (isinstance(ast, astree.Function) and ast.is_anonymous()):
            return None

        llvmmod = llvm.parse_assembly(str(self.generator.module))

        if optimize:
            pmb = llvm.create_pass_manager_builder()
            pmb.opt_level = 2
            pm = llvm.create_module_pass_manager()
            pmb.populate(pm)
            pm.run(llvmmod)

            if llvmdump:
                print('========== Optimized LLVM IR')
                print(str(llvmmod))

        target_machine = self.target.create_target_machine()
        with llvm.create_mcjit_compiler(llvmmod, target_machine) as ee:
            ee.finalize_object()

            if llvmdump:
                print('========== Michine code')
                print(target_machine.emit_assembly(llvmmod))

            fptr = CFUNCTYPE(c_int32)(ee.get_function_address(ast.proto.name))

            result = fptr(4, 7)
            return result