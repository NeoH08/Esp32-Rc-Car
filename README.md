# Esp32-Rc-Car
Esp32 RC Car

A 3-wheel RC car controlled over WiFi. I built this from scratch over a summer with no prior coding or embedded systems experience, teaching myself C++ and Python along the way.

What it does

The car runs on an ESP32 and uses a TB6612 motor driver to control the motors. A Python script on my laptop acts as the remote, sending throttle and steering commands over WiFi. Steering is handled with a single turning wheel on a swivel caster instead of a full differential setup.

A video of it driving is in the repo (see the file with the video link).

Problems I ran into

The WiFi kept disconnecting whenever I accelerated. It turned out the motors were pulling enough current under load to cause a voltage drop that the ESP32 couldn't handle, not a code issue like I originally assumed. Fixing the power distribution solved it.

Steering was another big one. I went through a few different chassis builds, including switching from 4 wheels to 3, before landing on a setup that actually turned reliably.

Weight distribution mattered more than I expected too. Moving the battery around changed how the car handled noticeably.

Most of the debugging came down to figuring out whether an issue was wiring or code, which took a while to get good at, including learning things like proper common grounding along the way.

##Files

-version5.ino, the firmware running on the ESP32
-remote4.py, the Python remote control script
-Photos of the car (top and side view)
-Video link file

##Built with

Arduino IDE, Python, and Wokwi for simulating the circuit before building it for real.
