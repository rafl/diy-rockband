#define _TASK_MICRO_RES
#include <TaskScheduler.h>
#include <USBHost_t36.h>
#include <MIDI.h>

#pragma GCC diagnostic error "-Wextra"

#define BIGBUFFER 1
#define DEBUG 1

#if BIGBUFFER
#  define MIDIDevice_t MIDIDevice_BigBuffer
#else
#  define MIDIDevice_t MIDIDevice
#endif

#if DEBUG
#  define DEB_SERIAL Serial
#  define DEB(...) DEB_SERIAL.printf(__VA_ARGS__)
#  define DEBP
#else
#  define DEB(...)
#  define DEBP __attribute__((unused))
#endif

typedef enum {
  OUT_KICK,
  OUT_PAD_RED,
  OUT_PAD_YELLOW,
  OUT_PAD_BLUE,
  OUT_PAD_GREEN,
  OUT_CYM_YELLOW,
  OUT_CYM_BLUE,
  OUT_CYM_GREEN,
  OUT_BUT_UP,
  OUT_BUT_DOWN,
  OUT_BUT_LEFT,
  OUT_BUT_RIGHT,
  OUT_BUT_A,
  OUT_BUT_B,
  OUT_BUT_X,
  OUT_BUT_Y,
  OUT_BUT_SHARE,
  OUT_BUT_HOME,
  OUT_BUT_OPTIONS,
  NUM_OUT,
} output_t;

#if DEBUG
static const char* const outputNames[NUM_OUT] = {
  "KICK",
  "PAD_RED",
  "PAD_YELLOW",
  "PAD_BLUE",
  "PAD_GREEN",
  "CYM_YELLOW",
  "CYM_BLUE",
  "CYM_GREEN",
  "BUT_UP",
  "BUT_DOWN",
  "BUT_LEFT",
  "BUT_RIGHT",
  "BUT_A",
  "BUT_B",
  "BUT_X",
  "BUT_Y",
  "BUT_SHARE",
  "BUT_HOME",
  "BUT_OPTIONS",
};
#endif

typedef struct {
  const unsigned long hold, holdOff;
} output_timing_t;

static const output_timing_t kickTiming = { .hold = 60 * TASK_MILLISECOND, .holdOff = 50 * TASK_MILLISECOND };
static const output_timing_t padTiming  = { .hold =  1 * TASK_MILLISECOND, .holdOff = 40 * TASK_MILLISECOND };
static const output_timing_t cymTiming  = { .hold = 25 * TASK_MILLISECOND, .holdOff = 40 * TASK_MILLISECOND };
static const output_timing_t butTiming  = { .hold = 25 * TASK_MILLISECOND, .holdOff = 40 * TASK_MILLISECOND };

typedef struct {
  const int pin;
  const output_timing_t *timing;
} output_conf_t;

#if __has_include("custom_kit.h")
#  include "custom_kit.h"
#else
static const output_conf_t outputs[NUM_OUT] = {
  [OUT_KICK]        = { .pin = 14, .timing = &kickTiming },
  [OUT_PAD_RED]     = { .pin = 23, .timing = &padTiming  },
  [OUT_PAD_YELLOW]  = { .pin = 22, .timing = &padTiming  },
  [OUT_PAD_BLUE]    = { .pin = 19, .timing = &padTiming  },
  [OUT_PAD_GREEN]   = { .pin = 18, .timing = &padTiming  },
  [OUT_CYM_YELLOW]  = { .pin = 15, .timing = &cymTiming  },
  [OUT_CYM_BLUE]    = { .pin = 16, .timing = &cymTiming  },
  [OUT_CYM_GREEN]   = { .pin = 17, .timing = &cymTiming  },
  [OUT_BUT_UP]      = { .pin =  2, .timing = &butTiming  },
  [OUT_BUT_DOWN]    = { .pin =  3, .timing = &butTiming  },
  [OUT_BUT_LEFT]    = { .pin =  4, .timing = &butTiming  },
  [OUT_BUT_RIGHT]   = { .pin =  5, .timing = &butTiming  },
  [OUT_BUT_A]       = { .pin =  6, .timing = &butTiming  },
  [OUT_BUT_B]       = { .pin =  7, .timing = &butTiming  },
  [OUT_BUT_X]       = { .pin =  8, .timing = &butTiming  },
  [OUT_BUT_Y]       = { .pin =  9, .timing = &butTiming  },
  [OUT_BUT_SHARE]   = { .pin = 10, .timing = &butTiming  },
  [OUT_BUT_HOME]    = { .pin = 11, .timing = &butTiming  },
  [OUT_BUT_OPTIONS] = { .pin = 12, .timing = &butTiming  },
};
#endif

typedef struct {
  unsigned long triggeredAt;
  bool triggered;
} output_state_t;

static output_state_t outputStates[NUM_OUT];

static const struct {
  const uint8_t hhHystLo, hhHystHi;
} input_conf = {
  .hhHystLo = 40,
  .hhHystHi = 90,
};

typedef enum {
  HH_OPEN,
  HH_CLOSED,
} hh_state_t;

static struct {
  hh_state_t hhState;
  bool hhSwitchEnable;
} input_state = {
  .hhState = HH_CLOSED,
  .hhSwitchEnable = true,
};

// this works reasonably well, but could use some refinement. maybe keep a
// buffer of recent notes instead. that way we could turn flams and such into
// R+Y hits and so on. maybe consider velocity, too. turning this into mostly
// configuration data might be nice, also.
static bool outputForNote(uint8_t note, output_t &out) {
  switch (note) {
    case 36:
      out = OUT_KICK;
      break;
    case 38:
    case 40:
      out = OUT_PAD_RED;
      break;
    case 43:
      out = OUT_PAD_GREEN;
      break;
    case 45:
      out = OUT_PAD_BLUE;
      break;
    case 26:
    case 46:
      out = !input_state.hhSwitchEnable || input_state.hhState == HH_CLOSED ? OUT_CYM_YELLOW : OUT_CYM_BLUE;
      break;
    case 48:
      out = OUT_PAD_YELLOW;
      break;
    case 49:
    case 52:
    case 55:
    case 57:
      out = OUT_CYM_GREEN;
      break;
    case 51:
    case 53:
    case 59:
      out = OUT_CYM_BLUE;
      break;
    case 41:
      input_state.hhSwitchEnable = !input_state.hhSwitchEnable;
      return false;
      break;
    default:
      return false;
  }
  return true;
}

static void writeOutput(output_t out, bool state) {
  digitalWrite(outputs[out].pin, state);
  outputStates[out].triggered = state;
}

static void noteOn(DEBP uint8_t channel, uint8_t note, DEBP uint8_t velocity) {
  DEB("%d %d %d ", channel, note, velocity);
  output_t out;
  if (!outputForNote(note, out)) {
    DEB("\n");
    return;
  }
  DEB("%s\n", outputNames[out]);

  auto io = &outputs[out];
  auto st = &outputStates[out];
  auto t = micros();
  if (t - st->triggeredAt > io->timing->hold + io->timing->holdOff) {
    writeOutput(out, HIGH);
    st->triggeredAt = t;
  }
}

static void cc(uint8_t, uint8_t control, uint8_t value) {
  if (control != 1 /* modulation wheel / HH pedal */) {
    return;
  }

  if (input_state.hhState == HH_OPEN && value >= input_conf.hhHystHi) {
    input_state.hhState = HH_CLOSED;
  }
  else if (input_state.hhState == HH_CLOSED && value <= input_conf.hhHystLo) {
    input_state.hhState = HH_OPEN;
  }
}

static USBHost usb;
static MIDIDevice_t usbMidi(usb);
static midi::MidiInterface<HardwareSerial> serialMidi(Serial1);

void setup() {
#if DEBUG
  DEB_SERIAL.begin(115200);
#endif

  for (auto out = 0; out < NUM_OUT; out++) {
    pinMode(outputs[out].pin, OUTPUT);
    writeOutput((output_t)out, LOW);
  }

  usb.begin();
  usbMidi.setHandleNoteOn(noteOn);
  usbMidi.setHandleControlChange(cc);

  serialMidi.begin(MIDI_CHANNEL_OMNI);
  serialMidi.setHandleNoteOn(noteOn);
  serialMidi.setHandleControlChange(cc);
}

static void runUsbMidiTask() {
  while (usbMidi.read()) {
    serialMidi.send(
      (midi::MidiType)usbMidi.getType(),
      usbMidi.getData1(),
      usbMidi.getData2(),
      usbMidi.getChannel()
    );
  }
}

static void runSerialMidiTask() {
  while (serialMidi.read()) {
    usbMidi.send(
      serialMidi.getType(),
      serialMidi.getData1(),
      serialMidi.getData2(),
      serialMidi.getChannel()
    );
  }
}

static void runTriggerTask() {
  auto t = micros();
  for (auto out = 0; out < NUM_OUT; out++) {
    if (outputStates[out].triggered && t - outputStates[out].triggeredAt > outputs[out].timing->hold) {
      writeOutput((output_t)out, LOW);
    }
  }
}

static Scheduler scheduler;
static Task usbTask(10, TASK_FOREVER, usb.Task, &scheduler, true);
static Task usbMidiTask(10, TASK_FOREVER, &runUsbMidiTask, &scheduler, true);
static Task serialMidiTask(10, TASK_FOREVER, &runSerialMidiTask, &scheduler, true);
static Task outputTask(10, TASK_FOREVER, &runTriggerTask, &scheduler, true);

void loop() {
  scheduler.execute();
}
