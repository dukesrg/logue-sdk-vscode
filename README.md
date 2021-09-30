# logue-sdk-vscode
Visual Studio Code template project for logue-sdk.

Contains predefined debug profiles for different ST-LINK and J-Link debug interfaces.
Build system is based on my fork of logue-sdk, but can be easily retargeted to vanilla logue-sdk repository.

### Project structure

* [.vscode/](.vscode/) : Visual Studio Code workspace configuration files.
* [inc/fxwrapper.h](inc/fxwrapper.h) : FX wrapper that allows creating all effect types from one source file.
* [lodue-sdk/](logue-sdk/) : My own logue-sdk fork with optimized Makefiles, and reduced project footprint.
* [src/](src/) : Effects and oscillator source file templates.
* [Template-delfx/](Template-delfx/) : Delay FX project template.
* [Template-osc/](Template-osc/) : Oscillator project template.
* [Template-modfx/](Template-modfx/) : Mod FX project template.
* [Template-revfx/](Template-revfx/) : Replay FX project template.
* [Makefile](Makefile) : Common Makefile for all projects.
* [unit.mk](unit.mk) : Per-project makefile wrapper.

### Setup
Follow logue-sdk initialization procedure described in the corresponding documentation.
In order to perform automated unit load and selection you need to install [logue-cli](logue-sdk/tools/logue-cli) from logue-sdk and [SendMIDI](https://github.com/gbevin/SendMIDI) and make sure to put them somewhere accessible with PATH variable.
For dumping option both [SendMIDI](https://github.com/gbevin/SendMIDI) and [ReceiveMIDI](https://github.com/gbevin/ReceiveMIDI) are required to be installed.
Open folder in VSCode, then you will be proposed to download dependent plugins, which is stated in [extensions.json](.vscode/extensions.json)

### Build options
* Build all : build all units in all supported synth variants.
* Build minilogue XD units : build all units for minilogue XD only.
* Build NTS-1 units : build all units for NTS-1 only.
* Build prologue units : build all units for prologue only.
* Clean all : delete all intermediat build files and unit files.
* Load unit : load selected unit to the last slot of the compatible synth and select it.
* Dump all units : download all units from the first connected synth.
* Update SVD files : download System View Description files which is needed for debug on the real synth.

### Debugging
* Run Update SVD files (only needed for the first time)
* Connect synth with USB port.
* Connect to one of the synth's SWD interfaces with the supported USB-dongle, like ST-LINK or J-Link (refer to [Cortex Debug](https://github.com/Marus/cortex-debug) plugin).
* Build target unit with one of the *Build \** tasks
* Load and select the unit on the synth either manually or by selecting the *\*.\*unit* file and running *Load unit* task.
* Select the *.elf* file inside of the *build* directory of the unit.
* Activate *Run and Debug* tab.
* From the *Run and Debug* dropdown list select the option, which is suitable for the unit type, synth model and debugger option.

### Credits
* [tokuhira](https://github.com/tokuhira) for debug options clarification.
