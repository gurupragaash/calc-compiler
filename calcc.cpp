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
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
#include <cmath>
=======
>>>>>>> parsing done
=======
#include <cmath>
>>>>>>> Done. Add comments and make it neat

using namespace llvm;
using namespace std;

static LLVMContext C;
static IRBuilder<NoFolder> Builder(C);
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;
int  gOffset = 0;



Value* parseExpression(string tab);
void skipSpaces(string tab);
=======
static std::unique_ptr<Module> M = llvm::make_unique<Module>("calc", C);
static ifstream gInFile;
=======
static std::unique_ptr<Module> M = llvm::make_unique<Module>("", C);
static std::map<int, Value *> gArgValues;
<<<<<<< b21c32b05863e1fff7581a521a4f782d865e53bf
>>>>>>> Done. Add comments and make it neat
=======
static vector<Value*> mutables(10);
static Value *zero = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Done with coding
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
bool debug = false;
int  gOffset = 0;
bool use_select = false;

<<<<<<< ef1e94be58d02a5bab3d4d3b3206f78a6e04f929


<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
Value* parseExpression();
void skipSpaces();
>>>>>>> parsing done
=======
=======
>>>>>>> fixed the code to read input from file
Value* parseExpression(string tab);
void skipSpaces(string tab);
>>>>>>> fixed the code to read input from file

void usage(void) {
  printf("executable <input file.calc>\r\n");
  return;
}

<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
=======
bool openFile(int argc, char **argv) {
  if (argc < 2) {
    usage();
    return false;
  }
  gInFile.open (argv[1], ifstream::in);
  return true;
}

>>>>>>> parsing done
=======
>>>>>>> Done. Add comments and make it neat
char getChar() {
  return gCurValue;
}

void nextChar(void) {
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

/*
bool accept(string c) {
  int i = 0, len = c.size();
  bool retVal = true;

  while ((i < len) && retVal) {
    retVal &= accept(c[i++]);
  }
  return retVal;
}*/

bool check(char c) {
  if (getChar() == c) {
    return true;
  }
  return false;
}

string getContext() {
  string context;
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
  getline(cin, context);
  return context;
}

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
  exit(1);
}

void parseComment(string tab) {
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  while (getnextChar() != '\n');
  //Skip \n
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
           gLineNo, gOffset, getChar(), getContext().c_str());
  exit(1);
}

void printError(int lineno, const char *c) {
  printf("%d:Unable to compile due to error \"%s\" at Line: %d Offset:%d \r\n",
      lineno,
      c, gLineNo, gOffset);
  printf("Remaining Code: %c%s", getChar(), getContext().c_str());
  exit(1);
}

void parseComment(string tab) {
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  while (getnextChar() != '\n');
  //Skip \n
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
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< d77025b4cd63efe9d68522c1c85219a17ecc7564
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      result = gArgValues[i];
=======
>>>>>>> parsing done
      break;
    }  
  }
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
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
  }

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
>>>>>>> Done. Add comments and make it neat
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

Value* parseIf(string tab) {
  Value *result = NULL;
  if (debug) {
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }

  if (accept('i') && accept('f')) {
    result = Builder.CreateSelect(parseBoolExpression(tab+"\t"),
                                  parseExpression(tab+"\t"),
                                  parseExpression(tab+"\t"));
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

<<<<<<< c3573d72b2a3e3bb5d707a8abb1d30ccb8f9f606
  while (true) {
>>>>>>> parsing done
=======
  while (getChar() != EOF) {
>>>>>>> parser mostly working
    if (accept(' ')) {
      continue;
    } else if (accept('\n')) {
      gLineNo++;
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      gOffset = 0;
=======
>>>>>>> parsing done
=======
      gOffset = 0;
>>>>>>> Done. Add comments and make it neat
      continue;
    }
    break;
  }

  if (debug) {
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
  Builder.CreateStore(result, mutableVariable);

  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
  }
  return result;
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
      if (gOffset == 0) { 
        parseComment(tab+"\t");
      } else {
        printError(__LINE__, "Encounter Comment in the middle of a line");
      }
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
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
  char ch = getnextChar();
  while(ch != EOF) {
    if (ch == '#') {
<<<<<<< 3df167b8eb9fffcdcfaf8ab8e33a1aeaa94c31e2
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      parseComment(tab+"\t");
    } else { 
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
      result = parseExpression(tab+"\t");
      skipSpaces(tab+"\t");
      if (getChar() != EOF) {
        printError(__LINE__, "Unknown expression at the end of file");
      }
      break;
    } else {
      printError(__LINE__, "Didnt find a comment or an expression");
    }
    ch = getChar();
  }
  if (debug) {
    printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
    printf("Parsed successfully\r\n");
  }
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

<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< 007b32a346b51a1ed2d3aca298a9aa441cd05678
=======
>>>>>>> Done. Add comments and make it neat
  gArgValues.clear();
  int argCount = 0;
  for (auto &Arg : F->args()) { 
    gArgValues[argCount++] = &Arg;
  }
<<<<<<< b21c32b05863e1fff7581a521a4f782d865e53bf
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813

  Value *RetVal = parser("");
=======
  // TODO: parse the source program
  // TODO: generate correct LLVM instead of just an empty function
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
  Builder.CreateRet(RetVal);
  M->dump();
  assert(!verifyModule(*M, &outs()));
  return 0;
}

int main(int argc, char **argv) { 
<<<<<<< e3a85e8828d8e4f737053287d07d64811bf70813
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
=======
>>>>>>> Done. Add comments and make it neat
  if (argc > 1) {
    debug = true;
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
}
