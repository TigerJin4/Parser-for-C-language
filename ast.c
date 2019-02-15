#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "utils.h"

/*
   Creates a new AST from a given type filename and linenum. You should not
   assume that filename will remain a legal pointer after this function
   terminates.
*/
AST* MakeAST(enum NodeType type, char* filename, int linenum) {
  AST* ast = (AST*)malloc(sizeof(AST));
  ast->type = type;
  ast->capacity = INITIAL_CAPACITY;
  ast->filename = (char*)malloc(sizeof(char) * (strlen(filename) + 1));
  if (ast->filename == NULL) {
    allocation_failed();
  }
  strcpy(ast->filename, filename);
  ast->linenum = linenum;
  ast->size = 0;
  ast->children = (AST**)malloc(sizeof(AST*) * ast->capacity);
  /* YOUR CODE HERE. */
  return ast;
}

/*
   Takes in a given AST and mallocs a new AST with the exact same details as the
   original. Again you should assume the original may be freed at any point
   after this function terminates.
*/
AST* CopyAST(AST* original) {
  AST* ast = MakeAST(original->type, original->filename, original->linenum);
  ast->size = original->size;
  ast->capacity = original->capacity;
  ast->children = (AST**)realloc(ast->children, sizeof(AST*) * ast->capacity);
  if (ast->children == NULL) {
    allocation_failed();
  }
  for (int i = 0; i < ast->size; i++) {
    ast->children[i] = CopyAST(original->children[i]);
  }

  /* Start Unique to Copy */
  if (ast->type == NODETYPE_ID) {
    ast->data.identifier =
        (char*)malloc(sizeof(char) * (strlen(original->data.identifier) + 1));
    if (ast->data.identifier == NULL) {
      allocation_failed();
    }
    strcpy(ast->data.identifier, original->data.identifier);
  } else if (ast->type == NODETYPE_CONSTANT_STRING) {
    ast->data.string =
        (char*)malloc(sizeof(char) * (strlen(original->data.string) + 1));
    if (ast->data.string == NULL) {
      allocation_failed();
    }
    strcpy(ast->data.string, original->data.string);
  }
  /* End of Unique to Copy */
  return ast;
}

/*
   Takes in an two ASTs and concatenates the two by making node a child
   of tree.
*/
void AppendAST(AST* tree, AST* node) {
  tree->size += 1;
  if (tree->size == tree->capacity){
    tree->capacity += INITIAL_CAPACITY;
    tree->children = (AST**)realloc(tree->children, sizeof(AST*) * tree->capacity);
  } else {
    tree->children = (AST**)realloc(tree->children, sizeof(AST *) * tree->size);
  }
  tree->children[tree->size - 1] = node;
  /* YOUR CODE HERE */
}

/*
   Frees the memory allocated by a single AST node.
*/
void FreeNode(AST* ast) {
  free(ast->children);
  free(ast->filename);
    switch (ast->type) {
        case NODETYPE_ID:
            free(t->data.identifier);
            break;
        case NODETYPE_CONSTANT_STRING:
            free(t->data.string);
            break;
        case NODETYPE_ERR:
            free(t->data.error);
            break;
        default:;
    }
  free(ast);

  /* YOUR CODE HERE */
}

/*
   Frees all the memory allocated by an AST.
*/
void FreeAST(AST* ast) {
  if (ast->children == NULL){
    FreeNode(ast);
  } else {
      free(ast->filename);
      for (int i = 0; i < ast->size; i++) {
          FreeAST(ast->children[i]);
      }
    free(ast);
    free(ast->children);
      switch (ast->type) {
          case NODETYPE_ID:
              free(ast->data.identifier);
              break;
          case NODETYPE_CONSTANT_STRING:
              free(ast->data.string);
              break;
          case NODETYPE_ERR:
              free(ast->data.error);
              break;
          default:;
      }
  }
  /* YOUR CODE HERE */
}
