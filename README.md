# ELEC3020-Group32-Project
//first try at navigating menu with 4 push buttons, game selection and "moving_block" simple game
//Issue with screen calibration, i.e. the coordinate (0,0) is not consistently in top left corner as expected -> likely to do with vga.show() usage or the vga mode.h header file having wrong vga values (hsync, hporch etc.)
//Issue with unresponsive buttons, often program will take a few moments to reboot before buttons can be used

//Next steps are to fix screen calibration, this will allow for better graphics to be printed and then more complex games
//Next steps is changing push button controller to wireless controller
