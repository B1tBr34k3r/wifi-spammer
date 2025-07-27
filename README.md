# 📡 ESP8266 WiFi Spammer

> A lightweight WiFi beacon spammer for the ESP8266 (NodeMCU / D1 Mini) — blasts fake SSIDs and random MACs around you 🚀

## ⚠️ Disclaimer

This project is **for educational and testing purposes only**.  
Do NOT use it to prank or disrupt real networks. That’s illegal in many places. You’re responsible for what you do with it.

---

## 💡 What It Does

- Sends out **random SSIDs** that appear in nearby WiFi scans
- Spoofs **random MAC addresses** for each broadcast
- Can broadcast **multiple SSIDs per second**
- Works on any ESP8266 board (NodeMCU, Wemos D1 Mini, etc.)

---

## 🔧 Requirements

- ESP8266 board (NodeMCU, Wemos D1 Mini, etc.)
- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP8266 board manager](https://github.com/esp8266/Arduino)
- Micro USB cable
- Some patience 🔌

---

## 🚀 Installation

1. Open Arduino IDE
2. Install ESP8266 board support via Board Manager
3. Clone or download this repo
4. Open `spammer.ino`
5. Select your board & COM port:
   - Tools → Board: “NodeMCU 1.0 (ESP-12E Module)” or similar
   - Tools → Port: whatever your ESP shows up as
6. Upload and you’re good to go ✨

##❓ FAQ

Q: Will this crash WiFi networks?
A: No. It only sends out fake beacons. It doesn’t jam or attack real WiFi.

Q: Why can’t I see all SSIDs on my phone?
A: Phones filter out duplicates & sketchy beacons. Try scanning with apps like WiFiAnalyzer.

Q: Is it legal?
A: In most places, spamming SSIDs isn’t allowed outside of controlled environments (like testing labs). Use responsibly.

##🙏 Credits
Inspired by ESP8266 Deauther

You, for not bricking your device

##📜 License
MIT — free to remix, but don’t be a jerk with it.
