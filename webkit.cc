#include <stdio.h>
#include <webkit2/webkit2.h>
#include <gtk/gtk.h>

int main() {
  printf("WebKit version (%d.%d.%d)",webkit_get_major_version(),webkit_get_minor_version(),webkit_get_micro_version());
}
