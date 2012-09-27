#ifndef _INCLUDE_ICSV_H_
#define _INCLUDE_ICSV_H_

/*----------------------------------------------------------------------------*/
/* define */
/*----------------------------------------------------------------------------*/
#define ICSV_BUFFER_SIZE 1024

/*----------------------------------------------------------------------------*/
/* include */
/*----------------------------------------------------------------------------*/
#include <string.h>
#include "ilist.h"
#include "istring.h"

/*----------------------------------------------------------------------------*/
/* icsv */
/*----------------------------------------------------------------------------*/
typedef struct ICSV
{
  size_t  nl;   /* # lines */
  size_t* ni;   /* # items in each line */
  char ***item; /* item[i][j] = the j-th item(string) in the i-th line */
} icsv;

/* new/free */
icsv *icsv_new(const char *_name);
void icsv_free(icsv *_csv);

/* show */
void icsv_show(icsv *_csv, FILE *_fp);

#endif /* _INCLUDE_ICSV_H_ */
