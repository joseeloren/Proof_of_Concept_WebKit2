#include <stdio.h>
#include <webkit2/webkit2.h>
#include <gtk/gtk.h>
#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSStringRef.h>

static void
web_view_javascript_finished (GObject      *object,
                              GAsyncResult *result,
                              gpointer      user_data)
{
    WebKitJavascriptResult *js_result;
    JSValueRef              value;
    JSGlobalContextRef      context;
    GError                 *error = NULL;

    js_result = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object), result, &error);


    if (!js_result) {
        g_warning ("Error running javascript: %s", error->message);
        g_error_free (error);
        return;
    }

    context = webkit_javascript_result_get_global_context (js_result);
    value = webkit_javascript_result_get_value (js_result);
    if (JSValueIsString (context, value)) {
        JSStringRef js_str_value;
        gchar      *str_value;
        gsize       str_length;

        js_str_value = JSValueToStringCopy (context, value, NULL);
        str_length = JSStringGetMaximumUTF8CStringSize (js_str_value);
        str_value = (gchar *)g_malloc (str_length);
        JSStringGetUTF8CString (js_str_value, str_value, str_length);
        JSStringRelease (js_str_value);
        g_print ("Script result: %s\n", str_value);
        g_free (str_value);
    } else {
        g_warning ("Error running javascript: unexpected return value");
    }
    webkit_javascript_result_unref (js_result);
}

static void
web_view_get_link_url (WebKitWebView *web_view)
{
    gchar *script;

    script = g_strdup_printf("window.document.getElementByIdd('%s').innerHTML;","web-content-rendering");


    JSStringRef s = JSStringCreateWithUTF8CString("window.document.getElementById('web-content-rendering').innerHTML;");
    JSGlobalContextRef c = webkit_web_view_get_javascript_global_context(web_view);
    JSValueRef ex;//const OpaqueJSValue** ex = NULL;
    JSValueRef val = JSEvaluateScript(c, s,0,0,0,(const OpaqueJSValue**)ex);
    //printf("%s\n",ex);
    if (val == NULL)
      printf("ok\n");
    bool b = JSCheckScriptSyntax(c, s,0,0,0);
    printf("%d\n",(b)?1:0);
    

    webkit_web_view_run_javascript(web_view,script,NULL,web_view_javascript_finished,NULL);
    g_free(script);
}

static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
{
    gtk_main_quit();
}

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
{
    gtk_widget_destroy(window);
    return TRUE;
}

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

    // Load a web page into the browser instance
    webkit_web_view_load_uri(webView, "http://www.webkitgtk.org/");

    // Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(main_window);

    web_view_get_link_url (webView);    

    // Run the main GTK+ event loop
    gtk_main();


    return 0;
}


