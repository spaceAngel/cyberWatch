# cyberWatch

Simple OS for [LILYGO® T-WATCH-2020 V3](http://www.lilygo.cn/prod_view.aspx?TypeId=50053&Id=1380&FId=t3:50053:3), based on [ Xinyuan-LilyGO /TTGO_TWatch_Library](https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library). 

Free time project to create lightweight and simple OS for smartwatch, with only necessary small functionality (to keep it simple and effective). With strong DIY cyberpunk motivation (don't want to support and pay money to big corporations). And with cool 80' cyberpunk retro design!

## Installation

 - download and install [Arduino IDE 2](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing)
 - ~~clone~~ download this repository
 - add [TTGO library](https://github.com/Xinyuan-LilyGO/TTGO_TWatch_Library) to sketch, following instructions in library's readme
 - connect [LillyGo T_Watch device](http://www.lilygo.cn/prod_view.aspx?TypeId=50053&Id=1380&FId=t3:50053:3) via USB
 - compile and upload via Arduino IDE 2 (*Sketch* -> *Upload*)
 - __have a fun!__
 
## Features
 
 - cool splashscreen :-)
 - battery consumption saving
   - turn off display(adjust 0 + display sleep) and sleep processor(esp light sleep mode) after 5 seconds of inactivity
   - turn off unused subcomponents (WI-FI chip)
 - shows current time
 - shows current date
 - shows battery status
 - step counter
 - for full list of features, see [changelog.txt](changelog.txt)
 
## Future features :-)
 - alarm
 - simple calendar
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
