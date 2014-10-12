/*******************************************************************************

 Bare Conductive Compiler Error Handler
 --------------------------------------
 
 Compiler_Errors.h - avoids incorrect builds due to wrong environment
 
 Bare Conductive code written by Stefan Dzisiewski-Smith and Peter Krige.
 
 This work is licensed under a Creative Commons Attribution-ShareAlike 3.0 
 Unported License (CC BY-SA 3.0) http://creativecommons.org/licenses/by-sa/3.0/
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.

*******************************************************************************/

#ifndef COMPILER_ERRORS_H
#define COMPILER_ERRORS_H

	// our automatic SFEMP3Shield library pin mapping only works with
	// Arduino >= 1.5.6
	#if ARDUINO < 156 
	  #error Please upgrade your Arduino IDE to 1.5.6 or greater
	#else 
		// for SFEMP3Shield pin mapping to work correctly Bare Conductive Touch Board
		// must be selected in Tools -> Board
		#ifndef ARDUINO_AVR_BARETOUCH
		 	#error Please select "Bare Conductive Touch Board" in the Tools -> Board menu.
		#endif
 	#endif

#endif // COMPILER_ERRORS_H