#ifndef __GSK_LAYER_CONTENT_H__
#define __GSK_LAYER_CONTENT_H__

#if !defined(__GSK_H_INSIDE__) && !defined(GSK_COMPILATION)
#error "Only <gsk/gsk.h> can be included directly."
#endif

#include <gsk/gsktypes.h>

G_BEGIN_DECLS

#define GSK_TYPE_LAYER_CONTENT                  (gsk_layer_content_get_type ())
#define GSK_LAYER_CONTENT(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_LAYER_CONTENT, GskLayerContent))
#define GSK_IS_LAYER_CONTENT(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_LAYER_CONTENT))
#define GSK_LAYER_CONTENT_GET_IFACE(obj)        (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GSK_TYPE_LAYER, GskLayerContentInterface))

typedef struct _GskLayerContentInterface        GskLayerContentInterface;

struct _GskLayerContentInterface
{
  GTypeInterface g_iface;

  void (* prepare)            (GskLayerContent *content,
                               GskLayer        *layer);

  void (* draw)               (GskLayerContent *content,
                               GskLayer        *layer,
                               cairo_t         *context);

  void (* get_preferred_size) (GskLayerContent *content,
                               graphene_size_t *size);

  void (* invalidate)         (GskLayerContent *content);

  void (* attached)           (GskLayerContent *content,
                               GskLayer        *layer);
  void (* detached)           (GskLayerContent *content,
                               GskLayer        *layer);

};

GDK_AVAILABLE_IN_3_14
GType gsk_layer_content_get_type (void) G_GNUC_CONST;

GDK_AVAILABLE_IN_3_14
void gsk_layer_content_get_preferred_size (GskLayerContent *content,
                                           graphene_size_t *size);

GDK_AVAILABLE_IN_3_14
void gsk_layer_content_invalidate (GskLayerContent *content);

G_END_DECLS

#endif /* __GSK_LAYER_CONTENT_H__ */
