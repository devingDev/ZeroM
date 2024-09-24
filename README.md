# ZeroM - Minecraft (PSVita Edition) presented by coderx3(aka Bizzy/Magus)

A Minecraft (PSVita Edition) plugin that will hopefully act like a mod loader

## Description

An experiment basically for now. Eventually might expand on it.


Probably have to do it for each version or have people use only one version.


## Getting Started

IMPORTANT: You might need to install ioplus.skprx first!!!

### Simple Install
Add in config.txt under your minecraft title id, this is for europe:

*PCSB00560
ur0:tai/ZeroM.suprx

### Usage
[L] + [Select] : toggle menu
Arrow keys : move in the menu
[X]/[O] : enter/back, depending on your setting(jp?) 
[L]/[R] : switch tabs

### Installing (more in-depth)

IMPORTANT: You will need to install ioplus first!!!


There are two types of installation:

[A] Simple install
or
[B] PluginReload install

Choose one and use your own paths (for example if you use ux0:/tai/ instead of ur0:/tai/)

#### [A] Simple install
0. Download the latest release
1. Place only ZeroM.suprx in ur0:/tai/ 
2. Add these lines in your ur0:/tai/config.txt
```
*PCSB00560
ur0:tai/ZeroM.suprx
``` 


#### [B] PluginReload install
0. Download the latest release
1. Place ZeroM.suprx in ur0:/tai/ 
2. Place PluginReload.suprx in ur0:/tai/ 
3. Add these lines in your ur0:/tai/config.txt
```
*PCSB00560
ur0:tai/PluginReload.suprx
``` 


### Running

* It should start as you launch Minecraft.
* ReloadPlugin works via key combo (currently it is Circle+LTrigger)
* to see outputs you need something like CatLog or similiar


## Building

### Dependencies

* [vitasdk](https://github.com/vitasdk/vdpm)
* (Optional) [lftp](https://lftp.yar.ru/)


### Steps

Run one of the scripts (the suprx will be in ZeroM-base/build/).

"zerom_build.sh" : main script, builds ZeroM.suprx

"run_zerom_all.sh" : builds ZeroM and then uploads it to the PSVita and listens via nc

"do_it_all.sh" : additionally also compiles PluginReload

Just look inside them, they are rather simple.

## Help

Use the issues page for problems

[ZeroM Discord Invite](https://discord.gg/GJAhrUsAeg) if you want to contact me on Discord.
