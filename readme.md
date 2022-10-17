# cyberWatch

Simple OS for [LILYGO® T-WATCH-2020 V3](http://www.lilygo.cn/prod_view.aspx?TypeId=50053&Id=1380&FId=t3:50053:3), based on [ Xinyuan-LilyGO /TTGO_TWatch_Library](https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library). Partially support for LILYGO® T-WATCH-2020 V2

Free time project to create lightweight and simple OS for smartwatch, with only necessary small functionality (to keep it simple and effective). With strong DIY cyberpunk motivation (don't want to support and pay money to big corporations). And with cool 80' cyberpunk retro design!

![license](https://img.shields.io/github/license/spaceangel/cyberwatch?style=for-the-badge)
![Last commit](https://img.shields.io/github/last-commit/spaceangel/cyberwatch?style=for-the-badge)
![activity](https://img.shields.io/github/commit-activity/m/spaceangel/cyberwatch?style=for-the-badge)
![github stars](https://img.shields.io/github/stars/spaceangel/cyberwatch?style=for-the-badge)

<a href="https://www.buymeacoffee.com/spaceangel" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>


## Installation

 - download and install [VS Code](https://code.visualstudio.com/download) and [PlatformIO](https://platformio.org/install/ide?install=vscode) (or any other C/C++ IDE)
    - (use complex IDE; this project is too large fro Arduino IDE)
 - ~~clone~~ download this repository
 - add [TTGO library](https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library) to the project, following instructions in library's readme
 - connect [LillyGo T_Watch device](http://www.lilygo.cn/prod_view.aspx?TypeId=50053&Id=1380&FId=t3:50053:3) via USB
 - compile and upload via your favorite IDE
 - __have a fun!__

## Code quality & standards
 - [Misra C++ standards](https://www.misra.org.uk/) (98% and still improving)

## Features

 - cool splashscreen and exit screen :-)
 - battery consumption saving
   - turn off display after 5 seconds of inactivity
   - use cpu light sleep mode cycles (100ms) in main loop
   - turn off unused subcomponents (WI-FI chip)
   - set CPU frequency to 20MHz
   - activate by:
     - touching display
     - short press button
     - "tilt up" maneuver (can be turn off on settings screen)
 - vibration can be disabled in settings screen
 - possibility of enabled "display always on" to show cool clockfaces
 - warns (vibrate, turn display on) when battery reach low levels(30% / 20%)
 - when screen goes sleep, always set to default datetimeapp (with previously selected face)
 - when screens wakeup by touch / PEKshort, is locked to prevent "accidentaly wakeup", could be unlocked by PEKshort
 - shows current time
 - shows current date
 - multiple clock faces - change by swipe vertical on datetime "miniapp"
 - shows battery status
 - step counter
 - horizontal swipe - switching between mainPanel components/miniapps
 - vertical swipe - control components
 - calendar with prev/next month feature
 - simple stop watch
 - for full list of features, see [changelog.txt](changelog.txt)
 - synchronize date & time with computer during compile/upload

## Known bugs
 - "tilt up" maneuver sometimes doesn't activate display (maybe will be solved by tuning BMA423 sensor)
 - activated by touch (when display is off) also do "touch event" on component on touch coords (e.g. when current screen is watch settings, activation also can activated display on, when display activation touch is at left top corner of display )

## Future features :-)
 - alarm
 - conection vith phone via BT (require app for android)
   - SMS notification icon
   - missed call icon
   - other notifications icon
   - show who's calling
     - ability to reject call
   - show SMS content (and mark as read in phone)
   - show notifications (and mark as read)
 - __many many more__

## Contact

Feel free to contact me via email (spaceangel@cyberdeck.cz ) if you need some help, want to participate or support me :-)
