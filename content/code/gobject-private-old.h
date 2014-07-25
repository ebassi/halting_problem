typedef struct _MyObject MyObject;
typedef struct _MyObjectPrivate MyObjectPrivate;
typedef struct _MyObjectClass MyObjectClass;

// instance structure
struct _MyObject {
  GObject parent_instance;

  // pointer for quick access to instance private data
  MyObjectPrivate *priv;
};

// class structure
struct _MyObjectClass {
  GObjectClass parent_class;
};

GType my_object_get_type (void);
