# ADJUSTABLE DC POWER SUPPLY UNIT

*My special thanks to my friend, my colleague, Trần Ngọc Duy (Lý Hoàng Duy), withou whose support I couldn't have managed this project. I would also like to express my gratitude towards my colleague, my master, [Mr. Nghĩa](https://github.com/nghiank97) at Apicoo Robotics for his unparallel knowledge of various communication systems. Thank you all for your contribution and dedication.*

***IN PROGRESS***

#
## ABOUT

<div align="justify">
As an electronics and prototyping hobbyist, the need for a power supply unit of a wide range of voltages and amperes yields that either I purchased a pre-built DC power supply, or hook up some buck-boost circuitries to a fixed one. Through market research and online shopping malls surveys, I came to the realization that pre-built DC PSUs are either too expensive or have very limited range of output. Hooking up a buck-boost converter to a fixed voltage PSU is a primitive idea yet surprisingly efficient in terms of price/performance. However, the hassle of having to get finicky with a screw driver and multimeter when manually adjusting the converter is loosely a deal breaker for this idea.

######
So I headed out to one of my friends, Trần Ngọc Duy, and was suggested a buck converter with adjusting knobs and LCD screen that could display current and set parameters. The buck converter <b><i>XY-6014</i></b> was designed for CNC machinery applications, but could be fitted to serve virtually any systems. And that was what I went for.
######
Then came the part of designing the a case that provides housing for the components. The PSU is made up of a 36V DC unit, the buck converter mentioned above, an AC power inlet, a microcontroller that can read serial data from the buck converter, and write certain effects to an LED strip that I mounted underneath the PSU, mainly for aesthetic purposes.
</div>

<div align="center"><img src="_assets/PSU_1.jfif" alt="Darstellar PSU" width="1000"/></div>