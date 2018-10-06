#ifndef KEYWORDS_CPP
#define KEYWORDS_CPP

/* C++ code produced by gperf version 3.0.4 */
/* Command-line: gperf --language=C++ --output-file=keywords.cpp tmp.txt  */
/* Computed positions: -k'1,5,$' */
#include <cstring>

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#define TOTAL_KEYWORDS 96
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 16
#define MIN_HASH_VALUE 3
#define MAX_HASH_VALUE 202
/* maximum key range = 200, duplicates = 0 */

class Perfect_Hash
{
private:
  static inline unsigned int hash (const char *str, unsigned int len);
public:
  static const char *in_word_set (const char *str, unsigned int len);
};

inline unsigned int
Perfect_Hash::hash ( const char *str,  unsigned int len)
{
  static unsigned char asso_values[] =
    {
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 100,
      203,   0, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203,  40,  50,  20,
       45,  15,  15,   0,  20,  30, 203,  10,  55,  70,
       35,  70,  60,  50,   0,   5,   0,  40, 100,  70,
        5,   0, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203, 203, 203, 203, 203,
      203, 203, 203, 203, 203, 203
    };
   int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

const char *
Perfect_Hash::in_word_set ( const char *str,  unsigned int len)
{
  static const char * wordlist[] =
    {
      "", "", "",
      "try",
      "", "", "", "",
      "xor",
      "this",
      "short",
      "", "",
      "",
      "", "",
      "reinterpret_cast",
      "",
      "for",
      "true",
      "float",
      "export",
      "",
      "reflexpr",
      "char",
      "const",
      "", "",
      "char32_t",
      "constexpr",
      "const_cast",
      "struct",
      "",
      "int",
      "else",
      "class",
      "import",
      "",
      "not",
      "case",
      "",
      "return",
      "concept",
      "requires",
      "",
      "using",
      "static_cast",
      "if",
      "static_assert",
      "",
      "false",
      "switch",
      "",
      "explicit",
      "",
      "bitor",
      "extern",
      "",
      "typename",
      "long",
      "",
      "static",
      "",
      "noexcept",
      "namespace",
      "catch",
      "delete",
      "typedef",
      "decltype",
      "", "",
      "signed",
      "or",
      "continue",
      "goto",
      "break",
      "xor_eq",
      "wchar_t",
      "template",
      "co_return",
      "",
      "typeid",
      "synchronized",
      "atomic_commit",
      "",
      "atomic_noexcept",
      "inline",
      "alignas",
      "and",
      "enum",
      "", "",
      "default",
      "unsigned",
      "", "",
      "sizeof",
      "alignof",
      "co_await",
      "", "",
      "friend",
      "nullptr",
      "co_yield",
      "",
      "while",
      "not_eq",
      "thread_local",
      "new",
      "bool",
      "",
      "and_eq",
      "",
      "asm",
      "auto",
      "union",
      "public",
      "do",
      "operator",
      "", "",
      "double",
      "private",
      "volatile",
      "", "", "",
      "dynamic_cast",
      "char16_t",
      "protected",
      "", "", "", "", "",
      "compl",
      "bitand",
      "",
      "atomic_cancel",
      "", "", "",
      "mutable",
      "", "",
      "throw",
      "module",
      "", "",
      "void",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "",
      "or_eq",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "", "",
      "", "", "", "", "", "", "", "",
      "virtual"
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
       int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
           const char *s = wordlist[key];

          if (*str == *s && !strcmp (str + 1, s + 1))
            return s;
        }
    }
  return 0;
}

#endif
