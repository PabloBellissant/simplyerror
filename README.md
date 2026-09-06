# Simply Error

A simple C library, for cascade logging errors

![example](https://github.com/PabloBellissant/simplyerror/blob/main/assets/example.png "Error logging example")

Usage :
- REGISTER_ERROR("format", ...) -> Register an error
- REGISTER_USER_ERROR("format", ...) -> Register an error that the user can see, even if NDEGUG is defined.

- CHECK_ERROR(expr, ...) -> Register an error if expr == 0, then return -1.
- CHECK_USER_ERROR(expr, ...) -> Register an error that the user can see if expr == 0, then return -1.

Example :
```c

int init(const char *file_name)
{
  int fd = open(file_name, O_RDONLY);
  CHECK_ERROR(fd == -1, "Failed to open input file %s", file_name);
  ...
  return (0);
}

int main(void)
{
  const char *file = "rabbit.obj";
  if (init(file) == -1)
  {
    REGISTER_ERROR("Init error");
    return (-1);
  }
  ...
  return (0);
}
```
Will produce :
![example 2](https://github.com/PabloBellissant/simplyerror/blob/main/assets/example2.png "Error logging example 2")

The library use the non-standard on_exit() function, to avoid any init/destroy function call from main. You only need to use REGISTER_ERROR.
made by [@PabloBellissant](https://github.com/PabloBellissant)
