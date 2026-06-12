# Pebble Watchface Template

<img width="297" height="334" alt="image" src="https://github.com/user-attachments/assets/486094cb-a82c-4e69-a0a4-83c4e52f4bee" />

Pebble watchface template based on the official Pebble guidelines. The project
uses the Pebble SDK, a native C watchface, PebbleKit JS for phone-side services,
and Clay for user configuration.

## Features

- Native Pebble watchface entry point with modular C services.
- Time and date display with configurable date visibility.
- Battery indicator.
- Bluetooth connection indicator.
- Weather display powered by phone location and Open-Meteo.
- Clay configuration page for background color, text color, temperature unit,
  and date visibility.
- Bundled Pixelify Sans fonts and Bluetooth icon resource.
- Targets classic and modern Pebble platforms: aplite, basalt, chalk, diorite,
  emery, flint, and gabbro.

## Requirements

- Pebble SDK 3 compatible toolchain.
- A paired phone or Pebble emulator for installation and testing.

## Setup

Build the watchface:

```sh
pebble build
```

Install on an emulator:

```sh
pebble install --emulator emery
```

Install on a paired phone:

```sh
pebble install --phone <ip>
```

## Project Layout

```text
src/c/                         Native watchface source
src/c/modules/app_message/    AppMessage setup and handlers
src/c/modules/battery/        Battery indicator service
src/c/modules/bluetooth/      Bluetooth indicator service
src/c/modules/time/           Time and date service
src/c/modules/timeline_peek/  Timeline peek service
src/c/modules/weather/        Weather display service
src/c/settings/                Clay settings persistence and UI updates
src/pkjs/                      PebbleKit JS and Clay configuration
resources/fonts/               Bundled watchface fonts
resources/images/              Bundled bitmap assets
package.json                   Pebble app metadata, resources, and message keys
wscript                        Pebble SDK build rules
```

## Customization

- Update app metadata, UUID, target platforms, capabilities, message keys, and
  resource declarations in `package.json`.
- Change layout and native service composition in `src/c/main_window.c`.
- Adjust settings defaults and display updates in
  `src/c/settings/clay_settings.c`.
- Edit the Clay configuration form in `src/pkjs/config.js`.
- Replace or add bundled assets under `resources/`.

## Documentation

Pebble/Rebble SDK documentation: <https://developer.repebble.com>
