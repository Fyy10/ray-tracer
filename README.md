# ray-tracer

- [ray-tracer](#ray-tracer)
  - [Output an Image](#output-an-image)
    - [The PPM Image Format](#the-ppm-image-format)
    - [Generate a Sample Image](#generate-a-sample-image)
    - [Convert to Other Formats](#convert-to-other-formats)

A vanilla ray tracer implemented in C/C++.

Reference: [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Output an Image

### The PPM Image Format

From [wikipedia](https://en.wikipedia.org/wiki/Netpbm#PPM_example):

```plain
P3
# "P3" means this is a RGB color image in ASCII
# "3 2" is the width and height of the image in pixels
# "255" is the maximum value for each color
# This, up through the "255" line below are the header.
# Everything after that is the image data: RGB triplets.
# In order: red, green, blue, yellow, white, and black.
3 2
255
255   0   0
  0 255   0
  0   0 255
255 255   0
255 255 255
  0   0   0
```

### Generate a Sample Image

```bash
g++ ppm_example.cpp -o ppm_example
./ppm_example > sample.ppm
```

The generated image (converted to PNG):

![ppm_example](img/ppm_example.png)

### Convert to Other Formats

Use `ffmpeg`:

```bash
ffmpeg -i input.ppm output.png
```

Or, use `ImageMagick`:

```bash
convert input.ppm output.png
```
