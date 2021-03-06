#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/PassManager.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

Module *makeLLVMModule();

int main(int argc, char **argv)
{
    Module *Mod = makeLLVMModule();

    verifyModule(*Mod, PrintMessageAction);

    PassManager PM;
    PM.add(createPrintModulePass(&outs()));
    PM.run(*Mod);

    delete Mod;
    return 0;
}

Module *makeLLVMModule()
{
    //Module Construction
    LLVMContext & gc = getGlobalContext();
    Module *mod = new Module("test", getGlobalContext());
    Constant *c = mod->getOrInsertFunction("mul_add",
				 /* ret type */ IntegerType::get(gc, 32),
				     /* args */ IntegerType::get(gc, 32),
					   IntegerType::get(gc, 32),
					   IntegerType::get(gc, 32),
			        /* varargs terminated with null */ NULL);

    Function *mul_add = cast < Function > (c);
mul_add->setCallingConv(CallingConv: :C);
Function: :arg_iterator args = mul_add->arg_begin();
    Value *x = args++;
    x->setName("x");
    Value *y = args++;
    y->setName("y");
    Value *z = args++;
    z->setName("z");
    BasicBlock *block = BasicBlock::Create(getGlobalContext(), "entry", mul_add);
    IRBuilder <> builder(block);
    Value *tmp = builder.CreateBinOp(Instruction::Mul,
				     x, y, "tmp");
    Value *tmp2 = builder.CreateBinOp(Instruction::Add,
				      tmp, z, "tmp2");

    builder.CreateRet(tmp2);

    return mod;
}
