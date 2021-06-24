#define BOUNCE_LOCK_OUT
#include <Bounce2.h>
#include <Keyboard.h>

#define PORT_START_STOP 2
#define PORT_NEXT 3
#define PORT_PREV 4
#define BOUNCE_TIME 5

#define ABLETON_NEXT_SCENE KEY_DOWN_ARROW
#define ABLETON_PREV_SCENE KEY_UP_ARROW
#define ABLETON_LAUNCH_SCENE 'j'
#define ABLETON_STOP_TRANSPORT 'k'
#define ABLETON_STOP_CLIPS 'l'

#define STOPPED = 0
#define STARTED = 1
#define MOVED = 2

unsigned state = STOPPED;

Bounce start_stop_bouncer = Bounce();
Bounce next_bouncer = Bounce();
Bounce prev_bouncer = Bounce();

void setup() {
  pinMode(PORT_START_STOP, INPUT);
  pinMode(PORT_NEXT, INPUT);
  pinMode(PORT_PREV, INPUT);
  digitalWrite(PORT_START_STOP, INPUT_PULLUP);
  digitalWrite(PORT_NEXT, INPUT_PULLUP);
  digitalWrite(PORT_PREV, INPUT_PULLUP);
  start_stop_bouncer.attach(PORT_START_STOP);
  next_bouncer.attach(PORT_NEXT);
  prev_bouncer.attach(PORT_PREV);
  start_stop_bouncer.interval(BOUNCE_TIME);
  next_bouncer.interval(BOUNCE_TIME);
  prev_bouncer.interval(BOUNCE_TIME);

  Keyboard.begin();
}

void loop() {
  start_stop_bouncer.update();
  next_bouncer.update();
  prev_bouncer.update();

  if (start_stop_bouncer.fell()) {
    onStartStopPressed();
  }
  if (next_bouncer.fell()) {
    onNextPressed();
  }
  if (prev_bouncer.fell()) {
    onPrevPressed();
  }
}

void onStartStopPressed() {
  if (state == STARTED) {
    Keyboard.write(ABLETON_STOP_TRANSPORT);
    delay(1);
    Keyboard.write(ABLETON_STOP_CLIPS);
    delay(1);
    Keyboard.write(ABLETON_STOP_TRANSPORT);
    state = STOPPED;
  } else {
    Keyboard.write(ABLETON_LAUNCH_SCENE);
    state = STARTED;
  }
}

void onNextPressed() {
  Keyboard.write(ABLETON_NEXT_SCENE);
  if (state == STARTED) {
    state = MOVED;
  }
}

void onPrevPressed() {
  Keyboard.write(ABLETON_PREV_SCENE);
  if (state == STARTED) {
    state = MOVED;
  }
}
