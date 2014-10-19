typedef struct _MyObject        MyObject;
typedef struct _MyObjectClass   MyObjectClass;

struct _MyObject { GObject parent_instance; };
struct _MyObjectClass { GObjectClass parent_class; };

GType my_object_get_type (void);

typedef struct {
  int foo;
  char *bar;
} MyObjectPrivate;

typedef struct {
  GProperty *foo;
} MyObjectClassPrivate;

G_DEFINE_TYPE_WITH_CODE (MyObject, my_object, G_TYPE_OBJECT,
                         G_ADD_PRIVATE (MyObject)
                         G_ADD_CLASS_PRIVATE (MyObject)
                         G_ADD_PROPERTY (MyObject, my_object, int, foo,
                                         G_PROPERTY_READWRITE
                                         G_PROPERTY_RANGE (-1, G_MAXINT)
                                         G_PROPERTY_DEFAULT (-1)))

static void
my_object_finalize (GObject *gobject)
{
  MyObject *self = MY_OBJECT (gobject);
  MyObjectPrivate *priv = my_object_get_instance_private (self);

  g_free (priv->bar);

  G_OBJECT_CLASS (my_object_parent_class)->finalize (self);
}

static void
my_object_class_init (MyObjectClass *klass)
{
  G_OBJECT_CLASS (klass)->finalize = my_object_finalize;
}

static void
my_object_init (MyObject *self)
{
  MyObjectPrivate *priv = my_object_get_instance_private (self);

  priv->bar = g_strdup ("Hello, World!");
}

MyObject *
my_object_new (void)
{
  return g_object_new (my_object_get_type (), NULL);
}

MyObject *
my_object_new_with_foo (int foo)
{
  return g_object_new (my_object_get_type (), "foo", foo, NULL);
}
