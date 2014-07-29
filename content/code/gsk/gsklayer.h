#ifndef __GSK_LAYER_H__
#define __GSK_LAYER_H__

#if !defined(__GSK_H_INSIDE__) && !defined(GSK_COMPILATION)
#error "Only <gsk/gsk.h> can be included directly."
#endif

#include <gsk/gsktypes.h>

G_BEGIN_DECLS

#define GSK_TYPE_LAYER                  (gsk_layer_get_type ())
#define GSK_LAYER(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GSK_TYPE_LAYER, GskLayer))
#define GSK_IS_LAYER(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GSK_TYPE_LAYER))
#define GSK_LAYER_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GSK_TYPE_LAYER, GskLayerClass))
#define GSK_IS_LAYER_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GSK_TYPE_LAYER))
#define GSK_LAYER_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GSK_TYPE_LAYER, GskLayerClass))

typedef struct _GskLayerClass           GskLayerClass;

/**
 * GskLayer:
 *
 * The base type for each element of the scene graph.
 *
 * By default, a layer is a transparent rectangle with no content.
 *
 * The top level element is attached to a windowing system surface, and
 * traversed from that point for both geometry and paiting.
 *
 * The layers hierarchy is defined in terms of a parent-children
 * relationship; each layer has a #GskLayer:parent element, unless that
 * layer is the top-level layer attached to a windowing system surface.
 * Layers can have children, and you can traverse the graph both in
 * a depth first as well as in a breadth first fashion.
 *
 * By default, child layers are not constrained when drawing to the
 * bounds of their parent layer; it is possible, however, to specify
 * that the parent should "clip" its drawing area to its bounding
 * box. The only layer that is bound to an implicit clip is the top
 * level element of the scene graph, which will always be clipped
 * to the windowing system surface size.
 *
 * Each element has specific geometry, transformations, and content.
 *
 * The geometry is defined in terms of the #GskLayer.position of a
 * #GskLayer:pivot-point and of a rectangle relative to that point,
 * called #GskLayer:bounds
 *
 * The rectangle has a width and a height, and its origin is always
 * positioned at the top left corner.
 *
 * The pivot point is expressed in normalized, layer-relative units,
 * and by default it is placed at the center of the layer's rectangle,
 * at the (0.5, 0.5) point.
 *
 * It is possible to set the position of the layer relative to the
 * parent's coordinate space by changing the position of the pivot
 * point in parent-relative units; by virtue of the pivot point being
 * always relative to the layer's dimensions, this implies that the
 * layer will change its relative position with regards to its parent.
 *
 * It is also possible to change the overall geometry of a layer by
 * changing its #GskLayer:frame; this is a shortcut that changes the
 * position and the layer's rectangle at the same time.
 *
 * A layer possesses a current transformation matrix; this matrix is
 * applied before the content of the layer is drawn. It is possible
 * to provide a full transformation matrix, relative to the layer's
 * pivot point, which specifies the transformations list in the order
 * the developer applies them; for convenience, it's also possible
 * to specify transformations using "shorthand" methods, which are
 * applies in a well-defined order internally.
 *
 * Transformations can also be applied by a parent to all its
 * children, through the use of a child transformation matrix. This
 * allows, for instance, to apply the same translation offset in a
 * "scrolling" layout, without necessarily change the children frame
 * or their own transformation matrix.
 *
 * Finally, each layer has its own #GskLayer:content.
 *
 * It is possible to provide content for a layer in two different
 * ways:
 *
 *   - use a #GskLayerContent interface implementation
 *   - override the @GskLayerClass.draw virtual function
 *
 * The #GskLayerContent interface specifies how a delegate object
 * can draw itself when asked by the layer that uses that content.
 *
 * The @GskLayerClass.draw virtual function provides a graphic
 * context for you to draw on, and it's called whenever the layer
 * contents have been invalidated and need to be redrawn.
 */
struct _GskLayer
{
  /*< private >*/
  GInitiallyUnowned parent_instance;
};

struct _GskLayerClass
{
  /*< private >*/
  GInitiallyUnownedClass parent_class;

  /*< public >*/
  /* virtual functions */
  void          (* draw)                (GskLayer         *layer,
                                         cairo_t          *context);

  void          (* queue_resize)        (GskLayer         *layer,
                                         GskLayer         *origin);
  void          (* queue_redraw)        (GskLayer         *layer,
                                         GskLayer         *origin);

  void          (* get_preferred_size)  (GskLayer         *layer,
                                         graphene_size_t  *size);

  void          (* layout_children)     (GskLayer         *layer);

  gboolean      (* contains_point)      (GskLayer               *layer,
                                         const graphene_point_t *point);
  gboolean      (* hit_test)            (GskLayer               *layer,
                                         const graphene_point_t *point);

  /* signals */
  void          (* child_added)         (GskLayer         *layer,
                                         GskLayer         *child);
  void          (* child_removed)       (GskLayer         *layer,
                                         GskLayer         *child);
  void          (* destroy)             (GskLayer         *layer);

  /*< private >*/
  gpointer _padding[16];
};

GDK_AVAILABLE_IN_3_14
GType gsk_layer_get_type (void);

GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_new                   (void);

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_queue_resize          (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_queue_redraw          (GskLayer                *layer);

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_name              (GskLayer                *layer,
                                                         const char              *name);
GDK_AVAILABLE_IN_3_14
const char *            gsk_layer_get_name              (GskLayer                *layer);

/* The layer hierarchy */

GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_parent            (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_add_child             (GskLayer                *layer,
                                                         GskLayer                *child);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_insert_child_at_index (GskLayer                *layer,
                                                         GskLayer                *child,
                                                         int                      index_);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_insert_child_above    (GskLayer                *layer,
                                                         GskLayer                *child,
                                                         GskLayer                *sibling);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_insert_child_below    (GskLayer                *layer,
                                                         GskLayer                *child,
                                                         GskLayer                *sibling);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_replace_child         (GskLayer                *layer,
                                                         GskLayer                *old_child,
                                                         GskLayer                *new_child);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_remove_child          (GskLayer                *layer,
                                                         GskLayer                *child);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_remove_all_children   (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_first_child       (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_last_child        (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_next_sibling      (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_previous_sibling  (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
guint                   gsk_layer_get_n_children        (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_child_at_index    (GskLayer                *layer,
                                                         GskLayer                *child,
                                                         gint                     index_);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_get_child_at_index    (GskLayer                *layer,
                                                         gint                     index_);
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_contains              (GskLayer                *layer,
                                                         GskLayer                *descendand);

/* Geometry */

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_frame             (GskLayer                *layer,
                                                         const graphene_rect_t   *frame);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_frame             (GskLayer                *layer,
                                                         graphene_rect_t         *frame);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_bounds            (GskLayer                *layer,
                                                         const graphene_rect_t   *bounds);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_bounds            (GskLayer                *layer,
                                                         graphene_rect_t         *bounds);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_pivot_point       (GskLayer                *layer,
                                                         const graphene_point_t  *pivot);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_pivot_point       (GskLayer                *layer,
                                                         graphene_point_t        *pivot);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_position          (GskLayer                *layer,
                                                         const graphene_point_t  *position);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_position          (GskLayer                *layer,
                                                         graphene_point_t        *position);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_preferred_size    (GskLayer                *layer,
                                                         graphene_size_t         *size);

/* Transformations */

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_pivot_point_z     (GskLayer                *layer,
                                                         float                    z_position);
GDK_AVAILABLE_IN_3_14
float                   gsk_layer_get_pivot_point_z     (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_z_position        (GskLayer                *layer,
                                                         float                    z_position);
GDK_AVAILABLE_IN_3_14
float                   gsk_layer_get_z_position        (GskLayer                *layer);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_transform         (GskLayer                *layer,
                                                         const graphene_matrix_t *transform);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_transform         (GskLayer                *layer,
                                                         graphene_matrix_t       *transform);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_child_transform   (GskLayer                *layer,
                                                         const graphene_matrix_t *transform);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_child_transform   (GskLayer                *layer,
                                                         graphene_matrix_t       *transform);

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_rotation          (GskLayer                *layer,
                                                         GskLayerRotationAxis     axis,
                                                         double                   degrees);
GDK_AVAILABLE_IN_3_14
void                    gsk_later_set_scale             (GskLayer                *layer,
                                                         float                    x,
                                                         float                    y,
                                                         float                    z);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_translation       (GskLayer                *layer,
                                                         float                    x,
                                                         float                    y,
                                                         float                    z);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_skew              (GskLayer                *layer,
                                                         float                    skew_x,
                                                         float                    skew_y);

/* Content */

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_visible           (GskLayer                *layer,
                                                         gboolean                 is_visible);
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_get_visible           (GskLayer                *layer);

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_clip_to_bounds    (GskLayer                *layer,
                                                         gboolean                 clip);
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_get_clip_to_bounds    (GskLayer                *layer);


GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_content           (GskLayer                *layer,
                                                         GskLayerContent         *content);
GDK_AVAILABLE_IN_3_14
GskLayerContent *       gsk_layer_get_content           (GskLayer                *layer);

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_background_color  (GskLayer                *layer,
                                                         const GdkRGBA           *color);
GDK_AVAILABLE_IN_3_14
void                    gsk_layer_get_background_color  (GskLayer                *layer,
                                                         GdkRGBA                 *color);

/* Layout management */

GDK_AVAILABLE_IN_3_14
void                    gsk_layer_set_layout_manager    (GskLayer                *layer,
                                                         GskLayoutManager        *manager);
GDK_AVAILABLE_IN_3_14
GskLayoutManager *      gsk_layer_get_layout_manager    (GskLayer                *layer);

/* Hit testing */
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_contains_point        (GskLayer                *layer,
                                                         const graphene_point_t  *point);
GDK_AVAILABLE_IN_3_14
GskLayer *              gsk_layer_hit_test              (GskLayer                *layer,
                                                         const graphene_point_t  *point);

/* Coordinate transformations */
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_transform_point       (GskLayer                *layer,
                                                         GskLayer                *source,
                                                         const graphene_point_t  *point,
                                                         graphene_point_t        *res);
GDK_AVAILABLE_IN_3_14
gboolean                gsk_layer_transform_rect        (GskLayer                *layer,
                                                         GskLayer                *source,
                                                         const graphene_rect_t   *rect,
                                                         graphene_rect_t         *res);

G_END_DECLS

#endif /* __GSK_LAYER_H__ */
