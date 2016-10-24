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

using namespace llvm;
using namespace std;

static LLVMContext C;
static IRBuilder<NoFolder> Builder(C);
static std::unique_ptr<Module> M = llvm::make_unique<Module>("calc", C);
static ifstream gInFile;
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
enum oper {ADD = 0, SUB, MUL, DIV, MOD};
bool debug = true;

Value* parseExpression();
void skipSpaces();

void usage(void) {
  printf("executable <input file.calc>\r\n");
  return;
}

bool openFile(int argc, char **argv) {
  if (argc < 2) {
    usage();
    return false;
  }
  gInFile.open (argv[1], ifstream::in);
  return true;
}

char getChar() {
  return gCurValue;
}

void nextChar(void) {
  if (!gInFile.eof()) {
    gCurValue = gInFile.get();
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
  getline(gInFile, context);
  return context;
}

void printError(int lineno) {
  printf ("%d:Invalid statement at LineNo:%d:%d - %c%s",
           lineno,
           gLineNo, (int)gInFile.tellg(), getChar(), getContext().c_str());
  exit(0);
}

void printError(int lineno, const char *c) {
  printf("%d:Unable to compile due to error %s at Line: %d FilePosition:%d \r\n",
      lineno,
      c, gLineNo, (int)gInFile.tellg());
  printf("Remaining Code: %c%s", getChar(), getContext().c_str());
  exit(0);
}

void parseComment() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  while (getnextChar() != '\n');
  //Skip \n
  getnextChar();
  gLineNo++;
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

Value* parseArgs() {
  char errmsg[50];
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  int i;
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
      if (debug) {
        printf("Exit %s\r\n", __PRETTY_FUNCTION__);
      }
      return ConstantInt::get(Type::getInt64Ty(C), i);
    }  
  }
  sprintf(errmsg, "Invalid argument (a%c) used in the program", 
          getChar());
  printError(__LINE__, errmsg);
  return NULL;
}

//Guess this should return an LLVM object
Value* parseArithmeticOperation(char oper) {
  Value* result = NULL;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  switch (oper) {
  case '+':
    result = Builder.CreateAdd(parseExpression(), 
						  								 parseExpression(), "addtmp");
  case '-':
    result = Builder.CreateSub(parseExpression(), 
						  								 parseExpression(), "subtmp");
  case '*':
    result = Builder.CreateMul(parseExpression(), 
						  								 parseExpression(), "multmp");
  case '/':
    result = Builder.CreateSDiv(parseExpression(), 
						  							    parseExpression(), "divtmp");
  case '%':
    result = Builder.CreateSRem(parseExpression(), 
					  								 	  parseExpression(), "modtmp");
  default:
    printError(__LINE__, "Fatal error in compiler. Cannot reach here");
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseNumber() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  int num = 0, count = 0;
  bool isNegative = false;
  char ch = getChar();

  if (ch == '-') {
    isNegative = true;
    ch = getnextChar();
  }
  while  ((ch >= '0') && (ch <= '9')) {
    num = (num * 10 * count++) + (0 + (ch - '0'));
    ch = getnextChar();
  }
  if (isNegative) {
    num = num * (-1);
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return ConstantInt::get(C, APInt(64, num));
}

Value* parseRelationalOperation() {
  Value* result = NULL;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  if (accept('>')) {
    if (accept('=')) {
      //This is greater than equals 
      result = Builder.CreateICmpSGE(parseExpression(),
                                     parseExpression(), "gethan");
    } else {
      //This is greater than
      result = Builder.CreateICmpSGT(parseExpression(),
                                     parseExpression(), "gthan");
    }
  } else if (accept('<')) {
    if (accept('=')) {
      //This is less than equals 
      result = Builder.CreateICmpSLE(parseExpression(),
                                     parseExpression(), "lethan");
    } else {
      //This is less than
      result = Builder.CreateICmpSLT(parseExpression(),
                                     parseExpression(), "lthan");
    }
  } else if (accept('!') && accept('=')) {
    //This is not equal to
    result = Builder.CreateICmpNE(parseExpression(),
                                  parseExpression(), "ne");
  } else if (accept('=') && accept('=')) {
    //This is double equals 
    result = Builder.CreateICmpEQ(parseExpression(),
                                  parseExpression(), "eq");
  } else {
    printError(__LINE__, "Invalid Relational Operator used");
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseBoolExpression() {
  Value* result = NULL;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  skipSpaces();

  char ch = getChar();

  if (accept('t') && accept('r') && accept('u') && accept('e')) {
    //Its a true condition
    result = ConstantInt::get(C, APInt(64, 1));
  } else if (accept('f') && accept('a') && accept('l') 
      && accept('s') && accept('e')) {
    //Its a false condition
    result = ConstantInt::get(C, APInt(64, 0));
  } else if ((ch == '>') || (ch == '<') || (ch == '=') || 
             (ch == '!')) {
    result = parseRelationalOperation(); 
  } else if (ch == ('(')) {
    getnextChar();
    result = parseBoolExpression();
    if (accept(')') == false) {
      printError(__LINE__, "Missing ) Paranthesis in boolean exp");
    }
  } else {
    printError(__LINE__, "Boolean expression Missing");
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parseIf() {
  Value *result = NULL;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  if (accept('i') && accept('f')) {
    result = Builder.CreateSelect(parseBoolExpression(),
                                  parseExpression(),
                                  parseExpression());
  } else {
    printError(__LINE__);
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return result;
}

void skipSpaces() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  while (getChar() != EOF) {
    if (accept(' ')) {
      continue;
    } else if (accept('\n')) {
      gLineNo++;
      continue;
    }
    break;
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

Value* parseExpression() {
  char errmsg[75];
  Value *result;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  skipSpaces();

  char ch = getChar();

  do{
    if (ch == '#') {
      parseComment();
    } else if (ch == 'a') {
      result = parseArgs();
      break;
    } else if (ch == '\n') {
      //Increment the line number, so that we can give a 
      //meaningful error message
      gLineNo++;
    } else if (ch == ' ') {
      //Ignore White space
    } else if ((ch == '+') || (ch == '-') || (ch == '*') || 
               (ch == '/') || (ch == '%')) {
      getnextChar();
      result = parseArithmeticOperation(ch); 
      break;
    } else if (ch == '-') {
      result = parseNumber();
      break;
    } else if ((ch >= '0') && (ch <= '9')) {
      result = parseNumber();
      break;
    } else if (ch == '(') {
      getnextChar();
      result = parseExpression();
      if (accept(')') == false) {
        printError(__LINE__, "Missing Matching paranthesis");
      }
      break;
    } else if (ch == 'i') {
      result = parseIf();
      break;
    } else if (ch == ')') {
      getnextChar();
      break;
    } else {
      printError(__LINE__);
    }
    ch = getChar();
  }while (ch != EOF);

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
  return result;
}

Value* parser() {
  Value *result = NULL;
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  char ch = getnextChar();
  while(ch != EOF) {
    if (ch == '#') {
      parseComment();
    } else {
      result = parseExpression();
      skipSpaces();
      if (getChar() == EOF) {
        break;
      } else {
        printError(__LINE__);
      }
    }
    ch = getChar();
  }
  printf("Parsed successfully\r\n");
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
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

  // TODO: parse the source program
  // TODO: generate correct LLVM instead of just an empty function
  Value *RetVal = parser();

  //Value *RetVal = ConstantInt::get(C, APInt(64, 0));
  Builder.CreateRet(RetVal);
  assert(verifyModule(*M));
  M->dump();
  return 0;
}

int main(int argc, char **argv) { 
  if (openFile(argc, argv) == true) {
    return compile(); 
  } 
  return -1;
}
