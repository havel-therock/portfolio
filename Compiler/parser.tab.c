/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

    // change int ot long long
    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <map>
    #include <vector>
    #include <algorithm>
    #include <queue>
    #include <iostream>
    #include <fstream>

    using namespace std;
    
    extern FILE *yyin;
    ofstream outfile;
    //extern FILE *yyout;
    //?
// Lex stuff
    int yylex(void);
    void yyerror(const char*);
    extern int linum;
    int one_place = 10;
    int minus_one_place = 9;
    int next_free_address = 8;
    

//Memory    
    // 0 - not usable 
    // 1-10 - register like for operations 
    // in 10 always value 1
    // in 9 always value -1 
    // 11-? - iterators then variables then arrays in memory
    unsigned long long memory_counter = 11;
    map<string, struct iter_for*> iter_memory_map;
    map<string, unsigned long long> vars_memory_map;
    map<string, struct array_prop*> arrays_memory_map;
    
    queue<struct three_address_code*> tacodes;

    vector<string> asm_instructions;
    long long asm_lineno = 0;

    map<string, string> jumps; //index = number of label to jump to || value = jump type [JUMP, Jneg, Jpos, Jzero]
    map<string, int> labels; //index = number of label || value = number of line where the label stand (asm_lineno)

// distinct number for label generation
    long long label_number;

    struct array_prop{
        long long min_index;
        long long max_index;
        unsigned long long first_element_addr;
    };
    struct array_prop* newArrayProp(long long min_index, long long max_index, unsigned long long first_element_addr);

// Lex token
    struct token {
        string name;
        long long number_value;
        int linum;
    };
    struct token* newToken(string name, long long number_value, int linum);

// Abstract syntax tree
    struct ast {
        struct ast* node1;
        struct ast* node2;
        struct ast* node3;
        struct ast* node4;
        string type; // rule that match tokens eg. program, expression

        string name; // terminal (pid) name of token. Non-terminal name of subrule. 
        long long number_value; // value of NUM token 
        int linum;
        
    };
    struct ast* newSubtree(string type, struct ast* node1, struct ast* node2, struct ast* node3, struct ast* node4, string name, long long number_value, int linum);

//Semantic analysis 
    void semanticAnalysis(struct ast* root); // main function that runs all the other semantic functions
    void iteratorsMemoryReservation(vector<string> iterators, struct ast* root); // 
    void memoryReservation(struct ast* root); // variables + arrays reservations
    void checkProperVariableUsage(struct ast* root); // array out of bounds + undeclared variables
    void checkVariablesInit(vector<string> &initialized, struct ast* root); // go through ast and check for usage of uninitilize variables

    struct iter_for{
        unsigned long long memory_index;
        bool visibility;
    };

    struct iter_for* newIterFor(unsigned long long memory_index, bool visibility);
    void set_visibility(struct iter_for*, bool visibility);
// Three Address Code
    enum instruction { PLUS2, MINUS2, TIMES2, DIV2, MOD2, DEC2, INC2, 
                       LOAD2, STORE2, LOADI, STOREI, LOADNEXT2, STORENEXT2, 
                       JUMP2, JPOS2, JZERO2, JNEG2, 
                       READ2, WRITE2, 
                       HALT2, 
                       LABEL2};

    struct tac_argument {
        string type; // [ITER, VAR, ARR_VAR, ARR_NUM, NUM, LAB]
        string name;
        string array_index;
        long long num_value;
    };
    struct tac_argument* newTacArg(string type, string name, string array_index, long long num_value);

    struct three_address_code {
        enum instruction instr;
        struct tac_argument* arg1;
        struct tac_argument* arg2;
    };
    struct three_address_code* newTac(enum instruction instr, struct tac_argument* arg1, struct tac_argument* arg2);

    void generateTAC(struct ast* root);
    void genTACCommands(struct ast* commands_node);

    void genTACCommand(struct ast* command_node);
    void genTACAssign(struct ast* assign_node);
    void genTACIfelse(struct ast* ifelse_node);
    void genTACIf(struct ast* if_node);
    void genTACWhile(struct ast* while_node);
    void genTACDowhile(struct ast* dowhile_node);
    void genTACFor(struct ast* for_node);
    void genTACFordown(struct ast* fordown_node);
    void genTACRead(struct ast* read_node);
    void genTACWrite(struct ast* write_node);

    void genTACExpression(struct ast* expression_node);
    void genTACValue(struct ast* value_node);
    void genTACPlus(struct ast* plus_node);
    void genTACMinus(struct ast* minus_node);
    void genTACTimes(struct ast* times_node);
    void genTACDiv(struct ast* div_node);
    void genTACMod(struct ast* mod_node);

    void genTACCondition(struct ast* condition_node, struct tac_argument* label_start, struct tac_argument* label_end);
    void genTACEq(struct ast* eq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACNeq(struct ast* neq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACLe(struct ast* le_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACGe(struct ast* ge_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACLeq(struct ast* leq_node, struct tac_argument* true_l, struct tac_argument* false_l);
    void genTACGeq(struct ast* geq_node, struct tac_argument* true_l, struct tac_argument* false_l);

    struct tac_argument* genTACArgument(struct ast* value_node);

// generate asm
    void genASM();
    void genASMPlus(struct three_address_code* code);
    void genASMMinus(struct three_address_code* code);
    void genASMINC(struct three_address_code* code);
    void genASMDEC(struct three_address_code* code);
    void genASMTimes(struct three_address_code* code);
    void genASMDiv(struct three_address_code* code);
    void genASMMod(struct three_address_code* code);
    void genASMLoad(struct three_address_code* code);
    void genASMLoadNext(struct three_address_code* code);
    void genASMStore(struct three_address_code* code);
    void genASMStoreNext(struct three_address_code* code); 
    void genASMJump(struct three_address_code* code);
    void genASMJpos(struct three_address_code* code);
    void genASMJzero(struct three_address_code* code);
    void genASMJneg(struct three_address_code* code);
    void genASMRead(struct three_address_code* code);
    void genASMWrite(struct three_address_code* code);
    void genASMHalt(struct three_address_code* code);
    void genASMLabel(struct three_address_code* code);

    void genASMConst(long long const_value);

    void genASMParityVector(struct tac_argument* arg);
    void genASMCheckParity(unsigned long long mem_cell);
    
    void loadArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell);
    void loadNextArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell);

    void asmStoreHelp(struct tac_argument* arg); // use memory cell 1, 2
    void asmStoreHelpNext(struct tac_argument* arg); // use memory cell 1, 2
// label generator
    struct tac_argument* newLabel(); 
//utils 
    void printTACQueue();
    void printTAC(struct three_address_code* root);
    void printTACArgument(struct tac_argument* arg);

    void preProcess();


#line 257 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PLUS = 258,
    MINUS = 259,
    DIV = 260,
    TIMES = 261,
    MOD = 262,
    EQ = 263,
    NEQ = 264,
    LE = 265,
    GE = 266,
    LEQ = 267,
    GEQ = 268,
    DECLARE = 269,
    BEGIN2 = 270,
    ASSIGN = 271,
    THEN = 272,
    ELSE = 273,
    ENDIF = 274,
    ENDWHILE = 275,
    WHILE = 276,
    ENDDO = 277,
    FOR = 278,
    DO = 279,
    IF = 280,
    END = 281,
    FROM = 282,
    TO = 283,
    ENDFOR = 284,
    READ = 285,
    WRITE = 286,
    DOWNTO = 287,
    PID = 288,
    NUM = 289
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 194 "parser.y" /* yacc.c:355  */

    struct token* token;
    struct ast* tree;

#line 337 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 354 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  9
/* YYNRULES -- Number of rules.  */
#define YYNRULES  35
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  96

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      35,    36,     2,     2,    37,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    34,    33,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   217,   217,   226,   231,   238,   243,   250,   256,   260,
     266,   270,   274,   278,   282,   286,   291,   296,   300,   306,
     310,   314,   318,   322,   326,   332,   336,   340,   344,   348,
     352,   358,   363,   368,   373,   379
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PLUS", "MINUS", "DIV", "TIMES", "MOD",
  "EQ", "NEQ", "LE", "GE", "LEQ", "GEQ", "DECLARE", "BEGIN2", "ASSIGN",
  "THEN", "ELSE", "ENDIF", "ENDWHILE", "WHILE", "ENDDO", "FOR", "DO", "IF",
  "END", "FROM", "TO", "ENDFOR", "READ", "WRITE", "DOWNTO", "';'", "':'",
  "'('", "')'", "','", "PID", "NUM", "$accept", "program", "declarations",
  "commands", "command", "expression", "condition", "value", "identifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,    59,    58,    40,    41,    44,   288,   289
};
# endif

#define YYPACT_NINF -37

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-37)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -9,   -36,    25,     7,    -2,   -37,     2,   -37,     5,    10,
      88,    11,     8,   -29,    12,   -37,   -29,   -37,    13,   -29,
      14,   -37,    32,    21,    16,   -37,    29,     6,   -37,    34,
     121,    48,    36,    38,   -27,   -29,    43,   -37,   -37,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -37,   -37,   -37,
      30,    45,    52,    33,    53,    77,   -37,   -37,   -37,   -37,
     -37,   -37,   -25,    -1,    49,   -37,   -37,   -37,   -29,   -29,
     -29,   -29,   -29,    55,   -37,   -29,   -29,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,    69,    70,    65,   -37,
     -37,   -37,    99,   110,   -37,   -37
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     0,     5,     0,     1,     0,     9,     0,     0,
       0,     3,     0,     0,     0,     9,     0,     2,     0,     0,
      33,     8,     0,     0,     0,    31,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     9,    17,    18,
       0,     0,     0,    19,     0,     0,    25,    26,    27,    28,
      29,    30,     0,     0,     0,    34,    35,    10,     0,     0,
       0,     0,     0,     0,    13,     0,     0,    14,     9,    12,
      20,    21,    23,    22,    24,     4,     0,     0,     0,     9,
       9,    11,     0,     0,    15,    16
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -14,   -37,   -37,   -12,   -13,   -10
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     4,    10,    21,    52,    26,    27,    28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      22,    30,     3,    75,    31,     1,    33,    76,    32,    20,
      25,    50,    51,     7,    39,    40,    41,    42,    43,    44,
      22,    77,    53,    38,    55,     5,    56,    57,    58,    59,
      60,    61,    62,    64,    63,     8,    68,    69,    70,    71,
      72,     9,     6,    11,    12,    22,    23,    24,    35,    34,
      29,    20,    37,    38,    22,    80,    81,    82,    83,    84,
      36,    45,    86,    87,    88,    47,    65,    78,    79,    48,
      13,    49,    14,    15,    16,    92,    93,    54,    22,    18,
      19,    66,    22,    22,    91,    67,    13,    20,    14,    15,
      16,    85,    73,    89,    90,    18,    19,    74,    13,     0,
      14,    15,    16,    20,     0,     0,     0,    18,    19,    13,
       0,    14,    15,    16,    17,    20,     0,     0,    18,    19,
      13,     0,    14,    15,    16,     0,    20,     0,    94,    18,
      19,    13,     0,    14,    15,    16,     0,    20,     0,    95,
      18,    19,    46,     0,    14,    15,    16,     0,    20,     0,
       0,    18,    19,     0,     0,     0,     0,     0,     0,    20
};

static const yytype_int8 yycheck[] =
{
      10,    15,    38,    28,    16,    14,    19,    32,    18,    38,
      39,    38,    39,    15,     8,     9,    10,    11,    12,    13,
      30,    22,    35,    24,    38,     0,    39,    40,    41,    42,
      43,    44,    45,    47,    46,    37,     3,     4,     5,     6,
       7,    39,    35,    38,    34,    55,    35,    39,    16,    35,
      38,    38,    36,    24,    64,    68,    69,    70,    71,    72,
      39,    27,    75,    76,    78,    17,    36,    18,    19,    33,
      21,    33,    23,    24,    25,    89,    90,    34,    88,    30,
      31,    36,    92,    93,    19,    33,    21,    38,    23,    24,
      25,    36,    39,    24,    24,    30,    31,    20,    21,    -1,
      23,    24,    25,    38,    -1,    -1,    -1,    30,    31,    21,
      -1,    23,    24,    25,    26,    38,    -1,    -1,    30,    31,
      21,    -1,    23,    24,    25,    -1,    38,    -1,    29,    30,
      31,    21,    -1,    23,    24,    25,    -1,    38,    -1,    29,
      30,    31,    21,    -1,    23,    24,    25,    -1,    38,    -1,
      -1,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    14,    41,    38,    42,     0,    35,    15,    37,    39,
      43,    38,    34,    21,    23,    24,    25,    26,    30,    31,
      38,    44,    48,    35,    39,    39,    46,    47,    48,    38,
      43,    46,    48,    47,    35,    16,    39,    36,    24,     8,
       9,    10,    11,    12,    13,    27,    21,    17,    33,    33,
      38,    39,    45,    47,    34,    43,    47,    47,    47,    47,
      47,    47,    47,    46,    43,    36,    36,    33,     3,     4,
       5,     6,     7,    39,    20,    28,    32,    22,    18,    19,
      47,    47,    47,    47,    47,    36,    47,    47,    43,    24,
      24,    19,    43,    43,    29,    29
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    42,    42,    43,    43,
      44,    44,    44,    44,    44,    44,    44,    44,    44,    45,
      45,    45,    45,    45,    45,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    48
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     3,     8,     1,     6,     0,     2,     0,
       4,     7,     5,     5,     5,     9,     9,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 217 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("program", (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, NULL, "", 0, (yyvsp[-4].token)->linum);
        semanticAnalysis((yyval.tree));
        generateTAC((yyval.tree));
        //printTACQueue();
        genASM();
}
#line 1501 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 226 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[0].token)->name, 0, (yyvsp[0].token)->linum);
        (yyval.tree) = newSubtree("declarations", (yyvsp[-2].tree), leaf, NULL, NULL, "decPID", 0, (yyvsp[0].token)->linum);
    }
#line 1510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 231 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf1 = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-5].token)->name, 0, (yyvsp[-5].token)->linum);
        struct ast* leaf2 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[-3].token)->number_value, (yyvsp[-3].token)->linum);
        struct ast* leaf3 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[-1].token)->number_value, (yyvsp[-1].token)->linum);
        (yyval.tree) = newSubtree("declarations", (yyvsp[-7].tree), leaf1, leaf2, leaf3, "decARR", 0, (yyvsp[-5].token)->linum);
    }
#line 1521 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 238 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[0].token)->name, 0, (yyvsp[0].token)->linum);
        (yyval.tree) = newSubtree("declarations", NULL, leaf, NULL, NULL, "decPID", 0, (yyvsp[0].token)->linum);
    }
#line 1530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 243 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf1 = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-5].token)->name, 0, (yyvsp[-5].token)->linum);
        struct ast* leaf2 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[-3].token)->number_value, (yyvsp[-3].token)->linum);
        struct ast* leaf3 = newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[-1].token)->number_value, (yyvsp[-1].token)->linum);
        (yyval.tree) = newSubtree("declarations", NULL, leaf1, leaf2, leaf3, "decARR", 0, (yyvsp[-5].token)->linum);
    }
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 250 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = NULL;
    }
#line 1549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 256 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("commands", (yyvsp[-1].tree), (yyvsp[0].tree), NULL, NULL, "", 0, (yyvsp[0].tree)->linum);
    }
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 260 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = NULL;
    }
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 266 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, NULL, "ASSIGN", 0, (yyvsp[-2].token)->linum);
    }
#line 1573 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 270 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-5].tree), (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, "IFELSE", 0, (yyvsp[-6].token)->linum);
    }
#line 1581 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 274 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, NULL, "IF", 0, (yyvsp[-4].token)->linum);
    }
#line 1589 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 278 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, NULL, "WHILE", 0, (yyvsp[-4].token)->linum);
    }
#line 1597 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 282 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-3].tree), (yyvsp[-1].tree), NULL, NULL, "DOWHILE", 0, (yyvsp[-4].token)->linum);
    }
#line 1605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 286 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-7].token)->name, 0,(yyvsp[-7].token)->linum);
        (yyval.tree) = newSubtree("command", leaf, (yyvsp[-5].tree), (yyvsp[-3].tree), (yyvsp[-1].tree), "UPFOR", 0, (yyvsp[-8].token)->linum);
    }
#line 1614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 291 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf = newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-7].token)->name, 0,(yyvsp[-7].token)->linum);
        (yyval.tree) = newSubtree("command", leaf, (yyvsp[-5].tree), (yyvsp[-3].tree), (yyvsp[-1].tree), "DOWNFOR", 0, (yyvsp[-8].token)->linum);
    }
#line 1623 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 296 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-1].tree), NULL, NULL, NULL, "READ", 0, (yyvsp[-2].token)->linum);
    }
#line 1631 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 300 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("command", (yyvsp[-1].tree), NULL, NULL, NULL, "WRITE", 0, (yyvsp[-2].token)->linum);
    }
#line 1639 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 306 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[0].tree), NULL, NULL, NULL, "VALUE", 0, (yyvsp[0].tree)->linum);
    }
#line 1647 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 310 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "PLUS", 0, (yyvsp[-2].tree)->linum);
    }
#line 1655 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 314 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "MINUS", 0, (yyvsp[-2].tree)->linum);
    }
#line 1663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 318 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "TIMES", 0, (yyvsp[-2].tree)->linum);
    }
#line 1671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 322 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "DIV", 0, (yyvsp[-2].tree)->linum);
    }
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 326 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("expression", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "MOD", 0, (yyvsp[-2].tree)->linum);
    }
#line 1687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 332 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "EQ", 0, (yyvsp[-2].tree)->linum);
    }
#line 1695 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 336 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "NEQ", 0, (yyvsp[-2].tree)->linum);
    }
#line 1703 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 340 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "LE", 0, (yyvsp[-2].tree)->linum);
    }
#line 1711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 344 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "GE", 0, (yyvsp[-2].tree)->linum);
    }
#line 1719 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 348 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "LEQ", 0, (yyvsp[-2].tree)->linum);
    }
#line 1727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 352 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("condition", (yyvsp[-2].tree), (yyvsp[0].tree), NULL, NULL, "GEQ", 0, (yyvsp[-2].tree)->linum);
    }
#line 1735 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 358 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf =  newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[0].token)->number_value, (yyvsp[0].token)->linum);
        (yyval.tree) = newSubtree("value", leaf, NULL, NULL, NULL, "NUM", 0, (yyvsp[0].token)->linum); 
    }
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 363 "parser.y" /* yacc.c:1646  */
    {
        (yyval.tree) = newSubtree("value", (yyvsp[0].tree), NULL, NULL, NULL, "IDENTIFIER", 0, (yyvsp[0].tree)->linum); 
    }
#line 1752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 368 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf =  newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[0].token)->name, 0, (yyvsp[0].token)->linum);
        (yyval.tree) = newSubtree("identifier", leaf, NULL, NULL, NULL, "PID", 0, (yyvsp[0].token)->linum); 
    }
#line 1761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 373 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf1 =  newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-3].token)->name, 0, (yyvsp[-3].token)->linum);
        struct ast* leaf2 =  newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-1].token)->name, 0, (yyvsp[-1].token)->linum);
        (yyval.tree) = newSubtree("identifier", leaf1, leaf2, NULL, NULL, "PIDPID", 0, (yyvsp[-3].token)->linum); 
    }
#line 1771 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 379 "parser.y" /* yacc.c:1646  */
    {
        struct ast* leaf1 =  newSubtree("PID", NULL, NULL, NULL, NULL, (yyvsp[-3].token)->name, 0, (yyvsp[-3].token)->linum);
        struct ast* leaf2 =  newSubtree("NUM", NULL, NULL, NULL, NULL, "", (yyvsp[-1].token)->number_value, (yyvsp[-1].token)->linum);
        (yyval.tree) = newSubtree("identifier", leaf1, leaf2, NULL, NULL, "PIDNUM", 0, (yyvsp[-3].token)->linum); 
    }
#line 1781 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1785 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 386 "parser.y" /* yacc.c:1906  */



struct token* newToken(string name, long long number_value, int linum){
    struct token* nt = new token();//(struct token*) malloc(sizeof(struct token));
    if(!nt){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    if(!name.empty()){
        nt->name = name;
    }
    nt->number_value = number_value;
    nt->linum = linum;
    
    return nt;
}

struct ast* newSubtree(string type, struct ast* node1, struct ast* node2, struct ast* node3, struct ast* node4, string name, long long number_value, int linum){
    struct ast* nst = new ast();//(struct ast*) malloc(sizeof(struct ast));
    if(!nst){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    nst->type = type;
    nst->node1 = node1;
    nst->node2 = node2;
    nst->node3 = node3;
    nst->node4 = node4;
    if(!name.empty()){ // miss this maybe
        nst->name = name;
    }
    nst->number_value = number_value;
    nst->linum = linum;
    
    return nst;
}

void freeSubtree(struct ast* root){
    if(root == NULL)
        return;
    freeSubtree(root->node1);
    root->node1 = NULL;
    freeSubtree(root->node2);
    root->node2 = NULL;
    freeSubtree(root->node3);
    root->node3 = NULL;
    freeSubtree(root->node4);
    root->node4 = NULL;

    free(root);
    root = NULL;
}

struct array_prop* newArrayProp(long long min_index, long long max_index, unsigned long long first_element_addr){
    struct array_prop* ap = new array_prop();//(struct array_prop*) malloc(sizeof(struct array_prop));
    if(!ap){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    ap->min_index = min_index;
    ap->max_index = max_index;
    ap->first_element_addr = first_element_addr;
    return ap;
}

//semantic analysis
void semanticAnalysis(struct ast* root){
    vector<string> iterators;
    iteratorsMemoryReservation(iterators, root->node2);
    memoryReservation(root->node1);
    checkProperVariableUsage(root->node2);
    vector<string> vars_init;
    checkVariablesInit(vars_init, root->node2);

}

void iteratorsMemoryReservation(vector<string> iterators, struct ast* node){
    if(node == NULL){
        return;
    } else if(node->type.compare("commands") == 0){
        vector<string> copy_iter = iterators; //???
        iteratorsMemoryReservation(copy_iter, node->node1);
        iteratorsMemoryReservation(iterators, node->node2);
        return;
    
    } else if(node->name.compare("UPFOR") == 0 || node->name.compare("DOWNFOR") == 0){
        // add to iterators new iterator
        string new_iterator_name = node->node1->name;
        if(find(iterators.begin(), iterators.end(), new_iterator_name) != iterators.end()){
            //found
            string msg = "Bad usage of iterators in line " + to_string(node->node1->linum);
            yyerror(&msg[0]);
        }else{
            //not found
            iterators.push_back(new_iterator_name);
            // memory reservation 
            struct iter_for* new_it = newIterFor(memory_counter, false); 
            memory_counter++;
            //struct iter_for* new_it = newIterFor(memory_counter, false);
            memory_counter++;
            // second memory cell is for limit in for // needed for constant range in fors
            iter_memory_map[new_iterator_name] = new_it;
            iteratorsMemoryReservation(iterators, node->node2);
            iteratorsMemoryReservation(iterators, node->node3);
            set_visibility(new_it, true);
            iteratorsMemoryReservation(iterators, node->node4);
            set_visibility(new_it, false);
            return;
        }   
    } else if(node->name.compare("ASSIGN") == 0){
        string check_variable = node->node1->node1->name;
         if(find(iterators.begin(), iterators.end(), check_variable) != iterators.end()){
            //found
            string msg = "Bad iterator value modyfication in line " + to_string(node->node1->linum);
            yyerror(&msg[0]);
        }
        return;

    } else if(node->type.compare("identifier") == 0){
        if(iter_memory_map[node->node1->name] != NULL){
            if(iter_memory_map[node->node1->name]->visibility == false){
                string msg = "Iterator used out of scope in line " + to_string(node->node1->linum);
                yyerror(&msg[0]);
            }
        }
        if(node->node2 != NULL && iter_memory_map[node->node2->name] != NULL){
            if(iter_memory_map[node->node2->name]->visibility == false){
                string msg = "Iterator used out of scope in line " + to_string(node->node2->linum);
                yyerror(&msg[0]);
            }
        }
        return;
    } else {
        iteratorsMemoryReservation(iterators, node->node1);
        iteratorsMemoryReservation(iterators, node->node2);
        iteratorsMemoryReservation(iterators, node->node3);
        iteratorsMemoryReservation(iterators, node->node4);
    }
    
} 

void memoryReservation(struct ast* node){
    if(node == NULL){
        return;
    }
    memoryReservation(node->node1);
    if(node->name.compare("decPID") == 0){
        if(vars_memory_map[node->node2->name] == 0){ // simple type so 0 and not NULL
            vars_memory_map[node->node2->name] = memory_counter;
            memory_counter++;
        }else{
            string msg = "Redeclaration error in line " + to_string(node->node2->linum);
            yyerror(&msg[0]);
        }

        if(iter_memory_map[node->node2->name] != NULL){
            string msg = "Variable " + node->node2->name +" declared in line " + to_string(node->node2->linum) + ". Later used as iterator.";
            yyerror(&msg[0]);
        }

        if(arrays_memory_map[node->node2->name] != NULL){
            string msg = "In line " + to_string(node->node2->linum) + " variable " + node->node2->name + ", aleready declared as array.";
            yyerror(&msg[0]);
        }
        return;
        
    } else if(node->name.compare("decARR") == 0){
        if(arrays_memory_map[node->node2->name] == NULL){
            long long min_index = node->node3->number_value;
            long long max_index = node->node4->number_value;
            if(max_index < min_index){
                string msg = "Wrong range in array in line " + to_string(node->node2->linum);
                yyerror(&msg[0]);
            }

            unsigned long long first_memory_index = memory_counter;
            struct array_prop* new_array = newArrayProp(min_index, max_index, first_memory_index);
            memory_counter += (max_index - min_index + 1);
            arrays_memory_map[node->node2->name] = new_array;
        }else{
            string msg = "Redeclaration error in line " + to_string(node->node2->linum);
            yyerror(&msg[0]);
        }

        if(iter_memory_map[node->node2->name] != NULL){
            string msg = "Array " + node->node2->name +" declared in line " + to_string(node->node2->linum) + ". Later used as iterator.";
            yyerror(&msg[0]);
        }

        if(vars_memory_map[node->node2->name] != 0){
            string msg = "In line " + to_string(node->node2->linum) + " array " + node->node2->name + ", aleready declared as variable.";
            yyerror(&msg[0]);
        }
        return;
    } else {
        printf("Tu nigdy nie powinien byc - %s\n", &node->name[0]);
        return;
    }
    
}

void checkProperVariableUsage(struct ast* node){
    if(node == NULL){
        return;
    } else if(node->name.compare("UPFOR") == 0 || node->name.compare("DOWNFOR") == 0){
        string new_iterator_name = node->node1->name;
        struct iter_for* it = iter_memory_map[new_iterator_name];
        checkProperVariableUsage(node->node2);
        checkProperVariableUsage(node->node3);
        set_visibility(it, true);
        checkProperVariableUsage(node->node4);
        set_visibility(it, false);
        return;
    
    }/* else if(node->name.compare("ASSIGN")){
        if(iter_memory_map[node->node1->node1->name] != NULL){
            string msg = "In line " + to_string(node->node1->node1->linum) + " forbidden modification of iterator value.";
            yyerror(&msg[0]);
        }else{
            checkProperVariableUsage(node->node1);
            checkProperVariableUsage(node->node2);
            return;
        }
    } */
    else if(node->type.compare("identifier") == 0){
        if(node->name.compare("PID") == 0){
            if(iter_memory_map[node->node1->name] == NULL && vars_memory_map[node->node1->name] == 0){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared variable or wrong usage of array.";
                yyerror(&msg[0]);
            } else if(iter_memory_map[node->node1->name] != NULL){
                if(iter_memory_map[node->node1->name]->visibility == false){
                    string msg = "In line " + to_string(node->node1->linum) + " iterator out of scope.";
                    yyerror(&msg[0]);
                }
            }
        } else if(node->name.compare("PIDPID") == 0){
            if(arrays_memory_map[node->node1->name] == NULL){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared array or wrong usage of variable.";
                yyerror(&msg[0]);
            }

            if(iter_memory_map[node->node2->name] == NULL && vars_memory_map[node->node2->name] == 0){
                string msg = "In line " + to_string(node->node2->linum) + " undeclared variable or wrong usage of array.";
                yyerror(&msg[0]);
            } else if(iter_memory_map[node->node2->name] != NULL){
                if(iter_memory_map[node->node2->name]->visibility == false){
                    string msg = "In line " + to_string(node->node2->linum) + " iterator out of scope.";
                    yyerror(&msg[0]);
                }
            }
        } else if(node->name.compare("PIDNUM") == 0){
            if(arrays_memory_map[node->node1->name] == NULL){
                string msg = "In line " + to_string(node->node1->linum) + " undeclared array or wrong usage of variable.";
                yyerror(&msg[0]);
            } else {
                struct array_prop* ap = arrays_memory_map[node->node1->name];
                long long check_index = node->node2->number_value;
                if(ap->min_index > check_index || ap->max_index < check_index){
                    string msg = "In line " + to_string(node->node1->linum) + " index out of arrays bound.";
                    yyerror(&msg[0]);
                }
            }
        }
    } else {
        checkProperVariableUsage(node->node1);
        checkProperVariableUsage(node->node2);
        checkProperVariableUsage(node->node3);
        checkProperVariableUsage(node->node4);
    }
    return;
}

void checkVariablesInit(vector<string> &initialized, struct ast* node){
    if(node == NULL){
        return;
    } else if(node->name.compare("ASSIGN") == 0){
        checkVariablesInit(initialized, node->node2); // right side
        checkVariablesInit(initialized, node->node1->node2); // arrays goes to the same case as variables 
        string var_name = node->node1->node1->name;
        if(find(initialized.begin(), initialized.end(), var_name) == initialized.end()){
            //not found
            initialized.push_back(var_name);
        } 
    } else if(node->type.compare("identifier") == 0){
        string var_name = node->node1->name;
        if(find(initialized.begin(), initialized.end(), var_name) == initialized.end()){
                if(iter_memory_map[var_name] == NULL){
                    string msg = "In line " + to_string(node->node1->linum) + " variable " + node->node1->name + " not initialized.";
                    yyerror(&msg[0]);
                }
        } 
    } else if(node->name.compare("READ") == 0){
        string var_name = node->node1->node1->name;
        initialized.push_back(var_name);
    } else {
        checkVariablesInit(initialized, node->node1);
        checkVariablesInit(initialized, node->node2);
        checkVariablesInit(initialized, node->node3);
        checkVariablesInit(initialized, node->node4);
    }
    return;
}


struct iter_for* newIterFor(unsigned long long memory_index, bool visibility){
    struct iter_for* it = new iter_for(); //(struct iter_for*) malloc(sizeof(struct iter_for));
    if(!it){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    it->memory_index = memory_index;
    it->visibility = visibility;
    return it;
}
// visibility for iterators
void set_visibility(struct iter_for* it, bool visibility){
    it->visibility = visibility;
}

// TAC
struct three_address_code* newTac(enum instruction instr, struct tac_argument* arg1, struct tac_argument* arg2){
    struct three_address_code* tac = new three_address_code(); //(struct three_address_code*) malloc(sizeof(struct three_address_code));
    if(!tac){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    tac->instr = instr;
    tac->arg1 = arg1;
    tac->arg2 = arg2;
    return tac;
}

struct tac_argument* newTacArg(string type, string name, string array_index, long long num_value){
    struct tac_argument* tac_arg = new tac_argument();//(struct tac_argument*) malloc(sizeof(struct tac_argument));
    if(!tac_arg){
        yyerror("Not enough memory. HyHy.");
        exit(-1);
    }
    tac_arg->type = &type[0]; 
    // maybe change this to type 
    if(name.empty()){
        name = " ";
    }
    tac_arg->name = name;

    if(array_index.empty()){
        array_index = " ";
    }
    tac_arg->array_index = array_index;

    tac_arg->num_value = num_value;

    return tac_arg;
}

//TAC generation section

void generateTAC(struct ast* root){
    if(root != NULL){
        genTACCommands(root->node2);
    }
    struct three_address_code* h = newTac(HALT2, NULL, NULL);
    tacodes.push(h);
}

void genTACCommands(struct ast* commands_node){
    if(commands_node == NULL){
        return;
    }
    genTACCommands(commands_node->node1);
    genTACCommand(commands_node->node2);

}

void genTACCommand(struct ast* command_node){
    if(command_node->name.compare("ASSIGN") == 0){
        genTACAssign(command_node);
    } else if(command_node->name.compare("IFELSE") == 0){
        genTACIfelse(command_node);
    } else if(command_node->name.compare("IF") == 0){
        genTACIf(command_node);
    } else if(command_node->name.compare("WHILE") == 0){
        genTACWhile(command_node);
    } else if(command_node->name.compare("DOWHILE") == 0){
        genTACDowhile(command_node);
    } else if(command_node->name.compare("UPFOR") == 0){
        genTACFor(command_node);
    } else if(command_node->name.compare("DOWNFOR") == 0){
        genTACFordown(command_node);
    } else if(command_node->name.compare("READ") == 0){
        genTACRead(command_node);
    } else if(command_node->name.compare("WRITE") == 0){
        genTACWrite(command_node);
    } else {
        string msg = "Error in ast command node.";
        yyerror(&msg[0]);
    }
}

void genTACAssign(struct ast* assign_node){
    genTACExpression(assign_node->node2);
    struct tac_argument* arg1 = NULL;
    if(assign_node->node1->name.compare("PID") == 0){
        arg1 = newTacArg("VAR", assign_node->node1->node1->name, "", 0);
    } else if(assign_node->node1->name.compare("PIDPID") == 0){
        arg1 = newTacArg("ARR_VAR", assign_node->node1->node1->name, assign_node->node1->node2->name, 0);
    } else if(assign_node->node1->name.compare("PIDNUM") == 0){
        arg1 = newTacArg("ARR_NUM", assign_node->node1->node1->name, "", assign_node->node1->node2->number_value);
    }

    struct three_address_code* tac = newTac(STORE2, arg1, NULL);
    tacodes.push(tac);
    
}

void genTACIfelse(struct ast* ifelse_node){
    struct tac_argument* label_start = newLabel();
    struct tac_argument* label_else = newLabel();
    struct tac_argument* label_end = newLabel();

    genTACCondition(ifelse_node->node1, label_start, label_else);
    struct three_address_code* tac_label_start = newTac(LABEL2, label_start, NULL);
    tacodes.push(tac_label_start);
    
    genTACCommands(ifelse_node->node2);
    struct three_address_code* tac_jump = newTac(JUMP2, label_end, NULL);
    tacodes.push(tac_jump);
    struct three_address_code* tac_label_else = newTac(LABEL2, label_else, NULL);
    tacodes.push(tac_label_else);

    genTACCommands(ifelse_node->node3);
    struct three_address_code* tac_label_end = newTac(LABEL2, label_end, NULL);
    tacodes.push(tac_label_end);
}

void genTACIf(struct ast* if_node){
    struct tac_argument* label_start = newLabel();
    struct tac_argument* label_end = newLabel();
    genTACCondition(if_node->node1, label_start, label_end);
    
    struct three_address_code* tac_label_start = newTac(LABEL2, label_start, NULL);
    tacodes.push(tac_label_start);
    genTACCommands(if_node->node2);

    struct three_address_code* tac_label_end = newTac(LABEL2, label_end, NULL);
    tacodes.push(tac_label_end);
}

void genTACWhile(struct ast* while_node){
    struct tac_argument* label_while_start = newLabel();
    struct tac_argument* label_while_true = newLabel();
    struct tac_argument* label_while_false = newLabel();

    struct three_address_code* tac_while_start = newTac(LABEL2, label_while_start, NULL);
    tacodes.push(tac_while_start);
    
    genTACCondition(while_node->node1, label_while_true, label_while_false);
    struct three_address_code* tac_while_true = newTac(LABEL2, label_while_true, NULL);
    tacodes.push(tac_while_true);

    genTACCommands(while_node->node2);

    struct three_address_code* tac_while_jump_start = newTac(JUMP2, label_while_start, NULL);
    tacodes.push(tac_while_jump_start);

    struct three_address_code* tac_while_false = newTac(LABEL2, label_while_false, NULL);
    tacodes.push(tac_while_false);

}


void genTACDowhile(struct ast* dowhile_node){
    struct tac_argument* label_while_start = newLabel();
    struct tac_argument* label_while_true = newLabel();
    struct tac_argument* label_while_false = newLabel();

    struct three_address_code* tac_while_start = newTac(LABEL2, label_while_start, NULL);
    tacodes.push(tac_while_start);
    genTACCommands(dowhile_node->node1);

    genTACCondition(dowhile_node->node2, label_while_true, label_while_false);
    
    struct three_address_code* tac_while_true = newTac(LABEL2, label_while_true, NULL);
    tacodes.push(tac_while_true);
    
    struct three_address_code* tac_while_jump_true = newTac(JUMP2, label_while_start, NULL);
    tacodes.push(tac_while_jump_true);

    struct three_address_code* tac_while_false = newTac(LABEL2, label_while_false, NULL);
    tacodes.push(tac_while_false);
}

void genTACFor(struct ast* for_node){
// FOR DYNAMIC RANGE 
/*

//pre for
    struct tac_argument* value1 = genTACArgument(for_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", for_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* label_for_start = newLabel();
    //struct tac_argument* label_for_true = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter < val2 
    struct tac_argument* value2 = genTACArgument(for_node->node3);

    struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//
    genTACCommands(for_node->node4);

// increment of iterator    
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_plus_iter1_1 = newTac(PLUS2, iter1, one);
    tacodes.push(tac_plus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL);
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);
*/
// FOR DYNAMIC RANGE END

//###########################################################

// FOR CONST RANGE 

//pre for
    struct tac_argument* value1 = genTACArgument(for_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", for_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* value2 = genTACArgument(for_node->node3); 
    //struct three_address_code* tac_load_limit = newTac(LOAD2, value2, NULL); // perhaps it is useless
    //tacodes.push(tac_load_limit);

    struct three_address_code* tac_value2_minus_value1 = newTac(MINUS2, value2, value1);
    tacodes.push(tac_value2_minus_value1);

    struct three_address_code* tac_store_limit = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit);

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter <= val2
    // IF limit >= 0
    struct three_address_code* load_limit_for_check = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(load_limit_for_check);

    //struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    //tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//

//  do in loop commands
    genTACCommands(for_node->node4);
//

// increment of iterator  //optimize with INC  
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_plus_iter1_1 = newTac(PLUS2, iter1, one);
    tacodes.push(tac_plus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//

// decrement of iterator limit
    struct three_address_code* tac_load_limit_before_dec = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(tac_load_limit_before_dec);

    struct three_address_code* tac_limit_minus_1 = newTac(DEC2, NULL, NULL);
    tacodes.push(tac_limit_minus_1);

    struct three_address_code* tac_store_limit_after_dec = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit_after_dec);

//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL);
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

// FOR CONST RANGE END

}

void genTACFordown(struct ast* fordown_node){
//FORDOWN DYNAMIC RANGE
/*
//pre for
    struct tac_argument* value1 = genTACArgument(fordown_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);
    struct tac_argument* iter1 = newTacArg("ITER", fordown_node->node1->name, "", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);
// IF iter > val2 
    struct tac_argument* value2 = genTACArgument(fordown_node->node3);

    struct three_address_code* tac_minus_iter1_val2 = newTac(MINUS2, value2, iter1); //update memory te dwa miejsca ostatnie i przed maybe not
    tacodes.push(tac_minus_iter1_val2);

    struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL);
    tacodes.push(tac_jump_pos); // push here ?? 
//
    genTACCommands(fordown_node->node4);
// decrement of iterator    
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_minus_iter1_1 = newTac(MINUS2, iter1, one);
    tacodes.push(tac_minus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL); // possibly problem  endless loops change from jump to jump pos or jump neg
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

*/    
//FORDOWN DYNAMIC RANGE END

//###########################################################

// FORDOWN CONST RANGE 

//pre for
    struct tac_argument* value1 = genTACArgument(fordown_node->node2);
    struct three_address_code* tac_load = newTac(LOAD2, value1, NULL);
    tacodes.push(tac_load);

    struct tac_argument* iter1 = newTacArg("ITER", fordown_node->node1->name, " ", 0);
    struct three_address_code* tac_store = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store);

    struct tac_argument* value2 = genTACArgument(fordown_node->node3); 
    //struct three_address_code* tac_load_limit = newTac(LOAD2, value2, NULL); // perhaps it is useless
    //tacodes.push(tac_load_limit);

// limit set
    struct three_address_code* tac_value1_minus_value2 = newTac(MINUS2, value1, value2);
    tacodes.push(tac_value1_minus_value2);

    struct three_address_code* tac_store_limit = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit);
// 

    struct tac_argument* label_for_start = newLabel();
    struct tac_argument* label_for_false = newLabel();

    struct three_address_code* tac_for_start = newTac(LABEL2, label_for_start, NULL);
    tacodes.push(tac_for_start);

// IF iter >= val2
    // IF limit >= 0
    struct three_address_code* load_limit_for_check = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(load_limit_for_check);

    //struct three_address_code* tac_minus_val2_iter1 = newTac(MINUS2, value2, iter1);
    //tacodes.push(tac_minus_val2_iter1);

    //struct three_address_code* tac_jump_pos = newTac(JPOS2, label_for_false, NULL); // something wrong here perhaps
    //tacodes.push(tac_jump_pos); //push here ? switch with this under
    struct three_address_code* tac_jump_neg = newTac(JNEG2, label_for_false, NULL); // something wrong here perhaps
    tacodes.push(tac_jump_neg); //push here ?   
//

//  do in loop commands
    genTACCommands(fordown_node->node4);
//

// decrement of iterator    //optimize with DEC
    struct tac_argument* one = newTacArg("NUM", "", "", 1);
    struct three_address_code* tac_minus_iter1_1 = newTac(MINUS2, iter1, one);
    tacodes.push(tac_minus_iter1_1);

    struct three_address_code* tac_store_iter1 = newTac(STORE2, iter1, NULL);
    tacodes.push(tac_store_iter1);
//

// decrement of iterator limit
    struct three_address_code* tac_load_limit_before_dec = newTac(LOADNEXT2, iter1, NULL);
    tacodes.push(tac_load_limit_before_dec);

    struct three_address_code* tac_limit_minus_1 = newTac(DEC2, NULL, NULL);
    tacodes.push(tac_limit_minus_1);

    struct three_address_code* tac_store_limit_after_dec = newTac(STORENEXT2, iter1, NULL);
    tacodes.push(tac_store_limit_after_dec);

//
    struct three_address_code* tac_for_jump_start = newTac(JUMP2, label_for_start, NULL); // possibly problem  endless loops change from jump to jump pos or jump neg
    tacodes.push(tac_for_jump_start);
    struct three_address_code* tac_for_false = newTac(LABEL2, label_for_false, NULL);
    tacodes.push(tac_for_false);

// FORDOWN CONST RANGE END

}

void genTACRead(struct ast* read_node){
    struct tac_argument* arg1 = NULL;
    if(read_node->node1->name.compare("PID") == 0){ // node1  --
        arg1 = newTacArg("VAR", read_node->node1->node1->name, "", 0);
    } else if(read_node->node1->name.compare("PIDPID") == 0){ // node1  --
        arg1 = newTacArg("ARR_VAR", read_node->node1->node1->name, read_node->node1->node2->name, 0);
    } else if(read_node->node1->name.compare("PIDNUM") == 0){ // node1  --
        arg1 = newTacArg("ARR_NUM", read_node->node1->node1->name, "", read_node->node1->node2->number_value);
    }

    struct three_address_code* tac_read = newTac(READ2, arg1, NULL);
    tacodes.push(tac_read);   
}
void genTACWrite(struct ast* write_node){
    struct tac_argument* arg1 = genTACArgument(write_node->node1); 
    struct three_address_code* tac_write = newTac(WRITE2, arg1, NULL);
    tacodes.push(tac_write); 
}

void genTACExpression(struct ast* expression_node){
    if(expression_node->name.compare("VALUE") == 0){
        genTACValue(expression_node);
    } else if(expression_node->name.compare("PLUS") == 0){
        genTACPlus(expression_node);
    } else if(expression_node->name.compare("MINUS") == 0){
        genTACMinus(expression_node);
    } else if(expression_node->name.compare("TIMES") == 0){
        genTACTimes(expression_node);
    } else if(expression_node->name.compare("DIV") == 0){
        genTACDiv(expression_node);
    } else if(expression_node->name.compare("MOD") == 0){
        genTACMod(expression_node);
    }
}

void genTACValue(struct ast* value_node){
    struct tac_argument* arg1 = genTACArgument(value_node->node1);
    struct three_address_code* load = newTac(LOAD2, arg1, NULL);
    tacodes.push(load);
}

void genTACPlus(struct ast* plus_node){
    struct tac_argument* arg1 = genTACArgument(plus_node->node1);
    struct tac_argument* arg2 = genTACArgument(plus_node->node2);
    struct three_address_code* plus = newTac(PLUS2, arg1, arg2);
    tacodes.push(plus);
}

void genTACMinus(struct ast* minus_node){
    struct tac_argument* arg1 = genTACArgument(minus_node->node1);
    struct tac_argument* arg2 = genTACArgument(minus_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);
}

// change here?
void genTACTimes(struct ast* times_node){
    struct tac_argument* arg1 = genTACArgument(times_node->node1);
    struct tac_argument* arg2 = genTACArgument(times_node->node2);
    struct three_address_code* times = newTac(TIMES2, arg1, arg2);
    tacodes.push(times);
}

void genTACDiv(struct ast* div_node){
    struct tac_argument* arg1 = genTACArgument(div_node->node1);
    struct tac_argument* arg2 = genTACArgument(div_node->node2);
    struct three_address_code* div = newTac(DIV2, arg1, arg2);
    tacodes.push(div);
}

void genTACMod(struct ast* mod_node){
    struct tac_argument* arg1 = genTACArgument(mod_node->node1);
    struct tac_argument* arg2 = genTACArgument(mod_node->node2);
    struct three_address_code* mod = newTac(MOD2, arg1, arg2);
    tacodes.push(mod);
}
// change here end?

void genTACCondition(struct ast* condition_node, struct tac_argument* true_l, struct tac_argument* false_l){
    if(condition_node->name.compare("EQ") == 0){
        genTACEq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("NEQ") == 0){
        genTACNeq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("LE") == 0){
        genTACLe(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("GE") == 0){
        genTACGe(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("LEQ") == 0){
        genTACLeq(condition_node, true_l, false_l);
    } else if(condition_node->name.compare("GEQ") == 0){
        genTACGeq(condition_node, true_l, false_l);
    }
}

void genTACEq(struct ast* eq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(eq_node->node1);
    struct tac_argument* arg2 = genTACArgument(eq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_zero = newTac(JZERO2, true_l, NULL);
    tacodes.push(j_zero);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACNeq(struct ast* neq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(neq_node->node1);
    struct tac_argument* arg2 = genTACArgument(neq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_zero = newTac(JZERO2, false_l, NULL);
    tacodes.push(j_zero);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}


void genTACLe(struct ast* le_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(le_node->node1);
    struct tac_argument* arg2 = genTACArgument(le_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, true_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACGe(struct ast* ge_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(ge_node->node1);
    struct tac_argument* arg2 = genTACArgument(ge_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg2, arg1);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, true_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, false_l, NULL);
    tacodes.push(jump_end);
}

void genTACLeq(struct ast* leq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(leq_node->node1);
    struct tac_argument* arg2 = genTACArgument(leq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg2, arg1);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, false_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}
void genTACGeq(struct ast* geq_node, struct tac_argument* true_l, struct tac_argument* false_l){
    struct tac_argument* arg1 = genTACArgument(geq_node->node1);
    struct tac_argument* arg2 = genTACArgument(geq_node->node2);
    struct three_address_code* minus = newTac(MINUS2, arg1, arg2);
    tacodes.push(minus);

    struct three_address_code* j_neg = newTac(JNEG2, false_l, NULL);
    tacodes.push(j_neg);
    struct three_address_code* jump_end = newTac(JUMP2, true_l, NULL);
    tacodes.push(jump_end);
}

struct tac_argument* genTACArgument(struct ast* value_node){
    if(value_node->name.compare("NUM") == 0){
        struct tac_argument* num = newTacArg("NUM", "", "", value_node->node1->number_value);
        return num;
    } else {
        if(value_node->node1->name.compare("PID") == 0){
            struct tac_argument* pid = NULL;
            string name_check = value_node->node1->node1->name; // where it's belong iters  or vars
            if(iter_memory_map[name_check] != NULL){
                pid = newTacArg("ITER", name_check, "", 0); // iterators
            } else {
                pid = newTacArg("VAR", name_check, "", 0); // variable
            }
            return pid;
        } else if(value_node->node1->name.compare("PIDPID") == 0){
            struct tac_argument* arr = newTacArg("ARR_VAR", value_node->node1->node1->name, value_node->node1->node2->name, 0); // iterators
            return arr;
        } else if(value_node->node1->name.compare("PIDNUM") == 0){
            struct tac_argument* arr = newTacArg("ARR_NUM", value_node->node1->node1->name, "", value_node->node1->node2->number_value); // iterators
            return arr;
        }
    }
    return NULL;
}

//label generator
struct tac_argument* newLabel(){
    label_number++;
    return newTacArg("LAB", " ", "", label_number);
}    

//TAC prints
void printTACQueue(){
    queue<struct three_address_code*> p = tacodes;
    while(!p.empty()){
        printTAC(p.front());
        p.pop();
    }
}
    
void printTAC(struct three_address_code* root){
    switch (root->instr){
        case PLUS2:
            printf("PLUS ");
            break;
        case MINUS2:
            printf("MINUS ");
            break;
        case INC2:
            printf("INC");
            break;
        case DEC2:
            printf("DEC");
            break;
        case TIMES2:
            printf("TIMES ");
            break;
        case DIV2:
            printf("DIV ");
            break;
        case MOD2:
            printf("MOD ");
            break;
        case LOAD2:
            printf("LOAD ");
            break;
        case STORE2: 
            printf("STORE ");
            break;//, LOADI, STOREI, 
        case LOADNEXT2:
            printf("LOADNEXT ");
            break;
        case STORENEXT2: 
            printf("STORENEXT ");
            break;//, LOADI, STOREI, 
        case JUMP2:
            printf("JUMP ");
            break;
        case JPOS2:
            printf("JPOS ");
            break;
        case JZERO2:
            printf("JZERO ");
            break;
        case JNEG2:
            printf("JNEG ");
            break;
        case READ2:
            printf("READ ");
            break;
        case WRITE2:
            printf("WRITE ");
            break; 
        case HALT2:
            printf("HALT ");
            break;
        case LABEL2:
            printf("LABEL "); 
            break;
        default: 
            printf(" ???? ");
            break;
    }
    
    printTACArgument(root->arg1);
    printTACArgument(root->arg2);
    printf("\n");

}

//print tac argument
void printTACArgument(struct tac_argument* arg){
    if(arg == NULL){
        return;
    }else if(arg->type.compare("ITER") == 0){
        printf("%s ", &arg->name[0]);
    } else if(arg->type.compare("VAR") == 0){
        printf("%s ", &arg->name[0]);
    } else if(arg->type.compare("ARR_VAR") == 0){
        printf("%s(%s) ", &arg->name[0], &arg->array_index[0]);
    } else if(arg->type.compare("ARR_NUM") == 0){
        printf("%s(%lld) ", &arg->name[0], arg->num_value);
    } else if(arg->type.compare("NUM") == 0){
        printf("%lld ", arg->num_value);
    } else if(arg->type.compare("LAB") == 0){
        printf("%s%lld ", &arg->type[0], arg->num_value);
    }
}

// generate asm
void genASM(){
    preProcess();
    // qureue froent 
    // pop
    // if odpowiedni uruchamiam 
    //first run over tacodes when jump convert into label number
    //and labels gone while labels map are being set to return proper number line of 'label'
    queue<struct three_address_code*> tac_copy = tacodes;
    while(!tac_copy.empty()){
        struct three_address_code* tac_into_asm = tac_copy.front();
        tac_copy.pop();
        switch (tac_into_asm->instr){
        case PLUS2:
            genASMPlus(tac_into_asm);
            //printf("PLUS ");
            break;
        case MINUS2:
            genASMMinus(tac_into_asm);
            //printf("MINUS ");
            break;
        case INC2:
            genASMINC(tac_into_asm);
            //printf("MINUS ");
            break;
        case DEC2:
            genASMDEC(tac_into_asm);
            //printf("MINUS ");
            break;
        case TIMES2: // Start ? to throw out
            genASMTimes(tac_into_asm);
            //printf("TIMES ");
            break;
        case DIV2:
            genASMDiv(tac_into_asm);
            //printf("DIV ");
            break;
        case MOD2:
            genASMMod(tac_into_asm); // end?
            //printf("MOD ");
            break;
        case LOAD2:
            genASMLoad(tac_into_asm);
            //printf("LOAD ");
            break;
        case STORE2:
            genASMStore(tac_into_asm); 
            //printf("STORE ");
            break;//, LOADI, STOREI, 
        case LOADNEXT2:
            genASMLoadNext(tac_into_asm);
            //printf("LOAD ");
            break;
        case STORENEXT2:
            genASMStoreNext(tac_into_asm); 
            //printf("STORE ");
            break; 
        case JUMP2:
            genASMJump(tac_into_asm);
            //printf("JUMP ");
            break;
        case JPOS2:
            genASMJpos(tac_into_asm);
            //printf("JPOS ");
            break;
        case JZERO2:
            genASMJzero(tac_into_asm);
            //printf("JZERO ");
            break;
        case JNEG2:
            genASMJneg(tac_into_asm);
            //printf("JNEG ");
            break;
        case READ2:
            genASMRead(tac_into_asm);
            //printf("READ ");
            break;
        case WRITE2:
            genASMWrite(tac_into_asm);
            //printf("WRITE ");
            break; 
        case HALT2:
            genASMHalt(tac_into_asm);
            //printf("HALT ");
            break;
        case LABEL2:
            genASMLabel(tac_into_asm);
            //printf("LABEL "); 
            break;
        default: 
            printf("    # ???? ");
            break;
    }

    }
    // now we have numbers instead of jumps, we need to repair this here
    // second run over the asm_instructions this time,  we convert numbers of labels  to real line numbers
    for(int i = 0; i < asm_instructions.size(); i++){
        if(asm_instructions[i].compare(to_string(atoll(&asm_instructions[i][0]))) == 0){
            //number so it is a jump to label
            asm_instructions[i] = jumps[asm_instructions[i]] + to_string(labels[asm_instructions[i]]); //+ "   " + asm_instructions[i];
        }
    }

    //third run over the asm_instructions to print everything 
    for(int i = 0; i < asm_instructions.size(); i++){
        // change to output file
        outfile << asm_instructions[i] << endl;
    }



    // else stuff

    

}

void genASMPlus(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 1);
    loadArgIntoMemory(code->arg2, 0);
    asm_instructions.push_back("ADD 1");
    asm_lineno++;
}

void genASMMinus(struct three_address_code* code){
    loadArgIntoMemory(code->arg2, 1);
    loadArgIntoMemory(code->arg1, 0);
    asm_instructions.push_back("SUB 1");
    asm_lineno++;
}

void genASMINC(struct three_address_code* code){
    asm_instructions.push_back("INC");
    asm_lineno++;
}

void genASMDEC(struct three_address_code* code){
    asm_instructions.push_back("DEC");
    asm_lineno++;
}

void genASMTimes(struct three_address_code* code){ // use memory cells 1, 2, 3.

    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);

    struct tac_argument* l_arg2_less_0 = newLabel(); 
    struct three_address_code* label_arg2_less_0 = newTac(LABEL2, l_arg2_less_0, NULL);

    struct tac_argument* l_end_end = newLabel(); 
    struct three_address_code* label_end_end = newTac(LABEL2, l_end_end, NULL);

    struct tac_argument* l_shift = newLabel(); 
    struct three_address_code* label_shift = newTac(LABEL2, l_shift, NULL);
    
    struct tac_argument* l_add = newLabel(); 
    struct three_address_code* label_add = newTac(LABEL2, l_add, NULL);
    
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    //optimize multiplication by one 

    // generate parity form smaller argument 
    // how to check if arg1 < arg2 or arg1 > arg2
    //loadArgIntoMemory(code->arg1, 0);
    //struct three_address_code jpos_arg1_g_zero = newTac(JPOS2, l_arg1_g_0, NULL);
    genASMParityVector(code->arg2); //temp arg2
    
//p[2] value of arg1
    loadArgIntoMemory(code->arg1, 2);  
    // only here change for TIMES rejestr 0 * arg2

//p[3] current value of multiplication. start from 0

    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;

// LABEL START
    genASMLabel(label_start);
// decrement memory counter
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;        
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    memory_counter--;
//
//check parity & end condition
    asm_instructions.push_back("LOADI "+ to_string(next_free_address));
    asm_lineno++;
    struct three_address_code* jpos_shift = newTac(JPOS2, l_shift, NULL);
    genASMJpos(jpos_shift);
    struct three_address_code* jneg_add = newTac(JNEG2, l_add, NULL);
    genASMJneg(jneg_add);
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
//
//Label shift
    genASMLabel(label_shift);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_as = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_as);
// label ADD
    genASMLabel(label_add);
    asm_instructions.push_back("LOAD 2");
    asm_lineno++;
    asm_instructions.push_back("ADD 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_aa = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_aa);
// Label end
    genASMLabel(label_end);
// pointer of memory to after p[memory_counter] = 0 cell
    memory_counter++;
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    
    //sign correction when
    // IF a < 0 && b < 0
    // IF a > 0 && b < 0
    //BOTH CASES looks identical in ASM
    // najpierw STORE 1
    
    //asm_instructions.push_back("STORE 3");
    //asm_lineno++;
    loadArgIntoMemory(code->arg2, 0); // when optimize need this to change
    struct three_address_code* jneg_arg2_l_0 = newTac(JNEG2, l_arg2_less_0, NULL);
    genASMJneg(jneg_arg2_l_0);
    struct three_address_code* jump_end_end = newTac(JUMP2, l_end_end, NULL);
    genASMJump(jump_end_end);
// label arg2 less tthan 0
    genASMLabel(label_arg2_less_0);

    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
// label end end
    genASMLabel(label_end_end);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;

    // Jneg B
    // JUMP END
    //LABEL NEGB
    // JNEG A
// CASE IF a > 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //JUMP END
//lABEL IF a < 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //LABEL END
    
}

void genASMTimes2(unsigned long long memory_cell_arg1, struct three_address_code* code){ // use memory cells 1, 2, 3.

    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);

    struct tac_argument* l_arg2_less_0 = newLabel(); 
    struct three_address_code* label_arg2_less_0 = newTac(LABEL2, l_arg2_less_0, NULL);

    struct tac_argument* l_end_end = newLabel(); 
    struct three_address_code* label_end_end = newTac(LABEL2, l_end_end, NULL);

    struct tac_argument* l_shift = newLabel(); 
    struct three_address_code* label_shift = newTac(LABEL2, l_shift, NULL);
    
    struct tac_argument* l_add = newLabel(); 
    struct three_address_code* label_add = newTac(LABEL2, l_add, NULL);
    
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    //optimize multiplication by one 

    // generate parity form smaller argument 
    // how to check if arg1 < arg2 or arg1 > arg2
    //loadArgIntoMemory(code->arg1, 0);
    //struct three_address_code jpos_arg1_g_zero = newTac(JPOS2, l_arg1_g_0, NULL);
    genASMParityVector(code->arg2); //temp arg2
    
//p[2] value of arg1
//    loadArgIntoMemory(code->arg1, 2);  
    asm_instructions.push_back("LOAD " + to_string(memory_cell_arg1));
    asm_lineno++;
    asm_instructions.push_back("STORE 2");
    asm_lineno++;
// only here change for TIMES rejestr 0 * arg2

//p[3] current value of multiplication. start from 0

    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;

// LABEL START
    genASMLabel(label_start);
// decrement memory counter
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;        
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    memory_counter--;
//
//check parity & end condition
    asm_instructions.push_back("LOADI "+ to_string(next_free_address));
    asm_lineno++;
    struct three_address_code* jpos_shift = newTac(JPOS2, l_shift, NULL);
    genASMJpos(jpos_shift);
    struct three_address_code* jneg_add = newTac(JNEG2, l_add, NULL);
    genASMJneg(jneg_add);
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
//
//Label shift
    genASMLabel(label_shift);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_as = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_as);
// label ADD
    genASMLabel(label_add);
    asm_instructions.push_back("LOAD 2");
    asm_lineno++;
    asm_instructions.push_back("ADD 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
    struct three_address_code* jump_start_aa = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start_aa);
// Label end
    genASMLabel(label_end);
// pointer of memory to after p[memory_counter] = 0 cell
    memory_counter++;
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
    
    //sign correction when
    // IF a < 0 && b < 0
    // IF a > 0 && b < 0
    //BOTH CASES looks identical in ASM
    // najpierw STORE 1
    
    //asm_instructions.push_back("STORE 3");
    //asm_lineno++;
    loadArgIntoMemory(code->arg2, 0); // when optimize need this to change
    struct three_address_code* jneg_arg2_l_0 = newTac(JNEG2, l_arg2_less_0, NULL);
    genASMJneg(jneg_arg2_l_0);
    struct three_address_code* jump_end_end = newTac(JUMP2, l_end_end, NULL);
    genASMJump(jump_end_end);
// label arg2 less tthan 0
    genASMLabel(label_arg2_less_0);

    asm_instructions.push_back("LOAD 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("SUB 3");
    asm_lineno++;
    asm_instructions.push_back("STORE 3");
    asm_lineno++;
// label end end
    genASMLabel(label_end_end);
    asm_instructions.push_back("LOAD 3");
    asm_lineno++;

    // Jneg B
    // JUMP END
    //LABEL NEGB
    // JNEG A
// CASE IF a > 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //JUMP END
//lABEL IF a < 0 && b < 0
    // STORE 1
    // SUB 1
    // SUB 1
    //LABEL END
    
}

void plusPlusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    //???
    loadArgIntoMemory(code->arg2, 7); 
    //???
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jpos_max_mul = newTac(JPOS2, l_set_max_mul, NULL);
    genASMJpos(jpos_max_mul);
//
// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

    struct three_address_code* jneg_reduce_mul = newTac(JNEG2, l_reduce_mul, NULL);
    genASMJneg(jneg_reduce_mul);

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);
    
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++;    
}   

void plusMinusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    
    loadArgIntoMemory(code->arg2, 7); 
    
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jpos_max_mul = newTac(JPOS2, l_set_max_mul, NULL);
    genASMJpos(jpos_max_mul);
//

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

// modyfication
    asm_instructions.push_back("SUB 7");
    asm_lineno++;
    asm_instructions.push_back("DEC");
    asm_lineno++;
//
    struct three_address_code* jneg_reduce_mul = newTac(JNEG2, l_reduce_mul, NULL);
    genASMJneg(jneg_reduce_mul);

// modyfication
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("ADD 7");
    asm_lineno++;
//   

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    asm_instructions.push_back("DEC");
    asm_lineno++;

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++; 
}

void minusPlusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    
    loadArgIntoMemory(code->arg2, 7); 
    
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jneg_max_mul = newTac(JNEG2, l_set_max_mul, NULL);
    genASMJneg(jneg_max_mul);
//

  //  asm_instructions.push_back("LOAD 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("SUB 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("SUB 6");
  //  asm_lineno++;
  //  asm_instructions.push_back("STORE 6");
  //  asm_lineno++;

// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

// modyfication
    asm_instructions.push_back("SUB 7");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
//
    struct three_address_code* jpos_reduce_mul = newTac(JPOS2, l_reduce_mul, NULL);
    genASMJpos(jpos_reduce_mul);

// modyfication
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("ADD 7");
    asm_lineno++;
//   

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    asm_instructions.push_back("DEC");
    asm_lineno++;

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++; 
}

void minusMinusDivide(struct three_address_code* code){
    struct tac_argument* l_set_max_mul = newLabel(); 
    struct three_address_code* label_set_max_mul = newTac(LABEL2, l_set_max_mul, NULL);
    struct tac_argument* l_step = newLabel(); 
    struct three_address_code* label_step = newTac(LABEL2, l_step, NULL);
    struct tac_argument* l_reduce_mul = newLabel(); 
    struct three_address_code* label_reduce_mul = newTac(LABEL2, l_reduce_mul, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    
    // p[6] multiplicator. power of 2
    //p[7] arg2 ??? maybe not necessary
    loadArgIntoMemory(code->arg1, 5);
    asm_instructions.push_back("LOAD " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    //???
    loadArgIntoMemory(code->arg2, 7); 
    //???
// LABEL SET MAX POWER OF TWO
    genASMLabel(label_set_max_mul);

    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;

    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;

    struct three_address_code* jneg_max_mul = newTac(JNEG2, l_set_max_mul, NULL);
    genASMJneg(jneg_max_mul);
//
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("SUB 6");
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
// LABEL STEP
// if mul* arg2 < arg1
    genASMLabel(label_step);
    genASMTimes2(6, code);
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    asm_instructions.push_back("SUB 1");
    asm_lineno++;

    struct three_address_code* jpos_reduce_mul = newTac(JPOS2, l_reduce_mul, NULL);
    genASMJpos(jpos_reduce_mul);

    asm_instructions.push_back("STORE 5");
    asm_lineno++;
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("ADD 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;

// LABEL reduce_mul
    genASMLabel(label_reduce_mul);
// case for nice dividing faster to end
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    struct three_address_code* jzero_end_rest = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_rest);
    
    asm_instructions.push_back("LOAD 6");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 6");
    asm_lineno++;
    struct three_address_code* jzero_end_mul = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end_mul);
    struct three_address_code* jump_step = newTac(JUMP2, l_step, NULL);
    genASMJump(jump_step);
// label end
    genASMLabel(label_end);
    asm_instructions.push_back("LOAD 4");
    asm_lineno++;   
}


void genASMDiv(struct three_address_code* code){ // use cells (1,2,3) <= multiplication (4,5,6,7) <= division part
    // 4 current value of division
    // 5 current rest from division

    struct tac_argument* l_arg1_plus = newLabel(); 
    struct three_address_code* label_arg1_plus = newTac(LABEL2, l_arg1_plus, NULL);
    struct tac_argument* l_arg1_minus = newLabel(); 
    struct three_address_code* label_arg1_minus = newTac(LABEL2, l_arg1_minus, NULL);
    struct tac_argument* l_arg_zero = newLabel(); 
    struct three_address_code* label_arg_zero = newTac(LABEL2, l_arg_zero, NULL);

    struct tac_argument* l_arg1_plus_arg2_plus = newLabel(); 
    struct three_address_code* label_arg1_plus_arg2_plus = newTac(LABEL2, l_arg1_plus_arg2_plus, NULL);
    struct tac_argument* l_arg1_plus_arg2_minus = newLabel(); 
    struct three_address_code* label_arg1_plus_arg2_minus = newTac(LABEL2, l_arg1_plus_arg2_minus, NULL);
    struct tac_argument* l_arg1_minus_arg2_plus = newLabel(); 
    struct three_address_code* label_arg1_minus_arg2_plus = newTac(LABEL2, l_arg1_minus_arg2_plus, NULL);
    struct tac_argument* l_arg1_minus_arg2_minus = newLabel(); 
    struct three_address_code* label_arg1_minus_arg2_minus = newTac(LABEL2, l_arg1_minus_arg2_minus, NULL);

    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
   

// dont know if necessary
    asm_instructions.push_back("SUB 0");
    asm_lineno++;
    asm_instructions.push_back("STORE 4");
    asm_lineno++;
    asm_instructions.push_back("STORE 5");
    asm_lineno++;
// set starter as zero

// determine case
    loadArgIntoMemory(code->arg1, 0);
    
    struct three_address_code* jpos_arg1_plus = newTac(JPOS2, l_arg1_plus, NULL);
    genASMJpos(jpos_arg1_plus);
    struct three_address_code* jneg_arg1_minus = newTac(JNEG2, l_arg1_minus, NULL);
    genASMJneg(jneg_arg1_minus);
    struct three_address_code* jzero_arg1_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg1_zero);
// L+
    genASMLabel(label_arg1_plus);
    loadArgIntoMemory(code->arg2, 0);
    struct three_address_code* jpos_arg1_plus_arg2_plus = newTac(JPOS2, l_arg1_plus_arg2_plus, NULL);
    genASMJpos(jpos_arg1_plus_arg2_plus);
    struct three_address_code* jneg_arg1_plus_arg2_minus = newTac(JNEG2, l_arg1_plus_arg2_minus, NULL);
    genASMJneg(jneg_arg1_plus_arg2_minus);
    struct three_address_code* jzero_arg2_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg2_zero);

// L-
    genASMLabel(label_arg1_minus);
    loadArgIntoMemory(code->arg2, 0);
    struct three_address_code* jpos_arg1_minus_arg2_plus = newTac(JPOS2, l_arg1_minus_arg2_plus, NULL);
    genASMJpos(jpos_arg1_minus_arg2_plus);
    struct three_address_code* jneg_arg1_minus_arg2_minus = newTac(JNEG2, l_arg1_minus_arg2_minus, NULL);
    genASMJneg(jneg_arg1_minus_arg2_minus);
    struct three_address_code* jzero_arg22_zero = newTac(JZERO2, l_arg_zero, NULL);
    genASMJzero(jzero_arg22_zero);
// L++
    genASMLabel(label_arg1_plus_arg2_plus);
    plusPlusDivide(code);
    struct three_address_code* jump_end1 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end1);
// L+-
    genASMLabel(label_arg1_plus_arg2_minus);
    plusMinusDivide(code);
    struct three_address_code* jump_end2 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end2);
// L-+
    genASMLabel(label_arg1_minus_arg2_plus);
    minusPlusDivide(code);
    struct three_address_code* jump_end3 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end3);
// L--
    genASMLabel(label_arg1_minus_arg2_minus);
    minusMinusDivide(code);
    struct three_address_code* jump_end4 = newTac(JUMP2, l_end, NULL);
    genASMJump(jump_end4);
// L0
    genASMLabel(label_arg_zero);
// L END
    genASMLabel(label_end);
}

void genASMMod(struct three_address_code* code){
    //the worst idea
    genASMDiv(code);
    asm_instructions.push_back("LOAD 5");
    asm_lineno++;
    //
}

void genASMJump(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JUMP ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}

void genASMJpos(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JPOS ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}
void genASMJzero(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JZERO ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}
void genASMJneg(struct three_address_code* code){
    jumps[to_string(code->arg1->num_value)] = "JNEG ";
    asm_instructions.push_back(to_string(code->arg1->num_value));
    asm_lineno++;
}

void genASMLabel(struct three_address_code* code){
    labels[to_string(code->arg1->num_value)] = asm_lineno;
    //asm_instructions.push_back("LAB " + to_string(code->arg1->num_value) + " lineno:"+ to_string(asm_lineno));
    //asm_lineno++;
}

void genASMLoad(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 0);
}

void genASMLoadNext(struct three_address_code* code){
    loadNextArgIntoMemory(code->arg1, 0);
}

void genASMStoreNext(struct three_address_code* code){
    asmStoreHelpNext(code->arg1);
}


void genASMStore(struct three_address_code* code){ 
    asmStoreHelp(code->arg1);
}
void asmStoreHelp(struct tac_argument* arg){ // use memory cell 1, 2
    if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name];
        asm_instructions.push_back("STORE " + to_string(var_address));
        asm_lineno++;
   
    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value;
        asm_instructions.push_back("STORE " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }else{
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
           // cout << "array[var]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index]));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index;
        asm_instructions.push_back("STORE " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    /*(if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }*/
}

void asmStoreHelpNext(struct tac_argument* arg){ // use memory cell 1, 2
    if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name] + 1;
        asm_instructions.push_back("STORE " + to_string(var_address));
        asm_lineno++;
   
    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value + 1;
        asm_instructions.push_back("STORE " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
        if(iter_memory_map[arg->array_index] != NULL){
           // cout << "array[iter]" << endl;
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index + 1));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }else{
            asm_instructions.push_back("STORE 1");
            asm_lineno++;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index] + 1));
            asm_lineno++;
            asm_instructions.push_back("STORE 2");
            asm_lineno++;
            asm_instructions.push_back("LOAD 1");
            asm_lineno++;
            asm_instructions.push_back("STOREI 2");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index + 1;
        asm_instructions.push_back("STORE " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    /*(if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }*/
}


void genASMRead(struct three_address_code* code){
    asm_instructions.push_back("GET");
    asm_lineno++;
    asmStoreHelp(code->arg1);
}

void genASMWrite(struct three_address_code* code){
    loadArgIntoMemory(code->arg1, 0);
    asm_instructions.push_back("PUT");
    asm_lineno++;
}

void genASMHalt(struct three_address_code* code){
    asm_instructions.push_back("HALT");
    asm_lineno++;
}

void genASMConst(long long const_value){
    vector<string> q; 
    string zero = "SUB 0";
    //asm_instructions.push_back(zero); // if not working try unncoment
    //asm_lineno++; // if not working try unncoment
    // optimization with SHIFT / rozklad na czynniki pierwsze ////////////////////////////////////////////////////////
    while(const_value != 0){
        if(const_value > 0){
            if(const_value%2 == 0){
                q.push_back("SHIFT " + to_string(one_place));
                const_value = const_value/2;
            }else{
                q.push_back("INC");
                const_value--;
            }
        } else { // const value < 0
            if(const_value%2 == 0){
                q.push_back("SHIFT " + to_string(one_place));
                const_value = const_value/2;
            }else{
                q.push_back("DEC");
                const_value++;
            }
        }
    }
    q.push_back(zero);
    
    for(int i = q.size() - 1; i >= 0; i--){
        asm_instructions.push_back(q[i]);
        asm_lineno++;
    }

}

void loadArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell){  //using cell 1 // 0-8 memory cells
    if(arg->type.compare("NUM") == 0){
        genASMConst(arg->num_value);
   
    } else if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name];
        asm_instructions.push_back("LOAD " + to_string(var_address));
        asm_lineno++;

    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value;
        asm_instructions.push_back("LOAD " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter] load" << endl;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index));
            asm_lineno++;
            // load?
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }else{
            //if arg->var->type iter to z map iteratorow wyciagnij wartosc
            //??????????????
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index]));
            asm_lineno++;
            // load?
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }

    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index;
        asm_instructions.push_back("LOAD " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }
}

void loadNextArgIntoMemory(struct tac_argument* arg, unsigned long long memoryCell){  // 0-8 memory cells
    if(arg->type.compare("NUM") == 0){
        genASMConst(arg->num_value);
   
    } else if(arg->type.compare("VAR") == 0){
        unsigned long long var_address = vars_memory_map[arg->name] + 1;
        asm_instructions.push_back("LOAD " + to_string(var_address));
        asm_lineno++;

    } else if(arg->type.compare("ARR_NUM") == 0){
        unsigned long long address_array_num = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index + arg->num_value + 1;
        asm_instructions.push_back("LOAD " + to_string(address_array_num));
        asm_lineno++;
   
    }  else if(arg->type.compare("ARR_VAR") == 0){
        //if arg->var->type iter to z map iteratorow wyciagnij wartosc
        if(iter_memory_map[arg->array_index] != NULL){
            //cout << "array[iter] load next" << endl;
            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(iter_memory_map[arg->array_index]->memory_index + 1));
            asm_lineno++;
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }else{

            unsigned long long address_array_0 = arrays_memory_map[arg->name]->first_element_addr - arrays_memory_map[arg->name]->min_index;
            genASMConst(address_array_0);
            asm_instructions.push_back("ADD " + to_string(vars_memory_map[arg->array_index] + 1));
            asm_lineno++;
            asm_instructions.push_back("LOADI 0");
            asm_lineno++;
        }
    }  else if(arg->type.compare("ITER") == 0){
        unsigned long long iter_address = iter_memory_map[arg->name]->memory_index + 1;
        asm_instructions.push_back("LOAD " + to_string(iter_address));
        asm_lineno++;
    } else {
        string msg = "Load Label into memory ???? " + arg->type;
        yyerror(&msg[0]);
    }
    if(memoryCell > 0){
        asm_instructions.push_back("STORE " + to_string(memoryCell));
        asm_lineno++;
    }
}



// arguments proper order make
/*
void swapArgs(struct three_address_code* code){
    struct tac_argument* arg1 = code->arg1;
    struct tac_argument* arg2 = code->arg2;
    if(code->) {

    }
}*/

// pre process function set some constans 
void genASMCheckParity(unsigned long long mem_cell){ // if p[0] == 0 it's even number, else odd
    asm_instructions.push_back("LOAD " + to_string(mem_cell)); 
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place)); 
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(one_place)); 
    asm_lineno++;
    asm_instructions.push_back("SUB " + to_string(mem_cell));
    asm_lineno++;
}

void genASMParityVector(struct tac_argument* arg){ //use p[1]
    struct tac_argument* l_start = newLabel(); 
    struct three_address_code* label_start = newTac(LABEL2, l_start, NULL);
    struct tac_argument* l_odd1 = newLabel(); 
    struct three_address_code* label_odd1 = newTac(LABEL2, l_odd1, NULL);
    //struct tac_argument* l_odd2 = newLabel(); 
    //struct three_address_code* label_odd2 = newTac(LABEL2, l_odd2, NULL);
   

    struct tac_argument* l_arg_under_0 = newLabel(); 
    struct three_address_code* label_arg_under_0 = newTac(LABEL2, l_arg_under_0, NULL);

    struct tac_argument* l_end_id = newLabel(); 
    struct three_address_code* label_end_id = newTac(LABEL2, l_end_id, NULL);

    struct tac_argument* l_even = newLabel(); 
    struct three_address_code* label_even = newTac(LABEL2, l_even, NULL);
    struct tac_argument* l_memo_update = newLabel(); 
    struct three_address_code* label_memo_update = newTac(LABEL2, l_memo_update, NULL);
    struct tac_argument* l_end = newLabel(); 
    struct three_address_code* label_end = newTac(LABEL2, l_end, NULL);
    

    loadArgIntoMemory(arg, 1);
    //asm_instructions.push_back("STORE 1"); 
    //asm_lineno++;
//LABEL START 
    genASMLabel(label_start);
//
    asm_instructions.push_back("LOAD 1"); 
    asm_lineno++;
    struct three_address_code* jzero_end = newTac(JZERO2, l_end, NULL);
    genASMJzero(jzero_end);
    genASMCheckParity(1);

// odd arg > 0
    struct three_address_code* jneg_odd1 = newTac(JNEG2, l_odd1, NULL);
    genASMJneg(jneg_odd1);
// odd arg < 0
    //struct three_address_code* jpos_odd2 = newTac(JPOS2, l_odd2, NULL);
   // genASMJpos(jpos_odd2);
// even
    struct three_address_code* jzero_even = newTac(JZERO2, l_even, NULL);
    genASMJzero(jzero_even);

// LABEL ODD1
    genASMLabel(label_odd1);
//save parity
// optimize with store od memorycounter ? not storeI
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    //jneg
    struct three_address_code* jneg_under_0 = newTac(JNEG2, l_arg_under_0, NULL);
    genASMJneg(jneg_under_0);
    asm_instructions.push_back("DEC");
    asm_lineno++;
    struct three_address_code* jump_end_id = newTac(JUMP2, l_end_id, NULL);
    genASMJump(jump_end_id);
// label arg <0
    genASMLabel(label_arg_under_0);
//
    asm_instructions.push_back("INC"); 
    asm_lineno++;
// label en of increment / decrement
    genASMLabel(label_end_id);

    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update1 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update1);
// LABEL ODD2
   /* genASMLabel(label_odd2);
    //save parity
// optimize with store od memorycounter ? not storeI
    asm_instructions.push_back("DEC");
    asm_lineno++;
    //asm_instructions.push_back("SUB 0"); 
    //asm_lineno++;
    asm_instructions.push_back("DEC");
    asm_lineno++;
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    asm_instructions.push_back("INC"); 
    asm_lineno++;
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update2 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update2);*/
// LABEL EVEN
    genASMLabel(label_even);
//save parity
// optimize with store od memorycounter ? not storeI    
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STOREI " + to_string(next_free_address));
    asm_lineno++;
    memory_counter++;
//
    asm_instructions.push_back("LOAD 1");
    asm_lineno++;
    asm_instructions.push_back("SHIFT " + to_string(minus_one_place));
    asm_lineno++;
    asm_instructions.push_back("STORE 1");
    asm_lineno++;
    struct three_address_code* jump_memo_update3 = newTac(JUMP2, l_memo_update, NULL);
    genASMJump(jump_memo_update3);
// LABEL memoUPDATE
    genASMLabel(label_memo_update);
    asm_instructions.push_back("LOAD " + to_string(next_free_address));
    asm_lineno++;
    asm_instructions.push_back("INC");
    asm_lineno++;
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;

    struct three_address_code* jump_start = newTac(JUMP2, l_start, NULL);
    genASMJump(jump_start);
// LABEL END
    genASMLabel(label_end);
}

void preProcess(){
    // p[10] = 1
    genASMConst(1);
    asm_instructions.push_back("STORE " + to_string(one_place));
    asm_lineno++;
    
    // p[9] = -1
    genASMConst(-1);
    asm_instructions.push_back("STORE " + to_string(minus_one_place));
    asm_lineno++;
    
    // p[memory_counter] = 0;
    genASMConst(0);
    asm_instructions.push_back("STORE " + to_string(memory_counter));
    asm_lineno++;
    
    // memory_counter++
    memory_counter++;
    
    // p[8] = pierwszy wolny adres pamieci
    genASMConst(memory_counter);
    asm_instructions.push_back("STORE " + to_string(next_free_address));
    asm_lineno++;
}

void yyerror(char const* msg){
    fprintf(stderr, "\x1B[31m%s.\x1B[0m\n", msg);
    exit(-1);
}


int main(int argc, char const *argv[]) {
    if(argc == 2){
        //if(argv[1] != "/dev/stdin"){
            yyin = fopen(argv[1], "r");
            outfile.open("/dev/stdout");
        //}
    } else if(argc == 3){
        //if(argv[1] != "/dev/stdin"){
            yyin = fopen(argv[1], "r");
        //}
        //if(argv[2] != "/dev/stdout"){
           // ofstream outfile; 
            outfile.open(argv[2]);
        //}
    } else {
           // ofstream outfile; 
            outfile.open("/dev/stdout");
    }
    yyparse();

    fclose(yyin);
    outfile.close();
    
    return 0;
}

