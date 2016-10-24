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

void parseExpression();
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
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
      break;
    }  
  }
  if (i == gArgsLen) {
    sprintf(errmsg, "Invalid argument (a%c) used in the program", 
            getChar());
    printError(errmsg);
  }
  getnextChar();
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

//Guess this should return an LLVM object
void parseArithmeticOperation() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  char oper = getChar();
  parseExpression();
  parseExpression();
  //Get Oper1
  //Oper1 = parseExpression();
  //Oper2 = parseExpression();
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parseNumber() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  int num = 0, count = 0;
  char ch = getChar();
  while  ((ch >= 0) && (ch <= 9)) {
    num = (num * 10 * count++) + (0 + (ch - '0'));
  }
  //changed the int to number;
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parseRelationalOperation() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  if (accept('>')) {
    //This is greater than
    if (accept('=')) {
      //This is greater than equals 
    }
  } else if (accept('<')) {
    //This is less than
    if (accept('=')) {
      //This is less than equals 
    }
  } else if (accept('!') && accept('=')) {
    //This is not equal to
  } else if (accept('=') && accept('=')) {
    //This is double equals 
  }
  parseExpression();
  parseExpression();
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parseBoolExpression() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  skipSpaces();

  char ch = getnextChar();

  if (accept('t') && accept('r') && accept('u') && accept('e')) {
    //Its a true condition
  } else if (accept('f') && accept('a') && accept('l') 
      && accept('s') && accept('e')) {
    //Its a false condition
  } else if ((ch == '>') || (ch == '<') || (ch == '=') || 
             (ch == '!')) {
    parseRelationalOperation(); 
  } else if (ch == ('(')) {
    parseBoolExpression();
    if (accept(')') == false) {
      printError("Missing ) Paranthesis in boolean exp");
    }
  }

  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parseIf() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  if (accept('i') && accept('f')) {
    //Move till you find the ( of the bool expression
      parseBoolExpression();
      parseExpression();
      parseExpression();
  } else {
    printError();
  }
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void skipSpaces() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  while (true) {
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

/* This function is called with the current pointer
 * at ( */
void parseExpression() {
  char errmsg[75];
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }

  skipSpaces();

  char ch = getChar();

  while (ch != EOF) {
    if (ch == '#') {
      parseComment();
      getnextChar();
    } else if (ch == 'a') {
      parseArgs();
      break;
    } else if (ch == '\n') {
      //Increment the line number, so that we can give a 
      //meaningful error message
      gLineNo++;
    } else if (ch == ' ') {
      //Ignore White space
    } else if ((ch == '+') || (ch == '-') || (ch == '*') || 
               (ch == '/') || (ch == '%')) {
      parseArithmeticOperation(); 
      break;
    } else if ((ch >= 0) && (ch <= 9)) {
      return parseNumber();
    } else if (ch == '(') {
      getnextChar();
      return parseExpression();
      if (check(')') == false) {
        printError("Missing Matching paranthesis");
      }
    } else if (ch == 'i') {
      parseIf();
      break;
    } else if (ch == ')') {
      getnextChar();
      break;
    } else {
      printError();
    }
    ch = getnextChar();
  }
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
}

void parser() {
  if (debug) {
    printf("Enter %s\r\n", __PRETTY_FUNCTION__);
  }
  char ch = getnextChar();
  while(ch != EOF) {
    if (ch == '#') {
      parseComment();
    } else {
      parseExpression();
      skipSpaces();
      if (getChar() == EOF) {
        break;
      } else {
        printError();
      }
    }
    ch = getnextChar();
  }
  printf("Parsed successfully\r\n");
  if (debug) {
    printf("Exit %s\r\n", __PRETTY_FUNCTION__);
  }
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

  Value *RetVal = ConstantInt::get(C, APInt(64, 0));
  Builder.CreateRet(RetVal);
  assert(!verifyModule(*M, &outs()));
  M->dump();
  return 0;
}

int main(int argc, char **argv) { 
  if (openFile(argc, argv) == true) {
    parser();
    //return compile(); 
  } 
  return -1;
}
