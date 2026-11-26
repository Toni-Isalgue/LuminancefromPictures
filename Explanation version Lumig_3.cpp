Explanation of uses of the program (c++ script) Lumi
Introduction
Program Lumi - after fjnn -  from program fotoj3 based on judi based on old programs Judit, and Jcolor2 (see PhD Judit Lopez-Besora)
weights parts of bmp picture and finds average partial luminance and deviations, Toni Isalgue and Judit Lopez-Besora, 2025-26
This is a "research" application. The results depend on appropriate calibration (with a luminance-meter). Also, might depend on kind of digital camera. Actual values were appropriate for a CANON EOS 550 camera saving pictures as .jpg files (using s-RGB colour space).
Previous:  modification /08/2016 produce grayscale with luminances. modification /01/2018 to introduce 3 pictures as HDR (high-definition range)
suggerence 5-9 steps in grey picture for luminances     modification: Feb 2018 scales of grey modified
March 2018: give info for colours, all and parts of picture
October 2024 simplified October 2024, 3 rectangles, and write down averages for the rectangles (R G B, L) and standard deviations. Final plot of Luminances improved
February 2026 Include “Brightness of picture” as possible entry for exposition EV, computation of x y z from CIE 1931 colour system.
November 2026 Includes computation of spatial contrast, according to Building and Environment 81 (2014) 320-333, for the global picture and for the 3 rectangles (maximum spatial contrast, 1, corresponds to a “chess board” pixel to pixel). Computed for b/w figure and for each r, g, b colours.
November 2026 Includes also the number of pixels in each luminance interval from the bands of luminance at the foot of the picture in resul.bmp.
The Lumi version including the 2026 addenda is called “Lumig_3.cpp” in the repository.
(The software does not need windows to execute, but the c code is compiled in windows in the actual directory. You could try directly to compile under other OS taking into account the needed #include in your c-compiler)

THIS IS A RESEARCH-DEMONSTRATION PROGRAM. Its reliability depends on the input data reliability and accuracy of calibration of pictures. The authors are not responsible for the results or its use (should be done only by knowledgeable users). The purpose is to give an easy application for teaching and first indications of luminance values in daily life.  
To run the application, the user should compile with a suitable c++ compiler if not dealing with Windows 10 or 11. It has been tested under Windows 10 and Windows 11, with Dev-C++ compiler ver. 6.3. With minor changes (address position of include files) should run under Linux Ubuntu.


Luminance of digital pictures. Uses digital pictures and numerical input data.
Needs pictures in non-compressed, s-rgb coded, bmp format .bmp as input, as well as an ascii file with codes:
Picture files:  dib1.bmp Where ASA/ISO, Exposition, Aperture are given
                        dib2.bmp Less exposition, recommended -2 stops
                        dib3.bmp More exposition, recommended +2 stops
Remember: The 3 bmp pictures need to be: Well-aligned, non-compressed, s-rgb colours, and of the same width, height.


Numerical file (in ascii) input.dat Contents:

Line1:   C1, integer, 0 normal processing reads ISO/ASA, Aperture Exposition
Line2:   C2, integer, stops between pictures ('bracketing')
	NOTE: if C2=0, will ask for the stops between pictures from the console
Line3:   C3, integer, number of luminance bands (recommended 5-7)
Line5:   C5c float, value of gamma compression  (if 0, takes 2.2 as default)
Line6:   if C1=0, ISO/ASA  of picture dib1.bmp (example: 200. Output will be 200)
Line7:   if C1=0, Aperture of picture dib1.bmp (ex: if f/11, give: 11. Output will be 11)
The script will compute the exposition value ev from the above, and print it on the screen. Here it asks for the ev value to be used, if 0 is entered, takes the previous computed ev value. If other value has to be used (calibration of the camera, for instance, giving “brilliance” and not the above parameters), it can be entered here
Line8:   if C1=0, Exposition     of   dib1.bmp (ex: if 1/320 s, give: 320. The output will be in s)
Line9:   C9 integer ask for RGB values of C9 points (xl[], yl[]). 0 if not
Lines10-11*: xl[], yl[] C9 times 2 numbers (2*C9 files) (*if C9=0, omit) if C9>0 Attention bmp starts left down corner
3 times:
Lin12-13: xini, xefe: x start, x end, x define rectangle to find averages
Lin14-15: yini, yefe, y start, x end, y define rectangle to find averages
          Attention: coordinates from down, left picture

Line24:   Value Normalize cd/m2 Luminance graph (to the right last division)
Line25:  Calib, multiplicative calibration factor for Luminance (default=1)
Line26:   0, normal computation (reserved)

	NOTES: If aperture, exposure time, and ISO/ASA are given, the program will compute and list the obtained value of (light exposure) EV and ask for the value to be used. In the case that the camera gives the values in the .jpg file header (EXIF version), give the same number. The value of the further "Calib" parameter is redundant with the introduced EV parameter, so please use it carefully (assign 1 if no more data available, or calibrate with a well-measured luminance surface on the picture). In the case that the picture does not contain ISO, Aperture and Exposure time, but give “Brightness”, the user should better calibrate the EV to be used by having one picture where actual luminance (in cd/m2) of some (surface) point(s) have been measured (an approximate relation, such as EV= 0.7911*Brightness + 6.4611 might hold, for 2<Brightness <9).
Gamma gives the “compression” of data, so if your camera device does not indicate the value, you can adjust by trying values (usually from 1-no compression to 2.4-high compression) until the ratio of the luminance at two different (surface) points, measured with a luminance-meter, are the same from the ratio of the treated picture(s), as from the measured values (not luminance values (which depend on absolute, proportional calibration), but ratios should be as near as possible, adjusting gamma).
Aperture, exposure time and ISO/ASA give the value of EV for a picture (equivalent to the quantity of light). If some of these values are not given by your camera system, you could assign fixed entrances to the software and adjust the “Calib” value as a multiplying factor to achieve the actual value of luminance at some points, after adjusting the gamma. 


Results of the script:
Res.bmp:  bitmap file
picture in grey scale, with bars with the luminance intervals in the lower part (numerical values in the numerical file)
The output res.bmp will have the same file headings as the central picture dib1.bmp



Lumi.dat: ascii file output with numerical results (including starting parameters):

          Average and standard deviations in the full picture, luminance, RGB values and x y z CIE 1931 colour coordinates. Spatial contrast parameters of the whole picture.

          Average and standard deviations in the defined rectangles, RGB values and standard deviations, x y z CIE 1931 colour coordinates
Spatial contrast parameters for each of the three rectangles indicated.

Luminance values corresponding to each bar on the lower part of the output picture, and number of pixels corresponding to each bar
First bar values from 0 and first value in luminance (cd/m2),
second bar values from first and second, and successively

Values of luminance points indicated (average +/- 1 pixel, total 9) for the 3 pictures and for the central picture only, RGB and x y z CIE 1931 colour coordinates

