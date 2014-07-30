static GtkWidget *
load_content (GPtrArray *stuff)
{
  /* create the model */
  GtkListStore *store = gtk_list_store_new (3,
                                            G_TYPE_STRING, /* foo */
                                            G_TYPE_STRING, /* bar */
                                            G_TYPE_BOOLEAN /* baz */);

  /* create the view */
  GtkWidget *view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));

  /* load each object data into a row of the model */
  for (int i = 0; i < stuff->len; i++)
    {
      YourObject *obj = stuff->pdata[i];
      GtkTreeIter iter;

      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
                          COLUMN_FOO, your_object_get_foo (obj),
                          COLUMN_BAR, your_object_get_bar (obj),
                          COLUMN_BAZ, your_object_get_baz (obj),
                          -1);
    }

  /* the view owns the model now */
  g_object_unref (store);

  return view;
}
