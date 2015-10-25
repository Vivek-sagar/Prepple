#pragma once

#define WAKEUP_REASON 0
#define WAKEUP_ID_KEY 1
#define PERSISTENT_COUNT_KEY 20

#define KEY_WORD 0
#define KEY_DEFINITION 1
#define KEY_COUNT 2

#define ANIM_DURATION 1000

Window *window;
TextLayer *title_layer;
TextLayer *text_layer_body;
TextLayer *text_layer_body_definition;
TextLayer *text_layer_body_next;
TextLayer *text_layer_error;

GFont next_font;
const char* prev_word;

static Layer *s_layer;
static PropertyAnimation *s_property_animation;

int loop_count = 0;
int count = 0;
enum display_states {WORD, DEFINITION};
enum display_states display_state = WORD;

bool webreq_complete = true;

static WakeupId s_wakeup_id;

struct wlist* current_word;

struct wlist{
  struct wlist *next;
  char *word;
  char *definition;
};