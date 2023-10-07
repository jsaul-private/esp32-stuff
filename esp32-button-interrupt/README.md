Motivation
==========

A simple push button generates interrupts when pressed or released.

This turned out to be more challenging than expected, due to
so-called bouncing of push buttongs during press or release.  The
transition from on to off or vice versa is not a sharp step function
but a transition during which there are very short spikes that can
trigger unwanted interrupts and that need to be dealt with. The
issue is not specific to ESP32 and there is a good explanation given
in the Arduino documentation [1].

In addition, there have been few cases of electrical noise on the
pin connected to the push button, causing interrupts without button
activity.

There are several examples in the web of how to deal with the issue,
but I needed a solution that works with interrupts. This is why I
had do come up with the code presented here as simple example.


[1] https://docs.arduino.cc/built-in-examples/digital/Debounce
