typedef struct {
  int foo;
} MyObjectPrivate;

// WITH_PRIVATE is like WITH_CODE (G_ADD_PRIVATE)
G_DEFINE_TYPE_WITH_PRIVATE (MyObject, my_object, G_TYPE_OBJECT)

static void
my_object_class_init (MyObjectClass *klass)
{
}

static void
my_object_init (MyObject *self)
{
  // get_instance_private() is just pointer arithmetic
  MyObjectPrivate *priv = my_object_get_instance_private (self);

  priv->foo = 42;
}
