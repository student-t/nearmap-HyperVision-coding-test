This is my solution for a software engineering position at NearMap. NearMap is an Australian company that provides customerized satellite imagery for enterprises. The solution is efficient and complete.

The parent site is at:
https://github.com/russellar/nearmap-HyperVision-coding-test.

----------------------------------------------------------------------------------------------------


# nearmap.com HyperVision C++ Technical Test

## Constraints

* Must be written in C++
* Recommended to build and run on Ubnutu Linux (10.04 or above).  Windows also accepted (but not preferred).
* Recommended to use the Qt SDK (http://qt.nokia.com/downloads/).  Stub project provided.  Boost also accepted (by not preferred).

## Task

* Create a command line tool that can calculate a red, green and blue histogram for an image and write to an output file in the format described below.  *It should be optimized for performance (e.g. multi-threaded).*
* Create a unit test to validate the results.  
To simplify the build process it is sufficient to include the test case in the command line tool.

## Output format

An ascii text file containing one line for each colour band in the image (in the order red, green, blue).  Each line is a comma separated list of the pixel count for each value (256 per line).

## Submission instructions

* A zip file containing the following - submitted to your agent or nearmap contact.
  * Full source code and project files required to build.  It should compile with no errors or warnings.
  * The output histogram file for the provided sample image.
  * DO NOT include any build intermediate files in the zip file.
  * DO NOT include the provided sample image in the zip file.


* DO NOT send pull requests against this repository for two reasons:
  * We don't want executables checked into source control
  * We don't want other candidates to see your solution.
