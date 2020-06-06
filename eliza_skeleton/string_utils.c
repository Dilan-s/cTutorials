#include "string_utils.h"
#include "map.h"
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* Returns a heap allocated, null-terminated, zero-length string. */

char *empty_string(void)
{
  char *empty_string = malloc(sizeof(char));
  if (empty_string == NULL) {
    perror("empty_string");
    exit(EXIT_FAILURE);
  }
  *empty_string = '\0';
  return empty_string;
  //  fprintf(stderr, "empty_string() unimplemented.\n");
  //  exit(EXIT_FAILURE);
}


/* Given a string, return a heap-allocated copy */

char *clone(const char *str)
{
  int length = strlen(str) + 1;
  char *clone = malloc((length + 1) * sizeof(char));
  if (clone == NULL) {
    perror("clone");
    exit(EXIT_FAILURE);
  }
  strcpy(clone, str);
  return clone;

  //  fprintf(stderr, "clone() unimplemented.\n");
  //exit(EXIT_FAILURE);
}


/* Returns a heap allocated string that consists of "current" appended to
 * "append". This process must either free current or prevent it from
 * being leaked via some other mechanism.
 */

char *push_string(char *current, const char *append)
{
  
  assert(current != NULL);
  assert(append != NULL);

  current = realloc(current, strlen(current) + strlen(append) + 1);
  if (current == NULL) {
    perror("push_string");
    exit(EXIT_FAILURE);
  }

  int lengthOfCurrent = strlen(current);
  for (int i = 0; i <= strlen(append); i++) {
    current[lengthOfCurrent + i] = append[i];
  }

  return current;

  //  fprintf(stderr, "push_string() unimplemented.\n");
  //  exit(EXIT_FAILURE);
}


/* Removes trailing /n (if present) from str */

void trim_newline(char *str)
{
  const size_t length = strlen(str);
  if (length > 0 && str[length - 1] == '\n')
    str[length - 1] = '\0';
}


/* Transforms a string to lowercase */

void make_lowercase(char *str)
{
  assert(str != NULL);

  for(; *str != '\0'; ++str)
    *str = tolower(*str);
}


/* Given an input string, return the number of tokens, and a table of
 * tokens in *tokens. The input string is damaged by this process. The
 * returned table should be freed after use.
 */

int tokenize(char ***tokens, char* input)
{
  assert(input != NULL);

  int token_count = 0;
  int middle_of_word = 0;
  char **output = malloc(0);
  assert(output != NULL);

  while(*input != '\0')
  {
    if (*input == ' ' || *input == '.' || *input == '?' || *input == '\n')
    {
      *input = '\0';
      middle_of_word = 0;
    }
    else if (!middle_of_word)
    {
      ++token_count;
      output = realloc(output, token_count * sizeof(char*));
      assert(output != NULL);
      output[token_count - 1] = input;
      middle_of_word = 1;
    }

    ++input;
  }
  *tokens = output;
  return token_count;
}


/* Rewrites the supplied string, using the mapping from strings to
 * strings in substitutions. The returned string should be freed after
 * use.
 */

char *rewrite_string(struct map *substitutions, const char* const_input)
{
  char *const input = clone(const_input);
  char **tokens;
  char *result = empty_string();

  const int token_count = tokenize(&tokens, input);
  for(int index = 0; index < token_count; ++index)
  {
    make_lowercase(tokens[index]);
    char *replacement = (char *) map_lookup(substitutions, tokens[index]);

    if (replacement == NULL)
      result = push_string(result, tokens[index]);
    else
      result = push_string(result, replacement);

    if (index + 1 < token_count)
      result = push_string(result, " ");
  }

  free(input);
  free(tokens);
  return result;
}
/*
int main() {
  char *str = empty_string();
  str = push_string(str, " This " );
  str = push_string(str, " is " );
  str = push_string(str, " a sequence of " );
  str = push_string(str, " string concatenations! " );
  printf(" %s \n " , str);
  free(str);
  return 0;
}
*/
