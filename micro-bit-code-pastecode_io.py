
pins.analog_set_pitch_pin(AnalogPin.P2)

def on_forever():
  if pins.digital_read_pin(DigitalPin.P0) == 0:
    basic.show_leds("""
      . . . . #
      . . . # #
      # . # # .
      # # # . .
      . # . . .
      """)
  else:
    basic.show_leds("""
      . . # . .
      . . # . .
      . . # . .
      . . . . .
      . . # . .
      """)
    for index in range(5):
      pins.analog_pitch(440, 200)
      basic.pause(100)
  if pins.digital_read_pin(DigitalPin.P1) == 1:
    while True:
      basic.show_leds("""
        . . . . .
        . # . # .
        . . . . .
        # . . . #
        . # # # .
        """)

basic.forever(on_forever)
