# DecorGrid

This is an Arduino project for drawing to a decorative grid of pixels.

## Notes

- This project expects to see a file called `arduino_secrets.h` in the working directory, which should contain the following:
  + `#define SECRET_SSID ""` where the quotes contain your local ssid (internet id)
  + `#define SECRET_PASS ""` where the quotes contain the internet password
- The `arduino_secrets.h` file must never be commited (since it may contain sensitive information)
