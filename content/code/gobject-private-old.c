struct _MyObjectPrivate
{
  int foo;
};

G_DEFINE_TYPE (MyObject, my_object, G_TYPE_OBJECT)

static void
my_object_class_init (MyObjectClass *klass)
{
  // tell the type system that the instance has private data
  g_type_class_add_private (klass, sizeof (MyObjectPrivate));
}

static void
my_object_init (MyObject *self)
{
  // G_TYPE_INSTANCE_GET_PRIVATE() is expensive, so we keep a back
  // pointer for quick access
  self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                            my_object_get_type (),
                                            MyObjectPrivate);
  self->priv->foo = 42;
}
