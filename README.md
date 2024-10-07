# ELEC3020-Group32-Project
This folder has all code needed in console for playing "Pong" and "moving block"
Has a tft display on console but needs to be fixed to prevent flicker (easy to do, just have tft.draw functions everytime there is a vga.show call)
Has controller of 4 buttons controlling pins, can easily be changed to wireless controller

To-do:
Memory implementation
Add another game and remove placeholders "game1" and "game2"
Fix flickering when changing whole screen - adjust buffer.count=1 to buffer.count=2, or draw_menu() function
Audio implementation
