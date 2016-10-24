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
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
#include <cmath>
=======
>>>>>>> parsing done

using namespace llvm;
using namespace std;

static LLVMContext C;
static IRBuilder<NoFolder> Builder(C);
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
char gCurValue = -1;
int  gArgsLen = 6;
int  gLineNo = 1;
enum oper {ADD = 0, SUB, MUL, DIV, MOD};
bool debug = true;

Value* parseExpression();
void skipSpaces();
>>>>>>> parsing done

void usage(void) {
  printf("executable <input file.calc>\r\n");
  return;
}

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
char getChar() {
  return gCurValue;
}

void nextChar(void) {
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
  if (!cin.eof()) {
    gCurValue = cin.get();
    gOffset++;
=======
  if (!gInFile.eof()) {
    gCurValue = gInFile.get();
>>>>>>> parsing done
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
>>>>>>> parsing done
  //Move the pointer next to a
  getnextChar();
  for (i = 0; i < gArgsLen; i++) {
    if (accept('0' + (i - 0))) { //Change from int to char
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
        printf("Exit %s\r\n", __PRETTY_FUNCTION__);
      }
      return ConstantInt::get(Type::getInt64Ty(C), i);
    }  
  }
  sprintf(errmsg, "Invalid argument (a%c) used in the program", 
          getChar());
  printError(__LINE__, errmsg);
  return NULL;
>>>>>>> Change to add LLVM code
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
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      gOffset = 0;
=======
>>>>>>> parsing done
      continue;
    }
    break;
  }

  if (debug) {
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
    //printf("%sExit %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
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
      if (gOffset == 0) { 
        parseComment(tab+"\t");
      } else {
        printError(__LINE__, "Encounter Comment in the middle of a line");
      }
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
    printf("%sEnter %s\r\n", tab.c_str(), __PRETTY_FUNCTION__);
=======
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
>>>>>>> parsing done
  }
  char ch = getnextChar();
  while(ch != EOF) {
    if (ch == '#') {
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
      parseComment(tab+"\t");
    } else if ((ch == ' ') | (ch == '\n')) {
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
  return result;
=======
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
<<<<<<< d77025b4cd63efe9d68522c1c85219a17ecc7564
>>>>>>> parsing done
=======
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

<<<<<<< 007b32a346b51a1ed2d3aca298a9aa441cd05678
  gArgValues.clear();
  int argCount = 0;
  for (auto &Arg : F->args()) { 
    gArgValues[argCount++] = &Arg;
  }

  Value *RetVal = parser("");
=======
  // TODO: parse the source program
  // TODO: generate correct LLVM instead of just an empty function
  Value *RetVal = parser();

  //Value *RetVal = ConstantInt::get(C, APInt(64, 0));
>>>>>>> Adding the parsing code
  Builder.CreateRet(RetVal);
  assert(!verifyModule(*M, &outs()));
  M->dump();
  return 0;
}

int main(int argc, char **argv) { 
<<<<<<< a950ae686d28d2d6a86a474bb576227ca5c8f693
  if (argc > 1) {
    debug = true;
  }
  return compile(); 
=======
  if (openFile(argc, argv) == true) {
    return compile(); 
  } 
  return -1;
>>>>>>> parsing done
}
