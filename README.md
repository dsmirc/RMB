# RMB
Mouse Panning for Ryujinx(https://ryujinx.org/).<br/>
It's a simple learning project. I wanted to use my mouse and change the camera view position but Ryujinx doesn't support this yet, you have to use third-party software to achieve it.<br/>
In short, this lets you use your mouse to change the in-game camera view position for some games.<br/>
**_For some games?_**<br/>
Well, if your desired game changes its camera view position according to your right-stick/left-stick/d-pad input and if you've bound these inputs with your keyboard then this can help you.

# Requirements
Just be able to run Ryujinx and for now this only works for Windows and Linux(X11 Window Manager).
But the code structure was designed to work on all the platforms Ryujinx supports, only needs to support native API(s) for specific platforms.

# How to configure?
It simulates keypress of your keyboard according to the mouse position.<br/>
**_What does it mean by simulate key press?_**<br/>
If you've bound the right-stick(Or the stick which changes the camera) inputs with your keyboard eg. the default Ryujinx input configuration binds the right-stick inputs like this:<br/>
![image](https://i.ibb.co/CbptV6w/image.png)<br/>
then after enabling mouse panning<br/>
it will send **_I_** keypress to Ryujinx if you move your mouse cursor **UP**,<br/>
**_K_** if you move **DOWN** and so on.<br/>
If you've changed these keys in Ryujinx make sure you also change those in RMB's configuration just click on the **Configure Input** and change accordingly.<br/>
![image](https://i.ibb.co/r4Qjnyr/image.png)<br/>

You can change the **_Sensitivity_** and **_Camera Update Time_** to adjust your needs.

# Disclaimer
This is a simple learning project so, things might get broken. Since it simulates key presses according to the mouse position, you might feel the camera movement is a bit choppy and weird/wrong. And since this simulates keypresses, you should close(recommended) or hide/minimize other applications.<br/><br/>
**_Make sure Ryujinx is running, focused, and is in the center of your screen before enabling mouse panning._**<br/>
**_Default Panning Toggle Hotkey is Ctrl+F9 if any other application uses the same hotkey it will fail so make sure to choose a unique hotkey or just close other applications._**

# How does this work?
1. It uses [GLFW](https://www.glfw.org/) and [ImGui](https://github.com/ocornut/imgui) for the UI part. It directly calls Native functions to handle keyboard and mouse events.
2. It always sets the mouse position to the center of the screen and if the user moves the mouse then it calculates which direction it was moved from the center of the screen and simulates key presses.

# Dependencies
* [GLFW 3.3+](https://github.com/glfw/glfw/) for windows/Linux a custom build was placed in this repo.
* [ImGui](https://github.com/ocornut/imgui) For simple or more like lazy UI.

# How to Build
* Windows: 
  - Visual Studio 2019+ with `Desktop development with C++` components installed should be able to build this. (Yes, no need to manually link ImGui and GLFW libs).
* Linux:
  - Install libx11, mesa and libxtst libs on your Linux machine.
    - On Debian/Ubuntu based Linux distros run `sudo apt install libx11-dev mesa-common-dev libxtst-dev`.
    - On Arch Linux based Linux distros run `sudo pacman -Syu base-devel libx11 mesa libxtst`.
  - After installing these libs simply run `make` on the directory.
* For other OSs/Platforms you need to implement all these stuff listed [here](#for-other-platforms). You also going to need GLFW 3.3+ lib for the corresponding platform/os.

# For Other Platforms
1. First you need to implement a global hotkey listener, for windows, a dummy window is created and `RegisterHotKey` API is used to register the hotkeys for that window and listened to `WM_HOTKEY` messages on that window. `XGrabKey` is used for X11 window manager.
2. Then you need to implement how to simulate the key presses on the corresponding OS, for windows `SendInput` was enough. For X11 wm `XTestFakeKeyEvent` API was used.
3. You now need to implement how to get the cursor position, for Windows `GetCursorPos` and for X11 wm `XQueryPointer` API(s) was used.
4. After that you need to implement how to set your cursor position, for Windows `SetCursorPos` API was used, same effect can be done by using `SendInput`. For X11 wm `XWarpPointer` did the job.
5. (Optional) If you want to hide your cursor during panning mode you need to actually change the cursor image file your system currently using, for Windows `SetSystemCursor` API is used. For X11 wm simple `XFixesHideCursor`/`XFixesShowCursor` API(s) did the job.
6. (Optional) If you want to automatically focus Ryujinx after entering panning mode then again you need to use some native API(s), for windows `SetForegroundWindow` API was used and for X11 wm `XSendEvent` was able to help. On both platforms you have to check all the visible windows and you can either check their class name/title name to select your target processs and send Focus/Active action.

Check `native.h` a simple interface that was used as a bridge to call these native API(s).<br/>
Use this as a base class for your specific OS implementation.

# FIN
Again this was a learning project, if anyone wants to help me improve I would really appreciate it. If you find any bugs or issues let me know by opening an issue. Feel free to pull any request. Thank you for your time.<br/>

You can download binaries for Windows and Linux from [releases](https://github.com/IamSanjid/RMB/releases/).

# Demo

https://user-images.githubusercontent.com/38256064/158840429-af35e4d8-bb21-4f9f-9e72-05ce3122eaf1.mp4


https://user-images.githubusercontent.com/38256064/158946691-4524f27a-d7b9-4cbc-9777-d4bc4719b939.mp4

