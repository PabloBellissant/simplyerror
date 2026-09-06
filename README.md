# Simply Error

A simple C library, for cascade logging errors

![alt text](https://github.com/PabloBellissant/simplyerror/blob/main/assets/example.png "Error logging example")

Usage :
- REGISTER_ERROR("format", ...) -> Register an error
- REGISTER_USER_ERROR("format", ...) -> Register an error that the user can see, even if NDEGUG is defined.

The library use the non-standard on_exit() function, to avoid any init/destroy function call from main. You only need to use REGISTER_ERROR.
