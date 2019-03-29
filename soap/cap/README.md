# CAP XML creation
This functionality was originally intended for use in the transition
process from the JSON provided by the AOI front-end to the CAP XML
format required by the CADG for later conversion to CMAC. In addition,
the intent was to use the functionality found here to replace the then
inoperative features of the gSOAP library. Since that time, the
necessary gSOAP features are now implemented into the project.

However, the functionality found here remains as a backup solution should
gSOAP give the next development team the same insurmountable obstacles
the original development team faced. It is roughly 90% complete, and
primarily needs a number of odd compilation errors corrected. It requires
the use of an Alert object found (at the time of this writing) in the
rest-server/src/model directory. Please note, the functionality here
assumes that the provided Alert object data is already validated as
correct. Providing unvalidated data will result in unforeseen outcomes.

To run this code:
1. cd into soap/cap
2. Use "sudo g++-8 -std=c++17 -o capTest cap.cpp" (Minus the quotes)
3. Use "./capTest" (Minus the quotes)