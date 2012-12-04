BlendUp
=======

Derivate from reaDIYmate pusher example. Connects to a WiFi signal (status Led Green when connected, Red if not) and wait for a pusher.com message to switch On or off a relay (status led orange when receiving pusher message).

To be able to build and upload this sketch to a reaDIYmate board:
 * Add avr-libraries from https://github.com/reaDIYmate to your Arduino libraries
 * Download and add SdFat lib to your Arduino "libraries" directory
 * From https://github.com/reaDIYmate/avr-arduino add content of 'cores' and 'variants' to /Applications/Arduino.app/Contents/Resources/Java/hardware/arduino and from boards.txt get reaDIYmate board profile and add it to your boards.txt 