#include "llvm/ADT/APInt.h"
#include "llvm/IR/ConstantRange.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/NoFolder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace llvm;
using namespace std;

static LLVMContext C;
static IRBuilder<NoFolder> Builder(C);
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
static vector<Value*> mutables(10);
static Value *zero = ConstantInt::get(C, APInt(64, 0));
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;
bool integerOverflow = false;
int  gLineOffset = 0;
int  gOffset = 0;
bool use_select = false;


Value* parseExpression(string tab);
void skipSpaces(string tab);

void usage(void) {
  printf("executable <input file.calc>\r\n");
  return;
}

char getChar() {
  return gCurValue;
}

void nextChar(void) {
  if (!cin.eof()) {
    gCurValue = cin.get();
    gLineOffset++;
    gOffset++;
  } else {
    gCurValue = EOF;
  }
} 

char getnextChar() {
  nextChar();
  return gCurValue;
}

bool accept(char c) {
  if (getChar() == c) {
    nextChar();
    return true;
  }
  return false;
}

bool check(char c) {
  if (getChar() == c) {
    return true;
  }
  return false;
}

string getContext() {
  string context;
  getline(cin, context);
  return context;
}

void printError(int lineno) {
  printf ("%d:Invalid statement at LineNo:%d:%d - %c%s",
           lineno,
           gLineNo, gLineOffset, getChar(), getContext().c_str());
  exit(1);
}

void printError(int lineno, const char *c) {
  printf("%d:Unable to compile due to error \"%s\" at Line: %d Offset:%d \r\n",
      lineno,
      c, gLineNo, gLineOffset);
  printf("Remaining Code: %c%s", getChar(), getContext().c_str());
  exit(1);
}

void parseComment(string tab) {
  char ch;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  while (getnextChar() != '\n');
  //Skip \n
  ch = getnextChar();
  gLineNo++;
  gLineOffset = 1;
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
}

Value* parseArgs(string tab) {
  char errmsg[50];
  int i;
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  //Consume a
  if (accept('a')) {
    for (i = 0; i < gArgsLen; i++) {
      if (accept('0' + (i - 0))) { //Change from int to char
        result = gArgValues[i];
        break;
      }  
    }
    if (i == gArgsLen) {
      sprintf(errmsg, "Invalid argument (a%c) used in the program", 
              getChar());
      printError(__LINE__, errmsg);
    }
  } else {
    printError(__LINE__);
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseMutables(string tab) {
  char errmsg[50];
  int i = 0;
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  //Consume m
  if (accept('m')) {
    for (; i < mutables.size(); i++) {
      if (accept('0' + (i - 0))) { //Change from int to char
        //result = Builder.CreateLoad(mutables[i]);
        result = mutables[i];
        break;
      }  
    }
  } else {
    printError(__LINE__, "Expecting a Mutable variable");
  }

  if (i == mutables.size()) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(__LINE__, errmsg);
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Function* createDivWithOverFlow(string tab) {
  std::map<int, Value *> divArgs;
  Value *didOverflow = NULL, *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  std::vector<Type *> TwoInts(2, Type::getInt64Ty(C));
  Type *retTypes[] = {Type::getInt64Ty(C), Type::getInt1Ty(C)};
  StructType* retType = StructType::get(C, ArrayRef<Type *>(retTypes, 2)); 

  FunctionType *FT = FunctionType::get(retType, TwoInts, false);
  Function *F = Function::Create(FT, Function::ExternalLinkage,
                    "sdiv_with_overflow", &*M);
  BasicBlock *BB = BasicBlock::Create(C, "entry", F);
  Builder.SetInsertPoint(BB);

  divArgs.clear();
  int argCount = 0;
  for (auto &Arg : F->args()) { 
    divArgs[argCount++] = &Arg;
  }

  didOverflow = Builder.CreateAnd(
                        Builder.CreateICmpEQ(divArgs[0], 
                                ConstantInt::get(Type::getInt64Ty(C), 
                                                 APInt::getSignedMinValue(64))),
                        Builder.CreateICmpEQ(divArgs[1],
                                ConstantInt::get(Type::getInt64Ty(C),
                                                 APInt(64, -1, true/*isSigned*/))),
                        "oper1 == IntMIN and oper2 == -1");
  didOverflow = Builder.CreateOr(didOverflow, 
                        Builder.CreateICmpEQ(divArgs[1],
                                ConstantInt::get(Type::getInt64Ty(C), 
                                                 APInt::getNullValue(64))),
                        "or oper2 == 0");
  result = Builder.CreateSDiv(divArgs[0], divArgs[1], "divtmp");
  Value *res =  ConstantStruct::get(retType, result, didOverflow, NULL);
  Builder.CreateRet(res);
  verifyFunction(*F);

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return F;
}

void createCallToTrap(int pos, string tab) {
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  string fName = "overflow_fail";
  Function *F = M->getFunction(fName); 

  //Check if the function is already present. Then return, else add
  if (F == NULL) {
    std::vector<Type *> OneInt(1, Type::getInt64Ty(C));
    FunctionType *FT = FunctionType::get(Type::getInt64Ty(C), OneInt, false);
    F = Function::Create(FT, Function::ExternalLinkage,
                     fName, &*M);
  }
  Value *position[1] = {ConstantInt::get(Type::getInt64Ty(C), pos)}; 
  Builder.CreateCall(F, ArrayRef<Value *>(position, 1), "calltrap");
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
}

Value* parseArithmeticOperationWithOverflowCheck(char oper, string tab) {
  int operatorPosition = gOffset - 1;
  Value* result = NULL, *didOverflow, *oper1, *oper2;
  Function *overflowCheckOper = NULL;
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept(oper) == false) {
    printError(__LINE__, "Expected an arithmetic operation");
  }

  oper1 = parseExpression(tab+"\t");
  oper2 = parseExpression(tab+"\t");
  Value * intrinsic_args[2] = { oper1, oper2};
  BasicBlock *CurrentBB = Builder.GetInsertBlock();

  switch (oper) {
    case '+':
      overflowCheckOper = 
        Intrinsic::getDeclaration(&*M, Intrinsic::sadd_with_overflow,
                                  ArrayRef<Type *>(Type::getInt64Ty(C)));
      break;
    case '-':
      overflowCheckOper = 
        Intrinsic::getDeclaration(&*M, Intrinsic::ssub_with_overflow,
                                  ArrayRef<Type *>(Type::getInt64Ty(C)));
      break;
    case '*':
      overflowCheckOper = 
        Intrinsic::getDeclaration(&*M, Intrinsic::smul_with_overflow,
                                  ArrayRef<Type *>(Type::getInt64Ty(C)));
      break;
    case '/':
      didOverflow = Builder.CreateAnd(
                            Builder.CreateICmpEQ(oper1, 
                                    ConstantInt::get(Type::getInt64Ty(C), 
                                                     APInt::getSignedMinValue(64))),
                            Builder.CreateICmpEQ(oper2,
                                    ConstantInt::get(Type::getInt64Ty(C),
                                                     APInt(64, -1, true/*isSigned*/))),
                            "oper1 == IntMIN and oper2 == -1");
      didOverflow = Builder.CreateOr(didOverflow, 
                            Builder.CreateICmpEQ(oper2,
                                    ConstantInt::get(Type::getInt64Ty(C), 
                                                     APInt::getNullValue(64))),
                            "or oper2 == 0");
      break;
    case '%':
      didOverflow = Builder.CreateICmpEQ(oper2,
                              ConstantInt::get(Type::getInt64Ty(C), 
                                             APInt::getNullValue(64)),
                            "oper2 == 0");
      break;
    default:
      printError(__LINE__, "Fatal error in compiler. Cannot reach here");
  }

  Builder.SetInsertPoint(CurrentBB);
  if (overflowCheckOper != NULL) {
    Value* v = Builder.CreateCall(overflowCheckOper, 
                                ArrayRef<Value *>(intrinsic_args, 2));
    result = Builder.CreateExtractValue(v, 0);
    didOverflow = Builder.CreateExtractValue(v, 1);
  }

  BasicBlock *ThenBB = BasicBlock::Create(C, "then");
  BasicBlock *ElseBB = BasicBlock::Create(C, "else");

  Builder.CreateCondBr(didOverflow, ThenBB, ElseBB);
  TheFunction->getBasicBlockList().push_back(ThenBB);
  Builder.SetInsertPoint(ThenBB);
  createCallToTrap(operatorPosition, tab+"\t");
  Builder.CreateBr(ElseBB);
  TheFunction->getBasicBlockList().push_back(ElseBB);
  Builder.SetInsertPoint(ElseBB);
  if (oper == '/') {
    result = Builder.CreateSDiv(oper1, oper2, "divtmp");
  } else if (oper == '%') {
    result = Builder.CreateSRem(oper1, oper2, "divtmp");
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;

}
//Guess this should return an LLVM object
Value* parseArithmeticOperation(char oper, string tab) {
  Value* result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept(oper) == false) {
    printError(__LINE__, "Expected an arithmetic operation");
  }

  switch (oper) {
    case '+':
      result = Builder.CreateAdd(parseExpression(tab+"\t"), 
                                 parseExpression(tab+"\t"), "addtmp");
      break;
    case '-':
      result = Builder.CreateSub(parseExpression(tab+"\t"), 
                                 parseExpression(tab+"\t"), "subtmp");
      break;
    case '*':
      result = Builder.CreateMul(parseExpression(tab+"\t"), 
                                 parseExpression(tab+"\t"), "multmp");
      break;
    case '/':
      result = Builder.CreateSDiv(parseExpression(tab+"\t"), 
                                  parseExpression(tab+"\t"), "divtmp");
      break;
    case '%':
      result = Builder.CreateSRem(parseExpression(tab+"\t"), 
                                  parseExpression(tab+"\t"), "modtmp");
      break;
    default:
      printError(__LINE__, "Fatal error in compiler. Cannot reach here");
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseNegativeNumber(string tab) {
  bool noNumber = true;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  unsigned long num = 0, oldNum = 0;
  char ch = getChar();

  while  ((ch >= '0') && (ch <= '9')) {
    noNumber = false;
    num = (num * 10) - (0 + (ch - '0'));
    ch = getnextChar();
    if ((signed long)oldNum < (signed long)num) {
      printError(__LINE__, "Given Number wraps over 64 bits. Invalid input");
    }
    oldNum = num;
  }

  if (noNumber) {
    printError(__LINE__, "Minus symbol not followed by number");
  }

  if (debug) {
    printf("%sExit %s \r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return ConstantInt::get(C, APInt(64, num));
}

Value* parsePositiveNumber(string tab) {
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  unsigned long num = 0, oldNum = 0;
  char ch = getChar();

  while  ((ch >= '0') && (ch <= '9')) {
    num = (num * 10) + (0 + (ch - '0'));
    ch = getnextChar();
    if ((signed long)oldNum > (signed long)num) {
      printError(__LINE__, "Given Number wraps over 64 bits. Invalid input");
    }
    oldNum = num;
  }

  if (debug) {
    printf("%sExit %s \r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return ConstantInt::get(C, APInt(64, num));
}

Value* parseRelationalOperation(string tab) {
  Value* result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept('>')) {
    if (accept('=')) {
      //This is greater than equals 
      result = Builder.CreateICmpSGE(parseExpression(tab+"\t"),
                                     parseExpression(tab+"\t"), "gethan");
    } else {
      //This is greater than
      result = Builder.CreateICmpSGT(parseExpression(tab+"\t"),
                                     parseExpression(tab+"\t"), "gthan");
    }
  } else if (accept('<')) {
    if (accept('=')) {
      //This is less than equals 
      result = Builder.CreateICmpSLE(parseExpression(tab+"\t"),
                                     parseExpression(tab+"\t"), "lethan");
    } else {
      //This is less than
      result = Builder.CreateICmpSLT(parseExpression(tab+"\t"),
                                     parseExpression(tab+"\t"), "lthan");
    }
  } else if (accept('!') && accept('=')) {
    //This is not equal to
    result = Builder.CreateICmpNE(parseExpression(tab+"\t"),
                                  parseExpression(tab+"\t"), "ne");
  } else if (accept('=') && accept('=')) {
    //This is double equals 
    result = Builder.CreateICmpEQ(parseExpression(tab+"\t"),
                                  parseExpression(tab+"\t"), "eq");
  } else {
    printError(__LINE__, "Invalid Relational Operator used");
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseBoolExpression(string tab) {
  Value* result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  skipSpaces(tab+"\t");

  char ch = getChar();

  if (accept('t') && accept('r') && accept('u') && accept('e')) {
    //Its a true condition
    result = ConstantInt::get(C, APInt(1, 1));
  } else if (accept('f') && accept('a') && accept('l') 
      && accept('s') && accept('e')) {
    //Its a false condition
    result = ConstantInt::get(C, APInt(1, 0));
  } else if ((ch == '>') || (ch == '<') || (ch == '=') || 
             (ch == '!')) {
    result = parseRelationalOperation(tab+"\t"); 
  } else if (ch == ('(')) {
    accept('(');
    result = parseBoolExpression(tab+"\t");
    if (accept(')') == false) {
      printError(__LINE__, "Missing ) Paranthesis in boolean exp");
    }
  } else {
    printError(__LINE__, "Boolean expression Missing");
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseWhile(string tab) {
  Value *whileValue, *result = NULL;

  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept('w') && accept('h') && accept('i') && accept('l') && accept('e')) {

    BasicBlock *CurrentBB = Builder.GetInsertBlock();
    BasicBlock *WhileEntryBB = BasicBlock::Create(C, "whileEntry", TheFunction);
    BasicBlock *WhileBodyBB = BasicBlock::Create(C, "whileBody", TheFunction);
    BasicBlock *WhileExitBB = BasicBlock::Create(C, "whileExit", TheFunction);

    Builder.CreateBr(WhileEntryBB);
    Builder.SetInsertPoint(WhileEntryBB);
    PHINode *PN = Builder.CreatePHI(zero->getType(), 2, "phiNode");
    PN->addIncoming(zero, CurrentBB);
    Builder.CreateCondBr(parseBoolExpression(tab+"\t"), 
                         WhileBodyBB, WhileExitBB);
    Builder.SetInsertPoint(WhileBodyBB);
    whileValue = parseExpression(tab+"\t");
    WhileBodyBB = Builder.GetInsertBlock();
    Builder.SetInsertPoint(WhileBodyBB);
    PN->addIncoming(whileValue, WhileBodyBB);
    Builder.CreateBr(WhileEntryBB);
    Builder.SetInsertPoint(WhileExitBB);
    result = PN;
  } else {
    printError(__LINE__);
  }
  

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseIf(string tab) {
  Value *result = NULL, *thenValue = NULL, *elseValue = NULL;

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept('i') && accept('f')) {
    if (use_select == false) {
      //To add a basic block to a function, 
      //We can pass the function while creating the block or else use
      //push_back function over the block list of the function
      //Here i have used pushback, in while it is while creation
      BasicBlock *ThenBB = BasicBlock::Create(C, "then");
      BasicBlock *ElseBB = BasicBlock::Create(C, "else");
      BasicBlock *MergeBB = BasicBlock::Create(C, "merge");
      //Based on the branch go to two block
      Builder.CreateCondBr(parseBoolExpression(tab+"\t"), ThenBB, ElseBB);

      //Now get inside Then block and parse the then expression
      TheFunction->getBasicBlockList().push_back(ThenBB);
      Builder.SetInsertPoint(ThenBB);
      thenValue = parseExpression(tab+"\t");
      //Now merge then block with mergeblock
      Builder.CreateBr(MergeBB);
      //Parse expression of Then could have added more blocks
      //So we have to update the Then block, so that the edges to the 
      //PHI node are appropriate
      ThenBB = Builder.GetInsertBlock();

      //Now do the same as THEN block for ELSE block
      TheFunction->getBasicBlockList().push_back(ElseBB);
      Builder.SetInsertPoint(ElseBB);
      elseValue = parseExpression(tab+"\t");
      Builder.CreateBr(MergeBB);
      ElseBB = Builder.GetInsertBlock();

      //Now in the MergeBlock, add a phi node
      TheFunction->getBasicBlockList().push_back(MergeBB);
      Builder.SetInsertPoint(MergeBB);
      PHINode *PN = Builder.CreatePHI(thenValue->getType(), 2, "phiNode");
      PN->addIncoming(thenValue, ThenBB);
      PN->addIncoming(elseValue, ElseBB);
      result = PN;
    } else {
      result = Builder.CreateSelect(parseBoolExpression(tab+"\t"),
                                    parseExpression(tab+"\t"),
                                    parseExpression(tab+"\t"));
    }
  } else {
    printError(__LINE__);
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

void skipSpaces(string tab) {
  if (debug) {
    //printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  while (getChar() != EOF) {
    if (accept(' ')) {
      gLineOffset++;
      continue;
    } else if (accept('\t')) {
      gLineOffset++;
      continue;
    } else if (accept('\r')) {
      gLineOffset++;
      continue;
    } else if (accept('\n')) {
      gLineNo++;
      gLineOffset = 1;
      continue;
    }
    break;
  }

  if (debug) {
    //printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
}

Value* parseSeq(string tab) {
  Value *result;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  skipSpaces(tab);
  parseExpression(tab+ "\t");
  result = parseExpression(tab+ "\t");

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseSet(string tab) {
  Value *result, *mutableVariable;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  result = parseExpression(tab+"\t");
  skipSpaces(tab+"\t");
  mutableVariable = parseMutables(tab+"\t");
  //Store values onto the mutable variable
  Builder.CreateStore(result, mutableVariable);

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseExpression(string tab) {
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  skipSpaces(tab+"\t");

  char ch = getChar();

  while (ch != EOF){
    if (ch == '#') {
      if (gLineOffset == 1) { 
        parseComment(tab+"\t");
        ch = getChar();
      } else {
        printError(__LINE__, "Encounter Comment in the middle of a line");
      }
    } else if (ch == 'a') {
      result = parseArgs(tab+"\t");
      break;
    } else if (ch == 'm') {
      //Get the mutable variable and do a load operation. The parse mutable
      //get address of mutable variable. So to get the value 
      //issue a load operation
      result = Builder.CreateLoad(parseMutables(tab+"\t"));
      break;
    } else if ((ch == '\n') || (ch == ' ') || (ch == '\t')){
      skipSpaces(tab+"\t");
      ch = getChar();
    } else if ((ch >= '0') && (ch <= '9')) {
      result = parsePositiveNumber(tab+"\t");
      break;
    } else if (ch == '-') {
      accept('-');
      result = parseNegativeNumber(tab+"\t");
      break;
    } else if (ch == '(') {
      accept('(');
      skipSpaces(tab+"\t");
      ch = getChar(); 
      if ((ch == '+') || (ch == '*') || (ch == '-') ||
          (ch == '/') || (ch == '%')) {
        if (integerOverflow == false) {
          result = parseArithmeticOperation(ch, tab+"\t"); 
        } else {
          result = parseArithmeticOperationWithOverflowCheck(ch, tab+"\t"); 
        }
      } else if (ch == 'i') {
        result = parseIf(tab+"\t");
      } else if (ch == 's') {
        if (accept('s') && accept('e'))  {
          if (accept('q')) {
            result = parseSeq(tab+"\t");
          } else if (accept('t')) {
            result = parseSet(tab+"\t");
          } else {
            printError(__LINE__);
          } 
        } else {
          printError(__LINE__);
        } 
      } else if (ch == 'w') {
        result = parseWhile(tab+"\t");
      } else {
        printError(__LINE__, "Didnt find a valid expression within ()");
      }
      skipSpaces(tab+"\t");
      if (accept(')') == false) {
        printError(__LINE__, "Missing Matching paranthesis");
      }
      break;
    } else {
      printError(__LINE__);
    }
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parser(string tab) {
  Value *result = NULL;
  char ch;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  //Read the first char and then call parseExpression
  getnextChar();
  result = parseExpression(tab+"\t");

  //Skip the spaces after the expression
  skipSpaces(tab+"\t");

  //The below ch should be EOF or a comment. Else throw error
  ch = getChar();
  while(ch != EOF) {
    if ((ch == '#') && (gLineOffset == 1)) {
      parseComment(tab+"\t");
      skipSpaces(tab+"\t");
      ch = getChar();
    } else { 
        printError(__LINE__, "Unknown expression at the end of file");
    }
  }
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
    printf("Parsed successfully\r\n");
  }
  return result;
}

static int compile() {
  M->setTargetTriple(llvm::sys::getProcessTriple());
  std::vector<Type *> SixInts(6, Type::getInt64Ty(C));
  FunctionType *FT = FunctionType::get(Type::getInt64Ty(C), SixInts, false);
  Function *F = Function::Create(FT, Function::ExternalLinkage, "f", &*M);
  BasicBlock *BB = BasicBlock::Create(C, "entry", F);
  Builder.SetInsertPoint(BB);

  gArgValues.clear();
  int argCount = 0;
  for (auto &Arg : F->args()) { 
    gArgValues[argCount++] = &Arg;
  }
  for (int i = 0; i < mutables.size(); i++) {
    mutables[i] = Builder.CreateAlloca(Type::getInt64Ty(C), 0, "Mutable"+std::to_string(i));
    Builder.CreateStore(zero, mutables[i]);

  }

  Value *RetVal = parser("");
  Builder.CreateRet(RetVal);
  M->dump();
  assert(!verifyModule(*M, &outs()));
  return 0;
}

int main(int argc, char **argv) { 
  if (argc > 1) {
    integerOverflow = true;
  } 
  if (argc > 2) {
    debug = true;
    integerOverflow = true;
  }
  return compile(); 
}
