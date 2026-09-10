/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         CMDparse
#define yylex           CMDlex
#define yyerror         CMDerror
#define yydebug         CMDdebug
#define yynerrs         CMDnerrs
#define yylval          CMDlval
#define yychar          CMDchar
#define yylloc          CMDlloc

/* First part of user prologue.  */
#line 4 "CMDgram.y"


// bison -d -v -p CMD -o CMDgram.cpp -HCMDgram.h CMDgram.y
// OLD: bison --defines=cmdgram.h --verbose -o cmdgram.cpp -p CMD CMDgram.y

// Make sure we don't get gram.h twice.
#define _CMDGRAM_H_

#include <stdlib.h>
#include <stdio.h>
#include "console/console.h"
#include "console/torquescript/compiler.h"
#include "console/consoleInternal.h"
#include "core/strings/stringFunctions.h"

#ifndef YYDEBUG
#define YYDEBUG 0
#endif

#define YYSSIZE 350

int outtext(char *fmt, ...);
extern int serrors;
extern Vector<String> lines;

#define nil 0
#undef YY_ARGS
#define YY_ARGS(x)   x

int CMDlex();
void CMDerror(const char *, ...);


#ifdef alloca
#undef alloca
#endif
#define alloca dMalloc

template< typename T >
struct Token
{
   T value;
//    U32 lineNumber;
   S32 lineNumber;
};

#line 52 "CMDgram.y"

   /* Reserved word token definitions */
#line 71 "CMDgram.y"

   /* Constant and identifier token definitions */
#line 86 "CMDgram.y"

   /* Operator token definitions */

#line 136 "CMDgram.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "CMDgram.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_rwDEFINE = 3,                   /* rwDEFINE  */
  YYSYMBOL_rwENDDEF = 4,                   /* rwENDDEF  */
  YYSYMBOL_rwDECLARE = 5,                  /* rwDECLARE  */
  YYSYMBOL_rwDECLARESINGLETON = 6,         /* rwDECLARESINGLETON  */
  YYSYMBOL_rwBREAK = 7,                    /* rwBREAK  */
  YYSYMBOL_rwELSE = 8,                     /* rwELSE  */
  YYSYMBOL_rwCONTINUE = 9,                 /* rwCONTINUE  */
  YYSYMBOL_rwGLOBAL = 10,                  /* rwGLOBAL  */
  YYSYMBOL_rwIF = 11,                      /* rwIF  */
  YYSYMBOL_rwNIL = 12,                     /* rwNIL  */
  YYSYMBOL_rwRETURN = 13,                  /* rwRETURN  */
  YYSYMBOL_rwWHILE = 14,                   /* rwWHILE  */
  YYSYMBOL_rwDO = 15,                      /* rwDO  */
  YYSYMBOL_rwENDIF = 16,                   /* rwENDIF  */
  YYSYMBOL_rwENDWHILE = 17,                /* rwENDWHILE  */
  YYSYMBOL_rwENDFOR = 18,                  /* rwENDFOR  */
  YYSYMBOL_rwDEFAULT = 19,                 /* rwDEFAULT  */
  YYSYMBOL_rwFOR = 20,                     /* rwFOR  */
  YYSYMBOL_rwFOREACH = 21,                 /* rwFOREACH  */
  YYSYMBOL_rwFOREACHSTR = 22,              /* rwFOREACHSTR  */
  YYSYMBOL_rwIN = 23,                      /* rwIN  */
  YYSYMBOL_rwDATABLOCK = 24,               /* rwDATABLOCK  */
  YYSYMBOL_rwSWITCH = 25,                  /* rwSWITCH  */
  YYSYMBOL_rwCASE = 26,                    /* rwCASE  */
  YYSYMBOL_rwSWITCHSTR = 27,               /* rwSWITCHSTR  */
  YYSYMBOL_rwCASEOR = 28,                  /* rwCASEOR  */
  YYSYMBOL_rwPACKAGE = 29,                 /* rwPACKAGE  */
  YYSYMBOL_rwASSERT = 30,                  /* rwASSERT  */
  YYSYMBOL_ILLEGAL_TOKEN = 31,             /* ILLEGAL_TOKEN  */
  YYSYMBOL_CHRCONST = 32,                  /* CHRCONST  */
  YYSYMBOL_INTCONST = 33,                  /* INTCONST  */
  YYSYMBOL_TTAG = 34,                      /* TTAG  */
  YYSYMBOL_VAR = 35,                       /* VAR  */
  YYSYMBOL_IDENT = 36,                     /* IDENT  */
  YYSYMBOL_TYPEIDENT = 37,                 /* TYPEIDENT  */
  YYSYMBOL_DOCBLOCK = 38,                  /* DOCBLOCK  */
  YYSYMBOL_STRATOM = 39,                   /* STRATOM  */
  YYSYMBOL_TAGATOM = 40,                   /* TAGATOM  */
  YYSYMBOL_FLTCONST = 41,                  /* FLTCONST  */
  YYSYMBOL_42_ = 42,                       /* '+'  */
  YYSYMBOL_43_ = 43,                       /* '-'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '/'  */
  YYSYMBOL_46_ = 46,                       /* '<'  */
  YYSYMBOL_47_ = 47,                       /* '>'  */
  YYSYMBOL_48_ = 48,                       /* '='  */
  YYSYMBOL_49_ = 49,                       /* '.'  */
  YYSYMBOL_50_ = 50,                       /* '|'  */
  YYSYMBOL_51_ = 51,                       /* '&'  */
  YYSYMBOL_52_ = 52,                       /* '%'  */
  YYSYMBOL_53_ = 53,                       /* '('  */
  YYSYMBOL_54_ = 54,                       /* ')'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* ':'  */
  YYSYMBOL_57_ = 57,                       /* ';'  */
  YYSYMBOL_58_ = 58,                       /* '{'  */
  YYSYMBOL_59_ = 59,                       /* '}'  */
  YYSYMBOL_60_ = 60,                       /* '^'  */
  YYSYMBOL_61_ = 61,                       /* '~'  */
  YYSYMBOL_62_ = 62,                       /* '!'  */
  YYSYMBOL_63_ = 63,                       /* '@'  */
  YYSYMBOL_opINTNAME = 64,                 /* opINTNAME  */
  YYSYMBOL_opINTNAMER = 65,                /* opINTNAMER  */
  YYSYMBOL_opMINUSMINUS = 66,              /* opMINUSMINUS  */
  YYSYMBOL_opPLUSPLUS = 67,                /* opPLUSPLUS  */
  YYSYMBOL_opSHL = 68,                     /* opSHL  */
  YYSYMBOL_opSHR = 69,                     /* opSHR  */
  YYSYMBOL_opPLASN = 70,                   /* opPLASN  */
  YYSYMBOL_opMIASN = 71,                   /* opMIASN  */
  YYSYMBOL_opMLASN = 72,                   /* opMLASN  */
  YYSYMBOL_opDVASN = 73,                   /* opDVASN  */
  YYSYMBOL_opMODASN = 74,                  /* opMODASN  */
  YYSYMBOL_opANDASN = 75,                  /* opANDASN  */
  YYSYMBOL_opXORASN = 76,                  /* opXORASN  */
  YYSYMBOL_opORASN = 77,                   /* opORASN  */
  YYSYMBOL_opSLASN = 78,                   /* opSLASN  */
  YYSYMBOL_opSRASN = 79,                   /* opSRASN  */
  YYSYMBOL_opCAT = 80,                     /* opCAT  */
  YYSYMBOL_opEQ = 81,                      /* opEQ  */
  YYSYMBOL_opNE = 82,                      /* opNE  */
  YYSYMBOL_opGE = 83,                      /* opGE  */
  YYSYMBOL_opLE = 84,                      /* opLE  */
  YYSYMBOL_opAND = 85,                     /* opAND  */
  YYSYMBOL_opOR = 86,                      /* opOR  */
  YYSYMBOL_opSTREQ = 87,                   /* opSTREQ  */
  YYSYMBOL_opSTRNE = 88,                   /* opSTRNE  */
  YYSYMBOL_opCOLONCOLON = 89,              /* opCOLONCOLON  */
  YYSYMBOL_opDOTDOT = 90,                  /* opDOTDOT  */
  YYSYMBOL_rwRANGE = 91,                   /* rwRANGE  */
  YYSYMBOL_rwSTEP = 92,                    /* rwSTEP  */
  YYSYMBOL_rwStruct = 93,                  /* rwStruct  */
  YYSYMBOL_94_ = 94,                       /* '['  */
  YYSYMBOL_95_ = 95,                       /* '?'  */
  YYSYMBOL_UNARY = 96,                     /* UNARY  */
  YYSYMBOL_97_ = 97,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 98,                  /* $accept  */
  YYSYMBOL_start = 99,                     /* start  */
  YYSYMBOL_decl_list = 100,                /* decl_list  */
  YYSYMBOL_decl = 101,                     /* decl  */
  YYSYMBOL_package_decl = 102,             /* package_decl  */
  YYSYMBOL_fn_decl_list = 103,             /* fn_decl_list  */
  YYSYMBOL_statement_list = 104,           /* statement_list  */
  YYSYMBOL_stmt = 105,                     /* stmt  */
  YYSYMBOL_fn_decl_stmt = 106,             /* fn_decl_stmt  */
  YYSYMBOL_var_list_decl = 107,            /* var_list_decl  */
  YYSYMBOL_var_list = 108,                 /* var_list  */
  YYSYMBOL_param = 109,                    /* param  */
  YYSYMBOL_datablock_decl = 110,           /* datablock_decl  */
  YYSYMBOL_object_decl = 111,              /* object_decl  */
  YYSYMBOL_parent_block = 112,             /* parent_block  */
  YYSYMBOL_object_name = 113,              /* object_name  */
  YYSYMBOL_object_args = 114,              /* object_args  */
  YYSYMBOL_object_declare_block = 115,     /* object_declare_block  */
  YYSYMBOL_object_decl_list = 116,         /* object_decl_list  */
  YYSYMBOL_stmt_block = 117,               /* stmt_block  */
  YYSYMBOL_switch_stmt = 118,              /* switch_stmt  */
  YYSYMBOL_case_block = 119,               /* case_block  */
  YYSYMBOL_case_expr = 120,                /* case_expr  */
  YYSYMBOL_if_stmt = 121,                  /* if_stmt  */
  YYSYMBOL_while_stmt = 122,               /* while_stmt  */
  YYSYMBOL_for_stmt = 123,                 /* for_stmt  */
  YYSYMBOL_foreach_stmt = 124,             /* foreach_stmt  */
  YYSYMBOL_expression_stmt = 125,          /* expression_stmt  */
  YYSYMBOL_expr = 126,                     /* expr  */
  YYSYMBOL_slot_acc = 127,                 /* slot_acc  */
  YYSYMBOL_intslot_acc = 128,              /* intslot_acc  */
  YYSYMBOL_class_name_expr = 129,          /* class_name_expr  */
  YYSYMBOL_assign_op_struct = 130,         /* assign_op_struct  */
  YYSYMBOL_stmt_expr = 131,                /* stmt_expr  */
  YYSYMBOL_funcall_expr = 132,             /* funcall_expr  */
  YYSYMBOL_func_arg_item = 133,            /* func_arg_item  */
  YYSYMBOL_func_arg_list = 134,            /* func_arg_list  */
  YYSYMBOL_func_arg_list_decl = 135,       /* func_arg_list_decl  */
  YYSYMBOL_assert_expr = 136,              /* assert_expr  */
  YYSYMBOL_expr_list = 137,                /* expr_list  */
  YYSYMBOL_slot_assign_list_opt = 138,     /* slot_assign_list_opt  */
  YYSYMBOL_slot_assign_list = 139,         /* slot_assign_list  */
  YYSYMBOL_slot_assign = 140,              /* slot_assign  */
  YYSYMBOL_aidx_expr = 141                 /* aidx_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3774

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  98
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  186
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  458

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    62,     2,     2,     2,    52,    51,     2,
      53,    54,    44,    42,    55,    43,    49,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    56,    57,
      46,    48,    47,    95,    63,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    94,     2,    97,    60,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    58,    50,    59,    61,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    96
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   208,   208,   214,   215,   220,   222,   224,   229,   234,
     236,   242,   243,   248,   249,   250,   251,   252,   253,   254,
     256,   258,   260,   263,   273,   275,   277,   279,   285,   288,
     294,   295,   300,   302,   319,   321,   323,   325,   330,   335,
     337,   339,   341,   343,   345,   351,   352,   358,   359,   365,
     366,   372,   373,   375,   377,   382,   384,   389,   391,   396,
     398,   406,   408,   410,   415,   417,   422,   424,   429,   431,
     436,   438,   440,   442,   444,   446,   448,   450,   454,   457,
     460,   463,   466,   477,   480,   483,   486,   489,   492,   495,
     500,   505,   507,   509,   511,   513,   515,   517,   519,   521,
     523,   525,   527,   529,   531,   533,   535,   537,   539,   541,
     543,   545,   547,   549,   551,   553,   555,   563,   565,   567,
     569,   571,   573,   575,   577,   579,   581,   583,   585,   587,
     593,   595,   600,   602,   607,   609,   614,   616,   618,   620,
     622,   624,   626,   628,   630,   632,   634,   636,   642,   644,
     646,   648,   652,   663,   667,   678,   680,   682,   684,   686,
     718,   721,   724,   730,   732,   744,   746,   752,   753,   774,
     776,   788,   790,   796,   797,   802,   804,   810,   814,   825,
     829,   840,   842,   846,   857,   880,   882
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "rwDEFINE", "rwENDDEF",
  "rwDECLARE", "rwDECLARESINGLETON", "rwBREAK", "rwELSE", "rwCONTINUE",
  "rwGLOBAL", "rwIF", "rwNIL", "rwRETURN", "rwWHILE", "rwDO", "rwENDIF",
  "rwENDWHILE", "rwENDFOR", "rwDEFAULT", "rwFOR", "rwFOREACH",
  "rwFOREACHSTR", "rwIN", "rwDATABLOCK", "rwSWITCH", "rwCASE",
  "rwSWITCHSTR", "rwCASEOR", "rwPACKAGE", "rwASSERT", "ILLEGAL_TOKEN",
  "CHRCONST", "INTCONST", "TTAG", "VAR", "IDENT", "TYPEIDENT", "DOCBLOCK",
  "STRATOM", "TAGATOM", "FLTCONST", "'+'", "'-'", "'*'", "'/'", "'<'",
  "'>'", "'='", "'.'", "'|'", "'&'", "'%'", "'('", "')'", "','", "':'",
  "';'", "'{'", "'}'", "'^'", "'~'", "'!'", "'@'", "opINTNAME",
  "opINTNAMER", "opMINUSMINUS", "opPLUSPLUS", "opSHL", "opSHR", "opPLASN",
  "opMIASN", "opMLASN", "opDVASN", "opMODASN", "opANDASN", "opXORASN",
  "opORASN", "opSLASN", "opSRASN", "opCAT", "opEQ", "opNE", "opGE", "opLE",
  "opAND", "opOR", "opSTREQ", "opSTRNE", "opCOLONCOLON", "opDOTDOT",
  "rwRANGE", "rwSTEP", "rwStruct", "'['", "'?'", "UNARY", "']'", "$accept",
  "start", "decl_list", "decl", "package_decl", "fn_decl_list",
  "statement_list", "stmt", "fn_decl_stmt", "var_list_decl", "var_list",
  "param", "datablock_decl", "object_decl", "parent_block", "object_name",
  "object_args", "object_declare_block", "object_decl_list", "stmt_block",
  "switch_stmt", "case_block", "case_expr", "if_stmt", "while_stmt",
  "for_stmt", "foreach_stmt", "expression_stmt", "expr", "slot_acc",
  "intslot_acc", "class_name_expr", "assign_op_struct", "stmt_expr",
  "funcall_expr", "func_arg_item", "func_arg_list", "func_arg_list_decl",
  "assert_expr", "expr_list", "slot_assign_list_opt", "slot_assign_list",
  "slot_assign", "aidx_expr", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-342)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-91)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -342,    33,   794,  -342,     4,    -6,    -6,    -8,     0,     9,
     309,    31,   882,    39,    48,    58,    -6,    71,    74,    15,
      76,  -342,    92,  3680,   -31,  -342,  -342,  -342,  -342,  1589,
    1589,  1589,  1589,  1589,  -342,  -342,  -342,  -342,  -342,  -342,
    -342,  -342,  -342,  -342,  -342,    30,  3436,   713,  -342,    84,
    -342,  -342,   -11,  -342,  1589,    94,    96,  -342,  -342,  1589,
    -342,  -342,  -342,  1589,  2066,  -342,  1589,  -342,  -342,   140,
     652,   120,   127,   110,  1589,  1589,   115,  1589,  1589,   711,
    -342,  -342,  1589,  1589,  1589,  1589,  1589,  1589,  1589,  1589,
    1589,  1589,  1589,  -342,  1109,   138,    34,    34,  2113,    34,
      34,  -342,  1589,  1589,  1589,  1589,  1589,  1589,   144,  1589,
    1589,  1589,  1589,  1589,    -6,    -6,  1589,  1589,  1589,  1589,
    1589,  1589,  1589,  1589,  1589,  1589,  1589,  1149,  -342,   141,
     145,  2160,    20,  1589,  2207,  3436,   -23,  -342,  2254,   940,
     132,   468,  1189,  2301,   164,   167,  1589,  2348,  2395,   190,
    1594,  1641,  1589,  3436,  3436,  3436,  3436,  3436,  3436,  3436,
    3436,  3436,  3436,  3436,  3436,   -21,  1589,  3436,  -342,   137,
     143,   147,  -342,   134,   134,    34,    34,   101,   101,   -29,
    3577,  3633,    34,  3605,   336,  -342,  -342,    61,    61,  3661,
    3661,   101,   101,  3530,   507,   336,   336,  2442,  1589,  3436,
     -28,   148,   146,  -342,   151,  -342,  1589,   149,  3436,   149,
     882,  1589,   150,   882,  -342,  -342,  1589,   189,  1229,  2489,
    1269,   233,  1589,  2536,   152,   154,    12,  -342,  -342,   170,
    1589,  -342,   -16,  1589,  3694,    53,  1109,  -342,  1109,  1109,
    1589,  1589,    77,  1589,   165,   156,   141,   141,   118,   180,
     162,   162,   213,  3436,  -342,  -342,  2583,  1589,  2630,   882,
    2684,  1309,  1349,  2731,  1589,  1688,  2778,   172,   201,   201,
     174,  -342,   181,  2825,  -342,  3436,  1389,  -342,  -342,  -342,
     182,   183,   -20,  3483,  -342,  3436,  1589,  -342,  -342,   187,
     149,  -342,  1589,   191,   192,   882,  -342,  1742,  1589,  -342,
     882,   882,  2872,   882,  2919,  1429,  1796,   882,  1589,   882,
     176,  1589,   184,   185,  -342,  -342,  -342,  1589,  3436,  -342,
    -342,  -342,  3436,   983,   194,   162,   193,   195,   196,  -342,
     882,  1589,  1850,  -342,  -342,   882,  -342,   882,   882,  2966,
     882,  1589,  -342,  1904,  -342,    83,    16,  3436,  -342,  -342,
      93,  -342,  -342,   202,    85,    85,  -342,  1958,   882,  1589,
    -342,  -342,  -342,   882,  -342,  2012,   882,  1589,   199,   -25,
     219,   200,    83,  -342,  1589,  -342,  -342,  1026,   203,   205,
     211,   112,    85,   212,   882,  1589,  -342,  3013,  -342,   882,
    1589,  -342,  3060,  1589,  1469,  1589,   -19,   207,  -342,  3436,
     839,  -342,    85,  -342,  -342,   218,   112,  -342,  -342,  3107,
     882,  -342,  3154,   882,  3201,  1589,  3248,   -18,  1509,  1589,
    -342,   204,  -342,   220,  -342,   882,  -342,   882,  -342,  -342,
     102,  -342,   210,  1589,  3295,   -17,  -342,  -342,  -342,  -342,
     221,  1549,   113,  -342,   234,  1069,  -342,  1589,  3342,   224,
    1589,   116,  -342,  -342,  3389,   227,  -342,  -342
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,   123,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   122,   103,   128,   126,    27,   127,   120,   121,     0,
       0,     0,     0,     0,     4,     7,     5,     6,    17,   150,
      18,    13,    14,    15,    16,     0,     0,   124,   125,    91,
     148,   149,     0,   134,     0,     0,     0,    19,    20,     0,
     123,   103,    21,     0,     0,    91,     0,    11,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     137,   136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   167,     0,   101,   102,     0,   119,
     118,    24,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,    30,
       0,     0,    47,    47,     0,   171,     0,    22,     0,     0,
       0,   128,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   151,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   185,     0,     0,   163,   165,   168,
       0,     0,    92,    97,    98,    99,   100,   105,   106,   130,
      96,    95,    94,    93,   117,   132,   133,   112,   113,   109,
     110,   107,   108,   114,   111,   115,   116,     0,     0,   158,
      34,     0,    31,    32,     0,   135,    47,    45,    48,    45,
       0,     0,     0,     0,    57,    12,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     9,   169,     0,
       0,    25,     0,     0,   129,     0,     0,   160,   167,   167,
       0,     0,     0,     0,    35,     0,     0,    30,     0,     0,
      49,    49,    66,   172,    23,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     0,   152,   186,     0,   156,   164,   166,
       0,     0,     0,   104,   159,    36,     0,    11,    33,     0,
      45,    46,     0,     0,     0,     0,    69,     0,     0,    77,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,   170,    26,     0,   153,   161,
     162,   131,    37,     0,     0,    49,    50,    40,    44,    67,
       0,     0,     0,    76,    75,     0,    73,     0,     0,     0,
       0,     0,    83,     0,    84,   173,     0,    64,    59,    60,
       0,    28,    11,     0,    51,    51,    82,     0,     0,     0,
      74,    72,    71,     0,    89,     0,     0,     0,     0,     0,
       0,     0,   174,   175,     0,    11,   154,     0,    42,     0,
       0,    53,    52,     0,     0,     0,    78,     0,    70,     0,
       0,    85,     0,     0,     0,     0,     0,     0,   176,    65,
      61,    29,    51,    55,    39,     0,    54,    43,    79,     0,
       0,    86,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,    63,     0,    56,     0,    80,     0,    87,   181,
       0,   177,     0,     0,     0,     0,    11,    41,    81,    88,
       0,     0,     0,   179,     0,    62,   178,     0,     0,     0,
       0,     0,   182,   180,     0,     0,   184,   183
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -342,  -342,  -342,  -342,  -342,  -342,  -278,    -1,  -137,     2,
    -342,    41,  -342,  -336,  -195,  -120,  -240,  -334,   -97,  -207,
    -342,  -261,  -342,  -342,  -342,  -342,  -342,  -342,   363,  -342,
    -342,     1,   -43,    -2,  -342,    52,  -342,  -104,  -342,  -150,
    -342,   -56,  -341,  -235
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,    34,    35,   226,   139,    68,    37,   201,
     202,   203,    38,    39,   250,   207,   293,   380,   381,    69,
      40,   312,   346,    41,    42,    43,    44,    45,    46,    47,
      48,    55,    93,    65,    50,   168,   169,   170,    51,   136,
     371,   382,   373,   165
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    36,   232,   252,   128,   282,   255,    56,   313,   323,
      49,   294,   227,   209,   251,     4,   235,    73,   379,   379,
     243,   383,    94,   394,   239,     5,     6,    60,   267,   418,
      53,   398,   211,     3,   233,   233,   212,   233,   233,   211,
      52,   398,   129,   274,   374,   405,   379,    54,   242,    57,
      20,    76,   299,    21,    61,    23,    24,    58,    95,    26,
      27,    28,    59,    29,    30,   240,   379,   244,   423,   395,
     405,   270,   375,    31,   377,   419,   234,   321,   130,   432,
     444,    32,    33,   108,    66,   353,   248,   101,   329,   271,
       5,     6,    70,   333,   334,   325,   336,   400,   114,   115,
     342,    71,   344,   102,   103,   104,   105,   368,   211,   368,
     108,    72,   278,   111,   206,   185,   186,     5,     6,   369,
     370,   369,   370,   356,    74,   114,   115,    75,   360,    77,
     361,   362,   211,   364,   280,   281,   284,    49,   215,   422,
      78,   -90,   326,   102,   103,   104,   105,   132,   211,   133,
     108,   386,   376,   111,   140,   144,   388,   211,   445,   391,
     417,   440,   145,   146,   113,   114,   115,   350,   211,   116,
     117,   211,   449,   149,   171,   455,   200,   408,   104,   105,
     179,   204,   411,   108,   435,   216,   111,   221,   124,   125,
     222,   277,   236,     4,     5,     6,    60,   237,   114,   115,
     238,   246,   245,   426,   247,   249,   428,   254,    49,   272,
     268,    49,   269,   286,   287,   290,   291,   292,   438,    20,
     439,   295,    21,    61,    23,    24,   310,   311,    26,    27,
      28,   314,    29,    30,   345,   315,   319,   320,     5,     6,
      60,   324,    31,   348,   349,   327,   328,   393,   211,   289,
      32,    33,   352,   354,   355,   396,   378,    49,   441,   397,
     436,   402,   403,    20,   420,   430,    21,    61,    23,    24,
     404,   407,    26,    27,    28,   424,    29,    30,   446,   437,
     257,   453,   450,   442,   457,   406,    31,   288,   279,   372,
       0,     0,     0,    49,    32,    33,     0,   451,    49,    49,
       0,    49,     0,     0,     0,    49,     0,    49,     0,     0,
       0,     0,     0,     0,     5,     6,    60,     0,     0,     0,
       0,    49,   215,     0,   264,     0,     0,     0,    49,     0,
       0,     0,     0,    49,     0,    49,    49,     0,    49,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     0,     0,    49,     0,     0,     0,
       0,    49,    31,     0,    49,     0,    62,    63,     0,     0,
      32,    33,     0,    64,     0,    49,   215,     0,   102,   103,
     104,   105,    49,     0,     0,   108,     0,    49,   111,     0,
       0,     0,    96,    97,    98,    99,   100,     0,    49,   215,
     114,   115,     0,     0,   116,   117,     0,     0,    49,     0,
       0,    49,     0,     0,     0,     0,     0,   131,     0,     0,
       0,     0,   134,    49,     0,    49,   135,     0,     0,   138,
       0,     0,     0,   143,     0,     0,     0,   147,   148,     0,
     150,   151,   153,    49,   215,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,     0,   167,     0,     0,
       0,     0,     0,     0,     0,   173,   174,   175,   176,   177,
     178,     0,   180,   181,   182,   183,   184,     0,     0,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     199,   217,     0,     0,     0,   208,   208,     0,     0,     0,
       0,     0,     0,     0,     0,   219,     0,     0,     0,   223,
       0,     0,     0,     0,     0,   135,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,     0,     0,     0,    80,    81,     0,     0,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     0,   102,
     103,   104,   105,   106,   107,     0,   108,   109,   110,   111,
       0,   135,    92,     0,     0,     0,     0,   112,     0,   208,
     113,   114,   115,     0,   253,   116,   117,     0,     0,   256,
     258,   260,     0,   263,   265,   266,     0,     0,   118,   119,
     120,   121,   122,   273,   124,   125,   275,     0,     0,   167,
       0,   167,   167,   164,   283,     0,   285,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     297,     0,     0,     0,   302,   304,     0,   306,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   318,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
       0,     0,     0,     0,     0,   135,     0,     5,     6,    60,
       0,   332,     0,     0,     0,     0,     0,     0,   339,     0,
       0,   343,     0,     0,   347,     0,     0,     0,     0,     0,
     135,     0,    20,     0,     0,    21,    61,   141,    24,     0,
       0,    26,    27,    28,   357,    29,    30,     0,     0,     0,
       0,     0,     0,     0,   365,    31,     0,     0,     0,   142,
       0,     0,     0,    32,    33,     0,     5,     6,    60,     0,
       0,     0,   387,     0,     0,     0,     0,     0,     0,     0,
     392,     0,     0,     0,     0,     0,     0,   399,     0,     0,
       0,    20,     0,     0,    21,    61,    23,    24,   409,     0,
      26,    27,    28,   412,    29,    30,   414,   416,   164,     0,
       0,   127,     0,     0,    31,     0,     0,     0,     0,   152,
       0,     0,    32,    33,     0,     0,     0,     0,   135,    80,
      81,   434,   164,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     0,     0,     0,   135,     4,     0,     5,
       6,     7,     0,     8,   448,     9,     0,    10,    11,    12,
     135,     0,     0,   454,    13,    14,    15,     0,    16,    17,
       0,    18,     0,    19,    20,     0,     0,    21,    22,    23,
      24,     0,    25,    26,    27,    28,     0,    29,    30,     0,
       0,     0,     0,     0,     5,     6,     7,    31,     8,     0,
       9,     0,    10,    11,    12,    32,    33,     0,   421,    13,
      14,    15,     0,    16,    17,   311,    18,     0,     0,    20,
       0,     0,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,    29,    30,     0,     0,     0,     5,     6,     7,
       0,     8,    31,     9,     0,    10,    11,    12,     0,     0,
      32,    33,    13,    14,    15,     0,    16,    17,     0,    18,
       0,     0,    20,     0,     0,    21,    22,    23,    24,     0,
      25,    26,    27,    28,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     0,     0,     0,     0,
      67,     0,     0,    32,    33,     5,     6,     7,     0,     8,
       0,     9,     0,    10,    11,    12,     0,     0,     0,     0,
      13,    14,    15,     0,    16,    17,     0,    18,     0,     0,
      20,     0,     0,    21,    22,    23,    24,     0,    25,    26,
      27,    28,     0,    29,    30,     0,     0,     0,     5,     6,
       7,     0,     8,    31,     9,     0,    10,    11,    12,   214,
       0,    32,    33,    13,    14,    15,     0,    16,    17,     0,
      18,     0,     0,    20,     0,     0,    21,    22,    23,    24,
       0,    25,    26,    27,    28,     0,    29,    30,     0,     0,
       0,     5,     6,     7,     0,     8,    31,     9,     0,    10,
      11,    12,   351,     0,    32,    33,    13,    14,    15,     0,
      16,    17,     0,    18,     0,     0,    20,     0,     0,    21,
      22,    23,    24,     0,    25,    26,    27,    28,     0,    29,
      30,     0,     0,     0,     5,     6,     7,     0,     8,    31,
       9,     0,    10,    11,    12,   401,     0,    32,    33,    13,
      14,    15,     0,    16,    17,     0,    18,     0,     0,    20,
       0,     0,    21,    22,    23,    24,     0,    25,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   166,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   198,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,   218,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,   259,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,   262,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,   301,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,   303,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   317,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,   338,     0,     0,     0,     0,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   415,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   433,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     5,     6,    60,     0,     0,     0,
       0,     0,    31,     0,     0,     0,     0,   447,     0,     0,
      32,    33,     0,     0,     0,     0,     0,     0,     0,    20,
       0,     0,    21,    61,    23,    24,     0,     0,    26,    27,
      28,     0,    29,    30,     0,     0,   102,   103,   104,   105,
     106,   107,    31,   108,   109,   110,   111,     0,   228,   229,
      32,    33,     0,     0,   112,     0,     0,   113,   114,   115,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,   102,   103,   104,   105,   106,   107,   126,
     108,   109,   110,   111,     0,     0,   230,     0,   231,     0,
       0,   112,     0,     0,   113,   114,   115,     0,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
     102,   103,   104,   105,   106,   107,   126,   108,   109,   110,
     111,     0,   307,     0,     0,     0,     0,     0,   112,     0,
       0,   113,   114,   115,     0,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,     0,   308,     0,
       0,     0,     0,   126,   102,   103,   104,   105,   106,   107,
       0,   108,   109,   110,   111,     0,   330,     0,     0,     0,
       0,     0,   112,     0,     0,   113,   114,   115,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,     0,   331,     0,     0,     0,     0,   126,   102,   103,
     104,   105,   106,   107,     0,   108,   109,   110,   111,     0,
     340,     0,     0,     0,     0,     0,   112,     0,     0,   113,
     114,   115,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,     0,   341,     0,     0,     0,
       0,   126,   102,   103,   104,   105,   106,   107,     0,   108,
     109,   110,   111,     0,   358,     0,     0,     0,     0,     0,
     112,     0,     0,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,     0,
       0,     0,   359,     0,     0,   126,   102,   103,   104,   105,
     106,   107,     0,   108,   109,   110,   111,     0,   366,     0,
       0,     0,     0,     0,   112,     0,     0,   113,   114,   115,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,     0,     0,     0,   367,     0,     0,   126,
     102,   103,   104,   105,   106,   107,     0,   108,   109,   110,
     111,     0,   384,     0,     0,     0,     0,     0,   112,     0,
       0,   113,   114,   115,     0,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,     0,     0,     0,
     385,     0,     0,   126,   102,   103,   104,   105,   106,   107,
       0,   108,   109,   110,   111,     0,   389,     0,     0,     0,
       0,     0,   112,     0,     0,   113,   114,   115,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,     0,     0,     0,   390,     0,     0,   126,   102,   103,
     104,   105,   106,   107,     0,   108,   109,   110,   111,     0,
       0,     0,     0,   137,     0,     0,   112,     0,     0,   113,
     114,   115,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   102,   103,   104,   105,   106,
     107,   126,   108,   109,   110,   111,     0,   172,     0,     0,
       0,     0,     0,   112,     0,     0,   113,   114,   115,     0,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,   125,   102,   103,   104,   105,   106,   107,   126,   108,
     109,   110,   111,     0,   205,     0,     0,     0,     0,     0,
     112,     0,     0,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,   102,
     103,   104,   105,   106,   107,   126,   108,   109,   110,   111,
       0,   210,     0,     0,     0,     0,     0,   112,     0,     0,
     113,   114,   115,     0,     0,   116,   117,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   102,   103,   104,   105,
     106,   107,   126,   108,   109,   110,   111,     0,   213,     0,
       0,     0,     0,     0,   112,     0,     0,   113,   114,   115,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,   102,   103,   104,   105,   106,   107,   126,
     108,   109,   110,   111,     0,     0,     0,     0,   220,     0,
       0,   112,     0,     0,   113,   114,   115,     0,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
     102,   103,   104,   105,   106,   107,   126,   108,   109,   110,
     111,     0,   224,     0,     0,     0,     0,     0,   112,     0,
       0,   113,   114,   115,     0,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,   102,   103,   104,
     105,   106,   107,   126,   108,   109,   110,   111,     0,   225,
       0,     0,     0,     0,     0,   112,     0,     0,   113,   114,
     115,     0,     0,   116,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   102,   103,   104,   105,   106,   107,
     126,   108,   109,   110,   111,     0,     0,     0,   241,     0,
       0,     0,   112,     0,     0,   113,   114,   115,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,   102,   103,   104,   105,   106,   107,   126,   108,   109,
     110,   111,     0,     0,     0,     0,   261,     0,     0,   112,
       0,     0,   113,   114,   115,     0,     0,   116,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   102,   103,
     104,   105,   106,   107,   126,   108,   109,   110,   111,     0,
       0,     0,   249,     0,     0,     0,   112,     0,     0,   113,
     114,   115,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   102,   103,   104,   105,   106,
     107,   126,   108,   109,   110,   111,     0,   296,     0,     0,
       0,     0,     0,   112,     0,     0,   113,   114,   115,     0,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,   125,   102,   103,   104,   105,   106,   107,   126,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
     112,     0,     0,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,     0,
     298,     0,     0,     0,     0,   126,   102,   103,   104,   105,
     106,   107,     0,   108,   109,   110,   111,     0,   300,     0,
       0,     0,     0,     0,   112,     0,     0,   113,   114,   115,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,   102,   103,   104,   105,   106,   107,   126,
     108,   109,   110,   111,     0,     0,     0,     0,   305,     0,
       0,   112,     0,     0,   113,   114,   115,     0,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
     102,   103,   104,   105,   106,   107,   126,   108,   109,   110,
     111,     0,   309,     0,     0,     0,     0,     0,   112,     0,
       0,   113,   114,   115,     0,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,   102,   103,   104,
     105,   106,   107,   126,   108,   109,   110,   111,     0,     0,
       0,     0,   316,     0,     0,   112,     0,     0,   113,   114,
     115,     0,     0,   116,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   102,   103,   104,   105,   106,   107,
     126,   108,   109,   110,   111,     0,   335,     0,     0,     0,
       0,     0,   112,     0,     0,   113,   114,   115,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,   102,   103,   104,   105,   106,   107,   126,   108,   109,
     110,   111,     0,   337,     0,     0,     0,     0,     0,   112,
       0,     0,   113,   114,   115,     0,     0,   116,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   102,   103,
     104,   105,   106,   107,   126,   108,   109,   110,   111,     0,
     363,     0,     0,     0,     0,     0,   112,     0,     0,   113,
     114,   115,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   102,   103,   104,   105,   106,
     107,   126,   108,   109,   110,   111,     0,   410,     0,     0,
       0,     0,     0,   112,     0,     0,   113,   114,   115,     0,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,   125,   102,   103,   104,   105,   106,   107,   126,   108,
     109,   110,   111,     0,   413,     0,     0,     0,     0,     0,
     112,     0,     0,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,   122,   123,   124,   125,   102,
     103,   104,   105,   106,   107,   126,   108,   109,   110,   111,
       0,   425,     0,     0,     0,     0,     0,   112,     0,     0,
     113,   114,   115,     0,     0,   116,   117,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   118,   119,
     120,   121,   122,   123,   124,   125,   102,   103,   104,   105,
     106,   107,   126,   108,   109,   110,   111,     0,   427,     0,
       0,     0,     0,     0,   112,     0,     0,   113,   114,   115,
       0,     0,   116,   117,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   121,   122,
     123,   124,   125,   102,   103,   104,   105,   106,   107,   126,
     108,   109,   110,   111,     0,     0,     0,     0,   429,     0,
       0,   112,     0,     0,   113,   114,   115,     0,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   121,   122,   123,   124,   125,
     102,   103,   104,   105,   106,   107,   126,   108,   109,   110,
     111,     0,     0,     0,     0,   431,     0,     0,   112,     0,
       0,   113,   114,   115,     0,     0,   116,   117,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
     119,   120,   121,   122,   123,   124,   125,   102,   103,   104,
     105,   106,   107,   126,   108,   109,   110,   111,     0,     0,
       0,     0,   443,     0,     0,   112,     0,     0,   113,   114,
     115,     0,     0,   116,   117,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   118,   119,   120,   121,
     122,   123,   124,   125,   102,   103,   104,   105,   106,   107,
     126,   108,   109,   110,   111,     0,     0,     0,     0,   452,
       0,     0,   112,     0,     0,   113,   114,   115,     0,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   119,   120,   121,   122,   123,   124,
     125,   102,   103,   104,   105,   106,   107,   126,   108,   109,
     110,   111,     0,     0,     0,     0,   456,     0,     0,   112,
       0,     0,   113,   114,   115,     0,     0,   116,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     118,   119,   120,   121,   122,   123,   124,   125,   102,   103,
     104,   105,   106,   107,   126,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   112,     0,     0,   113,
     114,   115,     0,     0,   116,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,   119,   120,
     121,   122,   123,   124,   125,   102,   103,   104,   105,   106,
     107,   126,   108,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,   112,     0,     0,   113,   114,   115,     0,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   119,   120,   121,   122,   123,
     124,   125,   102,   103,   104,   105,   106,   107,     0,   108,
     109,   110,   111,     0,     0,     0,     0,     0,     0,     0,
     112,     0,     0,   113,   114,   115,     0,     0,   116,   117,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   118,   119,   120,   121,     0,     0,   124,   125,   102,
     103,   104,   105,   106,   107,     0,   108,     0,   110,   111,
       0,     0,     0,     0,     0,     0,     0,   112,     0,     0,
     113,   114,   115,     0,     0,   116,   117,   102,   103,   104,
     105,   106,   107,     0,   108,     0,   110,   111,   118,   119,
     120,   121,     0,     0,   124,   125,     0,     0,   113,   114,
     115,     0,     0,   116,   117,   102,   103,   104,   105,   106,
     107,     0,   108,     0,     0,   111,   118,   119,   120,   121,
       0,     0,   124,   125,     0,     0,   113,   114,   115,     0,
       0,   116,   117,   102,   103,   104,   105,   106,   107,     0,
     108,     0,     0,   111,   118,   119,   120,   121,     0,     0,
     124,   125,     0,     0,   113,   114,   115,     0,    79,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   276,     0,   120,   121,    80,    81,   124,   125,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      80,    81,     0,     0,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92
};

static const yytype_int16 yycheck[] =
{
       2,     2,   152,   210,    47,   240,   213,     6,   269,   287,
      12,   251,   149,   133,   209,     3,   166,    16,   354,   355,
      48,   355,    53,    48,    53,     5,     6,     7,   223,    48,
      36,   372,    55,     0,    55,    55,    59,    55,    55,    55,
      36,   382,    53,    59,    28,   381,   382,    53,   198,    57,
      30,    36,   259,    33,    34,    35,    36,    57,    89,    39,
      40,    41,    53,    43,    44,    94,   402,    95,   402,    94,
     406,    59,    56,    53,   352,    94,    97,    97,    89,    97,
      97,    61,    62,    49,    53,   325,   206,    57,   295,   226,
       5,     6,    53,   300,   301,   290,   303,   375,    64,    65,
     307,    53,   309,    42,    43,    44,    45,    24,    55,    24,
      49,    53,    59,    52,    94,   114,   115,     5,     6,    36,
      37,    36,    37,   330,    53,    64,    65,    53,   335,    53,
     337,   338,    55,   340,   238,   239,    59,   139,   139,   400,
      48,    57,   292,    42,    43,    44,    45,    53,    55,    53,
      49,   358,    59,    52,    14,    35,   363,    55,   436,   366,
     395,    59,    35,    53,    63,    64,    65,   317,    55,    68,
      69,    55,    59,    58,    36,    59,    35,   384,    44,    45,
      36,    36,   389,    49,   419,    53,    52,    23,    87,    88,
      23,   234,    55,     3,     5,     6,     7,    54,    64,    65,
      53,    55,    54,   410,    53,    56,   413,    57,   210,    39,
      58,   213,    58,    48,    58,    97,    36,    55,   425,    30,
     427,     8,    33,    34,    35,    36,    54,    26,    39,    40,
      41,    57,    43,    44,    58,    54,    54,    54,     5,     6,
       7,    54,    53,    59,    59,    54,    54,    48,    55,   247,
      61,    62,    58,    58,    58,    36,    54,   259,    48,    59,
      56,    58,    57,    30,    57,   415,    33,    34,    35,    36,
      59,    59,    39,    40,    41,    57,    43,    44,    57,    59,
      91,    57,    48,   433,    57,   382,    53,   246,   236,   345,
      -1,    -1,    -1,   295,    61,    62,    -1,   447,   300,   301,
      -1,   303,    -1,    -1,    -1,   307,    -1,   309,    -1,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,    -1,    -1,    -1,
      -1,   323,   323,    -1,    91,    -1,    -1,    -1,   330,    -1,
      -1,    -1,    -1,   335,    -1,   337,   338,    -1,   340,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,   358,    -1,    -1,    -1,
      -1,   363,    53,    -1,   366,    -1,    57,    58,    -1,    -1,
      61,    62,    -1,    10,    -1,   377,   377,    -1,    42,    43,
      44,    45,   384,    -1,    -1,    49,    -1,   389,    52,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    -1,   400,   400,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,   410,    -1,
      -1,   413,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    59,   425,    -1,   427,    63,    -1,    -1,    66,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    74,    75,    -1,
      77,    78,    79,   445,   445,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   102,   103,   104,   105,   106,
     107,    -1,   109,   110,   111,   112,   113,    -1,    -1,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    23,    -1,    -1,    -1,   132,   133,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   142,    -1,    -1,    -1,   146,
      -1,    -1,    -1,    -1,    -1,   152,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    42,
      43,    44,    45,    46,    47,    -1,    49,    50,    51,    52,
      -1,   198,    94,    -1,    -1,    -1,    -1,    60,    -1,   206,
      63,    64,    65,    -1,   211,    68,    69,    -1,    -1,   216,
     217,   218,    -1,   220,   221,   222,    -1,    -1,    81,    82,
      83,    84,    85,   230,    87,    88,   233,    -1,    -1,   236,
      -1,   238,   239,   240,   241,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     257,    -1,    -1,    -1,   261,   262,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   276,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   286,
      -1,    -1,    -1,    -1,    -1,   292,    -1,     5,     6,     7,
      -1,   298,    -1,    -1,    -1,    -1,    -1,    -1,   305,    -1,
      -1,   308,    -1,    -1,   311,    -1,    -1,    -1,    -1,    -1,
     317,    -1,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      -1,    39,    40,    41,   331,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   341,    53,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    61,    62,    -1,     5,     6,     7,    -1,
      -1,    -1,   359,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     367,    -1,    -1,    -1,    -1,    -1,    -1,   374,    -1,    -1,
      -1,    30,    -1,    -1,    33,    34,    35,    36,   385,    -1,
      39,    40,    41,   390,    43,    44,   393,   394,   395,    -1,
      -1,    48,    -1,    -1,    53,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    61,    62,    -1,    -1,    -1,    -1,   415,    66,
      67,   418,   419,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    -1,    -1,   433,     3,    -1,     5,
       6,     7,    -1,     9,   441,    11,    -1,    13,    14,    15,
     447,    -1,    -1,   450,    20,    21,    22,    -1,    24,    25,
      -1,    27,    -1,    29,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    38,    39,    40,    41,    -1,    43,    44,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,    53,     9,    -1,
      11,    -1,    13,    14,    15,    61,    62,    -1,    19,    20,
      21,    22,    -1,    24,    25,    26,    27,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    38,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    -1,     5,     6,     7,
      -1,     9,    53,    11,    -1,    13,    14,    15,    -1,    -1,
      61,    62,    20,    21,    22,    -1,    24,    25,    -1,    27,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,    36,    -1,
      38,    39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      58,    -1,    -1,    61,    62,     5,     6,     7,    -1,     9,
      -1,    11,    -1,    13,    14,    15,    -1,    -1,    -1,    -1,
      20,    21,    22,    -1,    24,    25,    -1,    27,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    38,    39,
      40,    41,    -1,    43,    44,    -1,    -1,    -1,     5,     6,
       7,    -1,     9,    53,    11,    -1,    13,    14,    15,    59,
      -1,    61,    62,    20,    21,    22,    -1,    24,    25,    -1,
      27,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    36,
      -1,    38,    39,    40,    41,    -1,    43,    44,    -1,    -1,
      -1,     5,     6,     7,    -1,     9,    53,    11,    -1,    13,
      14,    15,    59,    -1,    61,    62,    20,    21,    22,    -1,
      24,    25,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,
      34,    35,    36,    -1,    38,    39,    40,    41,    -1,    43,
      44,    -1,    -1,    -1,     5,     6,     7,    -1,     9,    53,
      11,    -1,    13,    14,    15,    59,    -1,    61,    62,    20,
      21,    22,    -1,    24,    25,    -1,    27,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    38,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    42,    43,    44,    45,
      46,    47,    53,    49,    50,    51,    52,    -1,    54,    55,
      61,    62,    -1,    -1,    60,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    42,    43,    44,    45,    46,    47,    95,
      49,    50,    51,    52,    -1,    -1,    55,    -1,    57,    -1,
      -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      42,    43,    44,    45,    46,    47,    95,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    90,    -1,
      -1,    -1,    -1,    95,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    90,    -1,    -1,    -1,    -1,    95,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    -1,    90,    -1,    -1,    -1,
      -1,    95,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    92,    -1,    -1,    95,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    -1,    -1,    -1,    92,    -1,    -1,    95,
      42,    43,    44,    45,    46,    47,    -1,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    -1,    -1,    -1,
      92,    -1,    -1,    95,    42,    43,    44,    45,    46,    47,
      -1,    49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    -1,    -1,    -1,    92,    -1,    -1,    95,    42,    43,
      44,    45,    46,    47,    -1,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    60,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    42,    43,    44,    45,    46,
      47,    95,    49,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    42,    43,    44,    45,    46,    47,    95,    49,
      50,    51,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    42,
      43,    44,    45,    46,    47,    95,    49,    50,    51,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    42,    43,    44,    45,
      46,    47,    95,    49,    50,    51,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    42,    43,    44,    45,    46,    47,    95,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      42,    43,    44,    45,    46,    47,    95,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    42,    43,    44,
      45,    46,    47,    95,    49,    50,    51,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    42,    43,    44,    45,    46,    47,
      95,    49,    50,    51,    52,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    42,    43,    44,    45,    46,    47,    95,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,
      -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    42,    43,
      44,    45,    46,    47,    95,    49,    50,    51,    52,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    60,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    42,    43,    44,    45,    46,
      47,    95,    49,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    42,    43,    44,    45,    46,    47,    95,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    -1,
      90,    -1,    -1,    -1,    -1,    95,    42,    43,    44,    45,
      46,    47,    -1,    49,    50,    51,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    42,    43,    44,    45,    46,    47,    95,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      42,    43,    44,    45,    46,    47,    95,    49,    50,    51,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    42,    43,    44,
      45,    46,    47,    95,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    60,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    42,    43,    44,    45,    46,    47,
      95,    49,    50,    51,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    42,    43,    44,    45,    46,    47,    95,    49,    50,
      51,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,
      -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    42,    43,
      44,    45,    46,    47,    95,    49,    50,    51,    52,    -1,
      54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    42,    43,    44,    45,    46,
      47,    95,    49,    50,    51,    52,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    42,    43,    44,    45,    46,    47,    95,    49,
      50,    51,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    85,    86,    87,    88,    42,
      43,    44,    45,    46,    47,    95,    49,    50,    51,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    88,    42,    43,    44,    45,
      46,    47,    95,    49,    50,    51,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    42,    43,    44,    45,    46,    47,    95,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      42,    43,    44,    45,    46,    47,    95,    49,    50,    51,
      52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    42,    43,    44,
      45,    46,    47,    95,    49,    50,    51,    52,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    60,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,    84,
      85,    86,    87,    88,    42,    43,    44,    45,    46,    47,
      95,    49,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    42,    43,    44,    45,    46,    47,    95,    49,    50,
      51,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    60,
      -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    42,    43,
      44,    45,    46,    47,    95,    49,    50,    51,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    42,    43,    44,    45,    46,
      47,    95,    49,    50,    51,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    82,    83,    84,    85,    86,
      87,    88,    42,    43,    44,    45,    46,    47,    -1,    49,
      50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    83,    84,    -1,    -1,    87,    88,    42,
      43,    44,    45,    46,    47,    -1,    49,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      63,    64,    65,    -1,    -1,    68,    69,    42,    43,    44,
      45,    46,    47,    -1,    49,    -1,    51,    52,    81,    82,
      83,    84,    -1,    -1,    87,    88,    -1,    -1,    63,    64,
      65,    -1,    -1,    68,    69,    42,    43,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    52,    81,    82,    83,    84,
      -1,    -1,    87,    88,    -1,    -1,    63,    64,    65,    -1,
      -1,    68,    69,    42,    43,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    52,    81,    82,    83,    84,    -1,    -1,
      87,    88,    -1,    -1,    63,    64,    65,    -1,    48,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    83,    84,    66,    67,    87,    88,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      66,    67,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    94
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    99,   100,     0,     3,     5,     6,     7,     9,    11,
      13,    14,    15,    20,    21,    22,    24,    25,    27,    29,
      30,    33,    34,    35,    36,    38,    39,    40,    41,    43,
      44,    53,    61,    62,   101,   102,   105,   106,   110,   111,
     118,   121,   122,   123,   124,   125,   126,   127,   128,   131,
     132,   136,    36,    36,    53,   129,   129,    57,    57,    53,
       7,    34,    57,    58,   126,   131,    53,    58,   105,   117,
      53,    53,    53,   129,    53,    53,    36,    53,    48,    48,
      66,    67,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    94,   130,    53,    89,   126,   126,   126,   126,
     126,    57,    42,    43,    44,    45,    46,    47,    49,    50,
      51,    52,    60,    63,    64,    65,    68,    69,    81,    82,
      83,    84,    85,    86,    87,    88,    95,    48,   130,    53,
      89,   126,    53,    53,   126,   126,   137,    57,   126,   104,
      14,    35,    57,   126,    35,    35,    53,   126,   126,    58,
     126,   126,    58,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   141,    58,   126,   133,   134,
     135,    36,    54,   126,   126,   126,   126,   126,   126,    36,
     126,   126,   126,   126,   126,   129,   129,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,    58,   126,
      35,   107,   108,   109,    36,    54,    94,   113,   126,   113,
      54,    55,    59,    54,    59,   105,    53,    23,    57,   126,
      57,    23,    23,   126,    54,    54,   103,   106,    54,    55,
      55,    57,   137,    55,    97,   137,    55,    54,    53,    53,
      94,    56,   137,    48,    95,    54,    55,    53,   113,    56,
     112,   112,   117,   126,    57,   117,   126,    91,   126,    54,
     126,    57,    57,   126,    91,   126,   126,   112,    58,    58,
      59,   106,    39,   126,    59,   126,    48,   130,    59,   133,
     135,   135,   141,   126,    59,   126,    48,    58,   109,   107,
      97,    36,    55,   114,   114,     8,    54,   126,    90,   117,
      54,    54,   126,    54,   126,    57,   126,    54,    90,    54,
      54,    26,   119,   119,    57,    54,    57,    58,   126,    54,
      54,    97,   126,   104,    54,   112,   137,    54,    54,   117,
      54,    90,   126,   117,   117,    54,   117,    54,    54,   126,
      54,    90,   117,   126,   117,    58,   120,   126,    59,    59,
     137,    59,    58,   114,    58,    58,   117,   126,    54,    92,
     117,   117,   117,    54,   117,   126,    54,    92,    24,    36,
      37,   138,   139,   140,    28,    56,    59,   104,    54,   111,
     115,   116,   139,   115,    54,    92,   117,   126,   117,    54,
      92,   117,   126,    48,    48,    94,    36,    59,   140,   126,
     104,    59,    58,    57,    59,   111,   116,    59,   117,   126,
      54,   117,   126,    54,   126,    58,   126,   141,    48,    94,
      57,    19,   119,   115,    57,    54,   117,    54,   117,    57,
     137,    57,    97,    58,   126,   141,    56,    59,   117,   117,
      59,    48,   137,    57,    97,   104,    57,    58,   126,    59,
      48,   137,    57,    57,   126,    59,    57,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    98,    99,   100,   100,   101,   101,   101,   102,   103,
     103,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   109,   109,   110,   111,
     111,   111,   111,   111,   111,   112,   112,   113,   113,   114,
     114,   115,   115,   115,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   119,   120,   120,   121,   121,   122,   122,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     132,   132,   132,   133,   133,   134,   134,   135,   135,   136,
     136,   137,   137,   138,   138,   139,   139,   140,   140,   140,
     140,   140,   140,   140,   140,   141,   141
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     6,     1,
       2,     0,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     3,     5,     2,     4,     6,     1,     8,    10,
       0,     1,     1,     3,     1,     2,     3,     4,    10,    10,
       7,    12,     9,    10,     7,     0,     2,     0,     1,     0,
       2,     0,     1,     1,     2,     2,     3,     3,     1,     7,
       7,     4,     7,     5,     1,     3,     5,     7,     5,     6,
       9,     8,     8,     7,     8,     7,     7,     6,     9,    10,
      11,    12,     8,     7,     7,     9,    10,    11,    12,     8,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     5,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       3,     6,     3,     3,     1,     3,     1,     1,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     3,     5,     6,     8,     2,     5,     2,     3,     5,
       4,     6,     6,     1,     3,     1,     3,     0,     1,     4,
       6,     1,     3,     0,     1,     1,     2,     4,     6,     5,
       7,     4,     7,     9,     8,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




/* The kind of the lookahead of this context.  */
static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static yysymbol_kind_t
yypcontext_token (const yypcontext_t *yyctx)
{
  return yyctx->yytoken;
}

/* The location of the lookahead of this context.  */
static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx) YY_ATTRIBUTE_UNUSED;

static YYLTYPE *
yypcontext_location (const yypcontext_t *yyctx)
{
  return yyctx->yylloc;
}

/* User defined function to report a syntax error.  */
static int
yyreport_syntax_error (const yypcontext_t *yyctx);

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: decl_list  */
#line 209 "CMDgram.y"
      { }
#line 2415 "CMDgram.cpp"
    break;

  case 3: /* decl_list: %empty  */
#line 214 "CMDgram.y"
      { (yyval.stmt) = nil; }
#line 2421 "CMDgram.cpp"
    break;

  case 4: /* decl_list: decl_list decl  */
#line 216 "CMDgram.y"
      { if(!Script::gStatementList) { Script::gStatementList = (yyvsp[0].stmt); } else { Script::gStatementList->append((yyvsp[0].stmt)); } }
#line 2427 "CMDgram.cpp"
    break;

  case 5: /* decl: stmt  */
#line 221 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2433 "CMDgram.cpp"
    break;

  case 6: /* decl: fn_decl_stmt  */
#line 223 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2439 "CMDgram.cpp"
    break;

  case 7: /* decl: package_decl  */
#line 225 "CMDgram.y"
     { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2445 "CMDgram.cpp"
    break;

  case 8: /* package_decl: rwPACKAGE IDENT '{' fn_decl_list '}' ';'  */
#line 230 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-2].stmt); for(StmtNode *walk = ((yyvsp[-2].stmt));walk;walk = walk->getNext() ) walk->setPackage((yyvsp[-4].s).value); }
#line 2451 "CMDgram.cpp"
    break;

  case 9: /* fn_decl_list: fn_decl_stmt  */
#line 235 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2457 "CMDgram.cpp"
    break;

  case 10: /* fn_decl_list: fn_decl_list fn_decl_stmt  */
#line 237 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); ((yyvsp[-1].stmt))->append((yyvsp[0].stmt));  }
#line 2463 "CMDgram.cpp"
    break;

  case 11: /* statement_list: %empty  */
#line 242 "CMDgram.y"
      { (yyval.stmt) = nil; }
#line 2469 "CMDgram.cpp"
    break;

  case 12: /* statement_list: statement_list stmt  */
#line 244 "CMDgram.y"
      { if(!(yyvsp[-1].stmt)) { (yyval.stmt) = (yyvsp[0].stmt); } else { ((yyvsp[-1].stmt))->append((yyvsp[0].stmt)); (yyval.stmt) = (yyvsp[-1].stmt); } }
#line 2475 "CMDgram.cpp"
    break;

  case 19: /* stmt: rwBREAK ';'  */
#line 255 "CMDgram.y"
      { (yyval.stmt) = BreakStmtNode::alloc( (yyvsp[-1].i).lineNumber ); }
#line 2481 "CMDgram.cpp"
    break;

  case 20: /* stmt: rwCONTINUE ';'  */
#line 257 "CMDgram.y"
      { (yyval.stmt) = ContinueStmtNode::alloc( (yyvsp[-1].i).lineNumber ); }
#line 2487 "CMDgram.cpp"
    break;

  case 21: /* stmt: rwRETURN ';'  */
#line 259 "CMDgram.y"
      { (yyval.stmt) = ReturnStmtNode::alloc( (yyvsp[-1].i).lineNumber, NULL ); }
#line 2493 "CMDgram.cpp"
    break;

  case 22: /* stmt: rwRETURN expr ';'  */
#line 261 "CMDgram.y"
      { (yyval.stmt) = ReturnStmtNode::alloc( (yyvsp[-2].i).lineNumber, (yyvsp[-1].expr) ); }
#line 2499 "CMDgram.cpp"
    break;

  case 23: /* stmt: rwRETURN '{' expr_list '}' ';'  */
#line 264 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-4].i).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-2].expr);
//          for (ExprNode* expr = (ExprNode*)$3; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.stmt) = ReturnStmtNode::alloc( (yyvsp[-4].i).lineNumber, vecNode );
      }
#line 2512 "CMDgram.cpp"
    break;

  case 24: /* stmt: expression_stmt ';'  */
#line 274 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 2518 "CMDgram.cpp"
    break;

  case 25: /* stmt: TTAG '=' expr ';'  */
#line 276 "CMDgram.y"
      { (yyval.stmt) = TTagSetStmtNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-1].expr), NULL ); }
#line 2524 "CMDgram.cpp"
    break;

  case 26: /* stmt: TTAG '=' expr ',' expr ';'  */
#line 278 "CMDgram.y"
      { (yyval.stmt) = TTagSetStmtNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-5].s).value, (yyvsp[-3].expr), (yyvsp[-1].expr) ); }
#line 2530 "CMDgram.cpp"
    break;

  case 27: /* stmt: DOCBLOCK  */
#line 280 "CMDgram.y"
      { (yyval.stmt) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, false, true ); }
#line 2536 "CMDgram.cpp"
    break;

  case 28: /* fn_decl_stmt: rwDEFINE IDENT '(' var_list_decl ')' '{' statement_list '}'  */
#line 286 "CMDgram.y"
      { (yyval.stmt) = FunctionDeclStmtNode::alloc( (yyvsp[-7].i).lineNumber, (yyvsp[-6].s).value, NULL, (yyvsp[-4].var), (yyvsp[-1].stmt) ); }
#line 2542 "CMDgram.cpp"
    break;

  case 29: /* fn_decl_stmt: rwDEFINE IDENT opCOLONCOLON IDENT '(' var_list_decl ')' '{' statement_list '}'  */
#line 289 "CMDgram.y"
      { (yyval.stmt) = FunctionDeclStmtNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-6].s).value, (yyvsp[-8].s).value, (yyvsp[-4].var), (yyvsp[-1].stmt) ); }
#line 2548 "CMDgram.cpp"
    break;

  case 30: /* var_list_decl: %empty  */
#line 294 "CMDgram.y"
      { (yyval.var) = NULL; }
#line 2554 "CMDgram.cpp"
    break;

  case 31: /* var_list_decl: var_list  */
#line 296 "CMDgram.y"
      { (yyval.var) = (yyvsp[0].var); }
#line 2560 "CMDgram.cpp"
    break;

  case 32: /* var_list: param  */
#line 301 "CMDgram.y"
      { (yyval.var) = (yyvsp[0].var); }
#line 2566 "CMDgram.cpp"
    break;

  case 33: /* var_list: var_list ',' param  */
#line 303 "CMDgram.y"
      { (yyval.var) = (yyvsp[-2].var); ((StmtNode*)((yyvsp[-2].var)))->append((StmtNode*)(yyvsp[0].var) ); }
#line 2572 "CMDgram.cpp"
    break;

  case 34: /* param: VAR  */
#line 320 "CMDgram.y"
      { (yyval.var) = VarNode::allocParam((yyvsp[0].s).lineNumber, (yyvsp[0].s).value, NULL); }
#line 2578 "CMDgram.cpp"
    break;

  case 35: /* param: VAR '?'  */
#line 322 "CMDgram.y"
      { (yyval.var) = VarNode::allocParam((yyvsp[-1].s).lineNumber, (yyvsp[-1].s).value, NULL); }
#line 2584 "CMDgram.cpp"
    break;

  case 36: /* param: VAR '=' expr  */
#line 324 "CMDgram.y"
      { (yyval.var) = VarNode::allocParam((yyvsp[-2].s).lineNumber, (yyvsp[-2].s).value, (yyvsp[0].expr)); }
#line 2590 "CMDgram.cpp"
    break;

  case 37: /* param: VAR '?' '=' expr  */
#line 326 "CMDgram.y"
      { (yyval.var) = VarNode::allocParam((yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[0].expr)); }
#line 2596 "CMDgram.cpp"
    break;

  case 38: /* datablock_decl: rwDATABLOCK class_name_expr '(' expr parent_block ')' '{' slot_assign_list_opt '}' ';'  */
#line 331 "CMDgram.y"
      { (yyval.stmt) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), NULL, (yyvsp[-5].s).value, (yyvsp[-2].slist), NULL, true, false, false); }
#line 2602 "CMDgram.cpp"
    break;

  case 39: /* object_decl: rwDECLARE class_name_expr '(' object_name parent_block object_args ')' '{' object_declare_block '}'  */
#line 336 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, false, false); }
#line 2608 "CMDgram.cpp"
    break;

  case 40: /* object_decl: rwDECLARE class_name_expr '(' object_name parent_block object_args ')'  */
#line 338 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, false, false); }
#line 2614 "CMDgram.cpp"
    break;

  case 41: /* object_decl: rwDECLARE class_name_expr '(' '[' object_name ']' parent_block object_args ')' '{' object_declare_block '}'  */
#line 340 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-11].i).lineNumber, (yyvsp[-10].expr), (yyvsp[-7].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, true, false); }
#line 2620 "CMDgram.cpp"
    break;

  case 42: /* object_decl: rwDECLARE class_name_expr '(' '[' object_name ']' parent_block object_args ')'  */
#line 342 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-8].i).lineNumber, (yyvsp[-7].expr), (yyvsp[-4].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, true, false); }
#line 2626 "CMDgram.cpp"
    break;

  case 43: /* object_decl: rwDECLARESINGLETON class_name_expr '(' object_name parent_block object_args ')' '{' object_declare_block '}'  */
#line 344 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-9].i).lineNumber, (yyvsp[-8].expr), (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-5].s).value, (yyvsp[-1].odcl).slots, (yyvsp[-1].odcl).decls, false, false, true); }
#line 2632 "CMDgram.cpp"
    break;

  case 44: /* object_decl: rwDECLARESINGLETON class_name_expr '(' object_name parent_block object_args ')'  */
#line 346 "CMDgram.y"
      { (yyval.od) = ObjectDeclNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), (yyvsp[-1].expr), (yyvsp[-2].s).value, NULL, NULL, false, false, true); }
#line 2638 "CMDgram.cpp"
    break;

  case 45: /* parent_block: %empty  */
#line 351 "CMDgram.y"
      { (yyval.s).value = NULL; }
#line 2644 "CMDgram.cpp"
    break;

  case 46: /* parent_block: ':' IDENT  */
#line 353 "CMDgram.y"
      { (yyval.s) = (yyvsp[0].s); }
#line 2650 "CMDgram.cpp"
    break;

  case 47: /* object_name: %empty  */
#line 358 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( CodeBlock::smCurrentParser->getCurrentLine(), "", false); }
#line 2656 "CMDgram.cpp"
    break;

  case 48: /* object_name: expr  */
#line 360 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2662 "CMDgram.cpp"
    break;

  case 49: /* object_args: %empty  */
#line 365 "CMDgram.y"
      { (yyval.expr) = NULL; }
#line 2668 "CMDgram.cpp"
    break;

  case 50: /* object_args: ',' expr_list  */
#line 367 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2674 "CMDgram.cpp"
    break;

  case 51: /* object_declare_block: %empty  */
#line 372 "CMDgram.y"
      { (yyval.odcl).slots = NULL; (yyval.odcl).decls = NULL; }
#line 2680 "CMDgram.cpp"
    break;

  case 52: /* object_declare_block: slot_assign_list  */
#line 374 "CMDgram.y"
      { (yyval.odcl).slots = (yyvsp[0].slist); (yyval.odcl).decls = NULL; }
#line 2686 "CMDgram.cpp"
    break;

  case 53: /* object_declare_block: object_decl_list  */
#line 376 "CMDgram.y"
      { (yyval.odcl).slots = NULL; (yyval.odcl).decls = (yyvsp[0].od); }
#line 2692 "CMDgram.cpp"
    break;

  case 54: /* object_declare_block: slot_assign_list object_decl_list  */
#line 378 "CMDgram.y"
      { (yyval.odcl).slots = (yyvsp[-1].slist); (yyval.odcl).decls = (yyvsp[0].od); }
#line 2698 "CMDgram.cpp"
    break;

  case 55: /* object_decl_list: object_decl ';'  */
#line 383 "CMDgram.y"
      { (yyval.od) = (yyvsp[-1].od); }
#line 2704 "CMDgram.cpp"
    break;

  case 56: /* object_decl_list: object_decl_list object_decl ';'  */
#line 385 "CMDgram.y"
      { (yyvsp[-2].od)->append((yyvsp[-1].od)); (yyval.od) = (yyvsp[-2].od); }
#line 2710 "CMDgram.cpp"
    break;

  case 57: /* stmt_block: '{' statement_list '}'  */
#line 390 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].stmt); }
#line 2716 "CMDgram.cpp"
    break;

  case 58: /* stmt_block: stmt  */
#line 392 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].stmt); }
#line 2722 "CMDgram.cpp"
    break;

  case 59: /* switch_stmt: rwSWITCH '(' expr ')' '{' case_block '}'  */
#line 397 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].ifnode); (yyvsp[-1].ifnode)->propagateSwitchExpr((yyvsp[-4].expr), false); }
#line 2728 "CMDgram.cpp"
    break;

  case 60: /* switch_stmt: rwSWITCHSTR '(' expr ')' '{' case_block '}'  */
#line 399 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[-1].ifnode); (yyvsp[-1].ifnode)->propagateSwitchExpr((yyvsp[-4].expr), true); }
#line 2734 "CMDgram.cpp"
    break;

  case 61: /* case_block: rwCASE case_expr ':' statement_list  */
#line 407 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-3].i).lineNumber, (yyvsp[-2].expr), (yyvsp[0].stmt), NULL, false); }
#line 2740 "CMDgram.cpp"
    break;

  case 62: /* case_block: rwCASE case_expr ':' statement_list rwDEFAULT ':' statement_list  */
#line 409 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].stmt), (yyvsp[0].stmt), false); }
#line 2746 "CMDgram.cpp"
    break;

  case 63: /* case_block: rwCASE case_expr ':' statement_list case_block  */
#line 411 "CMDgram.y"
      { (yyval.ifnode) = IfStmtNode::alloc( (yyvsp[-4].i).lineNumber, (yyvsp[-3].expr), (yyvsp[-1].stmt), (yyvsp[0].ifnode), true); }
#line 2752 "CMDgram.cpp"
    break;

  case 64: /* case_expr: expr  */
#line 416 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2758 "CMDgram.cpp"
    break;

  case 65: /* case_expr: case_expr rwCASEOR expr  */
#line 418 "CMDgram.y"
      { ((yyvsp[-2].expr))->append((yyvsp[0].expr)); (yyval.expr) = (yyvsp[-2].expr); }
#line 2764 "CMDgram.cpp"
    break;

  case 66: /* if_stmt: rwIF '(' expr ')' stmt_block  */
#line 423 "CMDgram.y"
      { (yyval.stmt) = IfStmtNode::alloc((yyvsp[-4].i).lineNumber, (yyvsp[-2].expr), (yyvsp[0].stmt), NULL, false); }
#line 2770 "CMDgram.cpp"
    break;

  case 67: /* if_stmt: rwIF '(' expr ')' stmt_block rwELSE stmt_block  */
#line 425 "CMDgram.y"
      { (yyval.stmt) = IfStmtNode::alloc((yyvsp[-6].i).lineNumber, (yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt), false); }
#line 2776 "CMDgram.cpp"
    break;

  case 68: /* while_stmt: rwWHILE '(' expr ')' stmt_block  */
#line 430 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-4].i).lineNumber, nil, (yyvsp[-2].expr), nil, (yyvsp[0].stmt), false); }
#line 2782 "CMDgram.cpp"
    break;

  case 69: /* while_stmt: rwDO stmt_block rwWHILE '(' expr ')'  */
#line 432 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-3].i).lineNumber, nil, (yyvsp[-1].expr), nil, (yyvsp[-4].stmt), true); }
#line 2788 "CMDgram.cpp"
    break;

  case 70: /* for_stmt: rwFOR '(' expr ';' expr ';' expr ')' stmt_block  */
#line 437 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-8].i).lineNumber, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2794 "CMDgram.cpp"
    break;

  case 71: /* for_stmt: rwFOR '(' expr ';' expr ';' ')' stmt_block  */
#line 439 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].expr), (yyvsp[-3].expr), NULL, (yyvsp[0].stmt), false); }
#line 2800 "CMDgram.cpp"
    break;

  case 72: /* for_stmt: rwFOR '(' expr ';' ';' expr ')' stmt_block  */
#line 441 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].expr), NULL, (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2806 "CMDgram.cpp"
    break;

  case 73: /* for_stmt: rwFOR '(' expr ';' ';' ')' stmt_block  */
#line 443 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, (yyvsp[-4].expr), NULL, NULL, (yyvsp[0].stmt), false); }
#line 2812 "CMDgram.cpp"
    break;

  case 74: /* for_stmt: rwFOR '(' ';' expr ';' expr ')' stmt_block  */
#line 445 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-7].i).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2818 "CMDgram.cpp"
    break;

  case 75: /* for_stmt: rwFOR '(' ';' expr ';' ')' stmt_block  */
#line 447 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, NULL, (yyvsp[-3].expr), NULL, (yyvsp[0].stmt), false); }
#line 2824 "CMDgram.cpp"
    break;

  case 76: /* for_stmt: rwFOR '(' ';' ';' expr ')' stmt_block  */
#line 449 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-6].i).lineNumber, NULL, NULL, (yyvsp[-2].expr), (yyvsp[0].stmt), false); }
#line 2830 "CMDgram.cpp"
    break;

  case 77: /* for_stmt: rwFOR '(' ';' ';' ')' stmt_block  */
#line 451 "CMDgram.y"
      { (yyval.stmt) = LoopStmtNode::alloc((yyvsp[-5].i).lineNumber, NULL, NULL, NULL, (yyvsp[0].stmt), false); }
#line 2836 "CMDgram.cpp"
    break;

  case 78: /* for_stmt: rwFOR '(' VAR rwIN expr opDOTDOT expr ')' stmt_block  */
#line 455 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-8].i).lineNumber, (yyvsp[-6].s).value, (yyvsp[-4].expr), (yyvsp[-2].expr), NULL, (yyvsp[0].stmt), 2 ); }
#line 2842 "CMDgram.cpp"
    break;

  case 79: /* for_stmt: rwFOR '(' VAR rwIN rwRANGE expr opDOTDOT expr ')' stmt_block  */
#line 458 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-9].i).lineNumber, (yyvsp[-7].s).value, (yyvsp[-4].expr), (yyvsp[-2].expr), NULL, (yyvsp[0].stmt), 102 ); }
#line 2848 "CMDgram.cpp"
    break;

  case 80: /* for_stmt: rwFOR '(' VAR rwIN expr opDOTDOT expr rwSTEP expr ')' stmt_block  */
#line 461 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-10].i).lineNumber, (yyvsp[-8].s).value, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), 3 ); }
#line 2854 "CMDgram.cpp"
    break;

  case 81: /* for_stmt: rwFOR '(' VAR rwIN rwRANGE expr opDOTDOT expr rwSTEP expr ')' stmt_block  */
#line 464 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-11].i).lineNumber, (yyvsp[-9].s).value, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), 103 ); }
#line 2860 "CMDgram.cpp"
    break;

  case 82: /* for_stmt: rwFOR '(' VAR rwIN rwRANGE expr ')' stmt_block  */
#line 467 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].s).value, (yyvsp[-2].expr), NULL, NULL, (yyvsp[0].stmt), 104 ); }
#line 2866 "CMDgram.cpp"
    break;

  case 83: /* foreach_stmt: rwFOREACH '(' VAR rwIN expr ')' stmt_block  */
#line 478 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), NULL,NULL, (yyvsp[0].stmt), 0 ); }
#line 2872 "CMDgram.cpp"
    break;

  case 84: /* foreach_stmt: rwFOREACHSTR '(' VAR rwIN expr ')' stmt_block  */
#line 481 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc( (yyvsp[-6].i).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), NULL,NULL, (yyvsp[0].stmt), 1 ); }
#line 2878 "CMDgram.cpp"
    break;

  case 85: /* foreach_stmt: rwFOREACH '(' VAR rwIN expr opDOTDOT expr ')' stmt_block  */
#line 484 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-8].i).lineNumber, (yyvsp[-6].s).value, (yyvsp[-4].expr), (yyvsp[-2].expr), NULL, (yyvsp[0].stmt), 2 ); }
#line 2884 "CMDgram.cpp"
    break;

  case 86: /* foreach_stmt: rwFOREACH '(' VAR rwIN rwRANGE expr opDOTDOT expr ')' stmt_block  */
#line 487 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-9].i).lineNumber, (yyvsp[-7].s).value, (yyvsp[-4].expr), (yyvsp[-2].expr), NULL, (yyvsp[0].stmt), 102 ); }
#line 2890 "CMDgram.cpp"
    break;

  case 87: /* foreach_stmt: rwFOREACH '(' VAR rwIN expr opDOTDOT expr rwSTEP expr ')' stmt_block  */
#line 490 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-10].i).lineNumber, (yyvsp[-8].s).value, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), 3 ); }
#line 2896 "CMDgram.cpp"
    break;

  case 88: /* foreach_stmt: rwFOREACH '(' VAR rwIN rwRANGE expr opDOTDOT expr rwSTEP expr ')' stmt_block  */
#line 493 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-11].i).lineNumber, (yyvsp[-9].s).value, (yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt), 103 ); }
#line 2902 "CMDgram.cpp"
    break;

  case 89: /* foreach_stmt: rwFOREACH '(' VAR rwIN rwRANGE expr ')' stmt_block  */
#line 496 "CMDgram.y"
      { (yyval.stmt) = IterStmtNode::alloc((yyvsp[-7].i).lineNumber, (yyvsp[-5].s).value, (yyvsp[-2].expr), NULL, NULL, (yyvsp[0].stmt), 104 ); }
#line 2908 "CMDgram.cpp"
    break;

  case 90: /* expression_stmt: stmt_expr  */
#line 501 "CMDgram.y"
      { (yyval.stmt) = (yyvsp[0].expr); }
#line 2914 "CMDgram.cpp"
    break;

  case 91: /* expr: stmt_expr  */
#line 506 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 2920 "CMDgram.cpp"
    break;

  case 92: /* expr: '(' expr ')'  */
#line 508 "CMDgram.y"
      { (yyval.expr) = (yyvsp[-1].expr); }
#line 2926 "CMDgram.cpp"
    break;

  case 93: /* expr: expr '^' expr  */
#line 510 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2932 "CMDgram.cpp"
    break;

  case 94: /* expr: expr '%' expr  */
#line 512 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2938 "CMDgram.cpp"
    break;

  case 95: /* expr: expr '&' expr  */
#line 514 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2944 "CMDgram.cpp"
    break;

  case 96: /* expr: expr '|' expr  */
#line 516 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2950 "CMDgram.cpp"
    break;

  case 97: /* expr: expr '+' expr  */
#line 518 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2956 "CMDgram.cpp"
    break;

  case 98: /* expr: expr '-' expr  */
#line 520 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2962 "CMDgram.cpp"
    break;

  case 99: /* expr: expr '*' expr  */
#line 522 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2968 "CMDgram.cpp"
    break;

  case 100: /* expr: expr '/' expr  */
#line 524 "CMDgram.y"
      { (yyval.expr) = FloatBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2974 "CMDgram.cpp"
    break;

  case 101: /* expr: '-' expr  */
#line 526 "CMDgram.y"
      { (yyval.expr) = FloatUnaryExprNode::alloc( (yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 2980 "CMDgram.cpp"
    break;

  case 102: /* expr: '*' expr  */
#line 528 "CMDgram.y"
      { (yyval.expr) = TTagDerefNode::alloc( (yyvsp[-1].i).lineNumber, (yyvsp[0].expr) ); }
#line 2986 "CMDgram.cpp"
    break;

  case 103: /* expr: TTAG  */
#line 530 "CMDgram.y"
      { (yyval.expr) = TTagExprNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 2992 "CMDgram.cpp"
    break;

  case 104: /* expr: expr '?' expr ':' expr  */
#line 532 "CMDgram.y"
      { (yyval.expr) = ConditionalExprNode::alloc( (yyvsp[-4].expr)->dbgLineNumber, (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 2998 "CMDgram.cpp"
    break;

  case 105: /* expr: expr '<' expr  */
#line 534 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3004 "CMDgram.cpp"
    break;

  case 106: /* expr: expr '>' expr  */
#line 536 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3010 "CMDgram.cpp"
    break;

  case 107: /* expr: expr opGE expr  */
#line 538 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3016 "CMDgram.cpp"
    break;

  case 108: /* expr: expr opLE expr  */
#line 540 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3022 "CMDgram.cpp"
    break;

  case 109: /* expr: expr opEQ expr  */
#line 542 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3028 "CMDgram.cpp"
    break;

  case 110: /* expr: expr opNE expr  */
#line 544 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3034 "CMDgram.cpp"
    break;

  case 111: /* expr: expr opOR expr  */
#line 546 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3040 "CMDgram.cpp"
    break;

  case 112: /* expr: expr opSHL expr  */
#line 548 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3046 "CMDgram.cpp"
    break;

  case 113: /* expr: expr opSHR expr  */
#line 550 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3052 "CMDgram.cpp"
    break;

  case 114: /* expr: expr opAND expr  */
#line 552 "CMDgram.y"
      { (yyval.expr) = IntBinaryExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-1].i).value, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3058 "CMDgram.cpp"
    break;

  case 115: /* expr: expr opSTREQ expr  */
#line 554 "CMDgram.y"
      { (yyval.expr) = StreqExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), true); }
#line 3064 "CMDgram.cpp"
    break;

  case 116: /* expr: expr opSTRNE expr  */
#line 556 "CMDgram.y"
      { (yyval.expr) = StreqExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), false); }
#line 3070 "CMDgram.cpp"
    break;

  case 117: /* expr: expr '@' expr  */
#line 564 "CMDgram.y"
      { (yyval.expr) = StrcatExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr), (yyvsp[-1].i).value); }
#line 3076 "CMDgram.cpp"
    break;

  case 118: /* expr: '!' expr  */
#line 566 "CMDgram.y"
      { (yyval.expr) = IntUnaryExprNode::alloc((yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 3082 "CMDgram.cpp"
    break;

  case 119: /* expr: '~' expr  */
#line 568 "CMDgram.y"
      { (yyval.expr) = IntUnaryExprNode::alloc((yyvsp[-1].i).lineNumber, (yyvsp[-1].i).value, (yyvsp[0].expr)); }
#line 3088 "CMDgram.cpp"
    break;

  case 120: /* expr: TAGATOM  */
#line 570 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, true); }
#line 3094 "CMDgram.cpp"
    break;

  case 121: /* expr: FLTCONST  */
#line 572 "CMDgram.y"
      { (yyval.expr) = FloatNode::alloc( (yyvsp[0].f).lineNumber, (yyvsp[0].f).value ); }
#line 3100 "CMDgram.cpp"
    break;

  case 122: /* expr: INTCONST  */
#line 574 "CMDgram.y"
      { (yyval.expr) = IntNode::alloc( (yyvsp[0].i).lineNumber, (yyvsp[0].i).value ); }
#line 3106 "CMDgram.cpp"
    break;

  case 123: /* expr: rwBREAK  */
#line 576 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].i).lineNumber, StringTable->insert("break")); }
#line 3112 "CMDgram.cpp"
    break;

  case 124: /* expr: slot_acc  */
#line 578 "CMDgram.y"
      { (yyval.expr) = SlotAccessNode::alloc( (yyvsp[0].slot).lineNumber, (yyvsp[0].slot).object, (yyvsp[0].slot).array, (yyvsp[0].slot).slotName ); }
#line 3118 "CMDgram.cpp"
    break;

  case 125: /* expr: intslot_acc  */
#line 580 "CMDgram.y"
      { (yyval.expr) = InternalSlotAccessNode::alloc( (yyvsp[0].intslot).lineNumber, (yyvsp[0].intslot).object, (yyvsp[0].intslot).slotExpr, (yyvsp[0].intslot).recurse); }
#line 3124 "CMDgram.cpp"
    break;

  case 126: /* expr: IDENT  */
#line 582 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 3130 "CMDgram.cpp"
    break;

  case 127: /* expr: STRATOM  */
#line 584 "CMDgram.y"
      { (yyval.expr) = StrConstNode::alloc( (yyvsp[0].str).lineNumber, (yyvsp[0].str).value, false); }
#line 3136 "CMDgram.cpp"
    break;

  case 128: /* expr: VAR  */
#line 586 "CMDgram.y"
      { (yyval.expr) = (ExprNode*)VarNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value, NULL); }
#line 3142 "CMDgram.cpp"
    break;

  case 129: /* expr: VAR '[' aidx_expr ']'  */
#line 588 "CMDgram.y"
      { (yyval.expr) = (ExprNode*)VarNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-1].expr) ); }
#line 3148 "CMDgram.cpp"
    break;

  case 130: /* slot_acc: expr '.' IDENT  */
#line 594 "CMDgram.y"
      { (yyval.slot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.slot).object = (yyvsp[-2].expr); (yyval.slot).slotName = (yyvsp[0].s).value; (yyval.slot).array = NULL; }
#line 3154 "CMDgram.cpp"
    break;

  case 131: /* slot_acc: expr '.' IDENT '[' aidx_expr ']'  */
#line 596 "CMDgram.y"
      { (yyval.slot).lineNumber = (yyvsp[-5].expr)->dbgLineNumber; (yyval.slot).object = (yyvsp[-5].expr); (yyval.slot).slotName = (yyvsp[-3].s).value; (yyval.slot).array = (yyvsp[-1].expr); }
#line 3160 "CMDgram.cpp"
    break;

  case 132: /* intslot_acc: expr opINTNAME class_name_expr  */
#line 601 "CMDgram.y"
      { (yyval.intslot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.intslot).object = (yyvsp[-2].expr); (yyval.intslot).slotExpr = (yyvsp[0].expr); (yyval.intslot).recurse = false; }
#line 3166 "CMDgram.cpp"
    break;

  case 133: /* intslot_acc: expr opINTNAMER class_name_expr  */
#line 603 "CMDgram.y"
      { (yyval.intslot).lineNumber = (yyvsp[-2].expr)->dbgLineNumber; (yyval.intslot).object = (yyvsp[-2].expr); (yyval.intslot).slotExpr = (yyvsp[0].expr); (yyval.intslot).recurse = true; }
#line 3172 "CMDgram.cpp"
    break;

  case 134: /* class_name_expr: IDENT  */
#line 608 "CMDgram.y"
      { (yyval.expr) = ConstantNode::alloc( (yyvsp[0].s).lineNumber, (yyvsp[0].s).value ); }
#line 3178 "CMDgram.cpp"
    break;

  case 135: /* class_name_expr: '(' expr ')'  */
#line 610 "CMDgram.y"
      { (yyval.expr) = (yyvsp[-1].expr); }
#line 3184 "CMDgram.cpp"
    break;

  case 136: /* assign_op_struct: opPLUSPLUS  */
#line 615 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[0].i).lineNumber; (yyval.asn).token = opPLUSPLUS; (yyval.asn).expr = FloatNode::alloc( (yyvsp[0].i).lineNumber, 1 ); }
#line 3190 "CMDgram.cpp"
    break;

  case 137: /* assign_op_struct: opMINUSMINUS  */
#line 617 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[0].i).lineNumber; (yyval.asn).token = opMINUSMINUS; (yyval.asn).expr = FloatNode::alloc( (yyvsp[0].i).lineNumber, 1 ); }
#line 3196 "CMDgram.cpp"
    break;

  case 138: /* assign_op_struct: opPLASN expr  */
#line 619 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '+'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3202 "CMDgram.cpp"
    break;

  case 139: /* assign_op_struct: opMIASN expr  */
#line 621 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '-'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3208 "CMDgram.cpp"
    break;

  case 140: /* assign_op_struct: opMLASN expr  */
#line 623 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '*'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3214 "CMDgram.cpp"
    break;

  case 141: /* assign_op_struct: opDVASN expr  */
#line 625 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '/'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3220 "CMDgram.cpp"
    break;

  case 142: /* assign_op_struct: opMODASN expr  */
#line 627 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '%'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3226 "CMDgram.cpp"
    break;

  case 143: /* assign_op_struct: opANDASN expr  */
#line 629 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '&'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3232 "CMDgram.cpp"
    break;

  case 144: /* assign_op_struct: opXORASN expr  */
#line 631 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '^'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3238 "CMDgram.cpp"
    break;

  case 145: /* assign_op_struct: opORASN expr  */
#line 633 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = '|'; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3244 "CMDgram.cpp"
    break;

  case 146: /* assign_op_struct: opSLASN expr  */
#line 635 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = opSHL; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3250 "CMDgram.cpp"
    break;

  case 147: /* assign_op_struct: opSRASN expr  */
#line 637 "CMDgram.y"
      { (yyval.asn).lineNumber = (yyvsp[-1].i).lineNumber; (yyval.asn).token = opSHR; (yyval.asn).expr = (yyvsp[0].expr); }
#line 3256 "CMDgram.cpp"
    break;

  case 148: /* stmt_expr: funcall_expr  */
#line 643 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3262 "CMDgram.cpp"
    break;

  case 149: /* stmt_expr: assert_expr  */
#line 645 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3268 "CMDgram.cpp"
    break;

  case 150: /* stmt_expr: object_decl  */
#line 647 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].od); }
#line 3274 "CMDgram.cpp"
    break;

  case 151: /* stmt_expr: VAR '=' expr  */
#line 649 "CMDgram.y"
      { (yyval.expr) = AssignExprNode::alloc( (yyvsp[-2].s).lineNumber, (yyvsp[-2].s).value, NULL, (yyvsp[0].expr)); }
#line 3280 "CMDgram.cpp"
    break;

  case 152: /* stmt_expr: VAR '=' '{' expr_list '}'  */
#line 653 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-4].s).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-1].expr);
//          for (ExprNode* expr = (ExprNode*)$4; expr; expr = (ExprNode*)(expr->next)) {
//              vecNode->elements.push_back(expr);
//          }
         (yyval.expr) = AssignExprNode::alloc( (yyvsp[-4].s).lineNumber, (yyvsp[-4].s).value, NULL, vecNode);
      }
#line 3293 "CMDgram.cpp"
    break;

  case 153: /* stmt_expr: VAR '[' aidx_expr ']' '=' expr  */
#line 664 "CMDgram.y"
      { (yyval.expr) = AssignExprNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-5].s).value, (yyvsp[-3].expr), (yyvsp[0].expr)); }
#line 3299 "CMDgram.cpp"
    break;

  case 154: /* stmt_expr: VAR '[' aidx_expr ']' '=' '{' expr_list '}'  */
#line 668 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-7].s).lineNumber);
          vecNode->argList = (ExprNode*)(yyvsp[-1].expr);
//          for (ExprNode* expr = (ExprNode*)$7; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.expr) = AssignExprNode::alloc( (yyvsp[-7].s).lineNumber, (yyvsp[-7].s).value, (yyvsp[-5].expr), vecNode);
      }
#line 3312 "CMDgram.cpp"
    break;

  case 155: /* stmt_expr: VAR assign_op_struct  */
#line 679 "CMDgram.y"
      { (yyval.expr) = AssignOpExprNode::alloc( (yyvsp[-1].s).lineNumber, (yyvsp[-1].s).value, NULL, (yyvsp[0].asn).expr, (yyvsp[0].asn).token); }
#line 3318 "CMDgram.cpp"
    break;

  case 156: /* stmt_expr: VAR '[' aidx_expr ']' assign_op_struct  */
#line 681 "CMDgram.y"
      { (yyval.expr) = AssignOpExprNode::alloc( (yyvsp[-4].s).lineNumber, (yyvsp[-4].s).value, (yyvsp[-2].expr), (yyvsp[0].asn).expr, (yyvsp[0].asn).token); }
#line 3324 "CMDgram.cpp"
    break;

  case 157: /* stmt_expr: slot_acc assign_op_struct  */
#line 683 "CMDgram.y"
      { (yyval.expr) = SlotAssignOpNode::alloc( (yyvsp[-1].slot).lineNumber, (yyvsp[-1].slot).object, (yyvsp[-1].slot).slotName, (yyvsp[-1].slot).array, (yyvsp[0].asn).token, (yyvsp[0].asn).expr); }
#line 3330 "CMDgram.cpp"
    break;

  case 158: /* stmt_expr: slot_acc '=' expr  */
#line 685 "CMDgram.y"
      { (yyval.expr) = SlotAssignNode::alloc( (yyvsp[-2].slot).lineNumber, (yyvsp[-2].slot).object, (yyvsp[-2].slot).array, (yyvsp[-2].slot).slotName, (yyvsp[0].expr)); }
#line 3336 "CMDgram.cpp"
    break;

  case 159: /* stmt_expr: slot_acc '=' '{' expr_list '}'  */
#line 687 "CMDgram.y"
      { (yyval.expr) = SlotAssignNode::alloc( (yyvsp[-4].slot).lineNumber, (yyvsp[-4].slot).object, (yyvsp[-4].slot).array, (yyvsp[-4].slot).slotName, (yyvsp[-1].expr)); }
#line 3342 "CMDgram.cpp"
    break;

  case 160: /* funcall_expr: IDENT '(' func_arg_list_decl ')'  */
#line 719 "CMDgram.y"
      { (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-3].s).lineNumber, (yyvsp[-3].s).value, NULL, (yyvsp[-1].expr), false); }
#line 3348 "CMDgram.cpp"
    break;

  case 161: /* funcall_expr: IDENT opCOLONCOLON IDENT '(' func_arg_list_decl ')'  */
#line 722 "CMDgram.y"
      { (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-5].s).lineNumber, (yyvsp[-3].s).value, (yyvsp[-5].s).value, (yyvsp[-1].expr), false); }
#line 3354 "CMDgram.cpp"
    break;

  case 162: /* funcall_expr: expr '.' IDENT '(' func_arg_list_decl ')'  */
#line 725 "CMDgram.y"
      { (yyvsp[-5].expr)->append((yyvsp[-1].expr)); (yyval.expr) = FuncCallExprNode::alloc( (yyvsp[-5].expr)->dbgLineNumber, (yyvsp[-3].s).value, NULL, (yyvsp[-5].expr), true); }
#line 3360 "CMDgram.cpp"
    break;

  case 163: /* func_arg_item: expr  */
#line 731 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3366 "CMDgram.cpp"
    break;

  case 164: /* func_arg_item: '{' expr_list '}'  */
#line 733 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-2].i).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-1].expr);
//          for (ExprNode* expr = (ExprNode*)$2; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.expr) = vecNode;
      }
#line 3379 "CMDgram.cpp"
    break;

  case 165: /* func_arg_list: func_arg_item  */
#line 745 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3385 "CMDgram.cpp"
    break;

  case 166: /* func_arg_list: func_arg_list ',' func_arg_item  */
#line 747 "CMDgram.y"
      { ((yyvsp[-2].expr))->append((yyvsp[0].expr)); (yyval.expr) = (yyvsp[-2].expr); }
#line 3391 "CMDgram.cpp"
    break;

  case 167: /* func_arg_list_decl: %empty  */
#line 752 "CMDgram.y"
      { (yyval.expr) = NULL; }
#line 3397 "CMDgram.cpp"
    break;

  case 168: /* func_arg_list_decl: func_arg_list  */
#line 754 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3403 "CMDgram.cpp"
    break;

  case 169: /* assert_expr: rwASSERT '(' expr ')'  */
#line 775 "CMDgram.y"
      { (yyval.expr) = AssertCallExprNode::alloc( (yyvsp[-3].i).lineNumber, (yyvsp[-1].expr), NULL ); }
#line 3409 "CMDgram.cpp"
    break;

  case 170: /* assert_expr: rwASSERT '(' expr ',' STRATOM ')'  */
#line 777 "CMDgram.y"
      { (yyval.expr) = AssertCallExprNode::alloc( (yyvsp[-5].i).lineNumber, (yyvsp[-3].expr), (yyvsp[-1].str).value ); }
#line 3415 "CMDgram.cpp"
    break;

  case 171: /* expr_list: expr  */
#line 789 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3421 "CMDgram.cpp"
    break;

  case 172: /* expr_list: expr_list ',' expr  */
#line 791 "CMDgram.y"
      { ((yyvsp[-2].expr))->append((yyvsp[0].expr)); (yyval.expr) = (yyvsp[-2].expr); }
#line 3427 "CMDgram.cpp"
    break;

  case 173: /* slot_assign_list_opt: %empty  */
#line 796 "CMDgram.y"
      { (yyval.slist) = NULL; }
#line 3433 "CMDgram.cpp"
    break;

  case 174: /* slot_assign_list_opt: slot_assign_list  */
#line 798 "CMDgram.y"
      { (yyval.slist) = (yyvsp[0].slist); }
#line 3439 "CMDgram.cpp"
    break;

  case 175: /* slot_assign_list: slot_assign  */
#line 803 "CMDgram.y"
      { (yyval.slist) = (yyvsp[0].slist); }
#line 3445 "CMDgram.cpp"
    break;

  case 176: /* slot_assign_list: slot_assign_list slot_assign  */
#line 805 "CMDgram.y"
      { (yyvsp[-1].slist)->append((yyvsp[0].slist)); (yyval.slist) = (yyvsp[-1].slist); }
#line 3451 "CMDgram.cpp"
    break;

  case 177: /* slot_assign: IDENT '=' expr ';'  */
#line 811 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-3].s).lineNumber, NULL, NULL, (yyvsp[-3].s).value, (yyvsp[-1].expr)); }
#line 3457 "CMDgram.cpp"
    break;

  case 178: /* slot_assign: IDENT '=' '{' expr_list '}' ';'  */
#line 815 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-5].s).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-2].expr);
//          for (ExprNode* expr = (ExprNode*)$4; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-5].s).lineNumber, NULL, NULL, (yyvsp[-5].s).value, vecNode);
      }
#line 3470 "CMDgram.cpp"
    break;

  case 179: /* slot_assign: TYPEIDENT IDENT '=' expr ';'  */
#line 826 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-4].i).lineNumber, NULL, NULL, (yyvsp[-3].s).value, (yyvsp[-1].expr), (yyvsp[-4].i).value); }
#line 3476 "CMDgram.cpp"
    break;

  case 180: /* slot_assign: TYPEIDENT IDENT '=' '{' expr_list '}' ';'  */
#line 830 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-6].i).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-2].expr);
//          for (ExprNode* expr = (ExprNode*)$5; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-6].i).lineNumber, NULL, NULL, (yyvsp[-5].s).value, vecNode, (yyvsp[-6].i).value);
      }
#line 3489 "CMDgram.cpp"
    break;

  case 181: /* slot_assign: rwDATABLOCK '=' expr ';'  */
#line 841 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-3].i).lineNumber, NULL, NULL, StringTable->insert("datablock"), (yyvsp[-1].expr)); }
#line 3495 "CMDgram.cpp"
    break;

  case 182: /* slot_assign: IDENT '[' aidx_expr ']' '=' expr ';'  */
#line 843 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-6].s).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-6].s).value, (yyvsp[-1].expr)); }
#line 3501 "CMDgram.cpp"
    break;

  case 183: /* slot_assign: IDENT '[' aidx_expr ']' '=' '{' expr_list '}' ';'  */
#line 847 "CMDgram.y"
      {
         VectorConstructorNode* vecNode = VectorConstructorNode::alloc((yyvsp[-8].s).lineNumber);
         vecNode->argList = (ExprNode*)(yyvsp[-2].expr);
//          for (ExprNode* expr = (ExprNode*)$7; expr; expr = (ExprNode*)(expr->next)) {
//             vecNode->elements.push_back(expr);
//          }
         (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-8].s).lineNumber, NULL, (yyvsp[-6].expr), (yyvsp[-8].s).value, vecNode);
      }
#line 3514 "CMDgram.cpp"
    break;

  case 184: /* slot_assign: TYPEIDENT IDENT '[' aidx_expr ']' '=' expr ';'  */
#line 858 "CMDgram.y"
      { (yyval.slist) = SlotAssignNode::alloc( (yyvsp[-7].i).lineNumber, NULL, (yyvsp[-4].expr), (yyvsp[-6].s).value, (yyvsp[-1].expr), (yyvsp[-7].i).value); }
#line 3520 "CMDgram.cpp"
    break;

  case 185: /* aidx_expr: expr  */
#line 881 "CMDgram.y"
      { (yyval.expr) = (yyvsp[0].expr); }
#line 3526 "CMDgram.cpp"
    break;

  case 186: /* aidx_expr: aidx_expr ',' expr  */
#line 883 "CMDgram.y"
      { (yyval.expr) = CommaCatExprNode::alloc( (yyvsp[-2].expr)->dbgLineNumber, (yyvsp[-2].expr), (yyvsp[0].expr)); }
#line 3532 "CMDgram.cpp"
    break;


#line 3536 "CMDgram.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        if (yyreport_syntax_error (&yyctx) == 2)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 886 "CMDgram.y"


int
yyreport_syntax_error(const yypcontext_t *ctx)
{
   int ret = 0;
   String output;
   const YYLTYPE *loc = yypcontext_location(ctx);
   output += "syntax error: ";

   yysymbol_kind_t nxt = yypcontext_token(ctx);
   if (nxt != YYSYMBOL_YYEMPTY)
      output += String::ToString("unexpected: %s at column: %d",
                                 yysymbol_name(nxt), loc->first_column);

   enum { TOKENMAX = 10 };
   yysymbol_kind_t expected[TOKENMAX];

   int exp = yypcontext_expected_tokens(ctx, expected, TOKENMAX);
   if (exp < 0)
   {
      ret = exp;
   }
   else
   {
      for (int i = 0; i < exp; ++i)
         output += String::ToString("%s %s",
                                    i == 0 ? ": expected" : "or",
                                    yysymbol_name(expected[i]));
   }

   if (lines.size() > 0)
   {
      output += "\n";
      for (int i = 0; i < lines.size(); i++)
      {
         int line = lines.size() - i;
         output += String::ToString("%5d | ", loc->first_line - (line - 1))
                 + lines[i] + "\n";
      }
      output += String::ToString("%5s | %*s", "", loc->first_column, "^");
   }

   yyerror("%s", output.c_str());
   return ret;
}
