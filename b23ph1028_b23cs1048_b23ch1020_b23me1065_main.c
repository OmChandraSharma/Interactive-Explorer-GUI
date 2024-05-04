#include <stdio.h>
#include <gtk-3.0/gtk/gtk.h>
#include <string.h>
#include <sys/stat.h>   //creating folders
#include <dirent.h> //counting files
#include <pango/pangocairo.h>   //fonts
#include <time.h>   // for getting current time
#include <SDL2/SDL.h>   // for playing music
#include <SDL2/SDL_mixer.h> // for playing mp3 specifically
#include <pthread.h>    // for creating parallel processes to play music
#include <stdbool.h>
#include <libavformat/avformat.h>   // imports ffmpeg libraries for reading duration of mp3 file
#define SDL_MAIN_HANDLED


// these objects must be global
// all global variables-----------------------------------------------------------------------------

GtkBuilder *builder;
GtkWidget *main_window;
GtkWidget *stack;
GtkWidget* gallery_menu_fixed;
GtkWidget *gallery_menu_background;

GtkWidget *main_icon_buttons[7]; // number of icons + 1
GtkWidget *main_time_label;

GtkWidget *homepage_fixed;
GtkWidget *homepage_wallpaper;
GdkPixbuf *homepage_wallpaper_pixIn;
GdkPixbuf *homepage_wallpaper_pix;
GdkPixbuf *homepage_icon_button_pixIn;
GdkPixbuf *homepage_icon_button_pix;

//gallery variables-----------------------------------------------------------------------------------
GtkWidget *camera_images_fixed;
GtkWidget *camera_images_grid;
GtkWidget *camera_images_scrolled_window;
GtkWidget *camera_images_icon;
GtkWidget *no_of_camera_images_label;

GdkPixbuf *pixIn_gallery_menu_background;
GdkPixbuf *pix_gallery_menu_background;

GdkPixbuf *pixIn_camera_images_grid;
GdkPixbuf *pix_camera_images_grid;

GdkPixbuf *pixIn_camera_images_icon;
GdkPixbuf *pix_camera_images_icon;

char **images_list;

//music player variables-------------------------------------------------------------------------------
GtkWidget *music_menu_scrolled_window;
GtkWidget *music_menu_fixed; // assigning gallery menu fixed
GtkWidget *music_menu_grid;
GtkWidget *music_menu_add_new_folder_button;
GtkWidget *music_files_fixed;
GtkWidget *music_files_scrolled_window;

int music_menu_folders_number;
char **music_files_list;
char music_directory[128];
GtkWidget *music_player_play_pause_button;
int isPaused = 0;
Mix_Music* music;
char clicked_music_filepath[512];
GtkWidget *music_player_slider;
int music_is_playing;


//calculator variables---------------------------------------------------------


GtkWidget *calculator_normal_fixed;
GtkWidget *calculator_normal_entry;
GtkWidget *calculator_expression_label;
GtkWidget *calculator_scientific_fixed;
GtkWidget *calculator_scientific_entry;
GtkWidget *calculator_expression_label_2;


char *current_text;
char operator;
char op ='=';
char *num1;
char *num2;
int calculator_flag=0;
int calculator_flag1=0;
void increase_entry_text_size(GtkEntry *entry, int size);

void insert_text_handler(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer user_data);

void keyboard_entry_changed(GtkEntry *entry, gpointer user_data);
void keyboard_entry_changed_2(GtkEntry *entry, gpointer user_data);
void evaluate_changed_entry(GtkEntry *entry, GtkLabel *label);

double evaluate_entry(char *num1, char *num2, char operator);
void a_button_clicked(GtkButton *button, gpointer i);
void a_button_clicked_2(GtkButton *button, gpointer i);


//Alarm variables--------------------------------------------------------------

typedef void (*SwitchFunction)(GtkWidget*);
SwitchFunction switch_functions[3];
// All global variables for clock page 1
GtkWidget *window_clock;                            //window 1 for general timings
GtkWidget *clock_main_fixed_back;
GtkWidget *clock_menu_fixed;
GtkWidget **alarm_button_stored;                            // varible frame set on the window named frame1

GtkWidget *time_1_set_button;                    // widgets defined for specific tasks - time1 - constant in nature

GtkWidget *time_2_set_button;                  // value of conastant time 2

GtkWidget *time_3_set_button;                // value3 of const time

GtkWidget *custom_set_button;                // ustom button to flip the new window over older one for user to set time based on his wish

GtkWidget *alarm_switch1;                          // on /off for activate and deactivate the constant function s of time set1 ;

GtkWidget *alarm_switch2;                              // on /off for activate and deactivate the constant function s of time set2 ;

GtkWidget *alarm_switch3;                           // on /off for activate and deactivate the constant function s of time set3 ;

GtkWidget *clock_label;                         // header name of file - just  a noattion used by label feature

GtkWidget *alarm_Done_button ;


                          // declaring a builder for window and frames to work accordingly in terms of signaling and coordinating over each other

// All global variables for custom page





GtkWidget *clock_custom_fixed;

GtkWidget *clock_header;              // header just as a widget for representation ,

GtkWidget *final_button;             //  used to represent custom mode on for clock

GtkWidget *hour_spin;           // to control hour value

GtkWidget *minute_spin;         // to ccontrol minute 

GtkWidget *DAY;                // to select dauy to set for - an alarm 

GtkWidget *am_pm;             // am_ pm slection 
 
GtkWidget *vibration_button;           // use to have a beep sound notification 

GtkWidget *vibration_switch;        // to make vihbration feature on / off based on users wish

GtkWidget *hour_tag;            // label by using gk image feature 

GtkWidget *minute_label;    // label used for making minute feature 

GtkWidget *minute_tag;         

GtkWidget *hour_label;
GtkWidget *clock_stack ;
GtkWidget *alarm_sound_button;          // to make ringotnes be possible to play and set for an alarm 
GtkAdjustment *alarm_adjustment1;
GtkAdjustment *alarm_adjustment2;
GtkWidget *alarm_tag;

GtkWidget *alarm_sound_list;          // list of option for music 
char AM_set[3] = ("AM");              // varible for am 
 
int next_day ;
int flag_custom = 0 ;
int diff_day_code;
const gchar *am_pm_value ;
const gchar *DAY_value ;
int hour_value ;
int minute_value ;
int currentHour ;
int currentMinute ;


// global variable for alarm music 
Mix_Music* alarm_music;
Mix_Chunk* song1 = NULL;
Mix_Chunk* song2 = NULL;


// calendar variables
GtkWidget *calendar_fixed;
GtkWidget *icon_buttons[43]; // number of icons + 1
GtkComboBox *monthName;
GtkSpinButton *yearName;
GtkWidget *currentDate;
GtkWidget *dateContents;    
GtkWidget *editButton;

int year, monthNum, NumDays, PrevDays, dayIndex, check=0;

char calendar_note_filename[100];


// function prototypes--------------------------------------------------------------------------------
gboolean update_main_time_label(gpointer user_data);
void homepage_assets_generate();
void show_homepage();
void main_widgets_generate();

//Gallery functions--------------------------------------------------------------------------------------
void gallery_assets_generate();
void generate_gallery_menu_fixed();
void generate_camera_images_fixed();
void a_camera_image_clicked(GtkWidget *button, gpointer i);


//Music Player functions-------------------------------------------------------------------------------
void music_player_assets_generate();
void music_menu_add_new_folder_button_clicked();
void music_menu_folder_button_clicked();
void generate_music_files_fixed();


//Calculator functions---------------------------------------------------------

void calculator_assets_generate();
void displayContent();
void editContent(GtkButton *button);
void set_label_current_date(GtkWidget *label);
void set_button_color(GtkWidget *button);
int dayOfWeek(int day, int month, int year);
int monthToNumber(char* month);
bool isNumber(const char* str);
int get_date(int year,int monthNum);
void set_dropdown_value_by_index(GtkComboBox *combo_box, gint index);
void set_spinner_value(GtkSpinButton *spinner, gdouble value);
void setButtonDate(GtkWidget *button, int date);
int numberOfDays(int x, int y);
void getData();
void setCalendar();
void functionSet(GtkButton *button);
void getMonth(GtkComboBox *widget);
void getYear(GtkSpinButton *spinner);

//Alarm functions--------------------------------------------------------------

int alarm_assets_generate();
int convertTo24Hour(int hour, const char* am_pm);
// used to ensure calculation with 24 hours flipping to 12 in terms of am _pm
int timeDifferenceInSeconds(int wakeHour, int wakeMinute, const char* am_pm, int diff_day_code);
// final state - initial state
void current_time();
// to detect current time for diff calcultaion
int dayToCaseNo(const char *day);
// picking the wish of user set by , and feeding numbers for days sleection in the code
void setAlarm(int seconds, int wakeHour, int wakeMinute, const char *am_pm);
// to make a confirmation call for the alsrm to be set successfully
void on_alarm_switch1_state_set(GtkWidget *b);
//on/off for 6.00 am
void on_alarm_switch2_state_set(GtkWidget *b);
// on/ off for 6:45 am
void on_alarm_switch3_state_set(GtkWidget *b);
// on /off for 7:15 am
void on_custom_toggled();
// call command for custom mode to be on
int on_hour_spin_button();
// to set hours value for spin approach
int on_minute_spin_button();
// same for minutes even 
void on_combo_box_changed(GtkComboBox *combo_box, gpointer user_data);
// to pick text data from the option the user chose by clciking on it 
void on_clock_toggled();
// to call clock app form the main menu 
void on_Done_clicked(GtkButton *b);
// to set all changes finally to call for alarm set
// void on_final_button_clicked(GtkButton *button, gpointer user_data) ;
void on_alarm_Done_button_clicked(GtkButton *button, gpointer user_data);
gboolean process_switch_states(gpointer user_data);
// to process the switches current condition to be fedded in code
void set_spin_button_values(int *hour, int *minute);
gboolean on_window_custom_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data);
gboolean alarm_callback(gpointer data);
typedef void (*SwitchFunction)(GtkWidget*);
void on_time_set_button_clicked(GtkWidget *button_set, gpointer button_num);
void *load_and_play_music(void *selected_sound_ptr) ;
gboolean timer_callback(gpointer data)  ;
void on_alarm_end() ;


// calendar functions----------------------------------------------------------

void calendar_assets_generate();
void write_to_file(char text[200]);




    //compiling command
        //gcc b23ph1028_b23cs1048_b23ch1020_b23me1065_main.c -o app $(pkg-config --cflags --libs gtk+-3.0) $(pkg-config --cflags --libs SDL2_mixer) -Wl,--export-all-symbols -lavformat -lavcodec -lavutil -lswresample
int SDL_main(int argc, char *argv[])
{
    //GtkApplication *app;  // this is gtk4 specific

    //app = gtk_application_new("my.first.app", G_APPLICATION_DEFAULT_FLAGS);


    gtk_init(NULL, NULL);   //GtkApplication works in gtk4
    //GError *error = NULL;
    //builder = gtk_builder_new();
    builder = gtk_builder_new_from_file("assets/glade.glade"); // initialising builder object
    if(!builder)
    {
        g_printerr("Failed to load builder object. \n");
        return 1;
    }
        //initialising stack
    stack = gtk_stack_new();
    //g_error_free(error);

    // homepage code here------------------------------------------------------

    homepage_assets_generate();

    // gallery code here-------------------------------------------------------

    gallery_assets_generate();


    // Music player code here--------------------------------------------------

    music_player_assets_generate();


    // calculator code here----------------------------------------------------

    calculator_assets_generate();


    // Alarm code here---------------------------------------------------------


    alarm_assets_generate();


    // Calendar code here------------------------------------------------------


    calendar_assets_generate();



    // main_window and top level code here-------------------------------------
    main_widgets_generate();

    show_homepage();

    gtk_builder_connect_signals(builder, NULL);
    gtk_widget_show_all(main_window);

    gtk_main();


    // clearing and closing the application------------------------------------

    // Stop the music playback
    Mix_HaltMusic();
    // Free the music resource
    Mix_FreeMusic(music);
    // Close the audio system
    Mix_CloseAudio();
    // Quit the SDL subsystems
    SDL_Quit();
    // application has run without any errors
    return EXIT_SUCCESS;


}




//Gallery functions----------------------------------------------------------------------------------

void gallery_assets_generate()
{


    images_list = (char **)malloc(1024*sizeof(char *));
    // Gallery GtkFixed's definition
    gallery_menu_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "gallery_menu_fixed")); // assigning gallery menu fixed
    camera_images_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "camera_images_fixed"));
    camera_images_grid = GTK_WIDGET(gtk_builder_get_object(builder, "camera_images_grid"));

    //setting camera images scrolled menu
    camera_images_scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "camera_images_scrolled_window"));

    /* Setting gallery menu fixed stacks-------------------------------------------------------------------------------------*/
    gtk_container_add(GTK_CONTAINER(camera_images_scrolled_window), GTK_WIDGET(camera_images_fixed));//adding camera images fixed to scroll window

    // adding both pages to the GtkStack
    gtk_stack_add_named(GTK_STACK(stack), gallery_menu_fixed, "gallery_menu_fixed");
    gtk_stack_add_named(GTK_STACK(stack), camera_images_scrolled_window, "camera_images_scrolled_window");

    // Add widgets to GtkStack

    generate_camera_images_fixed();



}
void generate_gallery_menu_fixed()
{


    gallery_menu_background = gtk_image_new();
    gallery_menu_background = GTK_WIDGET(gtk_builder_get_object(builder, "gallery_menu_background"));
    pixIn_gallery_menu_background = gdk_pixbuf_new_from_file("assets/gallery_menu_background.jpg", NULL);    // unscaled pixbuf
    pix_gallery_menu_background = gdk_pixbuf_scale_simple(pixIn_gallery_menu_background, 1000, 800, GDK_INTERP_NEAREST); // scaled pixbuf
    gtk_image_set_from_pixbuf(GTK_IMAGE(gallery_menu_background), pix_gallery_menu_background);

    camera_images_icon = gtk_image_new();// assigning camera_images_icon
    camera_images_icon = GTK_WIDGET(gtk_builder_get_object(builder, "camera_icon"));
    pixIn_camera_images_icon = gdk_pixbuf_new_from_file("assets/camera_icon.jpg", NULL);    // unscaled pixbuf
    pix_camera_images_icon = gdk_pixbuf_scale_simple(pixIn_camera_images_icon, 200, 250, GDK_INTERP_NEAREST); // scaled pixbuf
    gtk_image_set_from_pixbuf(GTK_IMAGE(camera_images_icon), pix_camera_images_icon);
}

void generate_camera_images_fixed()
{



    char *user_profile = getenv("USERPROFILE"); // gets the system variables %USERPROFILE% (only in windows)
    char camera_directory[128];
    sprintf(camera_directory, "%s\\Pictures\\Camera Roll", user_profile);

    mkdir(camera_directory); // 0 if it makes a folder, -1 if already exist

    struct dirent *dir;
    DIR *d = opendir(camera_directory);

    int fileCount = -2; // . and .. also count as folders

    /* loop to iterate through camera roll directory images using dir pointer and storing the image file name using dirent struct
       and storing the name in a array of string pointers named images_list.
       Then creating a gtk button , adding the image to the thebutton , adding a signal to the button then adding the button to the grid*/
    while((dir = readdir(d)) != NULL)
    {
        if(fileCount >= 0)
        {
            char *imagefilepath = (char *)malloc(500*(sizeof(char)));
            char *button_name = (char *)malloc(500*sizeof(char));

            //condition to filter out image files
            if (g_str_has_suffix(dir->d_name, ".jpg") || g_str_has_suffix(dir->d_name, ".png") || g_str_has_suffix(dir->d_name, ".jpeg"))
            {
                sprintf(imagefilepath, "%s\\%s", camera_directory, dir->d_name); //adding image paths to imagefilepath string
                images_list[fileCount] = imagefilepath;//adding image path to array of names

                GtkWidget *button = gtk_button_new();// creating new gtk button

                g_signal_connect(button, "clicked", G_CALLBACK(a_camera_image_clicked), GINT_TO_POINTER(fileCount));// adding signal to button

                GtkWidget *image = gtk_image_new();// creating new gtk image
                pixIn_camera_images_grid = gdk_pixbuf_new_from_file(imagefilepath, NULL);    // adding image to the gtk image having the imagefilepath as path
                pix_camera_images_grid = gdk_pixbuf_scale_simple(pixIn_camera_images_grid, 175, 175, GDK_INTERP_NEAREST); // scaled pixbuf
                gtk_image_set_from_pixbuf(GTK_IMAGE(image), pix_camera_images_grid);

                gtk_button_set_image(GTK_BUTTON(button), image);

                // gtk_widget_add_css_class(button, "icon_button");
                //GtkCssProvider *css_provider = gtk_css_provider_new();
                //gtk_css_provider_load_from_data(css_provider, ".icon_button { background: none; box-shadow: none; border: none;}", -1, NULL);
                //GtkStyleContext *context = gtk_widget_get_style_context(button);
                //gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider),
                //GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

                // Attach image to the grid
                gtk_grid_attach(GTK_GRID(camera_images_grid), button, (fileCount)%5, (fileCount)/5, 1, 1);


                fileCount++;

            }
            else
            {
            sprintf(imagefilepath, "%s\\%s", camera_directory, dir->d_name);
            printf("NON-IMAGE FILE %s \n", imagefilepath);
            }

        }
        else
        {
            fileCount++;
        }
    }

    closedir(d);

    no_of_camera_images_label =GTK_WIDGET(gtk_builder_get_object(builder, "no_of_camera_images_label"));
    char no_of_images[20];
    if(fileCount ==1)
    {
        sprintf(no_of_images, "%d image", fileCount);
    }
    else
    {
        sprintf(no_of_images, "%d images", fileCount);
    }
    gtk_label_set_text(GTK_LABEL(no_of_camera_images_label), no_of_images);
    int n = (fileCount/5)+1;

    //setting no of rows of the grid
    gtk_grid_set_row_homogeneous(GTK_GRID(camera_images_grid), n);

}




void on_camera_images_button_clicked(GtkWidget *icon1)
{
    generate_camera_images_fixed();

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "camera_images_scrolled_window");
}

void on_camera_images_back_button_clicked(GtkWidget *icon1)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "gallery_menu_fixed");
}

void on_camera_images_home_button_clicked(GtkWidget *icon1)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");
}

void on_gallery_menu_back_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");
}

void on_gallery_menu_home_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");

}

void a_camera_image_clicked(GtkWidget * button, gpointer data)
{
    int i = GPOINTER_TO_INT(data);
    GtkWidget *image_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(image_window), images_list[i]);

    GdkPixbuf *pixIn_image = gdk_pixbuf_new_from_file(images_list[i], NULL);    // unscaled pixbuf

    int src_width = gdk_pixbuf_get_width(pixIn_image);
    int src_height = gdk_pixbuf_get_height(pixIn_image);

    int x = (800 * src_width)/src_height;

    GtkWidget *image = gtk_image_new_from_file(images_list[i]);
    GdkPixbuf *pix_image = gdk_pixbuf_scale_simple(pixIn_image, x, 800, GDK_INTERP_NEAREST); // scaled pixbuf

    gtk_image_set_from_pixbuf(GTK_IMAGE(image), pix_image);

    gtk_container_add(GTK_CONTAINER(image_window), image);

    // g_signal_connect(image_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
        //connects destroy signal (close button) to gtk_main_quit
    gtk_widget_show_all(image_window);
}


// music player functions------------------------------------------------------------------------

void music_player_assets_generate()
{

    // getting ScrolledWindow and fixed from builder
    music_menu_scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "music_menu_scrolled_window"));
    music_menu_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "music_menu_fixed")); // assigning gallery menu fixed
    gtk_container_add(GTK_CONTAINER(music_menu_scrolled_window), GTK_WIDGET(music_menu_fixed));//adding camera images fixed to scroll window
    music_menu_grid = GTK_WIDGET(gtk_builder_get_object(builder, "music_menu_grid")); // assigning gallery menu fixed


    gtk_stack_add_named(GTK_STACK(stack), music_menu_scrolled_window, "music_menu_scrolled_window");


    music_files_scrolled_window = GTK_WIDGET(gtk_builder_get_object(builder, "music_files_scrolled_window"));
    music_files_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "music_files_fixed"));
    gtk_container_add(GTK_CONTAINER(music_files_scrolled_window), GTK_WIDGET(music_files_fixed));//adding camera images fixed to scroll window

    gtk_stack_add_named(GTK_STACK(stack), music_files_scrolled_window, "music_files_scrolled_window");


    music_menu_folders_number = 1;
    generate_music_files_fixed();




    //music_menu_add_new_folder_button = gtk_button_new();
    //GtkWidget *music_menu_plus_image = gtk_image_new_from_icon_name("list-add", GTK_ICON_SIZE_BUTTON);
    //gtk_grid_attach(GTK_GRID(music_menu_grid), music_menu_add_new_folder_button, 1, 0, 1, 1);

    //g_signal_connect(music_menu_add_new_folder_button, "clicked", G_CALLBACK(music_menu_add_new_folder_button_clicked), NULL);



}

gboolean slider_grabbed = FALSE;


// Function to toggle play/pause state
void play_pause_clicked(GtkButton *music_player_play_pause_button, gpointer data)
{
    if (isPaused)
    {
        Mix_ResumeMusic();
        isPaused = 0;
        gtk_button_set_label(music_player_play_pause_button, "Pause");
    } else {
        Mix_PauseMusic();
        isPaused = 1;
        gtk_button_set_label(music_player_play_pause_button, "Play");
    }
}
void onDestroy(GtkWidget *widget, gpointer data)
{
    music_is_playing = 0;
    gtk_widget_destroy(music_player_slider);
    // Stop the music playback
    Mix_HaltMusic();

    //// Free the music resource
    //Mix_FreeMusic(music);

    //// Close the audio system
    //Mix_CloseAudio();

    //// Quit the SDL subsystems
    //SDL_Quit();


    //// Quit the GTK main loop
    //gtk_main_quit();
}

void *audio_parallel_thread(void *arg)
{

    music_is_playing = 1;

    // Initialize SDL with audio support
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return NULL;
    }

    // Initialize SDL_mixer with clearer error handling
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 256) < 0)
    {
        printf("SDL_mixer initialization failed: %s\n", Mix_GetError());
        SDL_Quit();
        return NULL;
    }

    // Load the MP3 file with a valid path
    Mix_Music* music = Mix_LoadMUS(clicked_music_filepath);
    if (!music)
    {
        printf("Failed to load MP3: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }

    // Play the music, handling potential errors
    if (Mix_PlayMusic(music, -1) < 0)
    {
        printf("Failed to play music: %s\n", Mix_GetError());
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
        return NULL;
    }

    // Wait for the music to finish or be paused/stopped
    while (Mix_PlayingMusic())
    {
        SDL_Delay(100);
    }

    music_is_playing = 0;
    return NULL;



}
// Audio callback function
void audioCallback(void *userdata, Uint8 *stream, int len)
{
    SDL_memset(stream, 0, len); // Clear the audio buffer
}

gboolean update_music_progress_slider(void *data)
{
    //if(music_is_playing && !slider_grabbed){
    if(music_is_playing)
    {
        // Get the current position of the music playback in milliseconds
        double current_position = Mix_GetMusicPosition(music);

        // Get the total duration of the music in milliseconds
        double total_duration = Mix_MusicDuration(music);

        // Calculate the position percentage
        double position_percentage = (double)current_position / (double)total_duration;

        printf("player at %lf%% \n", position_percentage);
        fflush(stdout);
        // Set the slider position based on the percentage
        gtk_range_set_value(GTK_RANGE(music_player_slider), position_percentage);
        return G_SOURCE_CONTINUE;   // allows g_timeout to keep it in a loop
    }
    //printf("hey?");
    else{
        G_SOURCE_REMOVE;    // the window is closed, stop the loop
    }

    //SDL_PauseAudioDevice(audioDevice, 0); // Resume audio playback
}

// Function to handle slider value changes
void on_slider_changed(GtkWidget* widget, gpointer data)
{
    //if (music_is_playing && slider_grabbed) {
    if (music_is_playing)
    {

        // Get the value of the slider
        double slider_value = gtk_range_get_value(GTK_RANGE(widget));

        // Get the total duration of the music in milliseconds
        double total_duration = Mix_MusicDuration(music);

        double old_position = Mix_GetMusicPosition(music);
        // Calculate the new position in milliseconds
        double new_position = (double)(slider_value * total_duration);
        Mix_SetMusicPosition(new_position);
    }
}

void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data)
{
    GtkTreeModel *model = gtk_tree_view_get_model(tree_view);
    GtkTreeIter iter;
    //char music_directory[128];


    // Get the iter associated with the clicked row
    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        // Now you can extract data from the model using the iter
        // For example, you can get the text of the first column
        gchar *filename;
        gtk_tree_model_get(model, &iter, 0, &filename, -1);
        //char clicked_music_filepath[512];
        sprintf(clicked_music_filepath, "%s\\%s", music_directory, filename);

        g_print("clicked on file %s\n", clicked_music_filepath);


    GtkWidget *music_player_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "no_of_music_files_label"));

    // Create a vertical box to hold the buttons
    GtkWidget *playbar_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    //GtkWidget *music_player_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *music_player_window = GTK_WIDGET(gtk_builder_get_object(builder, "music_player_window"));
    gtk_window_set_title(GTK_WINDOW(music_player_window), filename);

    g_signal_connect(music_player_window, "destroy", G_CALLBACK(onDestroy), NULL);


    // Create the slider
    music_player_slider = GTK_WIDGET(gtk_builder_get_object(builder, "music_player_slider"));

    gtk_widget_set_hexpand(music_player_slider, TRUE);

    // Create the play/pause button
    //music_player_play_pause_button = gtk_button_new_with_label("Pause");
    music_player_play_pause_button = GTK_WIDGET(gtk_builder_get_object(builder, "music_player_play_pause_button"));
    gtk_widget_show_all(music_player_window);


    // SDL2_mixer Code for playing music------------------

    // Start audio playback in a separate thread
    pthread_t audio_thread_id;
    pthread_create(&audio_thread_id, NULL, audio_parallel_thread, NULL);


    // Start the timeout function to update the slider
    g_timeout_add(500, update_music_progress_slider, NULL);

    };
}

char duration_full[64];
void get_music_file_duration(char *music_file_path)
{

    avformat_network_init();

    AVFormatContext *format_ctx = NULL;
    if (avformat_open_input(&format_ctx, music_file_path, NULL, NULL) != 0)
    {
        printf("Error: Couldn't open input file\n");
        return ;
    }

    if (avformat_find_stream_info(format_ctx, NULL) < 0)
    {
        printf("Error: Couldn't find stream information\n");
        avformat_close_input(&format_ctx);
        return ;
    }

    int duration_secs = format_ctx->duration / AV_TIME_BASE;
    int duration_hrs = duration_secs / 3600;
    int duration_min = (duration_secs % 3600) / 60;
    int duration_sec = duration_secs % 60;

    //char duration_full[64];
    sprintf(duration_full, "%02d:%02d:%02d\n", duration_hrs, duration_min, duration_sec);

    avformat_close_input(&format_ctx);

    //printf("THE DURATION OF %s IS %s", music_file_path, duration_full);
    fflush(stdout);
    //return duration_full;



}

void generate_music_files_fixed()
{


    char *user_profile = getenv("USERPROFILE"); // gets the system variables %USERPROFILE% (only in windows)
    //char music_directory[128];
    sprintf(music_directory, "%s\\Music", user_profile);

    mkdir(music_directory); // 0 if it makes a folder, -1 if already exist

    struct dirent *dir;
    DIR *d = opendir(music_directory);

    music_files_list = (char**) malloc(1024 * sizeof(char*));
    int musicfileCount = -2; // . and .. also count as folders
    GtkListStore *list_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

    /* loop to iterate through camera roll directory images using dir pointer and storing the image file name using dirent struct
       and storing the name in a array of string pointers named music_files_list.
       Then creating a gtk button , adding the image to the thebutton , adding a signal to the button then adding the button to the grid*/
    while((dir = readdir(d)) != NULL)
    {
        if(musicfileCount >= 0)
        {
            char *musicfilepath = (char *)malloc(500*(sizeof(char)));
            char *button_name = (char *)malloc(500*sizeof(char));

            //condition to filter out image files
            if (g_str_has_suffix(dir->d_name, ".mp3"))
            {
                sprintf(musicfilepath, "%s\\%s", music_directory, dir->d_name); //adding music filepaths to musicfilepath string
                music_files_list[musicfileCount] = musicfilepath;//adding music filepath to array of names


                // Attach image to the grid
                //gtk_grid_attach(GTK_GRID(camera_images_grid), button, (musicfileCount)%5, (musicfileCount)/5, 1, 1);
                GtkWidget *list_view = gtk_tree_view_new();
                gtk_tree_view_set_model(GTK_TREE_VIEW(list_view), GTK_TREE_MODEL(list_store));

                // Add columns to the list view
                GtkCellRenderer *renderer1 = gtk_cell_renderer_text_new();
                GtkCellRenderer *renderer2 = gtk_cell_renderer_text_new();
                GtkTreeViewColumn *column1 = gtk_tree_view_column_new_with_attributes("Music Files", renderer1, "text", 0, NULL);
                GtkTreeViewColumn *column2 = gtk_tree_view_column_new_with_attributes("Duration", renderer2, "text", 1, NULL);

                gtk_tree_view_column_set_fixed_width(column1, 820);


                gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), column1);
                gtk_tree_view_append_column(GTK_TREE_VIEW(list_view), column2);

                // Connect signal for row activation
                g_signal_connect(list_view, "row-activated", G_CALLBACK(on_row_activated), NULL);

                // Add music files to the list store
                // this modifies duration_full
                get_music_file_duration(musicfilepath);


                GtkTreeIter iter;
                gtk_list_store_append(list_store, &iter);
                gtk_list_store_set(list_store, &iter, 0, dir->d_name, 1, duration_full, -1);

                // Add list view to window and show all widgets
                gtk_fixed_put(GTK_FIXED(music_files_fixed), list_view, 50, 100);

                musicfileCount++;

            }
            else
            {
            sprintf(musicfilepath, "%s\\%s", music_directory, dir->d_name);
            printf("NON-MUSIC FILE %s \n", musicfilepath);
            }

        }
        else
        {
            musicfileCount++;
        }
    }

    closedir(d);

    no_of_camera_images_label =GTK_WIDGET(gtk_builder_get_object(builder, "no_of_music_files_label"));
    char no_of_images[20];
    if(musicfileCount ==1)
    {
        sprintf(no_of_images, "%d music file", musicfileCount);
    }
    else
    {
        sprintf(no_of_images, "%d music files", musicfileCount);
    }
    gtk_label_set_text(GTK_LABEL(no_of_camera_images_label), no_of_images);
    int n = (musicfileCount/5)+1;





}

void on_music_menu_button1_clicked(GtkWidget *music_menu_button1)
{
    generate_music_files_fixed();


    gtk_stack_set_visible_child_name(GTK_STACK(stack), "music_files_scrolled_window");
}

void music_menu_folder_button_clicked(GtkWidget *music_menu_folder_button, gpointer data)
{
    printf("THE BUTTON PRESSED IS FOR %s", data);
    ;
}

void on_music_menu_back_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");

}
void on_music_menu_home_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");

}

void on_music_files_back_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "music_menu_scrolled_window");

}

void on_music_files_home_button_clicked()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");

}


// calculator functions--------------------------------------------------------


gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    // Ignore arrow key events to prevent cursor movement
    if (event->keyval == GDK_KEY_Left || event->keyval == GDK_KEY_Right ||
        event->keyval == GDK_KEY_Up || event->keyval == GDK_KEY_Down) {
        return TRUE; // Stop further processing of the event
    }
    return FALSE; // Allow normal event processing
}
gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer user_data) {
    // Prevent entry from receiving focus when clicked
    gtk_widget_set_can_focus(widget, FALSE);
    return TRUE; // Stop further processing of the event
}


void calculator_assets_generate(){

    current_text= (char *)malloc(1024*sizeof(char));
    num1= (char *)malloc(1024*sizeof(char));
    num2= (char *)malloc(1024*sizeof(char));
    strcpy(num1,"");
    strcpy(num2, "");

    calculator_normal_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "calculator_normal_fixed"));
    calculator_normal_entry = GTK_WIDGET(gtk_builder_get_object(builder, "calculator_normal_entry"));
    calculator_expression_label =GTK_WIDGET(gtk_builder_get_object(builder, "calculator_expression_label"));

    calculator_scientific_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "calculator_scientific_fixed"));
    calculator_scientific_entry = GTK_WIDGET(gtk_builder_get_object(builder, "calculator_scientific_entry"));
    calculator_expression_label_2 =GTK_WIDGET(gtk_builder_get_object(builder, "calculator_expression_label_2"));


    for(int i=1; i<25;++i)
    {
        GtkWidget *button;
        char str[50];
        sprintf(str, "calculator_button_%d", i);
        button = GTK_WIDGET(gtk_builder_get_object(builder, str));

        g_signal_connect(button, "clicked", G_CALLBACK(a_button_clicked), GINT_TO_POINTER(i));// adding signal to button

    }
    for(int i=1; i<36;++i)
    {
        GtkWidget *button;
        char str[50];
        sprintf(str, "calculator2_button_%d", i);
        button = GTK_WIDGET(gtk_builder_get_object(builder, str));

        g_signal_connect(button, "clicked", G_CALLBACK(a_button_clicked_2), GINT_TO_POINTER(i));// adding signal to button

    }



    // Connect to the "button-press-event" signal to prevent the cursor from moving
    g_signal_connect(G_OBJECT(calculator_normal_entry), "key-press-event", G_CALLBACK(on_key_press), FALSE);
    g_signal_connect(calculator_normal_entry, "button-press-event", G_CALLBACK(on_button_press), NULL);
    increase_entry_text_size(GTK_ENTRY(calculator_normal_entry), 50);

    g_signal_connect(G_OBJECT(calculator_scientific_entry), "key-press-event", G_CALLBACK(on_key_press), FALSE);
    g_signal_connect(calculator_scientific_entry, "button-press-event", G_CALLBACK(on_button_press), NULL);
    increase_entry_text_size(GTK_ENTRY(calculator_scientific_entry), 50);

 
    gtk_stack_add_named(GTK_STACK(stack), calculator_normal_fixed, "calculator_normal_fixed");
    gtk_stack_add_named(GTK_STACK(stack), calculator_scientific_fixed, "calculator_scientific_fixed");

    g_signal_connect(calculator_normal_entry, "insert-text", G_CALLBACK(insert_text_handler), NULL);
    g_signal_connect(calculator_normal_entry, "changed", G_CALLBACK(keyboard_entry_changed), NULL);

    g_signal_connect(calculator_scientific_entry, "insert-text", G_CALLBACK(insert_text_handler), NULL);
    g_signal_connect(calculator_scientific_entry, "changed", G_CALLBACK(keyboard_entry_changed_2), NULL);


}


void insert_text_handler(GtkEditable *editable, const gchar *text, gint length, gint *position, gpointer user_data) 
{
    printf("%s", text);
    // Check if the inserted text is a valid integer
    if (!isdigit(text[length-1]) && text[length-1] != '*' && text[length-1] != '/' && text[length-1] != '-' && text[length-1] != '+' && text[length-1] != '.' && text[length-1] != '=')
    {
        // If any character is not a digit, prevent its insertion
        g_signal_stop_emission_by_name(editable, "insert-text");
        return;
    }
}
void increase_entry_text_size(GtkEntry *entry, int size) {
    // Create a CSS style provider
    GtkCssProvider *provider = gtk_css_provider_new();

    // Construct CSS style
    gchar *css_style = g_strdup_printf("entry { font-size: %dpx; }", size);

    // Load the CSS style
    gtk_css_provider_load_from_data(provider, css_style, -1, NULL);

    // Apply the style to the entry
    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(entry));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    // Free resources
    g_free(css_style);
    g_object_unref(provider);
}

void a_button_clicked(GtkButton *button, gpointer i)
{
    int a = GPOINTER_TO_INT(i);
    // Get the current cursor position
    gint cursor_pos = gtk_editable_get_position(GTK_EDITABLE(calculator_normal_entry));
    const char *text = gtk_entry_get_text(GTK_ENTRY(calculator_normal_entry));
    char str[1024];
    gint temp_length = gtk_entry_get_text_length(GTK_ENTRY(calculator_normal_entry));   
    const gchar *tex = gtk_label_get_text(GTK_LABEL(calculator_expression_label));
    int len_label = strlen(tex);
    strcpy(str , text);      

    char c;
    switch (a)
    {
        case 1:
                printf("yes");
                double pi =3.14159265359;
                if(temp_length == 0)
                {
                    sprintf(num2, "%f", pi);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), num2);
                    gtk_editable_set_position(GTK_EDITABLE(calculator_normal_entry), cursor_pos + strlen(num2));

                }
                
                return; 
        case 18: 
                    double e =2.718281828459045;
                    if(temp_length == 0)
                    {
                        sprintf(num2, "%f", e);
                        gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), num2);
                        gtk_editable_set_position(GTK_EDITABLE(calculator_normal_entry), cursor_pos + strlen(num2));
                    }
                return;                
        case 17: 

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;
                }
                if(temp_length==0)
                {
                    double temp = strtod(num1, NULL);
                    if(temp <0)
                        temp = temp*(-1);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }
                else{

                    double temp = strtod(str, NULL);
                    if(temp <0)
                        temp = temp*(-1);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }           
        case 19:

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length==0)
                {
                    if(strtod(num1,NULL)<=0)
                    {
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                        calculator_flag =1;
                        return;
                    }
                    else
                    {
                        double temp = log(strtod(num1, NULL));
                        sprintf(num1, "%f", temp);
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                        gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                        return ;
                    }
                }
                else{
                    double temp = log(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }
        case 22: 

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length==0)
                {
                    if(strtod(num1,NULL)<=0)
                    {
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                        calculator_flag =1;
                        return;
                    }
                    else
                    {
                        double temp = sqrt(strtod(num1, NULL));
                        sprintf(num1, "%f", temp);
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                        gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                        return ;
                    }
                }
                else
                {
                    double temp = sqrt(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }
        case 21:

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = pow((strtod(num1, NULL)),2);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }
                else
                {
                    double temp = pow((strtod(str, NULL)),2);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                    return ;
                }
                
        case 2: c='0'; break;
        case 3: c='.'; break;
        case 4: c='='; break;
        case 5: c='1'; break;
        case 6: c='2'; break;
        case 7: c='3'; break;
        case 8: c='+'; break;
        case 9: c='4'; break;
        case 10: c='5'; break;
        case 11: c='6'; break;
        case 12: c='-'; break;
        case 13: c='7'; break;
        case 14: c='8'; break;
        case 15: c='9'; break;
        case 16: c='*'; break;
        case 20: c='/'; break;
        case 23:

                 gtk_label_set_text(GTK_LABEL(calculator_expression_label), "");
                 gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), "");
                 strcpy(num1,"");
                 strcpy(num2,"");
                 return;
        case 24: 

                if (temp_length > 0) {
                gtk_editable_delete_text(GTK_EDITABLE(calculator_normal_entry), temp_length - 1, temp_length);
                }
                return;

        default:break;
    }
    sprintf(str,"%s%c", str,c);
    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), str);
    gtk_editable_set_position(GTK_EDITABLE(calculator_normal_entry), cursor_pos + strlen(str));

    evaluate_changed_entry(GTK_ENTRY(calculator_normal_entry),GTK_LABEL(calculator_expression_label));
}
void a_button_clicked_2(GtkButton *button, gpointer i)
{
    int a = GPOINTER_TO_INT(i);
    // Get the current cursor position
    gint cursor_pos = gtk_editable_get_position(GTK_EDITABLE(calculator_scientific_entry));
    const char *text = gtk_entry_get_text(GTK_ENTRY(calculator_scientific_entry));
    char str[1024];
    gint temp_length = gtk_entry_get_text_length(GTK_ENTRY(calculator_scientific_entry));   
    const gchar *tex = gtk_label_get_text(GTK_LABEL(calculator_expression_label_2));
    int len_label = strlen(tex);
    strcpy(str , text);      

    char c;
    switch (a)
    {
        case 22:
                printf("yes");
                double pi =3.14159265359;
                if(temp_length == 0)
                {
                    sprintf(num2, "%f", pi);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), num2);
                    gtk_editable_set_position(GTK_EDITABLE(calculator_scientific_entry), cursor_pos + strlen(num2));

                }
                
                return; 
        case 23: 
                    double e =2.718281828459045;
                    if(temp_length == 0)
                    {
                        sprintf(num2, "%f", e);
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), num2);
                        gtk_editable_set_position(GTK_EDITABLE(calculator_scientific_entry), cursor_pos + strlen(num2));
                    }
                return;                
        case 2: 

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;
                }
                if(temp_length==0)
                {
                    double temp = strtod(num1, NULL);
                    if(temp <0)
                        temp = temp*(-1);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else{

                    double temp = strtod(str, NULL);
                    if(temp <0)
                        temp = temp*(-1);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }           
        case 24:

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length==0)
                {
                    if(strtod(num1,NULL)<=0)
                    {
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        calculator_flag =1;
                        return;
                    }
                    else
                    {
                        double temp = log(strtod(num1, NULL));
                        sprintf(num1, "%f", temp);
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        return ;
                    }
                }
                else{
                    double temp = log(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
        case 28: 

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length==0)
                {
                    if(strtod(num1,NULL)<=0)
                    {
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        calculator_flag =1;
                        return;
                    }
                    else
                    {
                        double temp = sqrt(strtod(num1, NULL));
                        sprintf(num1, "%f", temp);
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        return ;
                    }
                }
                else
                {
                    double temp = sqrt(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
        case 27:

                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = pow((strtod(num1, NULL)),2);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = pow((strtod(str, NULL)),2);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
        case 29: 
        
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length==0)
                {
                    if(strtod(num1,NULL)<=0)
                    {
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        calculator_flag =1;
                        return;
                    }
                    else
                    {
                        double temp = log(strtod(num1, NULL))/log(10);
                        sprintf(num1, "%f", temp);
                        gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                        gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                        return ;
                    }
                }
                else{
                    double temp = log(strtod(str, NULL))/log(10);
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 30:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(strtod(num1,NULL)==0)
                {
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), "Invalid Input");
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    calculator_flag =1;
                    return;
                }
                else
                {
                    double temp = 1/(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 32:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = pow(2.718281828459045,strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = pow(2.718281828459045,strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 33:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = pow(2,strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = pow(2,(strtod(str, NULL)));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 1:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = 1/sin(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = 1/sin(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 6:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = 1/tan(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = 1/tan(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 11:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = 1/cos(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = 1/cos(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 16:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = tan(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = tan(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 21:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = cos(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = cos(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
            case 26:
                if(len_label ==0)
                {
                    strcpy(num1, str);
                    calculator_flag1 =1;

                }

                if(temp_length ==0)
                {
                    double temp = sin(strtod(num1, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }
                else
                {
                    double temp = sin(strtod(str, NULL));
                    sprintf(num1, "%f", temp);
                    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), num1);
                    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                    return ;
                }

        case 3: c='0'; break;
        case 4: c='.'; break;
        case 5: c='='; break;
        case 7: c='1'; break;
        case 8: c='2'; break;
        case 9: c='3'; break;
        case 10: c='+'; break;
        case 12: c='4'; break;
        case 13: c='5'; break;
        case 14: c='6'; break;
        case 15: c='-'; break;
        case 17: c='7'; break;
        case 18: c='8'; break;
        case 19: c='9'; break;
        case 20: c='*'; break;
        case 25: c='/'; break;
        case 34:

                 gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), "");
                 gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), "");
                 strcpy(num1,"");
                 strcpy(num2,"");
                 return;
        case 35: 

                if (temp_length > 0) {
                gtk_editable_delete_text(GTK_EDITABLE(calculator_scientific_entry), temp_length - 1, temp_length);
                }
                return;

        default:break;
    }
    sprintf(str,"%s%c", str,c);
    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), str);
    gtk_editable_set_position(GTK_EDITABLE(calculator_scientific_entry), cursor_pos + strlen(str));

    evaluate_changed_entry(GTK_ENTRY(calculator_scientific_entry),GTK_LABEL(calculator_expression_label_2));
}


void keyboard_entry_changed(GtkEntry *entry, gpointer user_data)
{
    evaluate_changed_entry(entry,GTK_LABEL(calculator_expression_label));
}

double evaluate_entry(char *num1, char *num2, char operator)
{
    double number1 =0, number2 =0;
    number1 = strtod(num1, NULL);
    number2 = strtod(num2, NULL);

    switch (operator)
    {
        case '+': return number1 + number2;
        case '/': return number1 / number2;
        case '*': return number1 * number2;
        case '-': return number1- number2;
        default:break; 
    }
}
void on_home_button_clicked()
{
;
}

void evaluate_changed_entry(GtkEntry *entry,GtkLabel *label)
{
    if(calculator_flag ==1)
    {
        gtk_label_set_text(GTK_LABEL(label), "");
        strcpy(num1,"");
        strcpy(num2,"");
        calculator_flag =0;
    }
    gint length = gtk_entry_get_text_length(GTK_ENTRY(entry));   
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    strcpy(current_text , text);
    double answer;
    char str[1024];

 
    const gchar *text_label = gtk_label_get_text(GTK_LABEL(label));
    int length_label = strlen(text_label);    
    int a=0, b =0;
    if(current_text[length-1] == '=' || current_text[length-1] == '/' || current_text[length-1] == '*' || current_text[length-1] == '-' || current_text[length-1] == '+')
    {
        operator = current_text[length-1];
        if(length_label == 0|| calculator_flag1 ==1)
        {
            calculator_flag1 =0;
            current_text[length-1]=' ';
            char temp[1024] ;
            strcpy(num1, current_text);

            op =operator;
            sprintf(str, "%s%c", current_text, operator);
            gtk_label_set_text(GTK_LABEL(label), str);
            gtk_entry_set_text(GTK_ENTRY(entry), "");
  
        }        
        else if(operator =='=')
        {
            if(current_text[0]=='=')
            {
                current_text[0]= ' ';
                gtk_entry_set_text(GTK_ENTRY(entry), "");

            }
            else if(op =='=')
            {
                current_text[length-1]=' ';
                strcpy(num1,current_text);
                gtk_label_set_text(GTK_LABEL(label), current_text);
                gtk_entry_set_text(GTK_ENTRY(entry), "");
            }
            else
            {
                current_text[length-1]=' ';

                strcpy(num2, current_text);
                if(op =='/' && strtod(num2,NULL) ==0)
                {
                    gtk_label_set_text(GTK_LABEL(label), "Invalid Input");
                    gtk_entry_set_text(GTK_ENTRY(entry), "");
                    calculator_flag =1;
                   
                }
                else
                {
                    answer =evaluate_entry(num1, num2, op);
                    sprintf(str, "%s %c %s = %f", num1, op, num2, answer);
                    gtk_label_set_text(GTK_LABEL(label), str);
                    sprintf(num1, "%f", answer);
                    gtk_entry_set_text(GTK_ENTRY(entry), "");
                    op =operator;
                }
            }

        }
        else
        {
            if(current_text[0] == operator)
            {

                if(op =='=')
                {
                    op =operator;
                    sprintf(str, "%s %c", num1, op);
                    gtk_label_set_text(GTK_LABEL(label), str);
                    gtk_entry_set_text(GTK_ENTRY(entry), "");

                }
                else if(op == '+')
                {
                    sprintf(str, "%s %c",num1, operator);
                    gtk_label_set_text(GTK_LABEL(label), str);
                    gtk_entry_set_text(GTK_ENTRY(entry), "");
                    op =operator;

                }
                else if(op == '-')
                {
                    if(operator == '+')
                    {
                        current_text[0]= ' ';
                        gtk_entry_set_text(GTK_ENTRY(entry), "");

                    }
                    else
                    {
                        sprintf(str, "%s %c",num1, operator);
                        gtk_label_set_text(GTK_LABEL(label), str);
                        gtk_entry_set_text(GTK_ENTRY(entry), "");
                        op =operator;
                    }
                }
                else if(op =='/' || op =='*')
                {
                    if(operator == '-')
                        ;
                    else
                    {
                        sprintf(str, "%s %c",num1, operator);
                        gtk_label_set_text(GTK_LABEL(label), str);
                        gtk_entry_set_text(GTK_ENTRY(entry), "");
                        op =operator;
                    }

                }
            }
            else
            {
                if(op =='=')
                {
                    current_text[length-1] =' ';
                    strcpy(num1, current_text);
                    op=operator;
                    sprintf(str, "%s %c",num1, operator);
                    gtk_label_set_text(GTK_LABEL(label), str);
                    gtk_entry_set_text(GTK_ENTRY(entry), "");
                }
                else
                {
                    current_text[length-1]=' ';
                    // if(calculator_flag1 ==1)
                    // {
                    //     strcpy(num1, current_text);
                    //     sprintf(str,"%s %c", num1, operator);
                    //     gtk_label_set_text(GTK_LABEL(calculator_expression_label), str);
                    //     op =operator;
                    //     calculator_flag =0;
                    //     return;
                    // }
                    // else
                        strcpy(num2, current_text);
                    printf("%s %s", num1, num2);
                    if(op =='/' && strtod(num2,NULL) ==0)
                    {
                        gtk_label_set_text(GTK_LABEL(label), "Invalid Input");
                        gtk_entry_set_text(GTK_ENTRY(entry), "");
                        calculator_flag =1;
                    
                    }
                    else
                    {
                        answer =evaluate_entry(num1, num2, op);
                        op = operator;
                        sprintf(num1, "%f", answer);
                        sprintf(str, "%s%c", num1, operator);
                        gtk_label_set_text(GTK_LABEL(label), str);
                        gtk_entry_set_text(GTK_ENTRY(entry), "");
                    }
                }
            }

        } 
    }

}

void on_normal_mode_clicked()
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(calculator_normal_entry));
    char temp_text[1024];
    strcpy(temp_text , text);
    gtk_entry_set_text(GTK_ENTRY(calculator_scientific_entry), temp_text);
    gint cursor_pos = gtk_editable_get_position(GTK_EDITABLE(calculator_normal_entry));
    gtk_editable_set_position(GTK_EDITABLE(calculator_scientific_entry), cursor_pos + strlen(temp_text));

    const gchar *text1 = gtk_label_get_text(GTK_LABEL(calculator_expression_label));
    gtk_label_set_text(GTK_LABEL(calculator_expression_label_2), text1);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "calculator_scientific_fixed");

}
void keyboard_entry_changed_2(GtkEntry *entry, gpointer user_data)
{

    evaluate_changed_entry(GTK_ENTRY(calculator_scientific_entry), GTK_LABEL(calculator_expression_label_2));
}
void on_scientific_mode_clicked()
{
    const char *text = gtk_entry_get_text(GTK_ENTRY(calculator_scientific_entry));
    char temp_text[1024];
    strcpy(temp_text , text);
    gtk_entry_set_text(GTK_ENTRY(calculator_normal_entry), temp_text);
    gint cursor_pos = gtk_editable_get_position(GTK_EDITABLE(calculator_normal_entry));
    gtk_editable_set_position(GTK_EDITABLE(calculator_normal_entry), cursor_pos + strlen(temp_text));

    const gchar *text1 = gtk_label_get_text(GTK_LABEL(calculator_expression_label_2));
    gtk_label_set_text(GTK_LABEL(calculator_expression_label), text1);
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "calculator_normal_fixed");


}


void on_calculator_home_button_clicked(){

    gtk_stack_set_visible_child_name(GTK_STACK(stack),"homepage_fixed");

}


// alarm functions-------------------------------------------------------------

int alarm_assets_generate()
{

    alarm_button_stored =(GtkWidget **)malloc(sizeof(GtkWidget *));
        // declaring plugin for window for clock 
    clock_custom_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "clock_custom_fixed"));
    clock_menu_fixed= GTK_WIDGET(gtk_builder_get_object(builder, "clock_menu_fixed"));

    gtk_stack_add_named(GTK_STACK(stack),clock_menu_fixed,"clock_menu_fixed");
    gtk_stack_add_named(GTK_STACK(stack),clock_custom_fixed,"clock_custom_fixed");

    on_clock_toggled();
    g_signal_connect(time_1_set_button,"clicked", G_CALLBACK(on_time_set_button_clicked),GINT_TO_POINTER(1));
    g_signal_connect(time_2_set_button, "clicked", G_CALLBACK(on_time_set_button_clicked),GINT_TO_POINTER(2));
    g_signal_connect(time_3_set_button, "clicked", G_CALLBACK(on_time_set_button_clicked), GINT_TO_POINTER(3));

        
  
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        g_print("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        g_print("SDL_mixer initialization failed: %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }
     g_signal_connect(alarm_sound_list, "changed", G_CALLBACK(timer_callback), NULL);



    // on_custom_toggled() ;



}

// GtkWidget *switches[3] ;
// int num_switches = G_N_ELEMENTS(switches);
// to count net switches in the list 
int timeDifferenceInSeconds(int wakeHour, int wakeMinute, const char* am_pm, int diff_day_code )
{
    time_t now;
    // current time 
    struct tm *currentTime;
    // structure for time 
    time(&now);  // Get current time
    currentTime = localtime(&now);

    currentHour = currentTime->tm_hour  ;
    // for setting the base to current time vs variation in time 
    currentMinute = currentTime->tm_min ;

    int currentSecond = currentTime->tm_sec ;
// same varition fo rminute even
    wakeHour = convertTo24Hour(wakeHour, am_pm);
    // to convert the time to 24 -> 12 hour balance system 
    int wakeTimeInSeconds = (wakeHour + diff_day_code) * 3600 + wakeMinute * 60;
    // feature to find difference of time based on the day selected 
    int currentTimeInSeconds = currentHour * 3600 + currentMinute * 60;

    int difference = wakeTimeInSeconds - currentTimeInSeconds;
    if (difference < 0)
    {
        difference += 24 * 3600;  // If wake-up time is earlier than current time, add a day
    }
    return (difference - currentSecond);
}


void on_clock_toggled(GtkWidget *)
{
    // when clock app is clicked , 
    gboolean state = true;
    if (state)
    {
         
        // creating a new builder for clock window  

      
        // improting plugins firm the gtk library in c 

         

        // widget declatred for settin g frame for first clock app ;

        time_1_set_button = GTK_WIDGET(gtk_builder_get_object(builder, "time_1_set_button"));
        // just  a button denoting the time value we used generally 

        time_2_set_button = GTK_WIDGET(gtk_builder_get_object(builder, "time_2_set_button"));
        alarm_switch1 = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_switch1"));
        // alarm_switch1 to set alarm to 6.00 Am
        clock_main_fixed_back = GTK_WIDGET(gtk_builder_get_object(builder, "clock_main_fixed_back"));
        alarm_switch2 = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_switch2"));
        // switch 2 to set alarm to 6.45 Am

        alarm_switch3 = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_switch3"));
        // switch 3 to set alarm to 7:15 Am 

        time_3_set_button = GTK_WIDGET(gtk_builder_get_object(builder, "time_3_set_button"));

        custom_set_button = GTK_WIDGET(gtk_builder_get_object(builder, "custom_set_button"));
       // to guide the user to use that user interface ;

        clock_label = GTK_WIDGET(gtk_builder_get_object(builder, "clock_label"));
        // headtag 
	    alarm_Done_button = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_Done_button"));
        // to finalize the command after user has enetered its options 

	   
        // command to intialize window_clock to work on ;
 	    
    }
}
void on_alarm_Done_button_clicked(GtkButton *button, gpointer user_data)
{
    // Retrieve the states of all three switches
    gboolean state_switch1 = gtk_switch_get_active(GTK_SWITCH(alarm_switch1));
    // TO  detect the current condition of alarm_switch1 - either true or false ;

    gboolean state_switch2 = gtk_switch_get_active(GTK_SWITCH(alarm_switch2));
    // TO  detect the current condition of alarm_switch2 - either true or false ;

    gboolean state_switch3 = gtk_switch_get_active(GTK_SWITCH(alarm_switch3));
    // TO  detect the current condition of alarm_switch3 - either true or false ;

    // Call respective functions based on the states of the switches
    if (state_switch1)
    {
        // Call function for switch 1
         int timediff1 = timeDifferenceInSeconds(hour_value,minute_value,am_pm_value,diff_day_code);
        setAlarm(timediff1,hour_value,minute_value,am_pm_value);
    }
    if (state_switch2)
    {
        // Call function for switch 2
        int timediff2 = timeDifferenceInSeconds(hour_value,minute_value,am_pm_value,diff_day_code);
           setAlarm(timediff2,hour_value,minute_value,am_pm_value);

    }
    if (state_switch3)
    {
        // Call function for switch 3
         int timediff3 = timeDifferenceInSeconds(hour_value,minute_value,am_pm_value,diff_day_code);
           setAlarm(timediff3,hour_value,minute_value,am_pm_value);


    }

}



void on_custom_toggled()
{
    gboolean state = true ;
    if (state)
    {
       
        // builder intialized and assigned to its file to read the plugins 
        // builder has function of reading data from the specified file and interpreting the plugins assigned 

       // connecting the plugins for window destroy command once eiteher the user click cross button or any other 
       // spot of the empty window 
        
       //connecting builder to its signl for getting invoked once its required after window intialization 

     
        clock_header = GTK_WIDGET(gtk_builder_get_object(builder, "clock_custom_back_button"));

        final_button = GTK_WIDGET(gtk_builder_get_object(builder, "final_button"));

        hour_spin = GTK_WIDGET(gtk_builder_get_object(builder, "hour_spin"));


        minute_spin = GTK_WIDGET(gtk_builder_get_object(builder, "minute_spin"));

        DAY = GTK_WIDGET(gtk_builder_get_object(builder, "DAY"));
       
         alarm_adjustment1 = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(hour_spin));
        alarm_adjustment2 = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(minute_spin));

        am_pm = GTK_WIDGET(gtk_builder_get_object(builder, "am_pm"));

        vibration_button = GTK_WIDGET(gtk_builder_get_object(builder, "vibration_button"));

        vibration_switch = GTK_WIDGET(gtk_builder_get_object(builder, "vibration_switch"));

        hour_tag = GTK_WIDGET(gtk_builder_get_object(builder, "hour_tag"));

        minute_label = GTK_WIDGET(gtk_builder_get_object(builder, "minute_label"));

        minute_tag = GTK_WIDGET(gtk_builder_get_object(builder, "minute_tag"));

        hour_label = GTK_WIDGET(gtk_builder_get_object(builder, "hour_label"));

        alarm_sound_button = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_sound_button"));

        alarm_tag = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_tag"));

        alarm_sound_list = GTK_WIDGET(gtk_builder_get_object(builder, "alarm_sound_list"));
       

        
    }
}
gboolean on_window_custom_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    // Hide the window instead of destroying it
    gtk_widget_hide(widget);
    // Return TRUE to indicate that the event has been handled
    return TRUE;
}

void on_final_button_clicked(GtkButton *button, gpointer user_data)
{
          
        alarm_adjustment1 = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(hour_spin));
        // thsi is a feature that allows us to read - current value from the spin button itself  
        alarm_adjustment2 = gtk_spin_button_get_adjustment(GTK_SPIN_BUTTON(minute_spin));
        // same for this even 
        hour_value = gtk_adjustment_get_value(alarm_adjustment1);
        // save the vlue to varible hour_value 
        minute_value = gtk_adjustment_get_value(alarm_adjustment2);
        // same for minute even 
        am_pm_value = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(am_pm));

        DAY_value = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(DAY));
        // if loop for checking that all the data required is feed or not 
        if (am_pm_value == NULL || DAY_value == NULL)
        {
        g_print("Please fill up all the required options first.\n");
        return;
        }

         next_day = dayToCaseNo(DAY_value); // generate the code or case no for next day - selected by the user 

        time_t t = time(NULL);  
        // function to invoke current time from the calender and NULL is used here beacuse , we arent interested in 
        // in chnaging the timezone feature of it now ;
        struct tm *tm = localtime(&t);

        int current_day = tm->tm_wday ;
        
        
        // the diff of day codes = diff_day_code 
        if((next_day - current_day)>=1)
        {
        diff_day_code = next_day - current_day - 1  ;
        }
        else if((next_day - current_day)<0)
        {
            diff_day_code = 6 - abs(next_day - current_day);
        }
        else if((next_day - current_day)==0)
        {
            diff_day_code = 0;
        }

       

        // int z = timeDifferenceInSeconds(hour_value, minute_value,am_pm_value, diff_day_code);
        char *label=(char *)malloc(20*sizeof(char));
        sprintf(label, "%02d:%02d %s", hour_value,minute_value,am_pm_value);
        gtk_button_set_label(GTK_BUTTON(alarm_button_stored[0]), label);
        // setAlarm(z, hour_value, minute_value,am_pm_value);

        gtk_stack_set_visible_child_name(GTK_STACK(stack),"clock_menu_fixed");

       
}
void set_spin_button_values(int *hour, int *minute)
{
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(hour_spin), *hour);
    
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(minute_spin), *minute);
}


int convertTo24Hour(int hour, const char* am_pm)
{
    if (strcmp(am_pm, "AM") == 0)
    {
        if (hour == 12)
        {
            return 0; // 12 AM is 0 hour
        } else {
            return hour;
        }
    } else { // PM
        if (hour == 12)
        {
            return 12; // 12 PM remains 12
        } else {
            return hour + 12; // Add 12 to the hour for PM
        }
    }
}


int dayToCaseNo(const char *day)
{
    char Day[10];
    strcpy(Day, day);
    // comapring day to each str , and return the code for it ;
    if (strcmp(Day, "Sunday") == 0)
    {
        return 0;
    } else if (strcmp(Day, "Monday") == 0)
    {
        return 1;
    } else if (strcmp(Day, "Tuesday") == 0)
    {
        return 2;
    } else if (strcmp(Day, "Wednesday") == 0)
    {
        return 3;
    } else if (strcmp(Day, "Thursday") == 0)
    {
        return 4;
    } else if (strcmp(Day, "Friday") == 0)
    {
        return 5;
    } else if (strcmp(Day, "Saturday") == 0)
    {
        return 6;
    } 
    return -1; // Invalid day
}

gboolean timer_callback(gpointer data)
{
    // Check if alarm_music is already playing
    if (Mix_PlayingMusic())
    {
        return FALSE; // alarm_Music is still playing, don't start a new instance
    }

    // Get the selected sound file from the combo box
    const gchar *selected_sound = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(alarm_sound_list));
   
    if (!selected_sound)
    {
        g_print("No sound selected!\n");
        return FALSE;
    }
     

    // Create a thread to load and play music
    pthread_t alarm_music_thread;
    pthread_create(&alarm_music_thread, NULL, load_and_play_music, (void *)selected_sound);


    // Construct the filename of the MP3 file
    
    return FALSE;
}
void *load_and_play_music(void *selected_sound_ptr)
{
    // Get the selected sound file from the combo box
    const gchar *selected_sound = (const gchar *)selected_sound_ptr;

    // Construct the filename of the MP3 file
    gchar *filename = g_strdup_printf("assets/%s.mp3", selected_sound);

    // Load the selected sound file
    alarm_music = Mix_LoadMUS(filename);
    g_free(filename);
    if (!alarm_music)
    {
        g_print("Failed to load music: %s\n", Mix_GetError());
        pthread_exit(NULL);
    }

    // Play the loaded music
    if (Mix_PlayMusic(alarm_music, 0) == -1)
    {
        g_print("Failed to play music: %s\n", Mix_GetError());
        Mix_FreeMusic(alarm_music);
        pthread_exit(NULL);
    } 

    // Wait for a while to allow the music to play
    while(Mix_PlayingMusic())
    {
        SDL_Delay(100);
    }
     on_alarm_end();
    // Clean up
    Mix_FreeMusic(alarm_music);
    pthread_exit(NULL);
}
void setAlarm(int seconds, int wakeHour, int wakeMinute, const char *am_pm)
{
   
    printf("Alarm set for %02d:%02d:%s ", wakeHour, wakeMinute, am_pm);
    fflush(stdout);
    if(flag_custom)
    {
        if ( next_day==1)
        {
            printf("- Monday\n");
        } else if (next_day == 2 )
        {
        printf("- Tuesday\n") ;
        } else if (next_day==3)
        {
            printf("- Wednesday\n"); 
        } else if (next_day==4)
        {
            printf("- Thrusday\n"); 
        } else if (next_day==5)
        {
            printf("- Firday\n"); 
        } else if (next_day==6)
        {
            printf("- Saturday\n"); 
        } else if (next_day==0)
        {
            printf("- Sunday\n"); 
        }
    }   

  printf("%d\n",seconds);
  fflush(stdout);
guint alarm_id = g_timeout_add_seconds(seconds, alarm_callback, NULL);
  return;
}
gboolean alarm_callback(gpointer data)
{
    // Function to be called when the alarm goes off
    printf("Alarm! Time's up!\n");
    fflush(stdout);
   guint timer_id = g_timeout_add_seconds(0, timer_callback, NULL);

    
    return FALSE; // Don't repeat the alarm
}
 void on_time_set_button_clicked(GtkWidget *button_set, gpointer button_num)
 {
    alarm_button_stored[0]= button_set;

    gtk_stack_set_visible_child_name(GTK_STACK(stack),"clock_custom_fixed");

    on_custom_toggled();

 }

void on_clock_menu_fixed_back_clicked()
{
      gtk_stack_set_visible_child_name(GTK_STACK(stack),"homepage_fixed");
}


void on_alarm_end()
{
    // Turn off the switch widget
    gtk_switch_set_active(GTK_SWITCH(alarm_switch1), FALSE);
}

void on_clock_custom_back_button_clicked()
{

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "clock_menu_fixed");
}


// calendar functions ---------------------------------------------------------

void calendar_assets_generate(){

    // Initialise all date buttons
    int k = 1;
    for(int i = 1; i < 7; i++){
        for(int j = 1; j < 8; j++){
            char buttonname[64];
            sprintf(buttonname, "r%dc%d",i , j);
            icon_buttons[k] = GTK_WIDGET(gtk_builder_get_object(builder, buttonname));
            k++;
        }
    }

    // Initialise and setup other buttons and menus
    editButton = GTK_WIDGET(gtk_builder_get_object(builder, "edit/save_button"));
    gtk_button_set_label(GTK_BUTTON(editButton), "Edit");
    gtk_widget_set_sensitive(editButton, false);

    monthName = GTK_COMBO_BOX(gtk_builder_get_object(builder, "month_name"));

    yearName = GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "year_name"));

    currentDate = GTK_WIDGET(gtk_builder_get_object(builder, "currentDateDisplay"));

    dateContents = GTK_WIDGET(gtk_builder_get_object(builder, "dateContents"));
    gtk_widget_set_sensitive(GTK_WIDGET(dateContents), false);
    gtk_entry_set_text(GTK_ENTRY(dateContents),"Nothing to display");

    // Set current date and month in label
    time_t t2 = time(NULL);
    struct tm tm1 = *localtime(&t2);
    year = tm1.tm_year + 1900; 
    monthNum = tm1.tm_mon + 1;
    set_label_current_date(currentDate);

    // Calendar setup process
    getData();
    setCalendar();

    // Setup miscellenous tool and widgets
    calendar_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "calendar_fixed"));
    gtk_stack_add_named(GTK_STACK(stack), calendar_fixed, "calendar_fixed");


}

// Function to write new content into file
void write_to_file(char text[200]) {
    // Open the file in write mode
    FILE *file = fopen("temp.txt", "w");
    
    // Check if file opened successfully
    if (file != NULL) {
        // Write the text to the file
        fprintf(file, "%s", text);
        const char* originalFileName = "temp.txt";
        remove(calendar_note_filename);
        fclose(file);
        rename(originalFileName, calendar_note_filename);
    } else {
        printf("Failed to open file for writing.\n");
    }
}

// Functin to print the content for each date in window
void displayContent() {
    // Open the file
    FILE *file = fopen(calendar_note_filename, "r");
    
    // Check if the file exists
    if (file == NULL) {
        gtk_entry_set_text(GTK_ENTRY(dateContents),"Nothing to display");
        return;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory to store the file content
    char *fileContent = (char *)malloc(fileSize + 1); // +1 for null terminator
    if (fileContent == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    // Read the file content into the allocated memory
    size_t bytesRead = fread(fileContent, 1, fileSize, file);
    if (bytesRead != fileSize) {
        printf("Error reading file.\n");
        fclose(file);
        free(fileContent);
        return;
    }

    // Null-terminate the string
    fileContent[fileSize] = '\0';

    // Close the file
    fclose(file);

    // Print the file content
    gtk_entry_set_text(GTK_ENTRY(dateContents),fileContent);
    // Free allocated memory
    free(fileContent);
}

// Function to edit content for each date in window
void editContent(GtkButton *button){

    // Check wether content is to be editted of saved
    if(check == 0){
        gtk_button_set_label(GTK_BUTTON(editButton), "Save");
        gtk_widget_set_sensitive(GTK_WIDGET(dateContents), true);
        for(int i = 1; i < 43; i++){
            gtk_widget_set_sensitive(GTK_WIDGET(icon_buttons[i]), false);
        }
        check = 1;
    } else {
        char buffer[200];
        const char *text = gtk_entry_get_text(GTK_ENTRY(dateContents));
        strcpy(buffer, text);
        write_to_file(buffer);
        gtk_button_set_label(GTK_BUTTON(editButton), "Edit");
        gtk_widget_set_sensitive(editButton, false);
        gtk_entry_set_text(GTK_ENTRY(dateContents),"Nothing to display");
        gtk_widget_set_sensitive(GTK_WIDGET(dateContents), false);
        for(int i = 1; i < 43; i++){            
            gtk_widget_set_sensitive(GTK_WIDGET(icon_buttons[i]), true);
        }
        check = 0;
    }
}

// Function to set label text with current date
void set_label_current_date(GtkWidget *label) {
    // Get current date and time
    GDateTime *now = g_date_time_new_now_local();
    
    // Format date string
    gchar *formatted_date = g_strdup_printf("%s, %d %s, %d",
        g_date_time_format(now, "%A"),   // Full weekday name (e.g., "Saturday")
        g_date_time_get_day_of_month(now), // Day of month (e.g., 20)
        g_date_time_format(now, "%B"),   // Full month name (e.g., "April")
        g_date_time_get_year(now));       // Year (e.g., 2024)

    // Set label text
    gtk_label_set_text(GTK_LABEL(label), formatted_date);

    // Free allocated memory
    g_date_time_unref(now);
    g_free(formatted_date);
}

// Highlight a button
void set_button_color(GtkWidget *button) {
    GdkRGBA text_color = {1.0, 0, 0, 1.0}; // Red text

    // Get the label widget of the button
    GtkWidget *label = gtk_bin_get_child(GTK_BIN(button));

    // Set label text color
    gtk_widget_override_color(label, GTK_STATE_FLAG_NORMAL, &text_color);

    // Create a PangoAttrList to hold the text attributes
    PangoAttrList *attr_list = pango_attr_list_new();

    // Create attributes for bold and underline
    PangoAttribute *attr_bold = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
    PangoAttribute *attr_underline = pango_attr_underline_new(PANGO_UNDERLINE_SINGLE);

    // Add attributes to the attribute list
    pango_attr_list_insert(attr_list, attr_bold);
    pango_attr_list_insert(attr_list, attr_underline);

    // Apply the attribute list to the label widget
    gtk_label_set_attributes(GTK_LABEL(label), attr_list);

    // Free the attribute list (attributes will be freed when the list is freed)
    pango_attr_list_unref(attr_list);
}

// Function to calculate the day of the week
int dayOfWeek(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }

    int K = year % 100;
    int J = year / 100;

    int h = (day + (13 * (month + 1)) / 5 + K + K / 4 + J / 4 - 2 * J) % 7;
    
    // Adjust for negative numbers
    if (h < 0)
        h += 7;

    return h;
}

// Function to convert month name to its corresponding number
int monthToNumber(char* month) {
    char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    for (int i = 0; i < 12; ++i) {
        if (strcasecmp(month, months[i]) == 0) {
            return i + 1;
        }
    }

    return -1;
}

// Function to check if the string contains only digits
bool isNumber(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }

    return true;
}

// Function to calculate the first day in each month
int get_date(int year,int monthNum) {

    // Calculate day of the week for the 1st day of the month
    int dayIndex = dayOfWeek(1, monthNum, year);
    
    // Setting day index of saturday as 7
    if (dayIndex == 0) {
        dayIndex = 7;
    }

    return dayIndex;
}

// Function to update month in drop down menu when moving forwards or backwards
void set_dropdown_value_by_index(GtkComboBox *combo_box, gint index) {
    GtkTreeModel *model;
    GtkTreeIter iter;

    // Get the model associated with the combo box
    model = gtk_combo_box_get_model(combo_box);

    // Check if the index is within the valid range of items
    if (index < 0) {
        g_print("Invalid index: %d\n", index);
        return;
    }

    // Set the active item using the index
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), index);
}

// Function to update year on screen when moving forwards or backwards
void set_spinner_value(GtkSpinButton *spinner, gdouble value) {
    // Ensure spinner is of type GtkSpinButton *
    g_return_if_fail(GTK_IS_SPIN_BUTTON(spinner));

    // Set the value of the spinner button
    gtk_spin_button_set_value(spinner, value);
}

// Function to set the label of the button to the specified date
void setButtonDate(GtkWidget *button, int date) {
    char label[3]; 
    sprintf(label, "%d", date);
    gtk_button_set_label(GTK_BUTTON(button), label);
}


// Function to get number of days in a given month
int numberOfDays(int x, int y){
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Compensating for leap years and century leap years
    if ( y == 2 && x%4 == 0 && x%100!=0){
        return (days[1]+1);
    }   
    return days[(y-1)];
}

// Function to get basic data required to setip the calendar
void getData(){

    // Getting first day of month for the current month and year
    dayIndex = get_date(year,monthNum);

    // Getting number of days in current month
    NumDays =  numberOfDays(year, monthNum);

    // Getting number of days in previous month
    if (monthNum == 1){
        PrevDays = numberOfDays(year, 12);
    } else {
        PrevDays = numberOfDays(year, monthNum-1);
    }
}

// Function to setup the calendar
void setCalendar(){
    // Filling buttons with dates of the specified month
    for(int i = dayIndex-1; i > 0; i--){
        setButtonDate(icon_buttons[i], PrevDays--);
        gtk_widget_set_opacity(GTK_WIDGET(icon_buttons[i]), 0.5);
    }
    for(int i = dayIndex; i < dayIndex+NumDays; i++){
        setButtonDate(icon_buttons[i], i-dayIndex+1);
        gtk_widget_set_opacity(GTK_WIDGET(icon_buttons[i]), 1.0);
    }
    int j = 1;
    for(int i = dayIndex+NumDays; i < 43; i++){
        setButtonDate(icon_buttons[i],j++);
        gtk_widget_set_opacity(GTK_WIDGET(icon_buttons[i]), 0.5);
    }

    // Setting initial month and year values
    set_dropdown_value_by_index(monthName,monthNum-1);
    set_spinner_value(yearName,year);

    // Getting current year and month
    time_t t2 = time(NULL);
    struct tm tm1 = *localtime(&t2);
    int currentyear = tm1.tm_year + 1900; 
    int currentmonth = tm1.tm_mon + 1; 
    int day = localtime(&(time_t){time(NULL)})->tm_mday;

    // HIghlighting current day
    if(year == currentyear && monthNum == currentmonth){
        set_button_color(icon_buttons[day+1]);
    }
}

// Function to check the type of button clicked and aacording select further course of action
void functionSet(GtkButton *button){
    char label[20];
    int num;
    float opacity;

    // Get opacity of widget to check if current date is clicked or some other month's
    opacity = gtk_widget_get_opacity(GTK_WIDGET(button));

    if(opacity != 1){

        const gchar *button_label = gtk_button_get_label(GTK_BUTTON(button));
        strcpy(label, button_label);
        num = atoi(label);

    // Move the calendar to next month or previous month
        if(num > 20){
            if(monthNum==1){
                monthNum=12;
                year--;
            } else {
                monthNum--;
            }
        } else {
            if(monthNum == 12){
                monthNum = 1;
                year++;
            } else {
                monthNum++;
            }
        }

        getData();
        setCalendar();  

    } else {

        // Read content of clicked date
        const gchar *text = gtk_button_get_label(button);
        int ref = atoi(text);
        sprintf(calendar_note_filename, "assets/%d_%d_%d.txt", year, monthNum, ref);
        gtk_widget_set_sensitive(editButton, true);

        displayContent(calendar_note_filename);
    }

    return;
}

// Function to set month and update calendar
void getMonth(GtkComboBox *widget){

    GtkTreeIter iter;
    GtkTreeModel *model;
    gchar *selected_value;

    // Get the model associated with the combo box
    model = gtk_combo_box_get_model(widget);

    // Get the currently selected item from the combo box
    if (gtk_combo_box_get_active_iter(widget, &iter)) {
        gtk_tree_model_get(model, &iter, 0, &selected_value, -1);
        monthNum = monthToNumber(selected_value);
        g_free(selected_value);
    }

    getData();
    setCalendar();
}

// Function to set year and update calendar
void getYear(GtkSpinButton *spinner) {

    // Get the currently selected year
    year = gtk_spin_button_get_value(spinner);

    getData();
    setCalendar();
}

void on_calendar_home_button_clicked(){

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");
}


/* homepage functions --------------------------------------------- */

gboolean update_main_time_label(gpointer user_data)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%I:%M:%S %p", timeinfo);


    gtk_label_set_text(GTK_LABEL(main_time_label), buffer);
        // this allows the function to be called repeatedly
    return G_SOURCE_CONTINUE;
}


void homepage_assets_generate()
{

    // to apply rounded effect on each button
    for(int i = 1; i < 7; i++)
    {
        // getting each button and applying rounded borders
        char buttonname[64];
        sprintf(buttonname, "icon_button%d", i);
        main_icon_buttons[i] = GTK_WIDGET(gtk_builder_get_object(builder, buttonname));
        GtkCssProvider *css_provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(css_provider,
            //".icon_button { border-radius: 25px; background: none; box-shadow: none; border: none;}",    // adds a class which is mentioned in the glad
            ".icon_button { border-radius: 25px; background: white;}",    // adds a class which is mentioned in the glad
            -1, NULL);
        GtkStyleContext *context = gtk_widget_get_style_context((main_icon_buttons[i]));
        gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);


            //adding image to each button
        if(i == 1 || i == 2)
        {
            continue;
        }

            //TODO
        GtkWidget *icon_button_image = gtk_image_new();
        char image_buttonname[64];
        sprintf(image_buttonname, "%s_image", buttonname);
        icon_button_image = GTK_WIDGET(gtk_builder_get_object(builder, image_buttonname));
        char buttonname_imagepath[64];
        sprintf(buttonname_imagepath, "assets/%s_image.jpg", buttonname);
        homepage_icon_button_pixIn = gdk_pixbuf_new_from_file(buttonname_imagepath, NULL);    // unscaled pixbuf
        homepage_icon_button_pix = gdk_pixbuf_scale_simple(homepage_icon_button_pixIn, 104, 104, GDK_INTERP_NEAREST); // scaled pixbuf
        gtk_image_set_from_pixbuf(GTK_IMAGE(icon_button_image), homepage_icon_button_pix);


    }

    //gtk_widget_set_name(main_icon_buttons[1], "rounded");



    main_time_label = GTK_WIDGET(gtk_builder_get_object(builder, "main_time_label"));
    gtk_widget_set_halign(main_time_label, GTK_ALIGN_CENTER);
    guint timeout_id = g_timeout_add_seconds(1, update_main_time_label, NULL);
    //PangoFontDescription *font_desc = pango_font_description_from_string("Sans 32");
    //gtk_widget_override_font(main_time_label, font_desc);

    //GtkWidget *icon_grid = GTK_WIDGET(gtk_builder_get_object(builder, "icon_grid"));
    //gtk_widget_set_halign(GTK_WIDGET(icon_grid), GTK_ALIGN_CENTER);

    homepage_wallpaper = gtk_image_new();
    homepage_wallpaper = GTK_WIDGET(gtk_builder_get_object(builder, "homepage_wallpaper"));
    homepage_wallpaper_pixIn = gdk_pixbuf_new_from_file("assets/homepage_wallpaper.jpg", NULL);    // unscaled pixbuf
    homepage_wallpaper_pix = gdk_pixbuf_scale_simple(homepage_wallpaper_pixIn, 1000, 800, GDK_INTERP_NEAREST); // scaled pixbuf
    gtk_image_set_from_pixbuf(GTK_IMAGE(homepage_wallpaper), homepage_wallpaper_pix);



}

void main_widgets_generate()
{


    main_window = GTK_WIDGET(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_default_size(GTK_WINDOW(main_window), 1000, 800);

        //connects destroy signal (close button) to gtk_main_quit (predefined)
    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        //creating a GtkStack that will contain the GtkFixed's of all pages
    gtk_container_add(GTK_CONTAINER(main_window), stack);


        //get all GtkFixed's from builder

    homepage_fixed = GTK_WIDGET(gtk_builder_get_object(builder, "homepage_fixed"));
        //adding all GtkFixed's to this GtkStack

    gtk_stack_add_named(GTK_STACK(stack), homepage_fixed, "homepage_fixed");


}

void show_homepage()
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "homepage_fixed");
}
void on_icon_button1_clicked(GtkWidget *icon_button1)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "music_menu_scrolled_window");

    printf("button1 clicked \n");
}
void on_icon_button2_clicked(GtkWidget *icon_button2)
{
    generate_gallery_menu_fixed();

    gtk_stack_set_visible_child_name(GTK_STACK(stack), "gallery_menu_fixed");
    printf("button2 clicked \n");
}
void on_icon_button3_clicked(GtkWidget *icon_button3)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "calculator_normal_fixed");
    printf("button3 clicked \n");
}
void on_icon_button4_clicked(GtkWidget *icon_button4)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "calendar_fixed");

    printf("button4 clicked \n");
}
void on_icon_button5_clicked(GtkWidget *icon_button5)
{
    gtk_stack_set_visible_child_name(GTK_STACK(stack),"clock_menu_fixed");

    printf("button5 clicked \n");
}
void on_icon_button6_clicked(GtkWidget *icon_button6)
{
    system("start microsoft.windows.camera:");

    printf("button6 clicked \n");
}
