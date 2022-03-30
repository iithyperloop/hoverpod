#include <gtk/gtk.h>
#include <string>
#include <stdio.h>

struct _AppWindow
{
  GtkApplicationWindow parent;
};

typedef struct _AppWindowPrivate AppWindowPrivate;

struct _AppWindowPrivate
{
  GtkWidget *stack;
};

//G_DEFINE_TYPE_WITH_PRIVATE(AppWindow, app_window, GTK_TYPE_APPLICATION_WINDOW);

int
main( int    argc,
      char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window, *view;
    GError     *error = NULL;
  
    /* Init GTK+ */
    gtk_init( &argc, &argv );

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    /* Load UI from file. If error occurs, report it and quit application. */
    if( ! gtk_builder_add_from_file( builder, "GUI.glade", &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }
  
    /* Get main window pointer from UI */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );

    /* Get textview pointer from UI */
    view = GTK_WIDGET(gtk_builder_get_object(builder, "speedText"));

    GtkTextBuffer *buffer;
    const gchar* text = "Test";
    gsize length = 4;
    // Text MUST be converted to utf8 format before being displayed to a text box
    gchar *contents = g_locale_to_utf8(text, length, NULL, NULL, NULL);

    // Gets buffer from current view
    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

    // Writes <length> characters from <contents> into <buffer> associated with <view>
    gtk_text_buffer_set_text (buffer, contents, length);
    g_free (contents);
    
    
    /* Connect signals */
    gtk_builder_connect_signals( builder, NULL );

    /* Destroy builder, since we don't need it anymore */
    g_object_unref( G_OBJECT( builder ) );

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show( window );
    
    /* Start main loop */
    gtk_main();
      
    return( 0 );
 }

