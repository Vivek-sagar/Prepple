#include <pebble.h>
#include "prepple.h"

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(text_layer_body, s_buffer);
}

void change_word()
{
    char* word = current_word->word;

    text_layer_set_text(text_layer_body, word);
}


void change_definition()
{
    int letter_count = 0;
    char* definition = current_word->definition;
  for (int i=0; *(definition+i) != '\0'; i++)
      letter_count++;
  text_layer_set_text_color(text_layer_body_definition, GColorMintGreen);
    if (letter_count > 30)
      text_layer_set_font(text_layer_body_definition, fonts_get_system_font(FONT_KEY_GOTHIC_24));
    else
      text_layer_set_font(text_layer_body_definition, fonts_get_system_font(FONT_KEY_GOTHIC_28));    
    
    text_layer_set_text(text_layer_body_definition, definition);
}

void show_error(char* msg)
{
    text_layer_set_text(text_layer_error, msg);
}

void clear_error()
{
    text_layer_set_text(text_layer_error, "");
}

void cycle_word()
{
    if (current_word->next == NULL)
    {
        show_error("No more words!");
        return;
    }
    struct wlist* temp;
    temp = current_word;
    current_word = current_word->next;
    free(temp);
    change_word();
}



void animation_started(Animation *animation, void *data) {
   // Animation started!
}

void animation_stopped(Animation *animation, bool finished, void *data) {
   // Animation stopped!
}

void animation_up_started(Animation *animation, void *data) {
   // Animation started!
  prev_word = text_layer_get_text(text_layer_body);
}

void animation_up_stopped(Animation *animation, bool finished, void *data) {
   // Animation stopped!
    if (prev_word == text_layer_get_text(text_layer_body))
      text_layer_set_text(text_layer_body, "Loading...");
    text_layer_set_text(text_layer_body_next, "Loading...");
    layer_set_frame(text_layer_get_layer(text_layer_body), GRect(0,50, 144, 154));
    layer_set_frame(text_layer_get_layer(text_layer_body_next), GRect(0, 160, 144, 154));    
}



static void trigger_custom_animation_out(){
    GRect from_frame = layer_get_frame(text_layer_get_layer(text_layer_body));
    GRect to_frame = GRect(-144, 50, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_started,
    .stopped = (AnimationStoppedHandler) animation_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
  
    from_frame = layer_get_frame(text_layer_get_layer(text_layer_body_definition));
    to_frame = GRect(0, 50, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body_definition), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body_definition), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body_definition), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_started,
    .stopped = (AnimationStoppedHandler) animation_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
}

static void trigger_custom_animation_in(){
    GRect from_frame = layer_get_frame(text_layer_get_layer(text_layer_body));
    GRect to_frame = GRect(0, 50, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_started,
    .stopped = (AnimationStoppedHandler) animation_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
  
    from_frame = layer_get_frame(text_layer_get_layer(text_layer_body_definition));
    to_frame = GRect(144, 50, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body_definition), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body_definition), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body_definition), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_started,
    .stopped = (AnimationStoppedHandler) animation_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
}

static void trigger_custom_animation_up(){
    GRect from_frame = layer_get_frame(text_layer_get_layer(text_layer_body));
    GRect to_frame = GRect(0, -154, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_started,
    .stopped = (AnimationStoppedHandler) animation_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
  
    from_frame = layer_get_frame(text_layer_get_layer(text_layer_body_next));
    to_frame = GRect(0, 50, 144, 154);
    animation_set_duration((Animation*)text_layer_get_layer(text_layer_body_next), ANIM_DURATION);
    animation_set_curve((Animation*)text_layer_get_layer(text_layer_body_next), AnimationCurveEaseInOut);
    s_property_animation = property_animation_create_layer_frame(text_layer_get_layer(text_layer_body_next), &from_frame, &to_frame);
  animation_set_handlers((Animation*) s_property_animation, (AnimationHandlers) {
    .started = (AnimationStartedHandler) animation_up_started,
    .stopped = (AnimationStoppedHandler) animation_up_stopped,
  }, NULL);
    animation_schedule((Animation*) s_property_animation);
}

void request_next_word()
{
  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_uint8(iter, KEY_COUNT,count);

  // Send the message!
  app_message_outbox_send();
  count++;
  if (count > 56)            //Specific to this dataset!
    count = 0;
  persist_write_int(PERSISTENT_COUNT_KEY, count);
  trigger_custom_animation_up();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
   clear_error();
   
   if (display_state == WORD)
   {
       display_state = DEFINITION;
       change_definition();
       trigger_custom_animation_out();
   }
  else if (display_state == DEFINITION)
   {
       display_state = WORD;
       change_word();
      trigger_custom_animation_in();
   }
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) 
{
  webreq_complete = false;
  if (display_state == DEFINITION)
   {
       display_state = WORD;
       trigger_custom_animation_in();
   }
    request_next_word();
    
}

static void wakeup_handler(WakeupId id, int32_t reason) {
  // A wakeup event has occurred
  vibes_double_pulse();
  persist_delete(WAKEUP_ID_KEY);
}

void wake_after_5_m()
{
  time_t future_time = time(NULL) + 300;
  // Schedule wakeup event and keep the WakeupId in case it needs to be queried
  s_wakeup_id = wakeup_schedule(future_time, WAKEUP_REASON, true);
  // Persist to allow wakeup query after the app is closed.
  persist_write_int(WAKEUP_ID_KEY, s_wakeup_id);
}

static void click_config_provider(void *context) {
  // Register the ClickHandlers
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char word_buffer[32];
  static char definition_buffer[128];

  // Read tuples for data
  Tuple *word_tuple = dict_find(iterator, KEY_WORD);
  Tuple *definition_tuple = dict_find(iterator, KEY_DEFINITION);

  // If all data is available, use it
  if(word_tuple && definition_tuple) {
    snprintf(word_buffer, sizeof(word_buffer), "%s", word_tuple->value->cstring);
    snprintf(definition_buffer, sizeof(definition_buffer), "%s", definition_tuple->value->cstring);

    // Assemble full string and display
    //snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s, %s", word_buffer, definition_buffer);
    //text_layer_set_text(text_layer_error, weather_layer_buffer);
    
    //Fill word and definition into a wlist object
    current_word->word = word_buffer;
    current_word->definition = definition_buffer;
    
    change_word();
  }
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

void handle_init(void) {
	// Create a window and text layer
	window = window_create();
  window_set_background_color(window, GColorDarkGreen);
	title_layer = text_layer_create(GRect(0, 0, 144, 154));
  text_layer_body = text_layer_create(GRect(0,50, 144, 154));
  text_layer_body_definition = text_layer_create(GRect(144,50, 144, 154));
  text_layer_body_next = text_layer_create(GRect(0,160, 144, 154));
  text_layer_error = text_layer_create(GRect(0,130, 144, 154));
  
  text_layer_set_background_color(title_layer, GColorDarkGreen);
  text_layer_set_text_color(title_layer, GColorMintGreen);
  text_layer_set_background_color(text_layer_body, GColorDarkGreen);
  text_layer_set_background_color(text_layer_body_definition, GColorDarkGreen);
  text_layer_set_background_color(text_layer_body_next, GColorDarkGreen);
  text_layer_set_background_color(text_layer_error, GColorDarkGreen);
  text_layer_set_text_color(text_layer_body, GColorMintGreen);
  text_layer_set_text_color(text_layer_body_next, GColorMintGreen);
  
	tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
	// Set the text, font, and text alignment
	text_layer_set_text(title_layer, "Prepple");
	text_layer_set_font(title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(title_layer, GTextAlignmentCenter);
  
	text_layer_set_text(text_layer_body, "");
   text_layer_set_font(text_layer_body, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer_body, GTextAlignmentCenter);
  
  text_layer_set_text(text_layer_body_definition, "");
	text_layer_set_text_alignment(text_layer_body_definition, GTextAlignmentCenter);
  
  text_layer_set_text(text_layer_body_next, "");
   text_layer_set_font(text_layer_body_next, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
	text_layer_set_text_alignment(text_layer_body_next, GTextAlignmentCenter);
  
  text_layer_set_text(text_layer_error, "");
  text_layer_set_font(title_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	text_layer_set_text_alignment(text_layer_error, GTextAlignmentCenter);
  
	// Add the text layer to the window
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(title_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer_error));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer_body));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer_body_definition));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer_body_next));
  
  // Register AppMessage callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

  //Configure buttons
  window_set_click_config_provider(window, click_config_provider);
  
  // Subscribe to Wakeup API
  wakeup_service_subscribe(wakeup_handler);
  
  //Set count to last word used
  if (persist_exists(PERSISTENT_COUNT_KEY)) {
    count = persist_read_int(PERSISTENT_COUNT_KEY);

  }
  
  if (launch_reason() == APP_LAUNCH_WAKEUP){
    WakeupId id = 0;
    int32_t reason = 0;
    
    wakeup_get_launch_event(&id, &reason);
    wakeup_handler(id, reason);
  }
  
	// Push the window
	window_stack_push(window, true);
	
	// App Logging!
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Just pushed a window!");
  
  //Setup Wakeup calls for the future
  wake_after_5_m();
  
  //Request new word
  request_next_word();
  
  next_font = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
}

void word_init()
{
  struct wlist *new_node = (struct wlist*) malloc (sizeof (struct wlist));
  current_word = new_node;
  new_node->word = "PREPPLE!";
  new_node->definition = "";
  new_node->next = NULL;
  
  struct wlist *new_node_2 = (struct wlist*) malloc (sizeof (struct wlist));
  new_node_2->word = "Slow down";
  new_node_2->definition = "";
  new_node_2->next = NULL;
  
  new_node->next = new_node_2;
}

void word_deinit()
{
  
}


void handle_deinit(void) {
	// Destroy the text layer
	text_layer_destroy(title_layer);
	text_layer_destroy(text_layer_body);
	// Destroy the window
	window_destroy(window);
}

int main(void) {
	handle_init();
  word_init();
  change_word();
  trigger_custom_animation_up();
	app_event_loop();
	handle_deinit();
}
