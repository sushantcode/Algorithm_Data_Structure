#include <gtk/gtk.h>
#include <stdlib.h>
#include <iostream>
#define __STDC_FORMAT_MACROS


#ifndef _MY__GLOBAL__H
#define _MY__GLOBAL__H

using namespace std;

/**************************************************************
 * GUI window stuff
 **************************************************************/

typedef struct 
{
  GtkWidget *window1; //visualization window

  GtkWidget *label_result;  // the label for the output

  GtkWidget *button_1;  //the 1 button
  GtkWidget *button_2;  //the 2 button
  GtkWidget *button_3;
  GtkWidget *button_4;
  GtkWidget *button_5;
  GtkWidget *button_6;
  GtkWidget *button_7;
  GtkWidget *button_8;
  GtkWidget *button_9;
  GtkWidget *button_0;
  GtkWidget *button_plus;  //the + button
  GtkWidget *button_minus;
  GtkWidget *button_times;
  GtkWidget *button_divide;
  GtkWidget *button_equal;
  GtkWidget *button_exit;  //the exit button

} Gui_Window_AppWidgets;

extern Gui_Window_AppWidgets *gui_app;

extern int operand;
extern int last_function;
extern int clear_f;

#endif
