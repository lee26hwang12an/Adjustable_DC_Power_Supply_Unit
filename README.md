# ADJUSTABLE DC POWER SUPPLY UNIT
*My special thanks to my friend, my colleague, Trần Ngọc Duy (Lý Hoàng Duy), without whose support I couldn't have managed this project. I would also like to express my gratitude towards my colleague, my master, [Mr. Nghĩa](https://github.com/nghiank97) at Apicoo Robotics for his unparalleled knowledge of various communication systems. Thank you all for your contribution and dedication.*

***IN PROGRESS***

#
## ABOUT
<div align="justify">
As an electronics and prototyping hobbyist, the need for a power supply unit of a wide range of voltages and amperes yields that either I purchased a pre-built DC power supply, or hook up some buck-boost circuitries to a fixed one. Through market research and online shopping malls surveys, I came to the realization that pre-built DC PSUs are either too expensive or have very limited range of output. Hooking up a buck-boost converter to a fixed voltage PSU is a primitive idea yet surprisingly efficient in terms of price/performance. However, the hassle of having to get finicky with a screw driver and multimeter when manually adjusting the converter is loosely a deal breaker for this idea.

######
So I headed out to one of my friends, Trần Ngọc Duy, and was suggested a buck converter with adjusting knobs and LCD screen that could display current and set parameters. The buck converter <b><i>XY-6014</i></b> was designed for CNC machinery applications, but could be fitted to serve virtually any systems. And that was what I went for.
######
Then came the part of designing a case that provides housing for the components. The PSU is made up of a 36V DC unit, the buck converter mentioned above, an AC power inlet, a microcontroller that can read serial data from the buck converter, and write certain effects to an LED strip that I mounted underneath the PSU, mainly for aesthetic purposes.
</div>

<div align="center"><img src="_assets/PSU_1.jfif" alt="Darstellar PSU" width="1000"/></div>

#
## COMPONENTS
- x1 36V-10A AC-DC Power Supply Unit
- x1 XY-6014 Buck Converter
- x1 5V Regulator
- x1 STM32F103C6T6A MCU
- x17 WS2812B RGB LED
- x2 (Manufactured) 310mm x 210mm x 3mm Aluminum Plates
- x1 (Manufactured) 310mm x 210mm x 3mm Black Acrylic Panel
- x3 (Manufactured) PETG Housing Parts
- x1 AC Inlet with Switch
- x1 AC Cable

#
## MECHANICAL DESIGN
<div align="justify">
The case parts for the PSU were designed in Solidworks. Initially I aimed to 3D print them all entirely, with hope that certain geometrically creative designs could be implemented. I took some references online on Pinterest and Google, looking for innovative concepts, and have stumbled upon various designs by incredible people.
</div>

######
<div align="center"><img src="_assets/ref_board.png" alt="Design References" width="1000"/></div>

######
<div align="justify">
But then I asked myself the question: Do I want it to look good? Or do I want it to also feel good to the touch? And not to mention the aspect of ergonomic and friendly design. Now with reprap (3D printing), I could have manufactured virtually any shapes and forms, but it wouldn't be able to rival the quality by CNC machining, and touching plastic would feel somewhat cheaper than touching, say, aluminum or glass. So after some considerations, I decided that my prototype must have non-industrial design, meaning that it must look like it belongs to a consumer's house, on a desk, not in a factory, and the corners should be rounded (I hate sharp corners). Furthermore, it should have certain parts where touching gives a sense of high quality and finish. In the end, I arrived at the design shown below:
</div>

######
<div align="center"><img src="_assets/final_cad.png" alt="Final Design" width="1000"/></div>

######
<div align="justify">
For manufacturing, every parts with complex form such as the side walls, the buck and AC-DC mounts were 3D printed using PETG filament. I especially increased the infill density to around 25% to achieve a tougher result. The top and bottom panels were of aluminum material, and were made by ordering local laser cutting shops in my region.
</div>

######
<div align="center"><img src="_assets/manufacturing_brief.png" alt="Manufacture Files" width="1000"/></div>

#####
And finally, the prototype: (Please excuse the cables, it was still in development the moment I took the pictures)

######
<div align="center"><img src="_assets/prototype.png" alt="Final Product" width="1000"/></div>

#
## MODBUSRTU AND WS2812B FIRMWARE
<div align="justify">
Okay, I know what you're thinking, what does Modbus RTU have to do with this amature PSU, and why even bother adding LEDs? Well, first, I like LEDs and making colors. Second, I like to make consumers-targetted products, so appearance definitely matters. Third, screw you all who say Functionalities over Aesthetics. Aesthetics is the key force that drives functionalities forward. Think of a Ford car at the very beginning of the automobile age, then think of any modern day cars: If they didn't want to imporve on the aesthetic aspect, why would you need complex CAN and LIN buses inside a thing made purely for traveling and not for entertaining or showing off purposes? I'm not saying Aesthetics over Functionalities, but in general they should be put side by side. To me, a good design has to base its functionalities around aesthetics, and the chosen aesthetics must revolve around its predetermined functionalities. Now back to fourth, the XY-6014 buck actually has a wifi module that could communicate with the base circuit through Serial using Modbus RTU. I did not, however, get the wifi version, so I have the Serial port hanging there for free doing nothing. And if it's there and I paid for it, it would be a sin not to utilize the product to its fullest.
</div>

##
### WS2812B with STM32 Timer and DMA
<div align="justify">
Why didn't I just use already existing libraries for driving these LEDs, such as FastLED or something like that? Well 3 reasons: Number 1, I don't know how to port those to the STM32 platform, number 2, those libraries don't have the functions and effects that I need, and number 3, those libraries have the functions and effects that I do not need. So I thought I would write my own program, with my own effects and functions.
</div>

######
<div align="justify">
I will not go into details on how to actually setup and configure STM32 peripherals and DMA to write data to the LEDs here since there have been countless tutorials online. I will, however, leave a link here to another repository of mine that is dedicated to solely driving WS2812B LEDs with STM32 Timer and DMA. If the link is not available, come back later, I didn't have the time to write a complete README yet.
</div>

######
Regarding ModbusRTU, it's the same. It is actually quite easy in terms of programming, since making a ModbusRTU client to send and read data on holding registers is rather simple, compared to writing a program for an RTU server.

######
So basically this is the flowchart for my STM32 ModbusRTU client + LEDs driver:
<div align="center"><img src="_assets/flowchart.png" alt="Flowchart" width="450"/></div>

######
The STM32 client requests data from the XY-6014 server every 2 seconds by calling:
```cpp
modbusClient.request(XY_6014_SERVER_ADDRESS, MODBUS_RTU_READ_HOLDING_REGISTERS, START_ADDRESS, DATA_BYTES_COUNT);
```
Then by switching the received values for Voltage and Current, the colors for the LEDs are decided. This scheme is arbitrary, but I'm choosing: Blue for 0-5V 0-1A, Cyan for 5-10V 1-3A, Green for 10-15V 3-5A, Yellow for 15-20V 5-7A, Orange for 20-25V 7-10A, Red for 25-30V 10A-12A, Purple for 30V+ 12A+.
```cpp
led.gradient2Colors(voltColor, startLED, ampColor, endLED);
led.transition(HAL_GetTick(), TRANSITION_DURATION_MS);
```
And the result:
(To be updated)