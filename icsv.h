#ifndef _INCLUDE_ICSV_H_
#define _INCLUDE_ICSV_H_

/*----------------------------------------------------------------------------*/
/* define */
/*----------------------------------------------------------------------------*/
#define ICSV_BUFFER_SIZE (1024 * 1024)

/*----------------------------------------------------------------------------*/
/* include */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <istring.h>
#include <ilist.h>

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
icsv *icsv_new_delimiter(const char *_name, const char *_del);
void icsv_free(icsv *_csv);

/* show/export */
void icsv_show(icsv *_csv, FILE *_fp);
void icsv_export(icsv *_csv, FILE *_fp);

/* get */
size_t icsv_num_line(icsv *_csv);
size_t icsv_num_item(icsv *_csv, size_t _i);
char  *icsv_get(icsv *_csv, size_t _i, size_t _j);

#endif /* _INCLUDE_ICSV_H_ */
