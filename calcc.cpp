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
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
#include <cmath>
=======
>>>>>>> parsing done
=======
#include <cmath>
>>>>>>> Done. Add comments and make it neat
=======
>>>>>>> parsing done
=======
#include <cmath>
>>>>>>> Done. Add comments and make it neat

using namespace llvm;
using namespace std;

static LLVMContext C;
static IRBuilder<NoFolder> Builder(C);
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;
bool integerOverflow = false;
int  gLineOffset = 0;
int  gOffset = 0;



Value* parseExpression(string tab);
void skipSpaces(string tab);
=======
static std::unique_ptr<Module> M = llvm::make_unique<Module>("calc", C);
static ifstream gInFile;
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
=======
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
<<<<<<< 9099d0e8b0a32744f9e439760cd09af651c3b1e1
<<<<<<< b21c32b05863e1fff7581a521a4f782d865e53bf
>>>>>>> Done. Add comments and make it neat
=======
static vector<Value*> mutables(10);
static Value *zero = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Done with coding
=======
static vector<Value*> mutables(10);
static Value *zero = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Done with coding
=======
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
<<<<<<< 4e9ef3470ff8b0d728e461ca258d0a9ffc0ad621
>>>>>>> Done. Add comments and make it neat
=======
static vector<Value*> mutables(10);
static Value *zero = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Done with coding
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;
bool integerOverflow = false;
int  gLineOffset = 0;
int  gOffset = 0;
<<<<<<< 4e9ef3470ff8b0d728e461ca258d0a9ffc0ad621
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
bool use_select = false;
<<<<<<< af87e32a17b2cb1aa3de1be5759422eda2d04a08
<<<<<<< 9099d0e8b0a32744f9e439760cd09af651c3b1e1
=======
bool use_select = false;
>>>>>>> Done with coding

<<<<<<< ef1e94be58d02a5bab3d4d3b3206f78a6e04f929
=======
>>>>>>> Done with coding
=======

<<<<<<< d30e234ea8e21fa2b312da24f45132f5c8a9c56b

>>>>>>> Done. Add comments and make it neat


<<<<<<< 9555d7726f0021c2c920405b7211c9f553440c2e
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
Value* parseExpression();
void skipSpaces();
>>>>>>> parsing done
=======
=======
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
=======
>>>>>>> fixed the code to read input from file
=======


>>>>>>> Done. Add comments and make it neat
Value* parseExpression(string tab);
void skipSpaces(string tab);
>>>>>>> fixed the code to read input from file
=======
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;

<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
Value* parseExpression();
void skipSpaces();
>>>>>>> parsing done

void usage(void) {
  printf("executable <input file.calc>\r\n");
  return;
}

<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
=======
=======
>>>>>>> parsing done
bool openFile(int argc, char **argv) {
  if (argc < 2) {
    usage();
    return false;
  }
  gInFile.open (argv[1], ifstream::in);
  return true;
}

<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
>>>>>>> parsing done
=======
>>>>>>> Done. Add comments and make it neat
=======
>>>>>>> parsing done
=======
>>>>>>> Done. Add comments and make it neat
char getChar() {
  return gCurValue;
}

void nextChar(void) {
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
  if (!cin.eof()) {
    gCurValue = cin.get();
    gOffset++;
=======
  if (!gInFile.eof()) {
    gCurValue = gInFile.get();
>>>>>>> parsing done
=======
  if (!cin.eof()) {
    gCurValue = cin.get();
    gLineOffset++;
    gOffset++;
>>>>>>> Done. Add comments and make it neat
=======
  if (!gInFile.eof()) {
    gCurValue = gInFile.get();
>>>>>>> parsing done
=======
  if (!cin.eof()) {
    gCurValue = cin.get();
    gLineOffset++;
    gOffset++;
>>>>>>> Done. Add comments and make it neat
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
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
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

<<<<<<< b29894b75a0413323d318678df6a01015d66a2c8
=======
  getline(gInFile, context);
=======
  getline(cin, context);
>>>>>>> Done. Add comments and make it neat
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
<<<<<<< d23052cfec9272773563b8dab7f07400a23983a2
  getnextChar();
  gLineNo++;
  gOffset = 0;
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
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
  int i;
>>>>>>> parsing done
=======

>>>>>>> Done. Add comments and make it neat
=======
  getline(gInFile, context);
  return context;
}

void printError() {
  printf ("Invalid statement at LineNo:%d:%d - %s",
           gLineNo, (int)gInFile.tellg(), getContext().c_str());
  exit(0);
}

void printError(const char *c) {
  printf("Unable to compile due to error %s at Line: %d FilePosition:%d \r\n",
      c, gLineNo, (int)gInFile.tellg());
  printf("Remaining Code: %s", getContext().c_str());
  exit(0);
}

void parseComment() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  while (getnextChar() != '\n');
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parseArgs() {
  char errmsg[50];
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  int i;
>>>>>>> parsing done
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< d77025b4cd63efe9d68522c1c85219a17ecc7564
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      result = gArgValues[i];
=======
>>>>>>> parsing done
=======
>>>>>>> parsing done
      break;
    }  
  }
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< c3573d72b2a3e3bb5d707a8abb1d30ccb8f9f606
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
    printError(__LINE__, errmsg);
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseMutables(string tab) {
  char errmsg[50];
  int i;
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < mutables.size(); i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
      result = mutables[i];
      break;
    }  
  }
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(__LINE__, errmsg);
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
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  long num = 0, oldNum = 0;
  char ch = getChar();

  while  ((ch >= '0') && (ch <= '9')) {
    num = (num * 10) - (0 + (ch - '0'));
    ch = getnextChar();
    if (oldNum < num) {
      printError(__LINE__, "Given Number wraps over 64 bits. Invalid input");
    }
    oldNum = num;
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

  long num = 0, oldNum = 0;
  char ch = getChar();

  while  ((ch >= '0') && (ch <= '9')) {
    num = (num * 10) + (0 + (ch - '0'));
    ch = getnextChar();
    if (oldNum > num) {
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
    getnextChar();
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
  //Function *TheFunction = Builder.GetInsertBlock()->getParent();

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept('i') && accept('f')) {
    if (use_select == false) {
      BasicBlock *ThenBB = BasicBlock::Create(C, "then", TheFunction);
      BasicBlock *ElseBB = BasicBlock::Create(C, "else", TheFunction);
      BasicBlock *MergeBB = BasicBlock::Create(C, "merge", TheFunction);
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
=======
    printError(errmsg);
=======
    printError(__LINE__, errmsg);
>>>>>>> parser mostly working
  }
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
=======
      if (debug) {
        printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
      }
      return ConstantInt::get(Type::getInt64Ty(C), i);
    }  
  }
  sprintf(errmsg, "Invalid argument (a%c) used in the program", 
          getChar());
  printError(__LINE__, errmsg);
  return NULL;
>>>>>>> Change to add LLVM code
=======
      result = gArgValues[i];
      break;
    }  
  }
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(__LINE__, errmsg);
=======
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
>>>>>>> All tests passed
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
>>>>>>> Done. Add comments and make it neat
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
      //overflowCheckOper = createDivWithOverFlow(tab+"\t");
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
      result = Builder.CreateSRem(oper1, oper2, "divtmp");
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
    result = Builder.CreateSDiv(oper1, oper2, "divtmp");
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
=======
Value* parseExpression(string tab);
void skipSpaces(string tab);
>>>>>>> fixed the code to read input from file

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

<<<<<<< e2dc92f42722645a9a542624e6b14f017ad1774e
Value* parseWhile(string tab) {
  Value *whileValue, *result = NULL;

  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
  if (accept('w') && accept('h') && accept('i') && accept('l') && accept('e')) {
=======
string getContext() {
  string context;
  getline(cin, context);
  return context;
}
>>>>>>> Done. Add comments and make it neat

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
=======
void printError(int lineno) {
  printf ("%d:Invalid statement at LineNo:%d:%d - %c%s",
           lineno,
           gLineNo, gOffset, getChar(), getContext().c_str());
  exit(1);
}

void printError(int lineno, const char *c) {
  printf("%d:Unable to compile due to error \"%s\" at Line: %d Offset:%d \r\n",
      lineno,
      c, gLineNo, gOffset);
  printf("Remaining Code: %c%s", getChar(), getContext().c_str());
<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
  exit(0);
>>>>>>> parser mostly working
}

Value* parseIf(string tab) {
  Value *result = NULL, *thenValue = NULL, *elseValue = NULL;

  // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
  Function *TheFunction = Builder.GetInsertBlock()->getParent();
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
<<<<<<< e2dc92f42722645a9a542624e6b14f017ad1774e

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
=======
  exit(1);
}

void parseComment(string tab) {
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
>>>>>>> fixed the code to read input from file
  }

=======
  while (getnextChar() != '\n');
  //Skip \n
  getnextChar();
  gLineNo++;
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
>>>>>>> parser mostly working
=======
  gOffset = 0;
>>>>>>> Done. Add comments and make it neat
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
}

<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
<<<<<<< 34181eae74af2141376e3589e6bbfe14983331d3
void skipSpaces(string tab) {
  if (debug) {
    //printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
<<<<<<< e2dc92f42722645a9a542624e6b14f017ad1774e

<<<<<<< c3573d72b2a3e3bb5d707a8abb1d30ccb8f9f606
  while (true) {
>>>>>>> parsing done
=======
  while (getChar() != EOF) {
>>>>>>> parser mostly working
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
<<<<<<< 65a4b1f8762117de77d649d683813001370c326c
<<<<<<< a81acd3362f5bc194fbd5df1da2fc5b694dee167
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      gOffset = 0;
=======
>>>>>>> parsing done
=======
      gOffset = 0;
>>>>>>> Done. Add comments and make it neat
=======
      gOffset = 1;
>>>>>>> All working
=======
      gLineOffset = 1;
>>>>>>> Working
=======
    printError(errmsg);
=======
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(__LINE__, errmsg);
>>>>>>> parser mostly working
  }
=======
  ch = getnextChar();
  gLineNo++;
<<<<<<< d20a717f312b4baa93cfcee7f32f08443d20f39d
  gOffset = 1;
>>>>>>> All working
=======
  gLineOffset = 1;
>>>>>>> Working
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
=======
Value* parseArgs() {
=======
Value* parseArgs(string tab) {
>>>>>>> fixed the code to read input from file
  char errmsg[50];
  int i;
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

<<<<<<< 70026b6870b943be4393e9573984216aaab56fb6
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
      result = gArgValues[i];
      break;
    }  
  }
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
  sprintf(errmsg, "Invalid argument (a%c) used in the program", 
          getChar());
  printError(__LINE__, errmsg);
  return NULL;
>>>>>>> Change to add LLVM code
=======
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(__LINE__, errmsg);
=======
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
>>>>>>> All tests passed
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
>>>>>>> Done. Add comments and make it neat
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
  int operatorPosition = gOffset;
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
      //overflowCheckOper = createDivWithOverFlow(tab+"\t");
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
      result = Builder.CreateSDiv(oper1, oper2, "divtmp");
 
      break;
    case '%':
      didOverflow = Builder.CreateICmpEQ(oper2,
                              ConstantInt::get(Type::getInt64Ty(C), 
                                             APInt::getNullValue(64)),
                            "oper2 == 0");
      result = Builder.CreateSRem(oper1, oper2, "divtmp");
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
<<<<<<< d20a717f312b4baa93cfcee7f32f08443d20f39d
<<<<<<< d23052cfec9272773563b8dab7f07400a23983a2
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
>>>>>>> parsing done
=======
      gOffset = 0;
>>>>>>> Done. Add comments and make it neat
=======
      gOffset = 1;
>>>>>>> All working
=======
      gLineOffset = 1;
>>>>>>> Working
      continue;
    }
    break;
  }

  if (debug) {
<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
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
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
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
=======
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
=======
    //printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
>>>>>>> fixed the code to read input from file
  }
}

Value* parseExpression(string tab) {
  char errmsg[75];
  Value *result;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  skipSpaces(tab+"\t");

  char ch = getChar();

  while (ch != EOF){
    if (ch == '#') {
      parseComment(tab+"\t");
=======
>>>>>>> Done. Add comments and make it neat
    } else if (ch == 'a') {
      result = parseArgs(tab+"\t");
      break;
    } else if ((ch == '\n') || (ch == ' ')){
      skipSpaces(tab+"\t");
      ch = getChar();
    } else if ((ch == '+') || (ch == '*') || 
               (ch == '/') || (ch == '%')) {
      //Negative case is special, handled below
      getnextChar();
      result = parseArithmeticOperation(ch, tab+"\t"); 
      break;
    } else if (ch == '-') {
      if (getnextChar() == ' ') {
        result = parseArithmeticOperation(ch, tab+"\t"); 
      } else {
        result = parseNegativeNumber(tab+"\t");
      }
      break;
    } else if ((ch >= '0') && (ch <= '9')) {
      result = parsePositiveNumber(tab+"\t");
      break;
    } else if (ch == '(') {
      getnextChar();
      result = parseExpression(tab+"\t");
      skipSpaces(tab+"\t");
      if (accept(')') == false) {
        printError(__LINE__, "Missing Matching paranthesis");
      }
      break;
    } else if (ch == 'i') {
      result = parseIf(tab+"\t");
      break;
    } else if (ch == 's') {
      if (accept('s') && accept('e'))  {
        if (accept('q')) {
          result = parseSeq(tab+"\t");
          break;
        } else if (accept('t')) {
          result = parseSet(tab+"\t");
          break;
        } 
      }
      //If its not a 'seq' or 'set' but starting with 's' or 'se', 
      //throw error
      printError(__LINE__);
    } else if (ch == 'w') {
      result = parseWhile(tab+"\t");
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
  if (debug) {
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
>>>>>>> parsing done
=======
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
>>>>>>> fixed the code to read input from file
  }
  //Read the first char and then call parseExpression
  getnextChar();
  result = parseExpression(tab+"\t");

  //Skip the spaces after the expression
  skipSpaces(tab+"\t");

  //The below ch should be EOF or a comment. Else throw error
  ch = getChar();
  while(ch != EOF) {
<<<<<<< 65a4b1f8762117de77d649d683813001370c326c
<<<<<<< a81acd3362f5bc194fbd5df1da2fc5b694dee167
    if (ch == '#') {
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      parseComment(tab+"\t");
    } else { 
<<<<<<< 9099d0e8b0a32744f9e439760cd09af651c3b1e1
      result = parseExpression(tab+"\t");
=======
    if ((ch == '#') && (gOffset == 1)) {
=======
    if ((ch == '#') && (gLineOffset == 1)) {
>>>>>>> Working
      parseComment(tab+"\t");
>>>>>>> All working
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
=======
      parseComment();
=======
      parseComment(tab+"\t");
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
>>>>>>> fixed the code to read input from file
    } else {
      result = parseExpression(tab+"\t");
=======
    } else if ((ch == ' ') | (ch == '\n')) {
>>>>>>> Done. Add comments and make it neat
      skipSpaces(tab+"\t");
      //If there is a space, then only expression can follow, else
      //throw an error
      if (check('(') == true) {
        result = parseExpression(tab+"\t");
        skipSpaces(tab+"\t");
        if (getChar() != EOF) {
          printError(__LINE__, "Unknown expression at the end of file");
        }
        break;
      } else {
        printError(__LINE__, "Expected an expression. But not found");
      }
    } else if (ch == '(') {
=======
>>>>>>> Done with coding
      result = parseExpression(tab+"\t");
      skipSpaces(tab+"\t");
      if (getChar() != EOF) {
        printError(__LINE__, "Unknown expression at the end of file");
      }
      break;
    }
    ch = getChar();
  }
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
    printf("Parsed successfully\r\n");
  }
<<<<<<< 9555d7726f0021c2c920405b7211c9f553440c2e
<<<<<<< ef1e94be58d02a5bab3d4d3b3206f78a6e04f929
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
<<<<<<< d77025b4cd63efe9d68522c1c85219a17ecc7564
>>>>>>> parsing done
=======
=======
  printf("Parsed successfully\r\n");
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
=======
  printf("Parsed successfully\r\n");
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
  return result;
>>>>>>> Change to add LLVM code
=======
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
=======
    //printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
>>>>>>> fixed the code to read input from file
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
<<<<<<< af87e32a17b2cb1aa3de1be5759422eda2d04a08
<<<<<<< d30e234ea8e21fa2b312da24f45132f5c8a9c56b
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
<<<<<<< 34181eae74af2141376e3589e6bbfe14983331d3
>>>>>>> parsing done
=======
=======
  printf("Parsed successfully\r\n");
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
=======
  printf("Parsed successfully\r\n");
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
  return result;
>>>>>>> Change to add LLVM code
}

static int compile() {
  M->setTargetTriple(llvm::sys::getProcessTriple());
  std::vector<Type *> SixInts(6, Type::getInt64Ty(C));
  FunctionType *FT = FunctionType::get(Type::getInt64Ty(C), SixInts, false);
  Function *F = Function::Create(FT, Function::ExternalLinkage, "f", &*M);
  BasicBlock *BB = BasicBlock::Create(C, "entry", F);
  Builder.SetInsertPoint(BB);

<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< 007b32a346b51a1ed2d3aca298a9aa441cd05678
=======
>>>>>>> Done. Add comments and make it neat
=======
>>>>>>> Done. Add comments and make it neat
  gArgValues.clear();
  int argCount = 0;
  for (auto &Arg : F->args()) { 
    gArgValues[argCount++] = &Arg;
  }
<<<<<<< 4e9ef3470ff8b0d728e461ca258d0a9ffc0ad621
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< 9099d0e8b0a32744f9e439760cd09af651c3b1e1
<<<<<<< b21c32b05863e1fff7581a521a4f782d865e53bf
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
=======
=======
>>>>>>> Done with coding
  for (int i = 0; i < mutables.size(); i++) {
    mutables[i] = Builder.CreateAlloca(Type::getInt64Ty(C), 0, "Mutable"+std::to_string(i));
    Builder.CreateStore(zero, mutables[i]);

  }
<<<<<<< 4e9ef3470ff8b0d728e461ca258d0a9ffc0ad621
>>>>>>> Done with coding
=======
>>>>>>> Done with coding

  Value *RetVal = parser("");
=======
  // TODO: parse the source program
  // TODO: generate correct LLVM instead of just an empty function
<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
<<<<<<< 84e846ae7e43a1ba1a5fbb9498c8e02eb7657f7d
  Value *RetVal = parser("");

  //Value *RetVal = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Adding the parsing code
=======
=======
  for (int i = 0; i < mutables.size(); i++) {
    mutables[i] = Builder.CreateAlloca(Type::getInt64Ty(C), 0, "Mutable"+std::to_string(i));
    Builder.CreateStore(zero, mutables[i]);

  }
>>>>>>> Done with coding

  Value *RetVal = parser("");
>>>>>>> Done. Add comments and make it neat
=======
  Value *RetVal = parser();
=======
  Value *RetVal = parser("");
>>>>>>> fixed the code to read input from file

  //Value *RetVal = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Adding the parsing code
=======

  Value *RetVal = parser("");
>>>>>>> Done. Add comments and make it neat
  Builder.CreateRet(RetVal);
  M->dump();
  assert(!verifyModule(*M, &outs()));
  return 0;
}

int main(int argc, char **argv) { 
<<<<<<< 87854e54e3a4851736023e27df7daf2cca00502c
<<<<<<< fc99818424e2f53f379eb27931b3727e9599abd5
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
=======
>>>>>>> Done. Add comments and make it neat
  if (argc > 1) {
    integerOverflow = true;
  } 
  if (argc > 2) {
    debug = true;
    integerOverflow = true;
  }
  return compile(); 
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
=======
  if (openFile(argc, argv) == true) {
    return compile(); 
  } 
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
  return -1;
>>>>>>> parsing done
=======
  return 1;
>>>>>>> fixed the code to read input from file
=======
>>>>>>> Done. Add comments and make it neat
=======
  if (openFile(argc, argv) == true) {
    return compile(); 
  } 
<<<<<<< 63e83c850d17b5031a59602e1846f84fa81dbbd6
  return -1;
>>>>>>> parsing done
=======
  return 1;
>>>>>>> fixed the code to read input from file
=======
  if (argc > 1) {
    integerOverflow = true;
  } 
  if (argc > 2) {
    debug = true;
    integerOverflow = true;
  }
  return compile(); 
>>>>>>> Done. Add comments and make it neat
}
