# ContextMenuNormalizer

In Windows 10 version 1903 Microsoft changed File Explorer immersive context menus highlight color from gray to white, making it very difficult to see.

This little tool runs at startup for a few milliseconds without need in adminstrator rights and patches the color in-memory, returning the look that was from version 1507 to 1809.

The distribution which can be downloaded from [Releases](https://github.com/krlvm/ContextMenuNormalizer/releases) includes batch files, which can be used for automatic installation and registering for running at startup.

Before:
![Before](https://github.com/krlvm/ContextMenuNormalizer/blob/master/.screenshots/before.png?raw=true)

After:
![After](https://github.com/krlvm/ContextMenuNormalizer/blob/master/.screenshots/after.png?raw=true)