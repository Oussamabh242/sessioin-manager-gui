#include <gtk/gtk.h>
#include <stdio.h>
static void killwindow(GtkWidget *window) {
    gtk_window_destroy(GTK_WINDOW(window));
}

typedef struct 
{
    char *msg  ;
    GtkWidget *window ;
}arg;



static void lockScreen(){

  system("i3lock -c 000000") ;
}

static void logout(){
  system("i3-msg exit"); 
}

static void restart(){
  system("reboot") ;
}

static void shutdown(){
  system("shutdown mow") ;
}

arg* init(GtkWidget* window , char* msg){

    arg *a = (arg*)malloc(sizeof(arg)) ; 
    a->msg = msg ;
    a->window = window ;
    return a ; 
}

static void gerdh( GtkWidget *button , gpointer user_data ){
  arg *thing = (arg*)user_data;
  char* message = thing->msg; 
  void (*func)(void) = NULL;
  if (strcmp(message, "logout") == 0) {
        func = logout;
    } else if (strcmp(message, "lockScreen") == 0) {
        func = lockScreen;
    } else if (strcmp(message, "shutdown") == 0) {
        func = shutdown;
    } else if (strcmp(message, "restart") == 0) {
        func = restart;
    } else {
        func = NULL; 
    }


   
  GtkWidget *window ;  
  GtkWidget *label ;
  GtkWidget *button1;
  GtkWidget *button2;
  GtkWidget *grid ;
  window = gtk_window_new();
  gtk_window_set_title(GTK_WINDOW(window), "Confirm");
  gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);
  gtk_widget_show(window);

  button1 = gtk_button_new_with_label("Yes") ;
  button2 = gtk_button_new_with_label("No") ;


  grid = gtk_grid_new();
  gtk_widget_set_margin_start(grid, 10);
  gtk_widget_set_margin_end(grid, 10);
  gtk_widget_set_margin_top(grid, 10);
  gtk_widget_set_margin_bottom(grid, 10);

  gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1); // (0,0)
  gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1);
  g_signal_connect(button1 , "clicked", G_CALLBACK (func)  , NULL);

  g_signal_connect_swapped(button1, "clicked", G_CALLBACK(gtk_window_destroy), thing->window);
  g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_window_destroy), thing->window);


  gtk_window_set_child(GTK_WINDOW(window), grid);


  gtk_widget_show(window);
  free(thing); 
}





static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;

    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Session Control");
    gtk_window_set_default_size(GTK_WINDOW(window), 100, 100);

    // Create a grid
    grid = gtk_grid_new();
    gtk_widget_set_margin_start(grid, 10);
    gtk_widget_set_margin_end(grid, 10);
    gtk_widget_set_margin_top(grid, 10);
    gtk_widget_set_margin_bottom(grid, 10);

    // Create buttons
    button1 = gtk_button_new_with_label("Logout");
    button2 = gtk_button_new_with_label("Lock");
    button3 = gtk_button_new_with_label("Shutdown");
    button4 = gtk_button_new_with_label("Restart");

    // Attach buttons to the grid
    gtk_grid_attach(GTK_GRID(grid), button1, 0, 0, 1, 1); // (0,0)
    gtk_grid_attach(GTK_GRID(grid), button2, 1, 0, 1, 1); // (1,0)
    gtk_grid_attach(GTK_GRID(grid), button3, 0, 1, 1, 1); // (0,1)
    gtk_grid_attach(GTK_GRID(grid), button4, 1, 1, 1, 1); // (1,1)

    g_signal_connect(button2, "clicked", G_CALLBACK (gerdh), init(window , "lockScreen"));
    g_signal_connect(button1, "clicked", G_CALLBACK (gerdh), init(window , "logout"));
    g_signal_connect(button4 , "clicked", G_CALLBACK (gerdh)  , init(window , "restart"));
    g_signal_connect(button3 , "clicked", G_CALLBACK(gerdh) , init(window , "shutdown")) ; 

  //     g_signal_connect_swapped(button1, "clicked", G_CALLBACK(gtk_window_destroy), window);
  //     g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_window_destroy), window);
  //     g_signal_connect_swapped(button3, "clicked", G_CALLBACK(gtk_window_destroy), window);
  // g_signal_connect_swapped(button4, "clicked", G_CALLBACK(gtk_window_destroy), window);

    // Add grid to the window
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // Show the window (and all its children)
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.Grid", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}