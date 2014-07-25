typedef struct _MyObject MyObject;
typedef struct _MyObjectClass MyObjectClass;

struct _MyObject {
  GObject parent_instance;
};

struct _MyObjectClass {
  GObjectClass parent_class;
};

GType my_object_get_type (void);
