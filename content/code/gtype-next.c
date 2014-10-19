typedef struct _MyObject        MyObject;
typedef struct _MyObjectClass   MyObjectClass;

struct _MyObject { GTypeInstance parent_instance; };
struct _MyObjectClass { GTypeClass parent_class; };

GType my_object_get_type (void);

typedef struct {
  int foo;
  char *bar;
} MyObjectPrivate;

G_DEFINE_TYPE_EXTENDED (MyObject, my_object, G_TYPE_INSTANCE,
                        G_TYPE_FLAG_FINAL,
                        G_ADD_ATOMIC_REF_COUNTING (MyObject, my_object)
                        G_ADD_PRIVATE (MyObject)
                        G_ADD_PROPERTY (MyObject, my_object, int, foo,
                                        G_PROPERTY_READWRITE
                                        G_PROPERTY_RANGE (-1, G_MAXINT)
                                        G_PROPERTY_DEFAULT (-1)))

static void
my_object_finalize (MyObject *self)
{
  MyObjectPrivate *priv = my_object_get_instance_private (self);

  g_free (priv->bar);
}

G_GNUC_UNUSED static void
my_object_dispose (MyObject *self)
{
}

static void
my_object_class_init (MyObjectClass *klass)
{
}

static void
my_object_init (MyObject *self)
{
  MyObjectPrivate *priv = my_object_get_instance_private (self);

  priv->bar = g_strdup ("Hello, world!");
}

/* this is shown for reference, but it's pretty much what g_object_new() would do */
MyObject *
my_object_new (const char *first_property, ...)
{
  MyObject *res = g_type_instance_create (my_object_get_type ());

  va_list args;
  va_start (args, first_property);
  g_type_instance_set_propertiesv (res, args);
  va_end (args);

  return g_ref_new_take (my_object_get_type (), res);
}

MyObject *
my_object_new_wit_foo (int foo)
{
  return my_object_new ("foo", foo, NULL);
}
