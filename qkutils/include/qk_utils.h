#ifndef QK_UTILS_H
#define QK_UTILS_H


#include <stdint.h>
#include <stdbool.h>

/*****************************************************************************
 *  Circular Buffers
 *****************************************************************************/

typedef volatile struct
{
  void      *buf;
  void      *bufEnd;
  uint32_t  capacity;
  uint32_t  itemSize;
  uint32_t  count;
  void      *head;
  void      *tail;
  bool      overwrite;
} qk_cb;

void      qk_cb_init      (qk_cb *cb, void *buf, uint32_t bufSize, uint32_t itemSize, bool overwrite);
void      qk_cb_write     (qk_cb *cb, const void *item);
void      qk_cb_read      (qk_cb *cb, void *item);
void*     qk_cb_pick      (qk_cb *cb);
bool      qk_cb_is_full   (qk_cb *cb);
bool      qk_cb_is_empty  (qk_cb *cb);
uint32_t  qk_cb_available (qk_cb *cb);

#endif /* QK_UTILS_H */
