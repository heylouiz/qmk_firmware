# Microcontroller configurations (Pro micro)
MCU = atmega32u4
F_CPU = 16000000
ARCH = AVR8
F_USB = $(F_CPU)
OPT_DEFS += -DINTERRUPT_CONTROL_ENDPOINT

# I needed to change this to caterina in order make it work on the promicro
BOOTLOADER = caterina

# Configuração de funcionalidades do teclado
# Coloque `yes` na frente da configuração para habilitar e `no` para desabilitar
MOUSEKEY_ENABLE = yes       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
NKRO_ENABLE = yes            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.
OLED_DRIVER_ENABLE = yes
RAW_ENABLE = yes
TAP_DANCE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
API_SYSEX_ENABLE = no
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

LAYOUTS = ortho_4x3
