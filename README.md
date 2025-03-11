This is a serial path tracer that I made following the book series by Peter Shirley and the gang, it has some images that  the raytracer generated in there if you wanna see some orbs.

If you clone the repo you can find the main file and at the bottom decide which scene to render using the switch statement.

the go into the root directory and run 

`cmake -B build`

and next

`cmake --build build`

This will generate `/build/Debug/Raytracer.exe`

So in terminal we can execute the program `RayTracer.exe > image.ppm` where ppm is a file format - if you don't have anything to display the format you can google one online.

NOTE: the current way that it raytraces the images isn't that good because it's inbetween builds - I'm going to work on some of the more advanced features in the future but we are using some weird monte carlo approximations at the moment.
