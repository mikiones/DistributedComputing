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

    Mod->dump();

    return 0;
}


Module *makeLLVMModule()
{
llvm: : LLVMContext & context = llvm: :getGlobalContext();
llvm: : Module * module = new llvm: :Module("stack", context);
llvm: :IRBuilder <> builder(context);

llvm: : FunctionType * funcType = llvm: : FunctionType: :get(builder.getVoidTy(), false);
llvm: :Function * mainFunc =
llvm: : Function: : Create(funcType, llvm: : Function: :ExternalLinkage, "main", module);
llvm: : BasicBlock * entry = llvm: : BasicBlock: :Create(context, "entrypoint", mainFunc);
    /* creating and initialize stack array holder */
    ArrayType *at = ArrayType::get(Type::getInt32Ty(context), 32);
    GlobalVariable *stack = new GlobalVariable(*module, at, false, GlobalVariable::LinkOnceAnyLinkage, Constant::getNullValue(at), "__stack__");


    GlobalVariable *stackIndex = new GlobalVariable(*module, Type::getInt64Ty(context), false, GlobalVariable::LinkOnceAnyLinkage, Constant::getNullValue(Type::getInt64Ty(context)), "__stack_index__");

    builder.SetInsertPoint(entry);

    /* load ptr of index element stacs array Value * index=
       builder.CreateLoad(stackIndex,"index");
       builder.CreateGEP(stack,index,"elementptr"); */


    Value *index = builder.CreateLoad(stackIndex, "index");
    Value *incra = builder.getInt64(1);
    Value *retc = builder.CreateAdd(index, incra, "newIndex");
    builder.CreateStore(retc, stackIndex);

    //builder.CreateLoad(el, "element");



    //
	builder.CreateRetVoid();



    return module;
}
