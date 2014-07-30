/* states in the FSM */
enum {
  STATE_STARTED,  /* start state */

  STATE_LOADING,  /* feeding the items to the model */
  STATE_COMPLETE, /* feeding the model to the view */

  STATE_FINISHED  /* finish state */
};

/* data to be passed to the idle handler */
typedef struct
{
  /* the current state */
  guint state;

  /* the idle handler id */
  guint load_id;

  /* the model */
  GtkListStore *list_store;

  /* the view */
  GtkWidget *tree_view;

  /* the items to be loaded */
  GPtrArray *items

  /* the currently loaded item */
  guint current_item;
} IdleData;

static void cleanup_load_items (gpointer data);

static void
load_content (GPtrArray *stuff)
{
  IdleData *data;

  data = g_new (IdleData, 1);

  data->items = g_ptr_array_ref (items);

  data->n_loaded = 0;

  /* create the model */
  data->list_store = gtk_list_store_new (3,
                                         G_TYPE_STRING, /* foo */
                                         G_TYPE_STRING, /* bar */
                                         G_TYPE_BOOLEAN /* baz */);
  /* create the view */
  data->tree_view = gtk_tree_view_new ();

  data->state = STATE_STARTED;
  data->load_id = g_idle_add_full (G_PRIORITY_HIGH_IDLE,
                                   load_items_idle,
                                   data,
                                   cleanup_load_items);

  return data->tree_view;
}

/* clean up function */
static void
cleanup_load_items (gpointer data_)
{
  IdleData *data = data_;

  /* make sure we are in the right state */
  g_assert (data->state == STATE_FINISHED);

  /* assign the model to the view */
  gtk_tree_view_set_model (GTK_TREE_VIEW (data->tree_view),
                           GTK_TREE_MODEL (data->list_store));

  /* the view now owns the model */
  g_object_unref (data->list_store);

  g_ptr_array_unref (data->items);
  g_free (data);
}

/* the actual loading function */
static gboolean
load_items_idle (gpointer data_)
{
  IdleData *data = data_;
  YourObject *obj;
  GtkTreeIter iter;

  /* make sure we are in the right state */
  g_assert (data->state == STATE_STARTED || data->state == STATE_LOADING)

  /* no items left */
  if (data->current_item == data->items->len)
    {
      /* set the correct state */
      data->state = STATE_FINISHED;

      /* remove the source.
       *
       * this will cause cleanup_load_items() to be called
       */
      return G_SOURCE_REMOVE;
    }

  /* we are now loading */
  if (data->state == STATE_STARTED)
    data->state = STATE_LOADING;

  /* get the next item in the list */
  obj = data->items->pdata[data->current_item];
  g_assert (obj != NULL);

  gtk_list_store_append (data->list_store, &iter);
  gtk_list_store_set (data->list_store, &iter,
                      COLUMN_FOO, your_object_get_foo (obj),
                      COLUMN_BAR, your_object_get_bar (obj),
                      COLUMN_BAZ, your_object_get_baz (obj),
                      -1);

  /* next item */
  data->current_item += 1;

  /* we can also update the UI, for instance with a nice progress bar */
  update_progress (data->current_item, data->items->len);

  /* continue loading */
  return G_SOURCE_CONTINUE;
}
