# smart-pill-dispenser
# Arduino Smart Pill Dispenser
Rehabilitation Engineering • Final Project 

Arduino-based smart pill dispenser designed to improve medication adherence through automated dispensing and multimodal reminders.

---

## Features
- Automated pill dispensing using a servo motor  
- Audio reminders using DFPlayer Mini (MP3 playback)  
- Visual alerts using LED and LCD display  
- User acknowledgment via push button  
- Escalation alert if medication is not taken within 5 seconds  

---

## System Workflow
1. Plays initial reminder audio (0001.mp3)  
2. Displays message on LCD  
3. Dispenses medication via servo  
4. Plays secondary alert (0002.mp3) and activates LED blinking  
5. Waits 5 seconds for user input  
6. If no response → plays escalation alert (0003.mp3)  

---

## Hardware Components
- Arduino Uno R4 Minima  
- Servo motor  
- DFPlayer Mini + speaker  
- I2C LCD display  
- Illuminated arcade push button  
- Breadboard + jumper wires  
- **3D-printed pill dispenser mechanism**  

---

## Future Improvements
- Address the current limitation where the servo does not consistently rotate the pill carousel by implementing a more secure mechanical linkage (e.g., rigid hub, gear system, or higher-torque servo)  
- Add real-time clock (RTC) for scheduled dispensing  
- Improve mechanical coupling for precise compartment indexing  
- Refine the 3D-printed design for better alignment and durability  
- Add mobile notifications or connectivity features  

---

## Audio Notes
The initial reminder audio (0001.mp3) is a short snippet from the song *"How We'll Remind You"* by Lewberger, used for demonstration purposes in this prototype.  

This project is not affiliated with or endorsed by Lewberger.
