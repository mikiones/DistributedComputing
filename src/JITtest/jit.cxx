/* Testing the jit execution */
/* constructing code::

 int add1f(int i)
 {
 return i+1;
 }
 int foo()
 {
 return add1f(10)
 }
 */

/*
 and executing it using JIT
 */

/* llvm headers for jit */

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/JIT.h>

/* llvm headers for block buildier and manipulation*/

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

/* helpers */

#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"

/*dumping assembler to ostream*/
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>

/*rwiting / reading code*/
#include <llvm/Bitcode/ReaderWriter.h>

using namespace llvm;

int main()
{
    InitializeNativeTarget();
    LLVMContext con;

    /* crate test module */
    Module *mo = new Module("Test", con);

    /* create and inssert function entry into module */
    Function *f_add1f = cast < Function > (mo->getOrInsertFunction("add1", Type::getInt32Ty(con), Type::getInt32Ty(con), (Type *) 0));

    /* create code for function */
    BasicBlock *bb = BasicBlock::Create(con, "EntryBlock", f_add1f);
    IRBuilder <> builder(bb);

    /* geting pointer to constant 1 */
    Value *one = builder.getInt32(1);

    /* making sure function have arguments.. */
    assert(f_add1f->arg_begin() != f_add1f->arg_end());
    Argument *arg1 = f_add1f->arg_begin();
    arg1->setName("argument1");

    /* create instruction what add 2 values ito basic block(body if
       function) */
    Value *add = builder.CreateAdd(one, arg1);

    /* and return statment */

    builder.CreateRet(add);

    /* defining function entry foo */
    Function *f_foo = cast < Function > (mo->getOrInsertFunction("foo", Type::getInt32Ty(con), NULL));
bb = BasicBlock: :Create(con, "EntryBlock", f_foo);

    /* seting writing point for builder */
    builder.SetInsertPoint(bb);

    /* creating constant 10 */
    Value *ten = builder.getInt32(10);

    /* calling f_add1 from foo */
    CallInst *callFoo = builder.CreateCall(f_add1f, ten);
    callFoo->setTailCall(true);

    /* return instruction for foo */
    builder.CreateRet(callFoo);


    /* printing assemblylisting on out */
    //verifyModule(*mo, PrintMessageAction);
    //PassManager PM;
    //PM.add(createPrintModulePass(&outs()));
    //PM.run(*mo);

    /* creating JIT */

    ExecutionEngine *EE = EngineBuilder(mo).create();
    outs() << "created module: \n\n" << *mo;
    outs() << "Bitcode : \n\n";
    WriteBitcodeToFile(mo, outs());
    outs() << "\n\n runing foo: ";
    outs().flush();

std: :vector < GenericValue > noargs;
    GenericValue gv = EE->runFunction(f_foo, noargs);

    outs() << "resoults: " << gv.IntVal << "\n";
    EE->freeMachineCodeForFunction(f_foo);
    delete EE;

    llvm_shutdown();

    return 0;

};
