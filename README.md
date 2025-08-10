# ESP32-4Wheel-Robot-with-PS4-Remote-Control
Hi guys!, I’ve been trying to use a PS4 controller (factory original) with the PS4 Controller Library by Juan Pablo. I tried, but it didn’t work for me. Then I looked into other libraries and found **Bluepad32**, so this is for those of you who have the same problem as me, using a factory original PS4 controller instead of a machine original one.
This project implements a robot control system using ESP32 and four motors. It uses the **Bluepad32** library to connect and read inputs from a PS4 controller. The robot moves forward, backward, turns smoothly, and spins in place based on joystick and button inputs. Motor speeds are controlled via PWM with calibration for balanced movement.

## Requirements
- ESP32 development board
- 4 DC motors
- 4 wheels
- 2 L298N motor drivers
- Robot chassis (compatible with 4 motors)
- Power source (e.g., LiPo Battery, Li-ion battery, or 6x AA batteries)
- Jumper wires (male-to-male and male-to-female)
- Breadboard or PCB (optional, for wiring)

## License
This project is licensed under the MIT License. See the [MIT License](https://choosealicense.com/licenses/mit/).

## Notes
It's recommended to change the IP address in **Sixaxis** first, because it can connect to everywhere if you don't change it (match it with your ESP32).

## Tags
[![ESP32](https://img.shields.io/badge/ESP32-0078D7?style=flat&logo=espressif&logoColor=white)](https://github.com/search?q=ESP32) [![PS4 Controller](https://img.shields.io/badge/PS4_Controller-003791?style=flat&logo=playstation&logoColor=white)](https://github.com/search?q=PS4+Controller) [![Bluepad32](https://img.shields.io/badge/Bluepad32-00C853?style=flat)](https://github.com/search?q=Bluepad32) [![Robot Car](https://img.shields.io/badge/Robot_Car-9C27B0?style=flat)](https://github.com/search?q=Robot+Car) [![L298N](https://img.shields.io/badge/L298N_Driver-4CAF50?style=flat)](https://github.com/search?q=L298N) [![PWM Control](https://img.shields.io/badge/PWM_Control-2196F3?style=flat)](https://github.com/search?q=PWM+Control)

