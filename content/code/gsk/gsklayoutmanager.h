#ifndef __GSK_LAYOUT_MANAGER_H__
#define __GSK_LAYOUT_MANAGER_H__

#if !defined(__GSK_H_INSIDE__) && !defined(GSK_COMPILATION)
#error "Only <gsk/gsk.h> can be included directly."
#endif

#include <gsk/gsktypes.h>

G_BEGIN_DECLS

#define GSK_TYPE_LAYOUT_MANAGER                 (gsk_layout_manager_get_type ())
#define GSK_LAYOUT_MANAGER(obj)                 (G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_LAYOUT_MANAGER, GskLayoutManager))
#define GSK_IS_LAYOUT_MANAGER(obj)              (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_LAYOUT_MANAGER))
#define GSK_LAYOUT_MANAGER_CLASS(klass)         (G_TYPE_CHECK_CLASS_CAST ((klass), GSK_TYPE_LAYOUT_MANAGER, GskLayoutManagerClass))
#define GSK_IS_LAYOUT_MANAGER_CLASS(klass)      (G_TYPE_CHECK_CLASS_TYPE ((klass), GSK_TYPE_LAYOUT_MANAGER))
#define GSK_LAYOUT_MANAGER_GET_CLASS(obj)       (G_TYPE_INSTANCE_GET_CLASS ((obj), GSK_TYPE_LAYOUT_MANAGER, GskLayoutManagerClass))

typedef struct _GskLayoutManagerClass   GskLayoutManagerClass;

struct _GskLayoutManager
{
  GObject parent_instance;
};

struct _GskLayoutManagerClass
{
  GObjectClass parent_class;

  void (* get_preferred_size_for_child) (GskLayoutManager *manager,
                                         GskLayout        *child);
  void (* layout_children)              (GskLayoutManager *manager,
                                         GskLayout        *layer);

  gpointer _padding[8];
};

GDK_AVAILABLE_IN_3_14
GType gsk_layout_manager_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __GSK_LAYOUT_MANAGER_H__ */
