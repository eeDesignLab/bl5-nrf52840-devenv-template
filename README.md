### Description

The goal of this project is to create a skeleton of a **customised firmware development environment** for build BLE and Bluetooth 5 applications running on Nordic’s nRF52 Series SoCs family, using the GNU ARM Embedded Toolchain and the Eclipse IDE. You could use it as a template whenever you start a new BLE or Bluetooth 5 application.

Reference:  [eedesignlab.com](https://eedesignlab.com/development-environment-setup-using-nordics-nrf5-sdk-gnu-gcc-and-eclipse-ide-part-i/)



### Contents

  * **Development Tools**
    * Hardware
    * Software

  * **Installation**
    * Toolchain
    * Project
    

- **Building, Flashing and Debugging**
  - Building and Flashing using the command line
  
  - Building, Flashing and Debugging using the Eclipse IDE
  
- **Pin Out**

  

### Development Tools



##### Hardware

- One [nRF52840-DK](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-DK).

- Two standard LEDs, one green and one red.

- Two 330 Ohm resistors.

- One breadboard.

- Jumper wires.

  

##### Software

- Nordic's SDK: [nRF5_SDK_15.3.0](https://www.nordicsemi.com/Software-and-tools/Software/nRF5-SDK/Download#infotabs)

- Nordic's [nRF Command Line Tools](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Command-Line-Tools/Download): *nrfjprog* and  *mergehex*.

- Nordic's Soft Device: [SoftDevice S140](https://www.nordicsemi.com/Software-and-Tools/Software/S140)

- Toolchain: [GNU Arm Embedded](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).

  

### Installation



##### Toolchain

- Download and extract the GNU ARM Embedded (go [here](https://eedesignlab.com/2019/09/development-environment-setup-using-nordics-nrf5-sdk-gnu-gcc-and-eclipse-ide-part-i/) for help).

- For **Windows Host Machines**: Open the `gcc/Makefile.windows` file and set the location (FULL PATH) and the version of the toolchain. 

  ```bash
  GNU_INSTALL_ROOT := C:/<toolchain location>/bin/
  majorGNU_VERSION := 8.3.1
  GNU_PREFIX := arm-none-eabi
  ```

- For **Linux Host Machines**: Open the `gcc/Makefile.posix` file and set the location (FULL PATH) and the version of the toolchain. 

  ```bash
  GNU_INSTALL_ROOT := /home/<toolchain location>/bin/
  majorGNU_VERSION := 8.3.1
  GNU_PREFIX := arm-none-eabi
  ```



##### Project

* Clone the project.

* Download and extract the SDK into the project's folder.

*  Install the command line tools on **Windows Host Machines** (go [here]( https://eedesignlab.com/development-environment-setup-using-nordics-nrf5-sdk-gnu-gcc-and-eclipse-ide-part-i/ ) for help). 

  * Run the script below from the project's root folder:

  ```bash
  cd cmd-tools &&
   curl -L https://www.nordicsemi.com/-/media/Software-and-other-downloads/Desktop-software/nRF-command-line-tools/sw/Versions-10-x-x/nRF-Command-Line-Tools_10_3_0_Installer_64.exe --output nRF-Command-Line-Tools_10_3_0_Installer_64.exe &&
   ./nRF-Command-Line-Tools_10_3_0_Installer_64.exe &&
   mkdir nrfjprog mergehex &&
   cp -r C:/'Program Files'/'Nordic Semiconductor'/nrf-command-line-tools/bin/* ./nrfjprog &&
   cp -r C:/'Program Files'/'Nordic Semiconductor'/nrf-command-line-tools/bin/* ./mergehex &&
   rm -r ./nrfjprog/mer* && rm -r ./nrfjprog/headers/mer* && rm -r ./mergehex/nrf* &&
   rm -r ./mergehex/headers/nr* && rm -r ./mergehex/headers/jlink* && rm -rf nRF* &&  
   cd ..
  ```

- Install the command line tools on **Linux Host Machines** (go [here]( https://eedesignlab.com/development-environment-setup-using-nordics-nrf5-sdk-gnu-gcc-and-eclipse-ide-part-i/ ) for help). 
  - Run the script below from the project's root folder:

  ```bash
  cd cmd-tools &&
   curl -L https://www.nordicsemi.com/-/media/Software-and-other-downloads/Desktop-software/nRF-command-line-tools/sw/Versions-10-x-x/nRFCommandLineTools1030Linuxamd64tar.gz --output nRFCommandLineTools1030Linuxamd64tar.gz &&
   tar -xzvf nRFCommandLineTools1030Linuxamd64tar.gz &&
   tar -xzvf nRF-Command-Line-Tools_10_3_0_Linux-amd64.tar.gz &&
   sudo apt install ./JLink_Linux_V644e_x86_64.deb &&
   rm -rf nRF* && rm JL* && rm R* &&  
   cd ..
  ```

  

### Building, Flashing and Debugging



##### Building and Flashing using the command line
* Run `make help` to show the available targets.

  

##### Building, Flashing and Debugging using the Eclipse IDE

- Go [here](https://eedesignlab.com/ble-and-bluetooth-5-with-nordics-nrf5-sdk-gnu-arm-embedded-and-eclipse-ide-part-2/) for setting up the Eclipse IDE for building, flashing and debugging the project.



### Pin Out

| nRF52840-DK Pin | External LEDs |
| --------------- | ------------- |
| P1.10           | Green         |
| P1.11           | Red           |

